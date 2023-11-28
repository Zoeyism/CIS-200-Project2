#include <iostream>
using namespace std;

//////////		LINKED NODE CLASS		////////// 
template <typename GivenType>
class LinkedNode
{
public:
	GivenType value;		// The GivenType's value for the node
	LinkedNode<GivenType>* next_node; // The next node's pointer

	LinkedNode()
	{
		value = {};
		next_node = nullptr;
	};
	LinkedNode(GivenType v)
	{
		value = v;
		next_node = nullptr;
	};
	LinkedNode(const LinkedNode& other) { /*ONLY COPIES VALUE from other node, NOT the pointer.*/ value = other->value; }
	void SwapNode(LinkedNode& other)
	{
		GivenType temp = other.value;
		if (this != nullptr && &other != nullptr && this != &other)
		{
			other.value = this->value;
			this->value = temp;
		}
	}
	~LinkedNode() { delete next_node; next_node = nullptr; /*cout << "\nNode deleted.";*/ }
};

//////////		LINKED LIST CLASS DEF		//////////
template <typename GivenType>
class LinkedList
{
public:
	LinkedList()
	{
		// Empty initialization leaves head_ptr as a nullptr.
		head_ptr = nullptr;
	}
	LinkedList(GivenType some_value)
	{
		// a new pointer is created if some_value of GivenType is given. 
		head_ptr = new LinkedNode<GivenType>;
		head_ptr->next_node = nullptr;
		head_ptr->value = some_value;
	}
	LinkedList& operator=(const LinkedList& other)
	{
		// Copy constructor for LinkedList. Deletes the current LinkedList,
		// and creates a deep copy of the other one.
		if (this == &other)
			return *this;

		LinkedNode<GivenType>* temp_last = nullptr;
		LinkedNode<GivenType>* temp_curr = nullptr;
		LinkedNode<GivenType>* other_node = other.head_ptr;

		// If the current head_ptr isn't null, delete it.
		if (head_ptr != nullptr)
			delete head_ptr; // Deleting current node list to make way for a new node list. 
							 // Each node deletes the next one down the line on their own.
		head_ptr = new LinkedNode<GivenType>;
		temp_curr = head_ptr;
		while (other_node != nullptr)
		{
			temp_curr->value = other_node->value;
			temp_curr->next_node = new LinkedNode<GivenType>;
			temp_last = temp_curr;
			temp_curr = temp_curr->next_node;

			other_node = other_node->next_node;
		}
		// By end, other_node = nullptr, and temp_curr = temp_last->next_node, which is a new ptr.
		// Needs to be deleted and set to nullptr.
		if (temp_last != nullptr && temp_last->next_node != nullptr)
		{
			delete (temp_last->next_node);
			temp_last->next_node = nullptr;
			temp_curr = nullptr; // Also set to nullptr for safety's sake.
		}

		return *this;
	};
	~LinkedList()
	{
		if (head_ptr != nullptr)
		{
			delete head_ptr;
			head_ptr = nullptr;
		}
		/*cout << "\nList deleted.";*/
	};

	int AppendList(const GivenType& new_value);
	void InsertFront(const GivenType& new_value);
	int PrintList(char separator = ' ') const;
	int InsertOrder(const GivenType& new_value);
	int ReplaceValue(const GivenType& new_value);
	GivenType GetValue(int index) const;
	GivenType GetValue(const GivenType& search_value, int& comparisons) const;
	int GetCount() const;
	int RemoveValue(GivenType compare_value);
	LinkedNode<GivenType>* GetNode(int index);
	static LinkedList<GivenType>* MergeSortedLinkedLists(LinkedList<GivenType>& first, LinkedList<GivenType>& second)
	{
		LinkedList<GivenType>* sorted = new LinkedList<GivenType>;
		LinkedNode<GivenType>* f_node = first.head_ptr;
		LinkedNode<GivenType>* s_node = second.head_ptr;

		while (f_node != nullptr && s_node != nullptr)
		{
			if (f_node->value < s_node->value)
			{
				sorted->AppendList(f_node->value);
				f_node = f_node->next_node;
			}
			else
			{
				sorted->AppendList(s_node->value);
				s_node = s_node->next_node;
			}
		}
		if (f_node == nullptr)
		{
			while (s_node != nullptr)
			{
				sorted->AppendList(s_node->value);
				s_node = s_node->next_node;
			}
		}

		if (s_node == nullptr)
		{
			while (f_node != nullptr)
			{
				sorted->AppendList(f_node->value);
				f_node = f_node->next_node;
			}
		}

		return sorted;
	}
	static LinkedList<GivenType>* MergeSort(LinkedList<GivenType>& sort_list, const int min, const int max)
	{
		int middle = (min + max) / 2;
		if (min == max) // If down to one index, then we're sorted, and good to go.
		{
			LinkedList<GivenType>* sorted = new LinkedList<GivenType>;
			sorted->AppendList(sort_list.GetValue(min));

			return sorted;
		}

		LinkedList<GivenType>* bottom_half = MergeSort(sort_list, min, middle);
		LinkedList<GivenType>* top_half = MergeSort(sort_list, middle + 1, max);

		LinkedList<GivenType>* merged_list = MergeSortedLinkedLists(*bottom_half, *top_half);

		return merged_list;
	}
	LinkedList<GivenType>* MergeSort();

private:
	LinkedNode<GivenType>* head_ptr;

};



//////////		LINKED LIST METHOD DEFINITIONS		//////////


// AppendList: Appends a value to the LinkedList as a new node.
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

// InsertFront: Creates a new node with the given value, and sets as the header for the LinkedList.
template <typename GivenType>
void LinkedList<GivenType>::InsertFront(const GivenType& new_value)
{
	LinkedNode<GivenType>* newest = new LinkedNode<GivenType>;
	newest->value = new_value;
	newest->next_node = head_ptr;
	head_ptr = newest;
}

// PrintList: Prints each node's value in the list, using "separator" as a separation between each value.
template <typename GivenType>
int LinkedList<GivenType>::PrintList(char separator) const
{
	int comparisons = 1;
	LinkedNode<GivenType>* temp_ptr = head_ptr;
	while (temp_ptr != nullptr)
	{
		cout << temp_ptr->value << separator;
		temp_ptr = temp_ptr->next_node;
		comparisons += 1;
	}
	return comparisons;
};

// InsertOrder: Inserts a given value into a SORTED LIST in order. MUST be sorted already.
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

// ReplaceValue: Finds the given value in the LinkedList, and removes the node from the LinkedList.
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

// GetValue: Inefficient, but goes through linked list to find an "index" in the list, and returns the value.
template <typename GivenType>
GivenType LinkedList<GivenType>::GetValue(int index) const
{
	// Returns the value at a given index in the LinkedList. If there is no value there,
	// returns a blank object instead.
	GivenType temp_object = {};
	LinkedNode<GivenType>* temp_ptr = head_ptr;
	int i = 0;
	if (index < 0)
		return temp_object;
	while (temp_ptr != nullptr)
	{
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

// GetValue: Inefficient, but goes through linked list to find a search value in the list, and returns the value itself.
// Not recommended for use.
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

// GetCount: Counts number of nodes in a LinkedList manually, by sequentially going through the list.
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

// RemoveValue: Finds a given value to remove, and removes the node from the list.
//		If no match is found, nothing happens.
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

// GetNode: Returns the node at a given index. Use with caution!
template <typename GivenType>
LinkedNode<GivenType>* LinkedList<GivenType>::GetNode(int index)
{
	int i = 0;
	LinkedNode<GivenType>* temp = head_ptr;
	if (index < 0)
		return nullptr;

	while (temp != nullptr && i < index)
	{
		temp = temp->next_node;
		i++;
	}

	if (i == index)
		return temp;
	else
		return nullptr;
}

// MergeSort: Returns a new, SEPARATE, sorted list from the instance's list. Recommended to use to avoid issues with parameters from the static version of this method.
// Example implementation: some_list = *some_list.MergeSort();
template <typename GivenType>
LinkedList<GivenType>* LinkedList<GivenType>::MergeSort()
{
	return MergeSort(*this, 0, (*this).GetCount() - 1);
}