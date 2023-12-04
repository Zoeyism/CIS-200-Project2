/***************
* Authors: Lyla Kerr & Zoey Vizzaccaro
* Creation Date: 26 November 2023
* Modification Date: 30 November 2023
* Purpose: Simulates proccessors doing jobs
* ***************/
#include "Processor.h"
#include <iostream>
#include <fstream>
#include "ErrorLogger.h"
#include <iomanip>

using namespace std;

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

string CreateLogString(int Time, Processor proc_list[], int totalProc, const listNode* regularQueue, const listNode* priorityQueue, bool add_header=false)
{
	// Returns a string to be used to log the processors' and queues' states at each time unit.
	string data_log = "";
	int totalQ = 0;		// Used for queue counts.
	listNode* temp = nullptr;

	// Adding header for data. Repeatedly done throughout file for ease of reading, not just on first call.
	if (add_header) 
	{
		data_log += "----------------| ";

		// Adding processors to log header
		for (int i = 0; i < totalProc; i++)
		{
			data_log += " Proc #";
			if (i < 10)
				data_log += " ";
			data_log += to_string(i) + "  | ";
		}

		data_log += "Regular Queue  | Priority Queue |----------------\n";
	}
	
	// Adding time stamp to start of line.
	data_log += "  Time: ";
	for (int i = 0; i < 5 - to_string(Time).length(); i++)
	{
		data_log += " ";
	}
	data_log += to_string(Time) + "   | ";

	// Adding each Processor's info to the log.
	for (int j = 0; j < totalProc; j++)
	{
		// only 10 characters to display each processor's info.
		if (proc_list[j].isActive())
		{
			data_log += "Type ";
			data_log += proc_list[j].currentJob().JobType;
			data_log += ", ";
			if (proc_list[j].currentJob().ProcessingTime < 10)
				data_log += ' ';
			data_log += to_string(proc_list[j].currentJob().ProcessingTime);
		}
		else
			data_log += "Not Active";

		data_log += " | ";
	}

	// Only 14 characters to work with for the Queue statuses.
	if (regularQueue != nullptr)
	{
		data_log += "Q Total: ";
		temp = regularQueue->next;
		totalQ += 1;
		while (temp != nullptr)
		{
			temp = temp->next;
			totalQ += 1;
		}

		// Adding total # of Queue items to the log (and any spaces as needed)
		for (int k = 0; k < 5 - to_string(totalQ).length(); k++)
			data_log += " ";
		data_log += to_string(totalQ);
	}
	else
		data_log += "No queue items";

	data_log += " | ";

	// Only 14 characters to work with for the Queue statuses.
	if (priorityQueue != nullptr)
	{
		data_log += "Q Total: "; // 9 characters, so only 5 remaining for total.
		temp = priorityQueue->next;
		totalQ = 1; // Reset totalQ to 1 for Priority Queue.
		while (temp != nullptr)
		{
			temp = temp->next;
			totalQ += 1;
		}

		// Adding total # of Queue items to the log (and any spaces as needed)
		for (int k = 0; k < 5 - to_string(totalQ).length(); k++)
			data_log += " ";
		data_log += to_string(totalQ);
	}
	else
		data_log += "No queue items";

	data_log += " | ";

	return data_log;
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

	ErrorLogger data_logger("trial_log", ".txt"); // Repurposing ErrorLogger class to log data instead of errors.
	bool AddHeader = false;

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

	//TOTAL WAIT TIME for each job type; used for average wait time of each job type
	int waitA = 0;
	int waitB = 0;
	int waitC = 0;
	int waitD = 0;

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

	// Head of log file
	data_logger.LogError("\t\tTotal Processors: " + to_string(totalProc) + "\n");

	entries.read((char*)&incoming, ENTRY_SIZE);

	for (int time = 0; time < 10000; time++)
	{
		if (time == 500)
		{
			//first report
			cout << "\n\tCurrent Time: " << time
				<< "\n\tTotal A: " << totalA << "\tCompleted A: " << compA 
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

						// Before replacing, need to correct the wait time counts
						switch (proc_list[i].currentJob().JobType)
						{
						case 'A':
							waitA += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
							break;
						case 'B':
							waitB += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
							break;
						case 'C':
							waitC += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
						}

						regularQueue->data = proc_list[i].replaceJob(priorityQueue->data);
					}
					else // If not active, then just assign the job in processor
					{
						// Before assigning, need to correct the wait time counts. ProcessingTime continues decreasing even if the job is done, so it still
						// accurately updates the wait time even if there's been a delay between finishing the job and assigning the new job.
						switch (proc_list[i].currentJob().JobType)
						{
						case 'A':
							waitA += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
							break;
						case 'B':
							waitB += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
							break;
						case 'C':
							waitC += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
							break;
						case 'D':
							waitD += time - proc_list[i].currentJob().ArrivalTime - proc_list[i].timeProcessing() + proc_list[i].currentJob().ProcessingTime;
						}
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

		if (time % 50 == 0)
			AddHeader = true;
		else
			AddHeader = false;
		data_logger.LogError(CreateLogString(time, proc_list, totalProc, regularQueue, priorityQueue, AddHeader));

	}
	// Adjusting wait times for remaining queue items
	tempQ = regularQueue;
	while (tempQ != nullptr)
	{
		if (tempQ->data.ArrivalTime < 10000)
		{
			switch (tempQ->data.JobType)
			{
			case 'A':
				waitA += 10000 - tempQ->data.ArrivalTime;
				break;
			case 'B':
				waitB += 10000 - tempQ->data.ArrivalTime;
				break;
			case 'C':
				waitC += 10000 - tempQ->data.ArrivalTime;
			}
		}
		tempQ = tempQ->next;
	}
	tempQ = priorityQueue;
	while (tempQ != nullptr)
	{
		waitD += 10000 - tempQ->data.ArrivalTime;
		tempQ = tempQ->next;
	}


	//second report
	cout << "\n\tCurrent Time: " << 10000
		<< "\n\tTotal A: " << totalA << "\tCompleted A: " << compA
		<< "\n\tTotal B: " << totalB << "\tCompleted B: " << compB
		<< "\n\tTotal C: " << totalC << "\tCompleted C: " << compC
		<< "\n\tTotal D: " << totalD << "\tCompleted D: " << compD
		<< "\n\tWait Averages"
		<< "\n\tA: " << fixed << setprecision(3) << ((float)waitA) / totalA << "s"
		<< "\n\tB: " << ((float)waitB) / totalB << "s"
		<< "\n\tC: " << ((float)waitC) / totalC << "s"
		<< "\n\tD: " << ((float)waitD) / totalD << "s" << endl << endl;
	system("Pause");

	// Deleting all pointers
	deleteLinkedNodes(priorityQueue);
	deleteLinkedNodes(regularQueue);

	return 0;
}