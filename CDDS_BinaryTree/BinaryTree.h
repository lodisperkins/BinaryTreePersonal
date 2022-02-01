#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
#include "TreeNode.h"

template<typename T>
class BinaryTree
{
public:

	BinaryTree() {};
	~BinaryTree();

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>* node, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	return m_root == nullptr;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	if (isEmpty())
	{
		m_root = new TreeNode<T>(value);
		return;
	}

	TreeNode<T>* lead = m_root;
	TreeNode<T>* trail = m_root;

	while (lead)
	{
		if (value < lead->getData())
		{
			trail = lead;
			lead = lead->getLeft();
		}
		else
		{
			trail = lead;
			lead = lead->getRight();
		}
	}

	if (value < trail->getData())
		trail->setLeft(new TreeNode<T>(value));
	else
		trail->setRight(new TreeNode<T>(value));
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	//Initialize node pointers
	TreeNode<T>* removeNode = nullptr;
	TreeNode<T>* nodeParent = nullptr;

	//Find the node we want to delete in the list and its parent
	if (!findNode(value, removeNode, nodeParent))
		return;

	//Initialize two iterators to find the data that will be copied and the node's parent
	TreeNode<T>* iter1 = removeNode;
	TreeNode<T>* iter2 = removeNode;

	///If the node has a right child, find the node with the smallest value to the right of the node we want to remove
	if (removeNode->hasRight())
	{
		//Sets the first iterator to the right of the node
		iter1 = removeNode->getRight();

		//Moves the first iterator to the left until it finds the smallest value
		while (iter1->hasLeft())
		{
			iter2 = iter1;
			iter1 = iter1->getLeft();
		}

		//Once the smallest value has been found, copy the value to the node we want to remove
		removeNode->setData(iter1->getData());

		//Connect any children the smallest node may have to the parent of the smallest node.
		if (iter2->hasLeft())
		{
			if (iter2->getLeft()->getData() == removeNode->getData())
			{
				iter2->setLeft(iter1->getRight());
			}
		}
		if (iter2->hasRight())
		{
			if (iter2->getRight()->getData() == removeNode->getData())
			{
				iter2->setRight(iter1->getRight());
			}
		}

		//Delete the node holding the smallest value
		delete iter1;
	}
	else
	{
		//Connect any children the node that needs to be removed may have to its parent.
		if (nodeParent->hasLeft())
		{
			if (nodeParent->getLeft()->getData() == removeNode->getData())
			{
				nodeParent->setLeft(removeNode->getLeft());
			}
		}
		if (nodeParent->hasRight())
		{
			if (nodeParent->getRight()->getData() == removeNode->getData())
			{
				nodeParent->setRight(removeNode->getLeft());
			}
		}
		//If the node we want to remove is the root, set the root to be its left child.
		if (m_root->getData() == removeNode->getData())
		{
			m_root = removeNode->getLeft();
		}
		//Delete the node we want to remove
		delete removeNode;
	}
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	TreeNode<T>* iter = m_root;
	if (!m_root) return nullptr;

	while (iter)
	{
		if (iter->getData() == value)
			return iter;

		if (value < iter->getData())
			iter = iter->getLeft();
		else
			iter = iter->getRight();
	}

	return nullptr;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T value, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	TreeNode<T>* lead = m_root;
	TreeNode<T>* trail = m_root;
	if (!m_root) return false;

	bool locatedNode = false;

	while (lead->hasLeft() || lead->hasRight())
	{
		if (lead->getData() == value)
		{
			locatedNode = true;
			break;
		}

		if (value < lead->getData())
		{
			trail = lead;
			lead = lead->getLeft();
		}
		else
		{
			trail = lead;
			lead = lead->getRight();
		}
	}

	nodeFound = lead;
	nodeParent = trail;

	return locatedNode;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//Decrease the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}
