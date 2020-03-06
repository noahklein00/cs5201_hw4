#include "MyVector.h"
#include <iostream>

using namespace std;

int main()
{
	MyVector<int> noah({1,2,3,4,5});
	MyVector<int> sean({2,4,56,6,7,3});
	cout << noah << endl;
	cout << sean << endl;
	MyVector<int> sam = noah + sean;
	cout << sam << endl;
	sam = sean + noah;
	cout << sam << endl;
	sam = noah * 2;
	cout << sam << endl;
	sam = 2 * noah;
	cout << sam << endl;
	return 0;
}