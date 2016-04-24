﻿//   RTree.java
//   Java Spatial Index Library
//   Copyright (C) 2002 Infomatiq Limited
//   Copyright (C) 2008 Aled Morris aled@sourceforge.net
//  
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

//  Ported to C# By Dror Gluska, April 9th, 2009
//  Ported to C++ By Dmitry Tsvetkov, April 21th, 2016
#pragma once
//#include <string>
#include "Node.h"
#include "Rectangle.h"
#include <map>
#include <intsafe.h>
#include <stack>
#include <list>
#include <debugapi.h>
#include <unordered_map>

namespace RTreeLib
{

	/// <summary>
	/// This is a lightweight RTree implementation, specifically designed 
	/// for the following features (in order of importance): 
	///
	/// Fast intersection query performance. To achieve this, the RTree 
	/// uses only main memory to store entries. Obviously this will only improve
	/// performance if there is enough physical memory to avoid paging.
	/// Low memory requirements.
	/// Fast add performance.
	///
	///
	/// The main reason for the high speed of this RTree implementation is the 
	/// avoidance of the creation of unnecessary objects, mainly achieved by using
	/// primitive collections from the trove4j library.
	/// author aled@sourceforge.net
	/// version 1.0b2p1
	/// Ported to C# By Dror Gluska, April 9th, 2009
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class RTree
	{
	private:
		const std::string version = "1.0b2p1";

		// parameters of the tree
		const int DEFAULT_MAX_NODE_ENTRIES = 10;
		int maxNodeEntries;
		int minNodeEntries;

		// map of nodeId -&gt; Node object
		// [x] TODO eliminate this map - it should not be needed. Nodes
		// can be found by traversing the tree.
		//private TIntObjectHashMap nodeMap = new TIntObjectHashMap();
		//std::map<int, Node> nodeMap;
		std::unordered_map<int, Node> nodeMap;

		// internal consistency checking - set to true if debugging tree corruption
		const bool INTERNAL_CONSISTENCY_CHECKING = false;

		// used to mark the status of entries during a Node split
		const int ENTRY_STATUS_ASSIGNED = 0;
		const int ENTRY_STATUS_UNASSIGNED = 1;
		std::vector<BYTE> entryStatus;
		std::vector<BYTE> initialEntryStatus;

		// stacks used to store nodeId and entry index of each Node
		// from the root down to the leaf. Enables fast lookup
		// of nodes when a split is propagated up the tree.
		//private TIntStack parents = new TIntStack();
		std::deque<int> parents;
		//private TIntStack parentsEntry = new TIntStack();
		std::deque<int> parentsEntry;

		// initialisation
		int treeHeight; // leaves are always level 1
		int rootNodeId;// = 0;
		int msize;// = 0;

		// Enables creation of new nodes
		//private int highestUsedNodeId = rootNodeId; 
		int highestUsedNodeId;// = 0;

		// Deleted Node objects are retained in the nodeMap, 
		// so that they can be reused. Store the IDs of nodes
		// which can be reused.
		//private TIntStack deletedNodeIds = new TIntStack();
		std::deque<int> deletedNodeIds;

		// std::list of nearest rectangles. Use a member variable to
		// avoid recreating the object each time nearest() is called.
		//private TIntArraystd::list nearestIds = new TIntArraystd::list();
		std::list<int> nearestIds;

		//Added dictionaries to support generic objects..
		//possibility to change the code to support objects without dictionaries.
		std::unordered_map<int, T> IdsToItems;
		std::unordered_map<T, int> ItemsToIds;
		volatile int idcounter;// = INT_MIN;

		//the recursion methods require a [&] to retrieve data
		typedef void (*FN)(int nId);
	public:
		/// <summary>
		/// Initialize implementation dependent properties of the RTree.
		/// </summary>
		RTree() : treeHeight(1), rootNodeId(0), msize(0), highestUsedNodeId(0), idcounter(INT_MIN), maxNodeEntries(0), minNodeEntries(0)
		{
			init();
		}

		/// <summary>
		/// Initialize implementation dependent properties of the RTree.
		/// </summary>
		/// <param name="MaxNodeEntries">his specifies the maximum number of entries
		///in a node. The default value is 10, which is used if the property is
		///not specified, or is less than 2.</param>
		/// <param name="MinNodeEntries">This specifies the minimum number of entries
		///in a node. The default value is half of the MaxNodeEntries value (rounded
		///down), which is used if the property is not specified or is less than 1.
		///</param>
		RTree(int MaxNodeEntries, int MinNodeEntries) : RTree()
		{
			minNodeEntries = MinNodeEntries;
			maxNodeEntries = MaxNodeEntries;
			init();
		}
	private:
		void init()
		{
			//initialize logs
			//log = LogManager.GetLogger(typeof(RTree<T>).FullName);
			//deleteLog = LogManager.GetLogger(typeof(RTree<T>).FullName + "-delete");

			// Obviously a Node with less than 2 entries cannot be split.
			// The Node splitting algorithm will work with only 2 entries
			// per node, but will be inefficient.
			if (maxNodeEntries < 2)
			{
				//log.Warn("Invalid MaxNodeEntries = " + maxNodeEntries + " Resetting to default value of " + DEFAULT_MAX_NODE_ENTRIES);
				maxNodeEntries = DEFAULT_MAX_NODE_ENTRIES;
			}

			// The MinNodeEntries must be less than or equal to (int) (MaxNodeEntries / 2)
			if (minNodeEntries < 1 || minNodeEntries > maxNodeEntries / 2)
			{
				//log.Warn("MinNodeEntries must be between 1 and MaxNodeEntries / 2");
				minNodeEntries = maxNodeEntries / 2;
			}

			entryStatus.resize(maxNodeEntries);
			initialEntryStatus.resize(maxNodeEntries);

			for (int i = 0; i < maxNodeEntries; i++)
			{
				initialEntryStatus[i] = ENTRY_STATUS_UNASSIGNED;
			}

			Node root = Node(rootNodeId, 1, maxNodeEntries);
			nodeMap.insert(std::make_pair(rootNodeId, root));

			//log.Info("init() " + " MaxNodeEntries = " + maxNodeEntries + ", MinNodeEntries = " + minNodeEntries);
		}


		void add(Rectangle r, int id)
		{
			//if (log.IsDebugEnabled)
			//{
			//	log.Debug("Adding rectangle " + r + ", id " + id);
			//}

			add(r.copy(), id, 1);

			msize++;
		}

		/// <summary>
		/// Adds a new entry at a specified level in the tree
		/// </summary>
		/// <param name="r"></param>
		/// <param name="id"></param>
		/// <param name="level"></param>
		void add(Rectangle r, int id, int level)
		{
			// I1 [Find position for new record] Invoke ChooseLeaf to select a 
			// leaf Node L in which to place r
			Node& n = chooseNode(r, level);
			Node* newLeaf=nullptr;

			// I2 [Add record to leaf node] If L has room for another entry, 
			// install E. Otherwise invoke SplitNode to obtain L and LL containing
			// E and all the old entries of L
			if (n.entryCount < maxNodeEntries)
			{
				n.addEntryNoCopy(r, id);
			}
			else
			{
				newLeaf = splitNode(n, r, id);
			}

			// I3 [Propagate changes upwards] Invoke AdjustTree on L, also passing LL
			// if a split was performed
			Node* newNode = adjustTree(&n, newLeaf);

			// I4 [Grow tree taller] If Node split propagation caused the root to 
			// split, create a new root whose children are the two resulting nodes.
			if (newNode != nullptr)
			{
				int oldRootNodeId = rootNodeId;
				Node oldRoot = getNode(oldRootNodeId);

				rootNodeId = getNextNodeId();
				treeHeight++;
				Node root(rootNodeId, treeHeight, maxNodeEntries);
				root.addEntry(newNode->mbr, newNode->nodeId);
				root.addEntry(oldRoot.mbr, oldRoot.nodeId);
				nodeMap.insert(std::make_pair(rootNodeId, root));
			}

			if (INTERNAL_CONSISTENCY_CHECKING)
			{
				checkConsistency(rootNodeId, treeHeight, NullRect);
			}
		}
		bool _delete(Rectangle r, int id)
		{
			// FindLeaf algorithm inlined here. Note the "official" algorithm 
			// searches all overlapping entries. This seems inefficient to me, 
			// as an entry is only worth searching if it contains (NOT overlaps)
			// the rectangle we are searching for.
			//
			// Also the algorithm has been changed so that it is not recursive.

			// FL1 [Search subtrees] If root is not a leaf, check each entry 
			// to determine if it contains r. For each entry found, invoke
			// findLeaf on the Node pointed to by the entry, until r is found or
			// all entries have been checked.
			parents.clear();
			parents.push_front(rootNodeId);

			parentsEntry.clear();
			parentsEntry.push_front(-1);
			Node n;
			int foundIndex = -1;  // index of entry to be deleted in leaf

			while (foundIndex == -1 && parents.size() > 0)
			{
				n = getNode(parents.front());
				int startIndex = parentsEntry.front() + 1;

				if (!n.isLeaf())
				{
					//deleteLog.Debug("searching Node " + n.nodeId + ", from index " + startIndex);
					bool contains = false;
					for (int i = startIndex; i < n.entryCount; i++)
					{
						if (n.entries[i].contains(r))
						{
							parents.push_front(n.ids[i]);
							parentsEntry.pop_front();
							parentsEntry.push_front(i); // this becomes the start index when the child has been searched
							parentsEntry.push_front(-1);
							contains = true;
							break; // ie go to next iteration of while()
						}
					}
					if (contains)
					{
						continue;
					}
				}
				else
				{
					foundIndex = n.findEntry(r, id);
				}

				parents.pop_front();
				parentsEntry.pop_front();
			} // while not found

			if (foundIndex != -1)
			{
				n.deleteEntry(foundIndex, minNodeEntries);
				condenseTree(n);
				msize--;
			}

			// shrink the tree if possible (i.e. if root Node&lt;T%gt; has exactly one entry,and that 
			// entry is not a leaf node, delete the root (it's entry becomes the new root)
			Node root = getNode(rootNodeId);
			while (root.entryCount == 1 && treeHeight > 1)
			{
				root.entryCount = 0;
				rootNodeId = root.ids[0];
				treeHeight--;
				root = getNode(rootNodeId);
			}

			return foundIndex != -1;
		}
		void nearest(Point p, FN v, float furthestDistance)
		{
			Node rootNode = getNode(rootNodeId);

			nearest(p, rootNode, furthestDistance);

			for(int id : nearestIds)
				v(id);
			nearestIds.clear();
		}
		template <class V>
		void intersects(Rectangle r, V v)
		{
			Node rootNode = getNode(rootNodeId);
			intersects(r, v, rootNode);
		}
		void contains(Rectangle r, FN v)
		{
			// find all rectangles in the tree that are contained by the passed rectangle
			// written to be non-recursive (should model other searches on this?)

			parents.clear();
			parents.push_front(rootNodeId);

			parentsEntry.clear();
			parentsEntry.push_front(-1);

			// TODO: possible shortcut here - could test for intersection with the 
			// MBR of the root node. If no intersection, return immediately.

			while (parents.size() > 0)
			{
				Node n = getNode(parents.front());
				int startIndex = parentsEntry.front() + 1;

				if (!n.isLeaf())
				{
					// go through every entry in the index Node to check
					// if it intersects the passed rectangle. If so, it 
					// could contain entries that are contained.
					bool intersects = false;
					for (int i = startIndex; i < n.entryCount; i++)
					{
						if (r.intersects(n.entries[i]))
						{
							parents.push_front(n.ids[i]);
							parentsEntry.pop_front();
							parentsEntry.push_front(i); // this becomes the start index when the child has been searched
							parentsEntry.push_front(-1);
							intersects = true;
							break; // ie go to next iteration of while()
						}
					}
					if (intersects)
					{
						continue;
					}
				}
				else
				{
					// go through every entry in the leaf to check if 
					// it is contained by the passed rectangle
					for (int i = 0; i < n.entryCount; i++)
					{
						if (r.contains(n.entries[i]))
						{
							v(n.ids[i]);
						}
					}
				}
				parents.pop_front();
				parentsEntry.pop_front();
			}
		}
	public:
		/// <summary>
		/// Adds an item to the spatial index
		/// </summary>
		/// <param name="r"></param>
		/// <param name="item"></param>
		void Add(Rectangle r, T item)
		{
			idcounter++;
			int id = idcounter;

			IdsToItems.insert(std::make_pair(id, item));
			ItemsToIds.insert(std::make_pair(item, id));

			add(r, id);
		}

		void Swap(T item1, T item2)
		{
			int id1 = ItemsToIds[item1];
			int id2 = ItemsToIds[item2];
			ItemsToIds[item1] = id2;
			ItemsToIds[item2] = id1;
			IdsToItems[id1] = item2;
			IdsToItems[id2] = item1;
		}
		/// <summary>
		/// Deletes an item from the spatial index
		/// </summary>
		/// <param name="r"></param>
		/// <param name="item"></param>
		/// <returns></returns>
		bool Delete(Rectangle r, T item)
		{
			int id = ItemsToIds[item];

			bool success = _delete(r, id);
			if (success == true)
			{
				IdsToItems.erase(id);
				ItemsToIds.erase(item);
			}
			return success;
		}


		/// <summary>
		/// Retrieve nearest items to a point in radius furthestDistance
		/// </summary>
		/// <param name="p">Point of origin</param>
		/// <param name="furthestDistance">maximum distance</param>
		/// <returns>std::list of items</returns>
		std::list<T> Nearest(Point p, float furthestDistance)
		{
			std::list<T> retval;
			nearest(p, [&](int id)
			{
				retval.Add(IdsToItems[id]);
			}, furthestDistance);
			return retval;
		}



		/// <summary>
		/// Retrieve items which intersect with Rectangle r
		/// </summary>
		/// <param name="r"></param>
		/// <returns></returns>
		std::list<T> Intersects(Rectangle r)
		{
			std::list<T> retval;
			intersects(r, [&](int id)
			{
				retval.push_back(IdsToItems[id]);
			});
			return retval;
		}



		/// <summary>
		/// find all rectangles in the tree that are contained by the passed rectangle
		/// written to be non-recursive (should model other searches on this?)</summary>
		/// <param name="r"></param>
		/// <returns></returns>
		std::list<T> Contains(Rectangle r)
		{
			std::list<T> retval;
			contains(r, [&](int id)
			{
				retval.Add(IdsToItems[id]);
			});

			return retval;
		}


		/**
		* @see com.infomatiq.jsi.SpatialIndex#getBounds()
		*/
		Rectangle getBounds()
		{
			Rectangle bounds;

			Node& n = getNode(getRootNodeId());
			//if (n != null && n.getMBR() != null)
			{
				bounds = n.getMBR().copy();
			}
			return bounds;
		}

		/**
		* @see com.infomatiq.jsi.SpatialIndex#getVersion()
		*/
		std::string getVersion() const
		{
			return std::string("RTree-") + version;
		}
		//-------------------------------------------------------------------------
		// end of SpatialIndex methods
		//-------------------------------------------------------------------------
private:
		/**
		* Get the next available Node ID. Reuse deleted Node IDs if
		* possible
		*/
		int getNextNodeId()
		{
			int nextNodeId;
			if (deletedNodeIds.size() > 0)
			{
				nextNodeId = deletedNodeIds.front();
				deletedNodeIds.pop_front();
			}
			else
			{
				nextNodeId = 1 + highestUsedNodeId++;
			}
			return nextNodeId;
		}





		/// <summary>
		/// Get a Node object, given the ID of the node.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		Node& getNode(int index)
		{
			return nodeMap[index];
		}
public:
		/// <summary>
		/// Get the highest used Node ID
		/// </summary>
		/// <returns></returns>
		int getHighestUsedNodeId() const
		{
			return highestUsedNodeId;
		}

		/// <summary>
		/// Get the root Node ID
		/// </summary>
		/// <returns></returns>
		int getRootNodeId() const
		{
			return rootNodeId;
		}
private:
		/// <summary>
		/// Split a node. Algorithm is taken pretty much verbatim from
		/// Guttman's original paper.
		/// </summary>
		/// <param name="n"></param>
		/// <param name="newRect"></param>
		/// <param name="newId"></param>
		/// <returns>return new Node object.</returns>
		Node* splitNode(Node & n, Rectangle newRect, int newId)
		{
			// [Pick first entry for each group] Apply algorithm pickSeeds to 
			// choose two entries to be the first elements of the groups. Assign
			// each to a group.

			// debug code
			//float initialArea = 0;
			//if (log.IsDebugEnabled)
			//{
			//	Rectangle _union = n.mbr._union(newRect);
			//	initialArea = _union.area();
			//}

			entryStatus = initialEntryStatus;

			int nodeId = getNextNodeId();
			nodeMap.insert(std::make_pair(nodeId, Node(nodeId, n.level, maxNodeEntries)));
			Node& newNode = nodeMap[nodeId];

			pickSeeds(n, newRect, newId, newNode); // this also sets the entryCount to 1

												   // [Check if done] If all entries have been assigned, stop. If one
												   // group has so few entries that all the rest must be assigned to it in 
												   // order for it to have the minimum number m, assign them and stop. 
			while (n.entryCount + newNode.entryCount < maxNodeEntries + 1)
			{
				if (maxNodeEntries + 1 - newNode.entryCount == minNodeEntries)
				{
					// assign all remaining entries to original node
					for (int i = 0; i < maxNodeEntries; i++)
					{
						if (entryStatus[i] == ENTRY_STATUS_UNASSIGNED)
						{
							entryStatus[i] = ENTRY_STATUS_ASSIGNED;
							n.mbr.add(n.entries[i]);
							++n.entryCount;
						}
					}
					break;
				}
				if (maxNodeEntries + 1 - n.entryCount == minNodeEntries)
				{
					// assign all remaining entries to new node
					for (int i = 0; i < maxNodeEntries; i++)
					{
						if (entryStatus[i] == ENTRY_STATUS_UNASSIGNED)
						{
							entryStatus[i] = ENTRY_STATUS_ASSIGNED;
							newNode.addEntryNoCopy(n.entries[i], n.ids[i]);
							n.entries[i] = NullRect;
						}
					}
					break;
				}

				// [Select entry to assign] Invoke algorithm pickNext to choose the
				// next entry to assign. Add it to the group whose covering rectangle 
				// will have to be enlarged least to accommodate it. Resolve ties
				// by adding the entry to the group with smaller area, then to the 
				// the one with fewer entries, then to either. Repeat from S2
				pickNext(n, newNode);
			}

			n.reorganize(this->maxNodeEntries-1);

			// check that the MBR stored for each Node is correct.
			if (INTERNAL_CONSISTENCY_CHECKING)
			{
				if (!(n.mbr ==calculateMBR(n)))
				{
					DebugBreak();
					//log.Error("Error: splitNode old Node MBR wrong");
				}

				if (!(newNode.mbr == calculateMBR(newNode)))
				{
					DebugBreak();
					//log.Error("Error: splitNode new Node MBR wrong");
				}
			}

			// debug code
			//if (log.IsDebugEnabled)
			//{
			//	float newArea = n.mbr.area() + newNode.mbr.area();
			//	float percentageIncrease = (100 * (newArea - initialArea)) / initialArea;
			//	log.Debug("Node " + n.nodeId + " split. New area increased by " + percentageIncrease + "%");
			//}

			return &newNode;
		}

		/// <summary>
		/// Pick the seeds used to split a node.
		/// Select two entries to be the first elements of the groups
		/// </summary>
		/// <param name="n"></param>
		/// <param name="newRect"></param>
		/// <param name="newId"></param>
		/// <param name="newNode"></param>
		void pickSeeds(Node & n, Rectangle newRect, int newId, Node & newNode)
		{
			// Find extreme rectangles along all dimension. Along each dimension,
			// find the entry whose rectangle has the highest low side, and the one 
			// with the lowest high side. Record the separation.
			float maxNormalizedSeparation = 0;
			int highestLowIndex = 0;
			int lowestHighIndex = 0;

			// for the purposes of picking seeds, take the MBR of the Node to include
			// the new rectangle aswell.
			n.mbr.add(newRect);

			//if (log.IsDebugEnabled)
			//{
			//	log.Debug("pickSeeds(): NodeId = " + n.nodeId + ", newRect = " + newRect);
			//}

			for (int d = 0; d < Rectangle::DIMENSIONS; d++)
			{
				float tempHighestLow = newRect.min[d];
				int tempHighestLowIndex = -1; // -1 indicates the new rectangle is the seed

				float tempLowestHigh = newRect.max[d];
				int tempLowestHighIndex = -1;

				for (int i = 0; i < n.entryCount; i++)
				{
					float tempLow = n.entries[i].min[d];
					if (tempLow >= tempHighestLow)
					{
						tempHighestLow = tempLow;
						tempHighestLowIndex = i;
					}
					else
					{  // ensure that the same index cannot be both lowestHigh and highestLow
						float tempHigh = n.entries[i].max[d];
						if (tempHigh <= tempLowestHigh)
						{
							tempLowestHigh = tempHigh;
							tempLowestHighIndex = i;
						}
					}

					// PS2 [Adjust for shape of the rectangle cluster] Normalize the separations
					// by dividing by the widths of the entire set along the corresponding
					// dimension
					float normalizedSeparation = (tempHighestLow - tempLowestHigh) / (n.mbr.max[d] - n.mbr.min[d]);

					if (normalizedSeparation > 1 || normalizedSeparation < -1)
					{
						//log.Error("Invalid normalized separation");
					}

					//if (log.IsDebugEnabled)
					//{
					//	log.Debug("Entry " + i + ", dimension " + d + ": HighestLow = " + tempHighestLow +
					//		" (index " + tempHighestLowIndex + ")" + ", LowestHigh = " +
					//		tempLowestHigh + " (index " + tempLowestHighIndex + ", NormalizedSeparation = " + normalizedSeparation);
					//}

					// PS3 [Select the most extreme pair] Choose the pair with the greatest
					// normalized separation along any dimension.
					if (normalizedSeparation > maxNormalizedSeparation)
					{
						maxNormalizedSeparation = normalizedSeparation;
						highestLowIndex = tempHighestLowIndex;
						lowestHighIndex = tempLowestHighIndex;
					}
				}
			}

			// highestLowIndex is the seed for the new node.
			if (highestLowIndex == -1)
			{
				newNode.addEntry(newRect, newId);
			}
			else
			{
				newNode.addEntryNoCopy(n.entries[highestLowIndex], n.ids[highestLowIndex]);
				//n.entries[highestLowIndex] = null;

				// move the new rectangle into the space vacated by the seed for the new node
				n.entries[highestLowIndex] = newRect;
				n.ids[highestLowIndex] = newId;
			}

			// lowestHighIndex is the seed for the original node. 
			if (lowestHighIndex == -1)
			{
				lowestHighIndex = highestLowIndex;
			}

			entryStatus[lowestHighIndex] = ENTRY_STATUS_ASSIGNED;
			n.entryCount = 1;
			n.mbr.set(n.entries[lowestHighIndex].min, n.entries[lowestHighIndex].max);
		}




		/// <summary>
		/// Pick the next entry to be assigned to a group during a Node split.
		/// [Determine cost of putting each entry in each group] For each 
		/// entry not yet in a group, calculate the area increase required
		/// in the covering rectangles of each group  
		/// </summary>
		/// <param name="n"></param>
		/// <param name="newNode"></param>
		/// <returns></returns>
		int pickNext(Node & n, Node & newNode)
		{
			float maxDifference = -FLT_MAX;
			int next = 0;
			int nextGroup = 0;

			//maxDifference = -FLT_MAX;

			//if (log.IsDebugEnabled)
			//{
			//	log.Debug("pickNext()");
			//}

			for (int i = 0; i < maxNodeEntries; i++)
			{
				if (entryStatus[i] == ENTRY_STATUS_UNASSIGNED)
				{

					if (n.entries[i] == NullRect)
					{
						DebugBreak();
						//log.Error("Error: Node " + n.nodeId + ", entry " + i + " is null");
					}

					float nIncrease = n.mbr.enlargement(n.entries[i]);
					float newNodeIncrease = newNode.mbr.enlargement(n.entries[i]);
					float difference = fabs(nIncrease - newNodeIncrease);

					if (difference > maxDifference)
					{
						next = i;

						if (nIncrease < newNodeIncrease)
						{
							nextGroup = 0;
						}
						else if (newNodeIncrease < nIncrease)
						{
							nextGroup = 1;
						}
						else if (n.mbr.area() < newNode.mbr.area())
						{
							nextGroup = 0;
						}
						else if (newNode.mbr.area() < n.mbr.area())
						{
							nextGroup = 1;
						}
						else if (newNode.entryCount < maxNodeEntries / 2)
						{
							nextGroup = 0;
						}
						else
						{
							nextGroup = 1;
						}
						maxDifference = difference;
					}
					//if (log.IsDebugEnabled)
					//{
					//	log.Debug("Entry " + i + " group0 increase = " + nIncrease + ", group1 increase = " + newNodeIncrease +
					//		", diff = " + difference + ", MaxDiff = " + maxDifference + " (entry " + next + ")");
					//}
				}
			}

			entryStatus[next] = ENTRY_STATUS_ASSIGNED;

			if (nextGroup == 0)
			{
				n.mbr.add(n.entries[next]);
				++n.entryCount;
			}
			else
			{
				// move to new node.
				newNode.addEntryNoCopy(n.entries[next], n.ids[next]);
				n.entries[next] = NullRect;
			}

			return next;
		}


		/// <summary>
		/// Recursively searches the tree for the nearest entry. Other queries
		/// call execute() on an IntProcedure when a matching entry is found; 
		/// however nearest() must store the entry Ids as it searches the tree,
		/// in case a nearer entry is found.
		/// Uses the member variable nearestIds to store the nearest
		/// entry IDs.
		/// </summary>
		/// <remarks>TODO rewrite this to be non-recursive?</remarks>
		/// <param name="p"></param>
		/// <param name="n"></param>
		/// <param name="nearestDistance"></param>
		/// <returns></returns>
		float nearest(Point p, Node n, float nearestDistance)
		{
			for (int i = 0; i < n.entryCount; i++)
			{
				float tempDistance = n.entries[i].distance(p);
				if (n.isLeaf())
				{ // for leaves, the distance is an actual nearest distance 
					if (tempDistance < nearestDistance)
					{
						nearestDistance = tempDistance;
						nearestIds.clear();
					}
					if (tempDistance <= nearestDistance)
					{
						nearestIds.push_back(n.ids[i]);
					}
				}
				else
				{ // for index nodes, only go into them if they potentially could have
				  // a rectangle nearer than actualNearest
					if (tempDistance <= nearestDistance)
					{
						// search the child node
						nearestDistance = nearest(p, getNode(n.ids[i]), nearestDistance);
					}
				}
			}
			return nearestDistance;
		}


		/// <summary>
		/// Recursively searches the tree for all intersecting entries.
		/// Immediately calls execute() on the passed IntProcedure when 
		/// a matching entry is found.
		/// [x] TODO rewrite this to be non-recursive? Make sure it
		/// doesn't slow it down.
		/// </summary>
		/// <param name="r"></param>
		/// <param name="v"></param>
		/// <param name="n"></param>
		template <class V>
		void intersects(const Rectangle& r, const V& v, const Node& n)
		{
			for (int i = 0; i < n.entryCount; i++)
			{
				if (r.intersects(n.entries[i]))
				{
					if (n.isLeaf())
					{
						v(n.ids[i]);
					}
					else
					{
						Node& childNode = getNode(n.ids[i]);
						intersects(r, v, childNode);
					}
				}
			}
		}

		/**
		* Used by delete(). Ensures that all nodes from the passed node
		* up to the root have the minimum number of entries.
		*
		* Note that the parent and parentEntry stacks are expected to
		* contain the nodeIds of all parents up to the root.
		*/

		void condenseTree(Node & l)
		{
			Rectangle oldRectangle(0, 0, 0, 0, 0, 0);
			// CT1 [Initialize] Set n=l. Set the list of eliminated
			// nodes to be empty.
			Node n = l;
			int parentEntry;

			//TIntStack eliminatedNodeIds = new TIntStack();
			std::deque<int> eliminatedNodeIds;

			// CT2 [Find parent entry] If N is the root, go to CT6. Otherwise 
			// let P be the parent of N, and let En be N's entry in P  
			while (n.level != treeHeight)
			{
				Node& parent = getNode(parents.front());
				parents.pop_front();
				parentEntry = parentsEntry.front();
				parentsEntry.pop_front();

				// CT3 [Eliminiate under-full node] If N has too few entries,
				// delete En from P and add N to the list of eliminated nodes
				if (n.entryCount < minNodeEntries)
				{
					parent.deleteEntry(parentEntry, minNodeEntries);
					eliminatedNodeIds.push_front(n.nodeId);
				}
				else
				{
					// CT4 [Adjust covering rectangle] If N has not been eliminated,
					// adjust EnI to tightly contain all entries in N
					if (!(n.mbr ==  parent.entries[parentEntry]))
					{
						oldRectangle.set(parent.entries[parentEntry].min, parent.entries[parentEntry].max);
						parent.entries[parentEntry].set(n.mbr.min, n.mbr.max);
						parent.recalculateMBR(oldRectangle);
					}
				}
				// CT5 [Move up one level in tree] Set N=P and repeat from CT2
				n = parent;
			}

			// CT6 [Reinsert orphaned entries] Reinsert all entries of nodes in set Q.
			// Entries from eliminated leaf nodes are reinserted in tree leaves as in 
			// Insert(), but entries from higher level nodes must be placed higher in 
			// the tree, so that leaves of their dependent subtrees will be on the same
			// level as leaves of the main tree
			while (eliminatedNodeIds.size() > 0)
			{
				Node& e = getNode(eliminatedNodeIds.front());
				eliminatedNodeIds.pop_front();
				for (int j = 0; j < e.entryCount; j++)
				{
					add(e.entries[j], e.ids[j], e.level);
					e.entries[j] = NullRect;
				}
				e.entryCount = 0;
				deletedNodeIds.push_front(e.nodeId);
				nodeMap.erase(e.nodeId);
			}
		}

		/**
		*  Used by add(). Chooses a leaf to add the rectangle to.
		*/
		Node& chooseNode(Rectangle r, int level)
		{
			// CL1 [Initialize] Set N to be the root node
			Node* n = &getNode(rootNodeId);
			parents.clear();
			parentsEntry.clear();

			// CL2 [Leaf check] If N is a leaf, return N
			while (true)
			{
				//if (n == null)
				//{
				//	log.Error("Could not get root Node (" + rootNodeId + ")");
				//}

				if (n->level == level)
				{
					return *n;
				}

				// CL3 [Choose subtree] If N is not at the desired level, let F be the entry in N 
				// whose rectangle FI needs least enlargement to include EI. Resolve
				// ties by choosing the entry with the rectangle of smaller area.
				float leastEnlargement = n->getEntry(0).enlargement(r);
				int index = 0; // index of rectangle in subtree
				for (int i = 1; i < n->entryCount; i++)
				{
					Rectangle tempRectangle = n->getEntry(i);
					float tempEnlargement = tempRectangle.enlargement(r);
					if ((tempEnlargement < leastEnlargement) ||
						((tempEnlargement == leastEnlargement) &&
						(tempRectangle.area() < n->getEntry(index).area())))
					{
						index = i;
						leastEnlargement = tempEnlargement;
					}
				}

				parents.push_front(n->nodeId);
				parentsEntry.push_front(index);

				// CL4 [Descend until a leaf is reached] Set N to be the child Node 
				// pointed to by Fp and repeat from CL2
				n = &getNode(n->ids[index]);
			}
		}

		/**
		* Ascend from a leaf Node L to the root, adjusting covering rectangles and
		* propagating Node splits as necessary.
		*/
		Node* adjustTree(Node* n, Node* nn)
		{
			// AT1 [Initialize] Set N=L. If L was split previously, set NN to be 
			// the resulting second node.

			// AT2 [Check if done] If N is the root, stop
			while (n->level != treeHeight)
			{

				// AT3 [Adjust covering rectangle in parent entry] Let P be the parent 
				// Node of N, and let En be N's entry in P. Adjust EnI so that it tightly
				// encloses all entry rectangles in N.
				Node& parent = getNode(parents.front());
				parents.pop_front();
				int entry = parentsEntry.front();
				parentsEntry.pop_front();

				//if (parent.ids[entry] != n.nodeId)
				//{
				//	log.Error("Error: entry " + entry + " in Node " +
				//		parent.nodeId + " should point to Node " +
				//		n.nodeId + "; actually points to Node " + parent.ids[entry]);
				//}

				if (!(parent.entries[entry] ==n->mbr))
				{
					parent.entries[entry].set(n->mbr.min, n->mbr.max);
					parent.mbr.set(parent.entries[0].min, parent.entries[0].max);
					for (int i = 1; i < parent.entryCount; i++)
					{
						parent.mbr.add(parent.entries[i]);
					}
				}

				// AT4 [Propagate Node split upward] If N has a partner NN resulting from 
				// an earlier split, create a new entry Enn with Ennp pointing to NN and 
				// Enni enclosing all rectangles in NN. Add Enn to P if there is room. 
				// Otherwise, invoke splitNode to produce P and PP containing Enn and
				// all P's old entries.
				Node *newNode = nullptr;
				if (nn != nullptr)
				{
					if (parent.entryCount < maxNodeEntries)
					{
						parent.addEntry(nn->mbr, nn->nodeId);
					}
					else
					{
						newNode = splitNode(parent, nn->mbr.copy(), nn->nodeId);
					}
				}

				// AT5 [Move up to next level] Set N = P and set NN = PP if a split 
				// occurred. Repeat from AT2
				n = &parent;
				nn = newNode;
				//parent = null;
				//newNode = null;
			}

			return nn;
		}

		/**
		* Check the consistency of the tree.
		*/
		void checkConsistency(int nodeId, int expectedLevel, Rectangle expectedMBR)
		{
			// go through the tree, and check that the internal data structures of 
			// the tree are not corrupted.    
			Node& n = getNode(nodeId);

			//if (n == null)
			//{
			//	log.Error("Error: Could not read Node " + nodeId);
			//}

			if (n.level != expectedLevel)
			{
				DebugBreak();
				//log.Error("Error: Node " + nodeId + ", expected level " + expectedLevel + ", actual level " + n.level);
			}

			Rectangle calculatedMBR = calculateMBR(n);

			if (!(n.mbr == calculatedMBR))
			{
				DebugBreak();
				//log.Error("Error: Node " + nodeId + ", calculated MBR does not equal stored MBR");
			}

			if (!(expectedMBR == NullRect) && !(n.mbr ==expectedMBR))
			{
				DebugBreak();
				//log.Error("Error: Node " + nodeId + ", expected MBR (from parent) does not equal stored MBR");
			}

			// Check for corruption where a parent entry is the same object as the child MBR
			if (!(expectedMBR == NullRect) && n.mbr.sameObject(expectedMBR))
			{
				DebugBreak();
				//log.Error("Error: Node " + nodeId + " MBR using same rectangle object as parent's entry");
			}

			for (int i = 0; i < n.entryCount; i++)
			{
				if (n.entries[i] == NullRect)
				{
					DebugBreak();
					//log.Error("Error: Node " + nodeId + ", Entry " + i + " is null");
				}

				if (n.level > 1)
				{ // if not a leaf
					checkConsistency(n.ids[i], n.level - 1, n.entries[i]);
				}
			}
		}

		/**
		* Given a Node object, calculate the Node MBR from it's entries.
		* Used in consistency checking
		*/
		static Rectangle calculateMBR(Node n)
		{
			Rectangle mbr(n.entries[0].min, n.entries[0].max);

			for (int i = 1; i < n.entryCount; i++)
			{
				mbr.add(n.entries[i]);
			}
			return mbr;
		}

		int size() const
		{
			return this.msize;
		}

	};
}
