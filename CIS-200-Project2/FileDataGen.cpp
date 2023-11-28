#include <iostream>
#include <fstream>
#include <string>
#include "JobEntry.cpp"

using namespace std;

const int TOTAL_ENTRIES[] = { 2400, 1650, 1100, 1200  }; // In order, A, B, C, D quantities

void SaveEntriesToFiles()
{
	// Creates all entries required for each Job Type, and saves to 4 separate files to be merged later.
	// LinkedList SomeLinkedList = {};
	Entry temp_entry = { 'A', 0, 0, 0 };

	ofstream entries_a;
	ofstream entries_b;
	ofstream entries_c;
	ofstream entries_d;

	int total_a = 0;
	int total_b = 0;
	int total_c = 0;
	int total_d = 0;

	// For creating job type A entries
	entries_a.open("entries_a.dat", ios::binary | ios::out);
	temp_entry.JobType = 'A';
	temp_entry.ArrivalTime = 0;
	for (int i = 0; i < TOTAL_ENTRIES[0]; i++)
	{
		temp_entry.ArrivalTime += 4 + rand() % 3;   // Initial value is 0, is added to for each entry.
		temp_entry.ProcessingTime = 1 + rand() % 5; // Processing time is replaced each time.
		temp_entry.JobIndex = i;

		entries_a.write((char*)&temp_entry, ENTRY_SIZE);
		total_a += 1;
	}
	entries_a.close();

	// For creating job type B entries
	entries_b.open("entries_b.dat", ios::binary | ios::out);
	temp_entry.JobType = 'B';
	temp_entry.ArrivalTime = 0;
	for (int i = 0; i < TOTAL_ENTRIES[1]; i++)
	{
		temp_entry.ArrivalTime += 6 + rand() % 3;
		temp_entry.ProcessingTime = 2 + rand() % 7;
		temp_entry.JobIndex = i;

		entries_b.write((char*)&temp_entry, ENTRY_SIZE);
		total_b += 1;
	}
	entries_b.close();

	// For creating job type C entries
	entries_c.open("entries_c.dat", ios::binary | ios::out);
	temp_entry.JobType = 'C';
	temp_entry.ArrivalTime = 0;
	for (int i = 0; i < TOTAL_ENTRIES[2]; i++)
	{
		temp_entry.ArrivalTime += 4 + rand() % 15;
		temp_entry.ProcessingTime = 6 + rand() % 7;
		temp_entry.JobIndex = i;

		entries_c.write((char*)&temp_entry, ENTRY_SIZE);
		total_c += 1;
	}
	entries_c.close();

	// For creating job type D entries
	entries_d.open("entries_d.dat", ios::binary | ios::out);
	temp_entry.JobType = 'D';
	temp_entry.ArrivalTime = 0;
	for (int i = 0; i < TOTAL_ENTRIES[3]; i++)
	{
		temp_entry.ArrivalTime += 4 + rand() % 11;
		temp_entry.ProcessingTime = 2 + rand() % 21;
		temp_entry.JobIndex = i;

		entries_d.write((char*)&temp_entry, ENTRY_SIZE);
		total_d += 1;
	}
	entries_d.close();

	cout << "\n\tTotal counts in order: " << total_a << " " << total_b << " " << total_c << " " << total_d << endl;
}

void MergeEntriesToFile()
{
	// Takes the 4 files created by SaveEntriesToFiles() and merges them in order of ascending arrival time.
	const int ENTRY_SIZE = sizeof(Entry);
	Entry temp_a = { 'A', 0, 0, 0 };
	Entry temp_b = { 'B', 0, 0, 0 };
	Entry temp_c = { 'C', 0, 0, 0 };
	Entry temp_d = { 'D', 0, 0, 0 };
	bool a_done = false;
	bool b_done = false;
	bool c_done = false;
	bool d_done = false;

	int time = 0;
	int total_entries = 0;
	
	ifstream entries_a; entries_a.open("entries_a.dat", ios::binary | ios::in);
	ifstream entries_b; entries_b.open("entries_b.dat", ios::binary | ios::in);
	ifstream entries_c; entries_c.open("entries_c.dat", ios::binary | ios::in);
	ifstream entries_d; entries_d.open("entries_d.dat", ios::binary | ios::in);

	ofstream entries_merged; entries_merged.open("entries_merged.dat", ios::binary | ios::out);

	if (entries_a && entries_b && entries_c && entries_d && entries_merged && time >= 0) // If all files opened properly (and time hasn't overflowed or something)
	{
		// Read in each entry to the temporary Entries
		entries_a.read((char*)&temp_a, ENTRY_SIZE);
		entries_b.read((char*)&temp_b, ENTRY_SIZE);
		entries_c.read((char*)&temp_c, ENTRY_SIZE);
		entries_d.read((char*)&temp_d, ENTRY_SIZE);

		// While at least one file is not at end of file...
		while (!(entries_a.eof()) || !(entries_b.eof()) || !(entries_c.eof()) || !(entries_d.eof()))
		{
			if (!d_done) // If file D isn't done... // Done first to ensure higher priority is first in queue if times are ==
			{
				if (temp_d.ArrivalTime == time) // Else, if the current entry's arrival is == time, add now and read in new entry.
				{
					entries_merged.write((char*)&temp_d, ENTRY_SIZE);
					entries_d.read((char*)&temp_d, ENTRY_SIZE);
					total_entries += 1;
					if (entries_d.eof()) // If at end of file, file is done and should not be checked further.
						d_done = true;
				}
			}

			if (!a_done) // If file A isn't done...
			{
				if (temp_a.ArrivalTime == time) // Else, if the current entry's arrival is == time, add now and read in new entry.
				{
					entries_merged.write((char*)&temp_a, ENTRY_SIZE);
					entries_a.read((char*)&temp_a, ENTRY_SIZE);
					total_entries += 1;
					if (entries_a.eof()) // If at end of file, file is done and should not be checked further.
						a_done = true;
				}
			}

			if (!b_done) // If file B isn't done...
			{
				if (temp_b.ArrivalTime == time) // Else, if the current entry's arrival is == time, add now and read in new entry.
				{
					entries_merged.write((char*)&temp_b, ENTRY_SIZE);
					entries_b.read((char*)&temp_b, ENTRY_SIZE);
					total_entries += 1;
					if (entries_b.eof()) // If at end of file, file is done and should not be checked further.
						b_done = true;
				}
			}

			if (!c_done) // If file C isn't done...
			{
				if (temp_c.ArrivalTime == time) // Else, if the current entry's arrival is == time, add now and read in new entry.
				{
					entries_merged.write((char*)&temp_c, ENTRY_SIZE);
					entries_c.read((char*)&temp_c, ENTRY_SIZE);
					total_entries += 1;
					if (entries_c.eof()) // If at end of file, file is done and should not be checked further.
						c_done = true;
				}
			}

			time += 1; // Increment time
		}
	}
	else
		cout << "\n\tError merging files: One of the files did not open properly.\n";

	cout << "\n\tCurrent Time: " << time << "\n\tTotal Entries : " << total_entries << "\tIntended Total : " 
		<< TOTAL_ENTRIES[0] + TOTAL_ENTRIES[1] + TOTAL_ENTRIES[2] + TOTAL_ENTRIES[3] << endl;
	entries_a.close();
	entries_b.close();
	entries_c.close();
	entries_d.close();

	entries_merged.close();
}

// ONLY RUN UNCOMMENTED IF YOU WANT TO REPLACE THE MERGED ENTRIES FILE
//int main()
//{
//	SaveEntriesToFiles();
//	MergeEntriesToFile();
//	return 0;
//}