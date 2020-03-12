//Header File Binary Search Tree

#ifndef H_binarySearchTree
#define H_binarySearchTree
#include <iostream> 
#include <string>
#include "binaryTree.h"
#include "String.h"
#include "myFunctions.h"

using namespace std;

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType>
{
public:
	/*
	Function to represent the tree's elements
	as a String
	*/
	string serialize() const;

	/*
	Function to create an object out of a String's
	"serial number" created in the serialize function
	*/
	void deserialize(string s, bSearchTreeType<elemType>* newTree) const;

	bool search(const elemType& searchItem) const;
	//Function to determine if searchItem is in the binary 
	//search tree.
	//Postcondition: Returns true if searchItem is found in 
	//               the binary search tree; otherwise, 
	//               returns false.

	void insert(const elemType& insertItem);
	//Function to insert insertItem in the binary search tree.
	//Postcondition: If there is no node in the binary search
	//               tree that has the same info as 
	//               insertItem, a node with the info 
	//               insertItem is created and inserted in the
	//               binary search tree.

	void deleteNode(const elemType& deleteItem);
	//Function to delete deleteItem from the binary search tree 
	//Postcondition: If a node with the same info as deleteItem
	//               is found, it is deleted from the binary 
	//               search tree.
	//               If the binary tree is empty or deleteItem
	//               is not in the binary tree, an appropriate
	//               message is printed.

	void swapSubtrees();
	//Function to swap the left and right subtrees of a binary tree
	//Postcondition: all the values greater than root are stored on the left side of the binary tree
	//               & all the values less than root are stored on the right side of the binary tree

private:
	string serialize(nodeType<elemType> *p, String& str ) const;
	//Function to return the serialized string 
	
	void swap(nodeType<elemType> *p);
	//Function to swap the left and right subtrees of a binary tree
	//Postcondition: all the values greater than root are stored on the left side of the binary tree
	//               & all the values less than root are stored on the right side of the binary tree

	void insertBackwards(const elemType& insertItem);
	//Function to create a BST by placing elements that are > than root 
	//on the left side of the BST and by placing elements that are < than root on the right side

	void deleteFromTree(nodeType<elemType>* &p);
	//Function to delete the node to which p points is 
	//deleted from the binary search tree.
	//Postcondition: The node to which p points is deleted
	//               from the binary search tree.
};


//template<class elemType>
// string bSearchTreeType<elemType>::serialize(nodeType<elemType>* p, String& str) const
//{
//	 string temp = "";
//	// string serialNumber = "";
//	if (p != nullptr)				// if not at end of tree
//	{
//		serialize(p->lLink, str);
//
//		/*if (str.getString() == "")
//			temp = ( str.getString() + intToString(p->info) + ", ") ;
//		
//		else */
//			temp = (str.getString() + intToString(p->info) + ", ");
//
//		str.setString(temp);
//
//		serialize(p->rLink, str);
//	}
//
//	return str.getString();
//}

//template<class elemType>
//string bSearchTreeType<elemType>::serialize() const
//{
//	 String str;
//
//	 string temp = "In order: " + noEndingPunctuation(serialize(root, str));
//
//	return temp;
//}

template<class elemType>
void bSearchTreeType<elemType>::deserialize(string s, bSearchTreeType<elemType>* newTree) const
{
	newTree->insert(stringToInt(s));
}

template <class elemType>
bool bSearchTreeType<elemType>::search
(const elemType& searchItem) const
{
	nodeType<elemType> *current;
	bool found = false;

	if (binaryTreeType<elemType>::root == nullptr)
		cout << "Cannot search an empty tree." << endl;
	else
	{
		current = binaryTreeType<elemType>::root;

		while (current != nullptr && !found)
		{
			if (current->info == searchItem)
				found = true;
			else if (current->info > searchItem)
				current = current->lLink;
			else
				current = current->rLink;
		}//end while
	}//end else

	return found;
}//end search

template <class elemType>
void bSearchTreeType<elemType>::insert
(const elemType& insertItem)
{
	nodeType<elemType> *current = nullptr; //pointer to traverse the tree
	nodeType<elemType> *trailCurrent = nullptr; //pointer behind current
	nodeType<elemType> *newNode = nullptr;  //pointer to create the node

	newNode = new nodeType<elemType>;
	newNode->info = insertItem;
	newNode->lLink = nullptr;
	newNode->rLink = nullptr;

	if (binaryTreeType<elemType>::root == nullptr)
		binaryTreeType<elemType>::root = newNode;
	else
	{
		current = binaryTreeType<elemType>::root;

		while (current != nullptr)
		{
			trailCurrent = current;

			if (current->info == insertItem)
			{
				return;
			}
			else if (current->info > insertItem)
				current = current->lLink;
			else
				current = current->rLink;
		}//end while

		if (trailCurrent->info > insertItem)
			trailCurrent->lLink = newNode;
		else
			trailCurrent->rLink = newNode;
	}
}//end insert

template <class elemType>
void bSearchTreeType<elemType>::swap(nodeType<elemType> *p)
{
	if (p != nullptr)
	{
		nodeType<elemType> *temp;
		swap(p->lLink);
		swap(p->rLink);
		temp = p->lLink;
		p->lLink = p->rLink;
		p->rLink = temp;
		
	}
	
}

template <class elemType>
void bSearchTreeType<elemType>::swapSubtrees()
{
	swap(binaryTreeType<elemType>::root);
}


template <class elemType>
void bSearchTreeType<elemType>::deleteNode
(const elemType& deleteItem)
{
	nodeType<elemType> *current; //pointer to traverse the tree
	nodeType<elemType> *trailCurrent; //pointer behind current
	bool found = false;

	if (binaryTreeType<elemType>::root == nullptr)
		cout << "Cannot delete from an empty tree."
		<< endl;
	else
	{
		current = binaryTreeType<elemType>::root;
		trailCurrent = binaryTreeType<elemType>::root;

		while (current != nullptr && !found)
		{
			if (current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;

				if (current->info > deleteItem)
					current = current->lLink;
				else
					current = current->rLink;
			}
		}//end while

		if (current == nullptr)
			cout << "The item to be deleted is not in the tree."
			<< endl;
		else if (found)
		{
			if (current == binaryTreeType<elemType>::root)
				deleteFromTree(binaryTreeType<elemType>::root);
			else if (trailCurrent->info > deleteItem)
				deleteFromTree(trailCurrent->lLink);
			else
				deleteFromTree(trailCurrent->rLink);
		}
		else
			cout << "The item to be deleted is not in the tree."
			<< endl;
	}
} //end deleteNode

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree
(nodeType<elemType>* &p)
{
	nodeType<elemType> *current; //pointer to traverse the tree
	nodeType<elemType> *trailCurrent;  //pointer behind current
	nodeType<elemType> *temp;      //pointer to delete the node

	if (p == nullptr)
		cout << "Error: The node to be deleted does not exist."
		<< endl;
	else if (p->lLink == nullptr && p->rLink == nullptr)
	{
		temp = p;
		p = nullptr;
		delete temp;
	}
	else if (p->lLink == nullptr)
	{
		temp = p;
		p = temp->rLink;
		delete temp;
	}
	else if (p->rLink == nullptr)
	{
		temp = p;
		p = temp->lLink;
		delete temp;
	}
	else
	{
		current = p->lLink;
		trailCurrent = nullptr;

		while (current->rLink != nullptr)
		{
			trailCurrent = current;
			current = current->rLink;
		}//end while

		p->info = current->info;

		if (trailCurrent == nullptr) //current did not move; 
									 //current == p->lLink; adjust p
			p->lLink = current->lLink;
		else
			trailCurrent->rLink = current->lLink;

		delete current;
	}//end else
} //end deleteFromTree

#endif