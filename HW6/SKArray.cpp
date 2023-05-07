#ifndef SKARRAY_CPP
#define SKARRAY_CPP

using namespace std;


#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

using namespace std;

namespace SKArray
{


	template<class T>
	class PFArray
	{
		public:
			class iterator
			{
			public:
				typedef forward_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T* pointer;
				typedef T& reference;

				inline iterator (shared_ptr<T> ptr, size_t index) : _ptr(ptr.get() + index) {}
				inline iterator(pointer p) : _ptr(p) {}
				inline reference operator*( ) const {return *(this->_ptr);}
				inline pointer operator->() const {return this->_ptr;}
				inline iterator& operator++() {++_ptr; return *this;}
				inline iterator& operator--() {--_ptr; return *this;}
				inline iterator operator--(int)
				{
				iterator temp(*this);
				--_ptr;
				return temp;
				}
				inline iterator operator++(int)
				{
				iterator temp(*this);
				++_ptr;
				return temp;
				}

				inline int operator-(const iterator& other) const { return _ptr - other._ptr; }
				inline iterator operator+(ptrdiff_t n) const { return iterator(_ptr + n); }
				iterator operator-(ptrdiff_t n) const { return iterator(_ptr - n); }
				bool operator<(const iterator& other) const { return _ptr < other._ptr;}


				inline iterator& operator=(const iterator &_iter){_ptr = _iter._ptr; return *this;}
				inline bool operator==(const iterator &_iter){ return (_iter._ptr == _ptr); }
				inline bool operator!=(const iterator &_iter){ return !(_iter._ptr == _ptr); }
				private:
					pointer _ptr;
			};

			PFArray( ); /* Initializes with a capacity of 50. */
			PFArray(size_t capacityValue); /* Initializes with a capacity of capacityValue. */
			PFArray(const PFArray<T>& pfaObject); /* Copy constructor. */
			PFArray(PFArray<T>&& pfaObject); /* Move constructor. */
			virtual ~PFArray( ); /* Destructor. */

			void addElement(const T& element); /* Adds an element to the end of the array. */
			bool empty( ) const; /* Returns true if the array is empty. */
			size_t size( ) const; /* Returns the capacity of the array. */
			size_t getNumberUsed( ) const; /* Returns the number of elements in the array. */
			inline void clear( ){ _used = 0; } /* Resets the number used to zero, effectively emptying the array. */
			T& operator[](size_t index); /* Returns the element at index. */
			PFArray<T>& operator =(const PFArray<T>& rightSide); /* Overloaded assignment operator. */
			PFArray<T>& operator =(PFArray<T>&& rightSide); /* Overloaded assignment operator with move function. */

			inline iterator begin() {return iterator(arr, 0);} /* Returns an iterator to the first element. */
			inline iterator end() {return iterator(arr, _used/*_size*/ );} /* Returns an iterator to the last element. */
			inline const iterator cbegin () const {return iterator(arr, 0);} /* Returns a const iterator to the first element. */
			inline const iterator cend () const {return iterator(arr, _used);} /* Returns a const iterator to the last element. */
			size_t  erase (const iterator &position);
		private:
			shared_ptr<T> arr;
			size_t _size;
			size_t _used;
	};

	

	template<class T>
	PFArray<T>::PFArray() : arr(new T[50])
	{
		_size = 50;
		_used = 0;
	}

	template<class T>
	PFArray<T>::PFArray(size_t capacityValue) : arr(new T[capacityValue])
	{
		_size = capacityValue;
		_used = 0;
		// cout << "PFArray constructor with size " << capacityValue << " called." << endl;
	}

	/*  */
	template<class T>
	PFArray<T>::PFArray(const PFArray<T>& pfaObject) :_size(pfaObject.size()), _used(pfaObject.getNumberUsed())
	{
		arr.reset(new T[_size]);
		for(int i = 0; i < _used; i++)
		{
			arr.get()[i] = pfaObject.arr.get()[i];
		}
	}
	
	template<class T>
	PFArray<T>::PFArray(PFArray<T>&& pfaObject) /* Move constructor. */
	{
		_size = pfaObject.size();
		_used = pfaObject.getNumberUsed();
		arr = move(pfaObject.arr);	//Making the object hollow so that it doesn't delete the array.
		pfaObject.arr = nullptr;
		pfaObject._size = 0;
		pfaObject._used = 0;
	}

	/* Precondition: The array is not full. Postcondition: The element has been added. */
	template<class T>
	void PFArray<T>::addElement(const T& element)
	{
		// cout << _used;
		if(_used >= _size)
		{
			_size += 10;
			shared_ptr<T> temp(new T[_size]);
			for(int i = 0; i < _used; i++)
				temp.get()[i] = arr.get()[i];
			arr = temp;
			temp = nullptr;
		}
		// cout << "Adding element " << element << " to array." << endl;
		arr.get()[_used] = element;
		++_used;
	}
	
	/* Returns true if the array is full; false, otherwise. */
	template<class T>
	bool PFArray<T>::empty() const
	{
		return (_used == 0);
	}
	
	/*  */
	template<class T>
	size_t PFArray<T>::size() const
	{
		return _size;
	}
	
	/*  */
	template<class T>
	size_t PFArray<T>::getNumberUsed() const
	{
		return _used;
	}
	
	
	template<class T>
	T& PFArray<T>::operator[](size_t index)
	{
		if(index >= _used)
			throw out_of_range("Illegal index in PFArray.\n");
		else 
			return arr.get()[index];
	}


	template<class T>
	PFArray<T>& PFArray<T>::operator=(const PFArray<T>& rightSide)
	{
		if(_size != rightSide._size)
		{
			arr.reset(new T[rightSide._size]);
		}

		_size = rightSide._size;
		_used = rightSide._used;

		for(int i = 0; i < _used; i++)
			arr.get()[i] = rightSide.arr.get()[i];

		return *this;
	}
	
	template<class T>
	PFArray<T>& PFArray<T>::operator=(PFArray<T>&& rightSide)
	{
		arr.reset();	//Deleting the array.
		_size = rightSide._size;
		_used = rightSide._used;
		arr = move(rightSide.arr);	//Making the object hollow so that it doesn't delete the array.
		rightSide.arr = nullptr;	
		rightSide._size = 0;
		rightSide._used = 0;
		return *this;
	}


	/*  */
	template<class T>
	PFArray<T>::~PFArray()
	{
		arr.reset();
	}

	template<class T>
	size_t  PFArray<T>::erase (const iterator &position)
	{
		bool found = false;
		size_t i = 0;

		for(auto iter = cbegin(); iter != cend(); ++iter)
		{
			if(iter == position)
			{
				// cout << "\nTEST\n";
				found = true;
				for(auto iter2 = iter; iter2 != cend(); ++iter2, ++i)
				{
					if(i == _used - 1)
						break;
					(*this)[i] = (*this)[i + 1];
				}
				--_used;
				break;
			}
			i++;
		}
		if(found == false)
			throw invalid_argument("Unable to find the corresponding item.\n");
		if(_used < 0 || _used > _size)
			throw out_of_range("Illegal index in PFArray.\n");

		return i;
	}

}

#endif