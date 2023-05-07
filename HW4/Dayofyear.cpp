#include "Dayofyear.hh"


namespace soy
{
DayOfYearSet::DayOfYear::DayOfYear(const Month month, const int day) : prev(nullptr), next(nullptr)
{
	set_month(month);		//catch throw can be added (to do)
	set_day(day);
}

const Month &DayOfYearSet::DayOfYear::get_month() const
{
	return _month;
}

const int &DayOfYearSet::DayOfYear::get_day() const
{
	return _day;
}

bool DayOfYearSet::DayOfYear::set_day(const int day)
{
	// cout << endl << day << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << (int)_month << endl; //DEBUG
	if(day > 0 && day <= 31)
	{
		if(day >= 28)
		{
			if(day <= 31 && (_month == Month::Jan || _month == Month::Mar || _month == Month::May 
				|| _month == Month::Jul || _month == Month::Aug || _month == Month::Oct || _month == Month::Dec))
				_day = day;
			else if(day <= 30 && (_month == Month::Apr || _month == Month::Jun || _month == Month::Sep || _month == Month::Nov))
				_day = day;
			else if(day <=29 && _month == Month::Feb)
				_day = day;
			else
			{
				// cout << "\nInvalid day insertion. Wrong date:" << day << '/' << (int)_month << endl; //can add throw and catch if seems needed
				_day = 0;
				return false;
			}
		}
		else
		{
			_day = day;
			return true;
		}
	}
	else
	{
		// cout << "\nInvalid day insertion. Wrong date:" << day << '/' << (int)_month << endl;
		_day = 0;
		return false;
	}
	return true;
}

bool DayOfYearSet::DayOfYear::set_month(const Month month)
{
	if(month <= Month::Dec && month >= Month::Jan)
	{
		_month = month;
		return true;
	}
	else
	{
		_month = Month::err;
		return false;
	}
}

DayOfYearSet::DayOfYear &DayOfYearSet::DayOfYear::operator=(const DayOfYear &doy) //only assigns the data
{
	set_month(doy.get_month());
	set_day(doy.get_day());
	return *this;
}

bool DayOfYearSet::DayOfYear::operator>(const DayOfYear &doy)
{
	if(get_month() > doy.get_month())
		return true;
	else if(get_month() == doy.get_month())
		if(get_day() > doy.get_day())
			return true;
	return false;
}

bool DayOfYearSet::DayOfYear::operator<(const DayOfYear &doy)
{
	if(get_month() < doy.get_month())
		return true;
	else if(get_month() == doy.get_month())
		if(get_day() < doy.get_day())
			return true;
	return false;
}

bool DayOfYearSet::DayOfYear::operator==(const DayOfYear &doy)
{
	if(doy.get_day() == get_day() && doy.get_month() == get_month())
		return true;
	return false;
}

bool DayOfYearSet::DayOfYear::operator!=(const DayOfYear &doy)
{
	if(*this == doy)
		return false;
	return true;
}

string DayOfYearSet::DayOfYear::is_where() //zero means prev and next are full, 1 means head, 2 means end, 3 means both are empty, 4 means it is nullptr.
{
	if(this == nullptr) //nullptr
		return "null";
	if(prev == nullptr && next != nullptr) //head
		return "head";
	if(prev != nullptr && next == nullptr) //end
		return "end";
	if(prev == nullptr && next == nullptr) //both empty
		return "both empty";
	
	return "mid"; //middle
}

DayOfYearSet::DayOfYear::~DayOfYear()
{
	// cout << endl << this->get_day() << endl << "\nnoluyo"; //DEBUG
}

DayOfYearSet::DayOfYear::DayOfYear(const DayOfYearSet::DayOfYear &doy) : prev(nullptr), next(nullptr)
{
	set_month(doy.get_month());
	set_day(doy.get_day());		//catch throw can be added (to do)
	// cout << endl<< get_day() <<"\ncopy"; //DEBUG
}

ostream &operator<<(ostream &out, DayOfYearSet::DayOfYear &doy)
{
	out << "\nDate: " << doy.get_day() << "/" <<(int)(doy.get_month());
	out << '	' << doy.is_where() << '	' << doy.prev << '	' << doy.next; //debug
	out << endl;
	return out;
}

DayOfYearSet::DayOfYear *DayOfYearSet::get_head() const
{
	return head;
}

DayOfYearSet::DayOfYearSet(initializer_list<DayOfYear> lst)
{
	DayOfYear *next;
	decltype(next) current;
	Month month;
	int day;
	int flag = 0; //skips the first element in the list since it is already saved outside the loop
	int validity_index = 0;
	// cout << "\nCONSTRUCT\n"; //DEBUG
	vector<DayOfYear> temp(lst);

	while(temp.at(validity_index).is_valid() == false && validity_index < temp.size())
		++validity_index;
	// cout << validity_index << endl; //DEBUG
	head = new DayOfYear(temp.at(validity_index).get_month(), temp.at(validity_index).get_day()); //constructing while allocating space

	// cout << "\n--------------------------\n" << head->is_where() << "\n--------------------------\n"; //DEBUG

	for(int i = validity_index + 1; i < temp.size(); i++)
	{
		if(temp.at(i).is_valid())
		{
			month = temp.at(i).get_month();
			day = temp.at(i).get_day();
			current = head;
			while(current != nullptr && temp.at(i) > *current)
				current = current->next;
			// cout << "\n--------------------------\n" << current->is_where() << "\n--------------------------\n"; //DEBUG
			if(current != nullptr && temp.at(i) == *current)
			{
				// cout << "\nayni eleman\n"; //DEBUG
				continue;
			}
			// cout << "\nhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"; //DEBUG
			if(current->is_where() == "head" || current->is_where() == "both empty") //nullptr->current
			{
				current = new DayOfYear(month, day);
				head->prev = current;
				current->next = head;
				head = current;
			}
			else if(current->is_where() == "null") //current->next->nullptr
			{
				next = head;
				while(next->next != nullptr)
					next = next->next;
				current = next;
				next = new DayOfYear(month, day);
				next->prev = current;
				current->next = next;
			}
			else if(current->is_where() == "mid" || current->is_where() == "end") //next->temp->current
			{
				DayOfYear *temp;
				temp = new DayOfYear(month, day);
				next = current->prev;
				next->next = temp;
				// cout << "\nasdasdasdasdasdasdasd\n"; //DEBUG
				temp->prev = next;
				temp->next = current;
				current->prev = temp;
			}
			else
				cout << "\nInvalid place\n";
		}
		else
			cout << "Day index: " << i + 1 << endl;
	}
	// cout << endl << get_head()->get_day() << endl;
	// cout << "\nDEBUG\n"; //DEBUG
}

DayOfYearSet::DayOfYearSet(DayOfYearSet &doy)
{
	auto current = doy.get_head(); //doy iterator;
	decltype(current) temp;
	decltype(current) tempp;
	
	tempp = new DayOfYearSet::DayOfYear(current->get_month(), current->get_day());
	head = tempp;
	current = current->next;
	while(current->is_where() != "null")
	{
		temp = new DayOfYearSet::DayOfYear(current->get_month(), current->get_day());
		temp->prev = tempp;
		tempp->next = temp;
		tempp = temp;
		current = current->next;
	}
	// cout << "haha" << *this;
}


bool DayOfYearSet::operator==(DayOfYearSet &set)
{
	// cout << "\n\nTEST\n\n"; //DEBUG
	DayOfYearSet::DayOfYear *temp_one;
	int equal_count = 0;
	DayOfYearSet::DayOfYear *temp_two;
	int size_one = size();
	int size_two = set.size();

	temp_one = get_head();
	temp_two = set.get_head();
	
	if(size_one == size_two)
	{
		while(temp_one != nullptr)
		{
			temp_two = set.get_head();
			while(temp_two != nullptr)
			{
				if(*temp_one  == *temp_two)
				{
					++equal_count;
					break;
				}
				temp_two = temp_two->next;
			}
			temp_one = temp_one->next;
		}
		if(equal_count == size())
			return true;
	}
	return false;
}

bool DayOfYearSet::operator!=(DayOfYearSet &set)
{
	if(*this == set)
		return false;
	return true;
}

int DayOfYearSet::size()
{
	DayOfYear *temp;
	temp = head;
	int size = 0;

	while(temp != nullptr)
	{
		++size;
		temp = temp->next;
	}
	return size;
}

bool DayOfYearSet::remove(DayOfYearSet::DayOfYear &doy)
{
	auto current = head;
	decltype(current) pre;
	decltype(current) nex;

	while(current->is_where() != "null")
	{
		if(*current == doy)
		{
			if(current->is_where() == "head")
			{
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
				return true;
			}
			else if(current->is_where() == "mid")
			{
				pre = current->prev;
				nex = current->next;
				current->prev = nullptr;
				current->next = nullptr;
				delete current;
				pre->next = nex;
				nex->prev = pre;
				return true;
			}
			else if(current->is_where() == "end")
			{
				// cout << "\nREMOVE\n"; //DEBUG
				pre = current->prev;
				current->prev = nullptr;
				current->next = nullptr;
				delete current;
				pre->next = nullptr;
				return true;
			}
		}
		current = current->next;
	}
	return false;
}

DayOfYearSet::DayOfYear *DayOfYearSet::find(const DayOfYearSet::DayOfYear &doy)
{
	DayOfYearSet::DayOfYear *current = head;
	// cout << "\nFINDER\n";
	while(current->is_where() != "null")
	{
		if(*current == doy)
			return current;
		current = current->next;
	}
	return nullptr;
}

bool DayOfYearSet::DayOfYear::is_valid()
{
	if(get_day() == 0 || get_month() == Month::err)
	{
		cout << "\nInvalid day insertion. Wrong date:" << get_day() << '/' << (int)get_month() << endl;
		return false;
	}
	return true;
}


DayOfYearSet::~DayOfYearSet()
{
	// cout << "\nDestructor\n"; //DEBUG
	// cout << head->get_day() << endl; //DEBUG

	// while(temp->next != nullptr)
	// {
	// 	// cout << temp->get_day() << endl; //DEBUG
	// 	temp = temp->next;
	// }
	while(head->next != nullptr)
	{
		head = head->next;
		delete head->prev;
	}
	delete head;
	// cout << "destruct\n"; //DEBUG
}

ostream &operator<<(ostream &out, DayOfYearSet &set)
{
	DayOfYearSet::DayOfYear *temp;
	temp = set.get_head();
	cout << "\n      Dates	Status	Prev		Next------------------------------------\n";
	while(temp != nullptr)
	{
		out << *temp;
		temp = temp->next;
	}
	// out << temp;
	return out;
}

DayOfYearSet &DayOfYearSet::operator+(DayOfYearSet::DayOfYear doy)
{
	if(doy.is_valid())
		{
			Month month = doy.get_month();
			int day = doy.get_day();
			auto *current = head;
			decltype(current) next;

			while(current != nullptr && doy > *current)
				current = current->next;
			// cout << "\n--------------------------\n" << current->is_where() << "\n--------------------------\n"; //DEBUG
			if(current != nullptr && doy == *current)
			{
				// cout << "\nayni eleman\n"; //DEBUG
				return *this;
			}
			// cout << "\nhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"; //DEBUG
			if(current->is_where() == "head" || current->is_where() == "both empty") //nullptr->current
			{
				current = new DayOfYearSet::DayOfYear(month, day);
				head->prev = current;
				current->next = head;
				head = current;
			}
			else if(current->is_where() == "null") //current->next->nullptr
			{
				next = head;
				while(next->next != nullptr)
					next = next->next;
				current = next;
				next = new DayOfYear(month, day);
				next->prev = current;
				current->next = next;
			}
			else if(current->is_where() == "mid" || current->is_where() == "end") //next->temp->current
			{
				DayOfYear *temp;
				temp = new DayOfYear(month, day);
				next = current->prev;
				next->next = temp;
				// cout << "\nasdasdasdasdasdasdasd\n"; //DEBUG
				temp->prev = next;
				temp->next = current;
				current->prev = temp;
			}
			else
				cout << "\nInvalid place\n";
		}
	return *this;
}
void DayOfYearSet::operator=(DayOfYearSet &doy)
{
	auto temp = head;	//*this iterator
	auto current = doy.get_head(); //doy iterator
	// cout << "aaaaaaaaaaaaaaaaaLLLLLLLLLLL\n"; //DEBUG
	while(current->is_where() != "null")
	{
		if(temp->is_where() == "end" || temp->is_where() == "both empty") //both empty means the list contains only one element
		{
			if(current->is_where() != "end")
			{
				temp->next = new DayOfYearSet::DayOfYear(current->next->get_month(), current->next->get_day());
			}
			else
				*temp = *current;
		}
		else if(temp->is_where() == "head" || temp->is_where() == "mid")
		{
			*temp = *current;
		}
		temp = temp->next;
		current = current->next;
	}
	temp->prev->next = nullptr;
	while(temp->next->is_where() != "null")
	{
		temp = temp->next;
		delete temp->prev;
	}
	delete temp;
}

DayOfYearSet &DayOfYearSet::operator+(const DayOfYearSet &set) //union
{
	DayOfYear *current = set.get_head();

	while(current->is_where() != "null")
	{
		*this + *current;
		current = current->next;
	}
	return *this;
}

DayOfYearSet &DayOfYearSet::operator-(const DayOfYearSet &set) //difference
{
	DayOfYear *current = set.get_head();

	while(current->is_where() != "null")
		{
			remove(*current);
			current = current->next;
		}
		return *this;
}

DayOfYearSet &DayOfYearSet::operator-(const DayOfYear doy) //difference
{
	DayOfYear *temp = head;
	while(temp->is_where() != "null")
	{
		if(*temp == doy)
		{
			remove(*temp);
			break;
		}
		temp = temp->next;
	}
	return *this;
}

DayOfYearSet &DayOfYearSet::operator^(DayOfYearSet set) //intersection
{
	DayOfYear *temp = head;


	while(temp->is_where() != "null")
	{
		// cout << "\n---------------------------\ninterSECT\n" << *temp << temp->is_where() << temp->prev << ' ' << temp << '	' << temp->next << endl; //DEBUG
		if(set.find(*temp)->is_where() == "null") //if it couldnt find the corresponding value in the other set, the element is ereased.
		{
			*this - *temp;
			temp = head;
		}
		temp = temp->next;
	}
	return *this;
}

DayOfYearSet &DayOfYearSet::operator!()
{
	DayOfYear doy(Month::Jan, 1);
	for(int month = (int)Month::Jan; month <= (int)Month::Dec; month++)
	{
		for(int day = 1; day <= 31; day++)
		{
			doy.set_month((Month)month);
			if(day >= 28)
			{
				if(day <= 31 && ((Month)month == Month::Jan || (Month)month == Month::Mar || (Month)month == Month::May 
					|| (Month)month == Month::Jul || (Month)month == Month::Aug || (Month)month == Month::Oct || (Month)month == Month::Dec))
						doy.set_day(day);
				else if(day <= 30 && ((Month)month == Month::Apr || (Month)month == Month::Jun || (Month)month == Month::Sep || (Month)month == Month::Nov))
						doy.set_day(day);
				else if(day <=29 && (Month)month == Month::Feb)
						doy.set_day(day);
				// else cout << day<< ' '<<month << endl;
			}
			else
				doy.set_day(day);
			if(find(doy)->is_where() != "null") //if it finds the day, it is removed. if it can't find, value is added.
				*this - doy;
			else
				*this + doy;
		}
	}
	return *this;
}

DayOfYearSet::DayOfYear &DayOfYearSet::operator[](int index)
{
	auto temp = head;

	while(index-- > 0 && temp->is_where() != "null")
		temp = temp->next;
	return *temp;
}

}