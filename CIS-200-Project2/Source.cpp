#include "LinkedList.h"
#include "Processor.h"

using namespace std;

int main()
{
	LinkedList<int> test;
	test.AppendList(3);
	test.AppendList(-1);
	test.AppendList(17);
	test.AppendList(1);
	test.AppendList(8);

	test = *test.MergeSort();

	test.PrintList();

	return 0;
}