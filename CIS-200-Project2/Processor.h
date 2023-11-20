#pragma once
#include "JobEntry.cpp"

class Processor
{
	Entry currentEntry;
	int currentTimeProcessing;
	bool active;

public:
	bool isActive() { return active; }
	bool isHighPriority();
	int timeProcessing() { return currentTimeProcessing; }
	Entry currentJob() { return currentEntry; }

	void assignJob(Entry newEntry);
	Entry replaceJob(Entry newEntry);
	void advanceJob();
};