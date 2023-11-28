#include "LinkedList.h"
#include "Processor.h"

using namespace std;

void TestLinkedList()
{
	LinkedList<int> test;
	test.AppendList(3);
	test.AppendList(-1);
	test.AppendList(17);
	test.AppendList(1);
	test.AppendList(8);

	cout << "\n\tTest List before MergeSort: ";
	test.PrintList();

	test = *test.MergeSort();

	cout << "\n\tTest List after MergeSort:  ";
	test.PrintList();
}

int main()
{
	
	return 0;
}