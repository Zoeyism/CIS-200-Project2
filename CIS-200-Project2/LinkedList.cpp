#pragma once
#include "LinkedList.h"
#include <iostream>

using namespace std;

template <typename GivenType>
int LinkedList<GivenType>::AppendList(const GivenType& new_value)
{
	int comparisons = 2; // Set to 2 for initial comparisons; if at head_ptr, -= 1.
	LinkedNode<GivenType>* temp = head_ptr;
	LinkedNode<GivenType>* newest = new LinkedNode<GivenType>;
	newest->value = new_value;
	newest->next_node = nullptr;

	// If head_ptr is nullptr, needs to be replaced instead of next
	if (temp == nullptr) // or (!temp)
	{
		head_ptr = newest;
		comparisons -= 1;
	}
	else
	{
		// If head_ptr isn't null, then find last ptr in chain
		while (temp->next_node != nullptr)
		{
			temp = temp->next_node;
			comparisons += 1;
		}

		temp->next_node = newest;
	}

	return comparisons;
};

template <typename GivenType>
int LinkedList<GivenType>::PrintList() const
{
	int comparisons = 1;
	LinkedNode<GivenType>* temp_ptr = head_ptr;
	while (temp_ptr != nullptr)
	{
		cout << temp_ptr->value << endl;
		temp_ptr = temp_ptr->next_node;
		comparisons += 1;
	}
	return comparisons;
};

template <typename GivenType>
int LinkedList<GivenType>::InsertOrder(const GivenType& new_value)
{	// Insert pointers in ascending order
	int comparisons = 2;
	LinkedNode<GivenType>* temp = head_ptr;
	LinkedNode<GivenType>* tempLast = nullptr;

	// Setting up new node.
	LinkedNode<GivenType>* newest = new LinkedNode<GivenType>;
	newest->next_node = nullptr;
	newest->value = new_value;

	// If head_ptr is nullptr, needs to be replaced instead of next
	if (temp == nullptr) // or (!temp)
	{
		head_ptr = newest;
		comparisons = 1;
	}
	else
	{
		// If head_ptr isn't null, then find last ptr in chain
		if (temp->value > new_value) // Add as first item in list
		{
			newest->next_node = head_ptr;
			head_ptr = newest;
		}
		else if (temp->value == new_value) // Duplicates not allowed, so if temp->num == nb, return.
		{
			cout << "\nDuplicates not allowed.\n";
			delete newest; newest = nullptr;
			return comparisons;
		}
		else { // List exists and at least one node
			while (temp->next_node != nullptr && temp->value < new_value)
			{
				tempLast = temp;
				temp = temp->next_node;
				comparisons += 1;
			}
			// If current node's or next node's number == nb, then return. (duplicates not allowed)
			if ((temp != nullptr && temp->value == new_value) || (temp->next_node != nullptr && temp->next_node->value == new_value))
			{
				cout << "\nDuplicates not allowed.\n";
				delete newest; newest = nullptr;
				comparisons += 1;
				return comparisons;
			}
			else if (temp != nullptr && temp->value > new_value) // Else, if current pointer's value > new_value, 
			{											// then newest gets inserted between current & last pointer.
				if (tempLast != nullptr)
					tempLast->next_node = newest;
				newest->next_node = temp;
				comparisons += 1;
			}
			// If at end of list and still haven't found number >= than nb, insert at end of list
			else if (temp != nullptr && temp->next_node == nullptr)
			{
				temp->next_node = newest;
				comparisons += 1;
			}
		}
	}
	return comparisons;
}

template <typename GivenType>
int LinkedList<GivenType>::ReplaceValue(const GivenType& new_value)
{
	// Finds and replaces a value with a new one.
	int comparisons = 2;
	LinkedNode<GivenType>* temp = head_ptr;
	LinkedNode<GivenType>* tempLast = nullptr;

	// If head_ptr is nullptr, there's nothing to replace, so exit.
	if (temp == nullptr) // or (!temp)
	{
		comparisons = 1;
		return comparisons;
	}
	else
	{
		// If head_ptr isn't null, then find equivalent pointer
		if (temp->value == new_value) // Immediately replaces value.
		{
			temp->value = new_value;
			comparisons = 2;
		}
		else { // List exists and at least one node, and it isn't == to first one
			while (temp->next_node != nullptr && !(temp->value == new_value))
			{
				tempLast = temp;
				temp = temp->next_node;
				comparisons += 1;
			}
			// If current node's value == search value, then replace.
			if (temp != nullptr && temp->value == new_value)
			{
				temp->value = new_value;
				comparisons += 1;
			}
			// Unnecessary case that will never occur
			/*else if (temp != nullptr && temp->next_node != nullptr && temp->next_node->value == new_value)
			{
				temp->next_node->value = new_value;
			}*/
		}
	}
	return comparisons;
}

template <typename GivenType>
GivenType LinkedList<GivenType>::GetValue(int index, int& comparisons) const
{
	// Returns the value at a given index in the LinkedList. If there is no value there,
	// returns a blank object instead.
	comparisons = 0;
	GivenType temp_object = {};
	LinkedNode<GivenType>* temp_ptr = head_ptr;
	int i = 0;
	if (index < 0)
		return temp_object;
	while (temp_ptr != nullptr)
	{
		comparisons += 1;
		if (i == index)
		{
			temp_object = temp_ptr->value;
			break;
		}
		if (temp_ptr->next_node != nullptr)
			temp_ptr = temp_ptr->next_node;
		i++;
	}

	return temp_object;
}

template <typename GivenType>
GivenType LinkedList<GivenType>::GetValue(const GivenType& search_value, int& comparisons) const
{
	// Returns a value that is equivalent to the given one. 
	comparisons = 2;
	GivenType temp_object = {};
	LinkedNode<GivenType>* temp_ptr = head_ptr;

	// If head_ptr is nullptr, there's nothing to replace, so exit.
	if (temp_ptr == nullptr) // or (!temp)
	{
		comparisons = 1;
		return temp_object;
	}
	else
	{
		// If head_ptr isn't null, then find equivalent pointer
		if (temp_ptr->value == search_value) // Immediately replaces value.
		{
			temp_object = temp_ptr->value;
		}
		else { // List exists and at least one node, and it isn't == to first one
			while (temp_ptr->next_node != nullptr && !(temp_ptr->value == search_value))
			{
				temp_ptr = temp_ptr->next_node;
				comparisons += 1;
			}
			// If current node's value == search value, then replace.
			comparisons += 1;
			if (temp_ptr != nullptr && temp_ptr->value == search_value)
			{
				temp_object = temp_ptr->value;
			}
		}
	}

	return temp_object;
}

template <typename GivenType>
int LinkedList<GivenType>::GetCount() const
{
	// Gets total # of entries in the list by linearly searching through all the pointers.
	int count = 0;
	LinkedNode<GivenType>* temp_ptr = head_ptr;
	while (temp_ptr != nullptr)
	{
		temp_ptr = temp_ptr->next_node;
		count++;
	}
	return count;
}

template <typename GivenType>
int LinkedList<GivenType>::RemoveValue(GivenType compare_value)
{
	// Finds and deletes a node that has a value equal to the given one.
	int comparisons = 2;
	LinkedNode<GivenType>* temp = head_ptr;
	LinkedNode<GivenType>* tempLast = nullptr;

	// If head_ptr is nullptr, there's nothing to remove, so exit.
	if (temp == nullptr) // or (!temp)
	{
		comparisons = 1;
		return comparisons;
	}
	else
	{
		// If head_ptr isn't null, then find equivalent pointer
		if (temp->value == compare_value) // Immediately removes & replaces head_ptr if equal.
		{
			head_ptr = temp->next_node;
			temp->next_node = nullptr;
			delete temp; temp = nullptr;
		}
		else { // List exists and at least one node, and it isn't == to first one
			while (temp->next_node != nullptr && !(temp->value == compare_value))
			{
				tempLast = temp;
				temp = temp->next_node;
				comparisons += 1;
			}
			// If current node's value == search value, then remove.
			comparisons += 1;
			if (temp != nullptr && temp->value == compare_value)
			{
				if (tempLast != nullptr)
					tempLast->next_node = temp->next_node;
				temp->next_node = nullptr;
				delete temp; temp = nullptr;
			}
		}
	}
	return comparisons;
}