struct Entry
{
	char JobType;		// A, B, C, or D; D is HIGH priority
	int ArrivalTime;	// Varies by job type
	int ProcessingTime; // Also varies by job type
	int JobIndex;		// Index of entry within specific job

	//		Specifications for Entries
	// Type		Arrival Time	Processing Time
	// A		5 +/- 1			3 +/- 2 
	// B		7 +/- 1			5 +/- 3
	// C		11 +/- 7		9 +/- 3
	// D		9 +/- 5			12 +/- 10

	// 5 +/- 1 is 4, 5, 6; -> 4 + rand()%3
};