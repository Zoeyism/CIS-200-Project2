#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Entry
{
	char JobType; // A, B, C, or D; D is HIGH priority
	int ArrivalTime; // Varies by job type
	int ProcessingTime; // Also varies by job type
	int JobIndex; // Index of entry within specific job

	// Type		Arrival Time	Processing Time
	// A		5 +/- 1			3 +/- 2 
	// B		7 +/- 1			5 +/- 3
	// C		11 +/- 7		9 +/- 3
	// D		9 +/- 5			12 +/- 10

	// 5 +/- 1 is 4, 5, 6; -> 4 + rand()%3
};

const int TOTAL_ENTRIES[] = { 2400, 1650, 1100, 1200  }; // In order, A, B, C, D quantities

Entry CreateEntry(char jobT)
{
	Entry newE = {};
	int ARRIVAL_TIMES[] = { 5, 7, 11, 9 }; 


	return newE;
}

void SaveEntriesToFile(fstream& file)
{
	// LinkedList SomeLinkedList = {};
	Entry temp_entry = { 'A', 0, 0 };
	if (file)
	{
		// For creating job type A entries
		for (int i = 0; i < TOTAL_ENTRIES[0]; i++)
		{
			temp_entry.JobType = 'A';
			temp_entry.ArrivalTime = 4 + rand() % 3;
			temp_entry.ProcessingTime = 1 + rand() % 5;
			temp_entry.JobIndex = i;

			// temp_entry.ArrivalTime += SomeLinkedList[i-1].ArrivalTime;

			// SomeLinkedList.append(temp_entry);
		}

		// For creating job type B entries
		for (int i = 0; i < TOTAL_ENTRIES[1]; i++)
		{
			temp_entry.JobType = 'B';
			temp_entry.ArrivalTime = 6 + rand() % 3;
			temp_entry.ProcessingTime = 2 + rand() % 7;
			temp_entry.JobIndex = i;

			// temp_entry.ArrivalTime += SomeLinkedList[i-1].ArrivalTime;

			// SomeLinkedList.append(temp_entry);
		}

		// For creating job type C entries
		for (int i = 0; i < TOTAL_ENTRIES[2]; i++)

		{
			temp_entry.JobType = 'C';
			temp_entry.ArrivalTime = 4 + rand() % 15;
			temp_entry.ProcessingTime = 6 + rand() % 7;
			temp_entry.JobIndex = i;

			// temp_entry.ArrivalTime += SomeLinkedList[i-1].ArrivalTime;

			// SomeLinkedList.append(temp_entry);
		}

		// For creating job type D entries
		for (int i = 0; i < TOTAL_ENTRIES[3]; i++)

		{
			temp_entry.JobType = 'D';
			temp_entry.ArrivalTime = 4 + rand() % 11;
			temp_entry.ProcessingTime = 2 + rand() % 21;
			temp_entry.JobIndex = i;

			// temp_entry.ArrivalTime += SomeLinkedList[i-1].ArrivalTime;

			// SomeLinkedList.append(temp_entry);
		}

		while (linkedListPtr != nullptr)
		{

		}

	}
}