#include "LinkedList.h"
#include "Processor.h"
#include <iostream>
#include <fstream>

using namespace std;

void TestLinkedList()
{
	LinkedList<int> test;
	test.AppendList(3);
	test.AppendList(-1);
	test.AppendList(17);
	test.AppendList(1);
	test.AppendList(8);

	cout << "\n\tTest List before MergeSort: ";
	test.PrintList();

	test = *test.MergeSort();

	cout << "\n\tTest List after MergeSort:  ";
	test.PrintList();
}

struct listNode // linked list node for queues
{
	Entry data;
	listNode* next;
};

int deleteLinkedNodes(listNode* head)
{
	// Takes the head pointer in a linked list, and deletes all nodes in the from the
	// header onwards. Returns # of nodes deleted with this process.
	int nodes_deleted = 0;
	listNode* temp = head;
	listNode* temp_last = nullptr;
	while (temp != nullptr)
	{
		temp_last = temp;
		temp = temp->next;
		delete temp_last;
		nodes_deleted++;
	}

	return nodes_deleted;
}

int main()
{
	ifstream entries; 
	entries.open("entries_merged.dat", ios::binary | ios::in);
	if (entries.peek() == EOF)
	{
		//empty file error here
		return -1;
	}

	listNode* priorityQueue = nullptr;
	listNode* regularQueue = nullptr;
	listNode* tempQ = nullptr; //listNode pointer for temp storage

	//specify amount of processors

	Entry incoming;

	//TOTAL ARRIVALS for each job
	int totalA = 0;
	int totalB = 0;
	int totalC = 0;
	int totalD = 0;

	//TOTAL COMPLETIONS for each job
	int compA = 0;
	int compB = 0;
	int compC = 0;
	int compD = 0;

	//const int TOTAL_PROC = 1; // Total processors. Constant int for easy changing between runs.
	//Processor proc_list[TOTAL_PROC];

	int totalProc = 0; //User Defined Amount of processors
	cout << "How many processors shall be used?\n";
	cin >> totalProc;
	while (cin.fail() || totalProc <= 0 || totalProc > 100)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Error, not a valid number. Re-enter amount: ";
		cin >> totalProc;
	}

	Processor* proc_list = new Processor[totalProc];


	entries.read((char*)&incoming, ENTRY_SIZE);

	for (int time = 0; time < 10000; time++)
	{
		if (time == 500)
		{
			//first report
			cout << "\n\tTotal A: " << totalA << "\tCompleted A: " << compA 
				<< "\n\tTotal B: " << totalB << "\tCompleted B: " << compB
				<< "\n\tTotal C: " << totalC << "\tCompleted C: " << compC 
				<< "\n\tTotal D: " << totalD << "\tCompleted D: " << compD << endl << endl;
			system("Pause");
		}

		// new Arrival(s)
		while (incoming.ArrivalTime <= time)
		{
			if (incoming.JobType == 'D') //priority job
			{
				totalD++;
				if(priorityQueue == nullptr) //empty queue
				{
					priorityQueue = new listNode;
					priorityQueue->data = incoming;
					priorityQueue->next = nullptr;
				}
				else
				{
					tempQ = priorityQueue;
					while (tempQ->next != nullptr)
					{
						tempQ = tempQ->next;
					}
					tempQ->next = new listNode;
					tempQ = tempQ->next;
					tempQ->data = incoming;
					tempQ->next = nullptr;
				}
			}
			else //nonpriority job
			{
				switch (incoming.JobType)
				{
				case 'A':
					totalA++;
					break;
				case 'B':
					totalB++;
					break;
				case 'C':
					totalC++;
				}
				if (regularQueue == nullptr) // If empty queue, create new head node
				{
					regularQueue = new listNode;
					regularQueue->data = incoming;
					regularQueue->next = nullptr;
				}
				else
				{
					tempQ = regularQueue;
					while (tempQ->next != nullptr)
					{
						tempQ = tempQ->next;
					}
					tempQ->next = new listNode;
					tempQ = tempQ->next;
					tempQ->data = incoming;
					tempQ->next = nullptr;
				}
			}


			entries.read((char*)&incoming, ENTRY_SIZE);
		} 

		// Advancing time for processors and assigning priority/regular jobs as needed
		//for (int i = 0; i < TOTAL_PROC; i++)
		for (int i = 0; i < totalProc; i++)
		{
			// If, after advancing the job the processing time reaches 0, 
			if (proc_list[i].advanceJob())
			{
				// then add to completed jobs
				switch (proc_list[i].currentJob().JobType)
				{
				case 'A':
					compA += 1;
					break;
				case 'B':
					compB += 1;
					break;
				case 'C':
					compC += 1;
					break;
				case 'D':
					compD += 1;
				}
			}

			// If there is a priority entry in the priority queue, attempt to swap in to the current processor
			if (priorityQueue != nullptr)
			{
				// If the current processor is not active, or is not high priority (but also active), then assign a high priority entry
				if (!proc_list[i].isActive() || !proc_list[i].isHighPriority())
				{
					// If it is active but not high priority, then swap the entry into the non-priority queue.
					if (proc_list[i].isActive() && !proc_list[i].isHighPriority())
					{
						// Works in both cases: if regularQueue == nullptr, or if it is has nodes
						tempQ = regularQueue; 

						// make a new node the new head of the list, set data == to the replaced job
						regularQueue = new listNode;
						regularQueue->next = tempQ;
						regularQueue->data = proc_list[i].replaceJob(priorityQueue->data);
					}
					else // If not active, then just assign the job in processor
					{
						proc_list[i].assignJob(priorityQueue->data);
					}
					// Remove assigned node from priority queue.
					tempQ = priorityQueue;
					priorityQueue = priorityQueue->next;
					delete tempQ;
					tempQ = nullptr;
				}
			}
			// Otherwise, if the regular queue has entries to add...
			else if (regularQueue != nullptr)
			{
				// If the processor isn't active, add in the new job; otherwise, do nothing.
				if (!proc_list[i].isActive())
				{
					proc_list[i].assignJob(regularQueue->data);

					// Remove assigned node from regular queue.
					tempQ = regularQueue;
					regularQueue = regularQueue->next;
					delete tempQ;
					tempQ = nullptr;
				}
			}
		}



	}
	//second report
	cout << "\n\tTotal A: " << totalA << "\tCompleted A: " << compA
		<< "\n\tTotal B: " << totalB << "\tCompleted B: " << compB
		<< "\n\tTotal C: " << totalC << "\tCompleted C: " << compC
		<< "\n\tTotal D: " << totalD << "\tCompleted D: " << compD << endl << endl;
	system("Pause");

	// Deleting all pointers
	deleteLinkedNodes(priorityQueue);
	deleteLinkedNodes(regularQueue);

	return 0;
}