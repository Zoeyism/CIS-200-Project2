#include "Processor.h"

bool Processor::isHighPriority()
{
	if()
	if (currentEntry.JobType == 'D')
	{
		return true;
	}
	else
		return false;
}

void Processor::assignJob(Entry newEntry)
{
	currentEntry = newEntry;
	active = true;
}

Entry Processor::replaceJob(Entry newEntry)
{

}