/***************
* Authors: Lyla Kerr & Zoey Vizzaccaro
* Creation Date: 26 November 2023
* Modification Date: 26 November 2023
* Purpose: Simulates a proccessor that can do jobs
* ***************/
#pragma once
#include "JobEntry.cpp"

class Processor
{
	Entry currentEntry;
	int currentTimeProcessing;
	bool active;

public:
	Processor();								// Default constructor; sets up base values.
												// Copy constructor.
	Processor(Processor& p)
	{
		if (this != &p)
		{
			active = p.active;
			currentEntry = p.currentEntry;
			currentTimeProcessing = p.currentTimeProcessing;
		}
		else
		{
			active = false;
			currentEntry = {};
			currentTimeProcessing = 0;
		}
	}
	bool isActive() { return active; }			// true if running a job, otherwise false
	bool isHighPriority();						// true if running a high priority job, otherwise false
	int timeProcessing() { return currentTimeProcessing; }	// time spent processing current job
	Entry currentJob() { return currentEntry; }	// returns the current job; if no active job, returns the previously running job

	void assignJob(Entry newEntry);				// Assigns job, does not check if there is already a job, 
												//		does not reset currenttime processing to 0
	Entry replaceJob(Entry newEntry);			// Assigns job, returns current job, for use with overriding
												//		a low priority job with a high priority one
	bool advanceJob();							// Advances time for current job, if job finishes, sets active
												//		to false and sets currentTimeProcessing to 0, returns
												//		true if job is completed
};
