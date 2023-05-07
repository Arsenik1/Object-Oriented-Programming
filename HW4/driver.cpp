#include "Dayofyear.hh"


int main()
{
	srand((unsigned) time(NULL));
	string s1 = "f1.txt";
	string s2 = "f2.txt";
	string s3 = "f3.txt";
	string s4 = "f4.txt";
	string s5 = "f5.txt";
	string s7 = "f7.txt";
	string s8 = "f8.txt";

	ofstream file1(s1);
	ofstream file2(s2);
	ofstream file3(s3);
	ofstream file4(s4);
	ofstream file5(s5);
	ofstream file7(s7);
	ofstream file8(s8);
	int day;
	int month;
	int flag = 0;
	cout << "\033[2J" << "\033[0;0f";
	cout << "\nNOTE: IN THIS PROGRAM EACH DayOfYear OBJECT IS A NODE AND EVERY SET IS A LINKED LIST.\nYOU WILL BE ABLE TO SEE ALL THE POINTER AND DATA VALUES SINCE THIS IS A TEST PROGRAM.\n";
	cout << "\nI PREFERRED LINKED LIST DATA TYPE BECAUSE I ALREADY MADE THE PREVIOUS HOMEWORK WITH DYNAMIC ARRAYS AND IT IS EASIER TO MODIFY THE SET THIS WAY.\nALL VERSIONS OF SHOWN SETS WILL BE WRITTEN TO A FILE.\n\n\n\n";
	cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
	cout << "\033[2J" << "\033[0;0f";
	cout << "\n\n\n\n\n";
	{
		DayOfYearSet::DayOfYear doy((Month)1, 1);
		DayOfYearSet::DayOfYear tempdoy((Month)1, 1);
		DayOfYearSet set({doy});
		DayOfYearSet tempset({tempdoy});
		cout << "Test starting. 10 random days will be generated and the valid ones will be added to the set. Press Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		int iter = 10;
		while(iter-- >= 0)
		{
			month = rand() % 12 + 1;
			day = rand() % 32 + 1;
			cout << "--------------------------------------------------------------------------------\n\nTrying to create random day using	Month: " << month << "	Day: " << day << endl;
			doy.set_month((Month)month);
			doy.set_day(day);
			if(doy.is_valid())
			{
				cout << "Day is valid. Details: " ;
				cout << "\n      Dates	Status		Prev	Next------------------------------------";
				cout << doy << endl;
				set + doy;
				if(flag == 0)
				{
					++flag;
					doy.set_day(1);
					doy.set_month((Month)1);
					set - doy;
				}
			}
		}
		cout << "\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << "\n\n\nThe set created from the valid days:" << set;
		file1 << set;
		cout << "\n\nThe set above has been saved to file \""  << s1 << '"' << endl;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << "Deleting and adding random days to the set:\n";
		iter = 5;
		int index;
		while(iter-- >= 0)
		{
			day = rand() % 32 + 1;
			month = rand() % 12 + 1;
			cout << "Trying to add random day: " << day << '/' << month << endl;
			doy.set_month((Month)month);
			doy.set_day(day);
			set + doy;
			index = rand() % set.size();
			cout << "Trying to delete random day: " << set[index] <<  endl;
			set - set[index];
		}
		cout << "\n\nResult:" << set;
		file2 << set;
		cout << "\n\nThe set above has been saved to file \""  << s2 << '"' << endl;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << "Now, to show the compliment set in work, the compliment of the set will be taken 2 times which means everything shpuld be the same after 2 calls.\n";
		cout << "\n\nPress Enter to see the first call.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << !set;
		cout << "\n\nPress Enter to see the second call.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << !set;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		cout << "DayOfYear tests are complete. All of the functions have been tested more than 5 times. Time for the set tests.";
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
	}
	{
		DayOfYearSet::DayOfYear doy((Month)1, 1);
		DayOfYearSet::DayOfYear tempdoy((Month)1, 1);
		DayOfYearSet set({doy});
		DayOfYearSet tempset({tempdoy});
		cout << "Welcome to the set test. two random sets will be generated and some operations will be performed.";
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		int iter = 4;
		flag = 0;
		while(iter--)
		{
			month = rand() % 12 + 1;
			day = rand() % 32 + 1;
			doy.set_month((Month)month);
			doy.set_day(day);
			if(doy.is_valid())
			{
				set + doy;
				if(flag == 0)
				{
					++flag;
					doy.set_day(1);
					doy.set_month((Month)1);
					set - doy;
				}
			}
		}
		cout << "\n--------------------------SET 1-----------------------\n"<< set;
		file3 << set;
		cout << "\n\nThe set above has been saved to file \""  << s3 << '"' << endl;
		flag = 0;
		iter = 4;
		while(iter--)
		{
			month = rand() % 12 + 1;
			day = rand() % 32 + 1;
			tempdoy.set_month((Month)month);
			tempdoy.set_day(day);
			if(tempdoy.is_valid())
			{
				tempset + tempdoy;
				if(flag == 0)
				{
					++flag;
					tempdoy.set_day(1);
					tempdoy.set_month((Month)1);
					tempset - tempdoy;
				}
			}
		}
		cout << "\n--------------------------SET 2-----------------------\n"<< tempset;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		DayOfYearSet backset(set);
		DayOfYearSet backtempset(tempset);
		cout << "\n\nBackup created using copy constructor since we will perform multiple operations.\n";
		cout << "\nFirst, the intersection test. Since there is a low chance for these two sets to intersect, at least 2 random days will be added to both.\n\n";
		iter = 3;
		while(iter--)
		{
			month = rand() % 12 + 1;
			day = rand() % 32 + 1;
			tempdoy.set_month((Month)month);
			tempdoy.set_day(day);
			if(!tempdoy.is_valid())
				++iter;
			else
			{
				set + tempdoy;
				tempset + tempdoy;
			}
		}
		cout << "\n--------------------------SET 1-----------------------\n"<< set;
		file4 << set;
		cout << "\n\nThe set above has been saved to file \""  << s4 << '"' << endl;
		cout << "\n--------------------------SET 2-----------------------\n"<< tempset;
		set + backset;
		tempset + backtempset;
		cout << "\n\nPress Enter to see intersection.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		set ^ tempset;
		cout << "\n--------------------------INTERSECTION SET-----------------------\n"<< set;
		file5 << set;
		cout << "\n\nThe set above has been saved to file \""  << s5 << '"' << endl;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		set + backset;
		tempset + backtempset;
		cout << "\n--------------------------SET 1-----------------------\n"<< set;
		file7 << set;
		cout << "\n\nThe set above has been saved to file \""  << s7 << '"' << endl;
		cout << "\n--------------------------SET 2-----------------------\n"<< tempset;
		cout << "\n\nPress Enter to see the difference set. (SET 1 - SET 2)";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		set - tempset;
		cout << "\n--------------------------SET 1 - SET 2-----------------------\n"<< set;
		file8 << set;
		cout << "\n\nThe set above has been saved to file \""  << s8 << '"' << endl;
		cout << "\n\nPress Enter to continue.";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\033[2J" << "\033[0;0f";
		set + backset;
		tempset + backtempset;
		cout << "\n--------------------------SET 1-----------------------\n"<< set;
		cout << "\n--------------------------SET 2-----------------------\n"<< tempset;
		cout << "\n\nReturn bool value for (SET 1 == SET 2) -> " << (set == tempset) << "\n\nReturn bool value for (SET 1 != SET 2) -> " << (set != tempset) << "\n\nReturn bool value for (SET 1 == SET 1) -> " << (set == set);
		cout << "\n\nSize of SET 1: " << set.size() << "\nSize of SET 2: " << tempset.size() << endl;
		cout << "\n\n\nTEST COMPLETE. EVERYTHING IN THE CLASSES HES BEEN TESTED THOROUGHLY\nI TRIED MY BEST TO WRITE THIS PROGRAM. I TRIED TO MAKE IT USEFUL, NOT ONLY FOR ME BUT ALSO FOR EVERYONE.\nI HOPE YOU LIKED.\n\n";
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
	file5.close();
	file7.close();
	file8.close();
	return 0;
}