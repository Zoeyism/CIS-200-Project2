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


	entries.read((char*)&incoming, ENTRY_SIZE);

	for (int time = 0; time < 10000; time++)
	{
		if (time == 500)
		{
			//first report
			cout << totalA << ' ' << totalB << ' ' << totalC << ' ' << totalD;
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
				if (regularQueue == nullptr) // empty queue
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

	}
	//second report
	return 0;
}