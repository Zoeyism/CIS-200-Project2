/***************
* Authors: Lyla Kerr & Zoey Vizzaccaro
* Creation Date: 26 November 2023
* Modification Date: 26 November 2023
* Purpose: Simulates a proccessor that can do jobs
* ***************/
#include "Processor.h"

Processor::Processor()
{
	currentEntry = {};
	currentTimeProcessing = 0;
	active = false;
}

bool Processor::isHighPriority()
{
	if (active)
	{
		if (currentEntry.JobType == 'D')
		{
			return true;
		}
	}
	return false;
}

void Processor::assignJob(Entry newEntry) 
{
	currentEntry = newEntry;
	active = true;
	currentTimeProcessing = 0;
}

Entry Processor::replaceJob(Entry newEntry)
{
	currentTimeProcessing = 0;
	Entry temp = currentEntry;
	currentEntry = newEntry;
	return temp;
}

bool Processor::advanceJob() 
{
	// Decreases remaining processing time, and returns whether the job has completed at this moment or not.
	currentEntry.ProcessingTime--;
	if (currentEntry.ProcessingTime < 1 && active) // Must be active to return that the job has advanced.
	{
		active = false;
		return true;
	}
	else
	{
		currentTimeProcessing++;
		return false;
	}
}