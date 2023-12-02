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
}

Entry Processor::replaceJob(Entry newEntry)
{
	Entry temp = currentEntry;
	currentEntry = newEntry;
	return temp;
}

bool Processor::advanceJob() 
{
	// Decreases remaining processing time, and returns whether the job is completed or not.
	currentEntry.ProcessingTime--;
	if (currentEntry.ProcessingTime < 1)
	{
		currentTimeProcessing = 0;
		active = false;
		return true;
	}
	else
	{
		currentTimeProcessing++;
		return false;
	}
}