#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Entry
{
	char JobType; // A, B, C, or D; D is HIGH priority
	int ArrivalTime; // Varies by job type
	int ProcessingTime; // Also varies by job type

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

void SaveEntryToFile(fstream& file)
{
	if (file)
	{
		
	}
}