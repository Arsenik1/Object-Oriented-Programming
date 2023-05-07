#include "SKArray.cpp"
#include <iostream>

using namespace SKArray;

int main()
{
	{
		cout << endl << "Testing default constructor:\n";
		PFArray<int> pfa1;
		cout << "pfa1 has size " << pfa1.getNumberUsed() << " and capacity " << pfa1.size() << endl;

		cout << endl << "Testing alternate constructor:\n";
		PFArray<int> pfa2(100);
		cout << "pfa2 has size " << pfa2.getNumberUsed() << " and capacity " << pfa2.size() << endl;

		cout << endl << "Testing addElement and empty functions:\n";
		for (int i = 0; i < 50; i++)
		{
			pfa1.addElement(i);
		}
		cout << "pfa1 is empty: '" << pfa1.empty() << '\''<< endl;

		cout << "pfa1 elements: ";
		for (auto it = pfa1.begin(); it != pfa1.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;

		cout << endl << "Testing copy constructor:\n";
		PFArray<int> pfa3(pfa1);
		cout << "pfa3 has size " << pfa3.getNumberUsed() << " and capacity " << pfa3.size() << endl;

		cout << endl << "Testing clear function:\n";
		pfa3.clear();
		cout << "pfa3 has size " << pfa3.getNumberUsed() << " and capacity " << pfa3.size() << endl;
		cout << "pfa3 is empty: " << pfa3.empty() << endl;

		cout << endl << "Testing square bracket operator:\n";
		pfa1[5] = 10;
		cout << "pfa1[5] = " << pfa1[5] << endl;

		cout << endl << "Testing assignment operator:\n";
		pfa3 = pfa1;
		cout << "pfa3 has size " << pfa3.getNumberUsed() << " and capacity " << pfa3.size() << endl;

		cout << endl << "Testing begin and end iterators:\n";
		cout << "pfa1 elements: ";
		for (PFArray<int>::iterator it = pfa1.begin(); it != pfa1.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;

		cout << endl << "Testing cbegin and cend iterators:\n";
		cout << "pfa1 elements: ";
		for (auto it = pfa1.cbegin(); it != pfa1.cend(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;

		cout << endl << "Testing erase function:\n";
		pfa1.erase((pfa1.cbegin()));
		auto it = pfa1.cbegin();
		cout << "pfa1 elements after erase: \n";
		for (PFArray<int>::iterator it = pfa1.begin(); it != pfa1.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	{
		cout << endl << "Testing range based for loop:\n";
		PFArray<int> pfArray;
		pfArray.addElement(1);
		pfArray.addElement(2);
		pfArray.addElement(3);
		for (int &i : pfArray) {
			cout << i << endl;
		}

		cout << endl << "Testing std::find:\n";
		PFArray<int>::iterator it = std::find(pfArray.begin(), pfArray.end(), 2);
		if (it != pfArray.end()) {
			cout << "2 found in the array" << endl;
		} else {
			cout << "2 not found in the array" << endl;
		}

		cout << endl << "Testing std::for_each:\n";
		std::for_each(pfArray.begin(), pfArray.end(), [](int &i) { cout << i << endl; });

		cout << endl << "Testing std::sort:\n";
		std::sort(pfArray.begin(), pfArray.end());
		for (int &i : pfArray) {
			cout << i << endl;
		}
	}
	{

		cout << endl << "Testing default constructor:\n";
		PFArray<int> arr;

		cout << endl << "Testing addElement function:\n";
		arr.addElement(1);
		arr.addElement(2);
		arr.addElement(3);

		cout << endl << "Testing size function:\n";
		cout << "Size of array: " << arr.size() << endl; // should print 3

		cout << endl << "Testing getNumberUsed function:\n";
		cout << "Number of used elements: " << arr.getNumberUsed() << endl; // should print 3

		cout << endl << "Testing empty function:\n";
		cout << "Array is empty: " << arr.empty() << endl; // should print 0 (false)

		cout << endl << "Testing clear function:\n";
		arr.clear();
		cout << "Array is empty: " << arr.empty() << endl; // should print 1 (true)

		cout << endl << "Testing overloaded operator[] function:\n";
		arr.addElement(10);
		arr.addElement(20);
		cout << "Element at index 1: " << arr[1] << endl; // should print 20

		cout << endl << "Testing copy constructor:\n";
		PFArray<int> arr2(arr);
		cout << "Element at index 1 of copied array: " << arr2[1] << endl; // should print 20

		cout << endl << "Testing overloaded assignment operator:\n";
		PFArray<int> arr3;
		cout << "Assignment operator called.\n";
		arr3 = arr;
		cout << "Element at index 1 of assigned array: " << arr3[1] << endl; // should print 20

		cout << endl << "Testing iterator functions:\n";
		cout << "Elements of array through iterators: ";
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl; // should print 10 20

		cout << endl << "Testing erase function:\n";
		arr.erase(arr.begin());
		cout << "Elements of array after erasing first element through iterators: ";
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl; // should print 20

		cout << endl << "Testing compatibility with std::sort algorithm:\n";
		arr.addElement(15);
		arr.addElement(5);
		sort(arr.begin(), arr.end());
		cout << "Elements of array after sorting through std::sort: ";
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl; // should print 5 15 20

		cout << endl << "Testing compatibility with std::find algorithm:\n";
		auto it = find(arr.begin(), arr.end(), 15);
		if (it != arr.end()) {
			cout << "15 found in the array" << endl; // should print 15 found in the array
		} else {
			cout << "15 not found in the array" << endl;
		}

		cout << endl << "Testing compatibility with std::for_each algorithm:\n";
		for_each(arr.begin(), arr.end(), [](int &i) { cout << i << endl; });
		// should print 5 15 20
	}

	return 0;
}