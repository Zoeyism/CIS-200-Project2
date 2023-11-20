#include "Processor.h"

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