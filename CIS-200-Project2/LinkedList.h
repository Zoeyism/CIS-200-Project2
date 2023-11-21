#pragma once
#include "LinkedList.cpp"

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
	~LinkedNode() { delete next_node; next_node = nullptr; /*cout << "\nNode deleted.";*/ }
};

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
	int PrintList() const;
	int InsertOrder(const GivenType& new_value);
	int ReplaceValue(const GivenType& new_value);
	GivenType GetValue(int index, int& comparisons) const;	
	GivenType GetValue(const GivenType& search_value, int& comparisons) const;
	int GetCount() const;
	int RemoveValue(GivenType compare_value);
private:
	LinkedNode<GivenType>* head_ptr;

};