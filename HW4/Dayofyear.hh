#ifndef __DYEAR__
#define __DYEAR__

#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h> //to sleep the program.
#include <initializer_list>
#include <limits> //to use press enter to continue on the test code.
#include <cstdlib>
#include <ctime>
#include <fstream>

#define INT_MAX 2147483647

using std::ostream;
using std::string;
using std::initializer_list;
using std::ofstream;

enum class Month
{
	err = 0,
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};

using namespace std;
namespace soy
{
	class DayOfYearSet
	{
	public:
		class DayOfYear
		{
		public:
			explicit DayOfYear(const Month month,const int day);	//Requested constructor in the pdf
			~DayOfYear();	//does nothing since this class cannot allocate anything
			DayOfYear(const DayOfYearSet::DayOfYear &doy);	//copy constructor, makes deep copy
			const Month &get_month() const;	//moth getter
			const int &get_day() const;	//day getter
			bool set_day(const int day);	//day setter
			bool set_month(const Month  month);	//month setter
			DayOfYear &operator=(const DayOfYear &doy);	//deeply assigns one object to another
			bool operator==(const DayOfYear &doy);	//checks if it is the same date or not
			bool operator!=(const DayOfYear &doy);
			bool operator<(const DayOfYear &doy);	//check if the date is later or not
			bool operator>(const DayOfYear &doy);
			string is_where();	//returns where the node is at
			friend ostream &operator<<(ostream &out, DayOfYear &doy); //printing
			bool is_valid();	//returns if it contains a valid date or not

			DayOfYear *prev; //I have looked up on the Internet and found out that these two pointers are mostly held in the public region of classes
			DayOfYear *next; //nothing will be allocated to these pointers so no user defined constructor is needed.
		private:
			Month _month;
			int _day;
		};
		void operator=(DayOfYearSet &doy);	//deeply assigns one set to the other
		explicit DayOfYearSet(initializer_list<DayOfYear> lst);	//list initializer constructor
		DayOfYearSet(DayOfYearSet &doy);	//deep copy constructor
		friend ostream &operator<<(ostream &out, DayOfYearSet &set);	//printing
		bool operator==(DayOfYearSet &set);	//as pdf requests
		bool operator!=(DayOfYearSet &set); //as pdf requests
		~DayOfYearSet();	//deallocates all of the linked list
		DayOfYear *get_head() const;	//head pointer getter
		int size();	//as pdf requests
		bool remove(DayOfYear &doy); //as pdf requests
		DayOfYear *find(const DayOfYear &doy); //finds the corresponding DayOfYear from the linked list and returns its address. if it can't find it, returns nullptr.
		DayOfYearSet &operator+(const DayOfYear doy);	//as pdf requests
		DayOfYearSet &operator+(const DayOfYearSet &set);	//as pdf requests
		DayOfYearSet &operator-(const DayOfYearSet &set);	//as pdf requests
		DayOfYearSet &operator-(const DayOfYear doy);	//as pdf requests
		DayOfYearSet &operator^(DayOfYearSet set);	//as pdf requests
		DayOfYearSet &operator!();	//as pdf requests
		DayOfYear &operator[](int index);	//as pdf requests
	private:
		DayOfYear *head; //as pdf requests, all data is stored in this pointer. the only way to access the data is through here. 
	};
	ostream &operator<<(ostream &out, DayOfYearSet &set);	//these two are used for multiple calls in cout. when only defined in class without using friend, only one parameter can be added
	ostream &operator<<(ostream &out, DayOfYearSet::DayOfYear &doy);	//so making this a friend function is necessary.
}

using namespace soy;

#endif