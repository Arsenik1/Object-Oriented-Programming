#ifndef __TWOD__
#define __TWOD__

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib> //to generate random number.
#include <time.h> //random number seed is taken from here.
#include <unistd.h> //to sleep the program.
#include <limits> //used only in tester

using std::cout;
using std::cin;
using std::endl;
using std::string;


#define INT_MAX 2147483647

namespace Stetris
{
	enum class Shape
	{
		I = 'I',
		O = 'O',
		T = 'T',
		J = 'J',
		L = 'L',
		S = 'S',
		Z = 'Z',
		Empty = '*'
	};

	class Tetromino;

	class TwoD
	{
	public:
		TwoD(Shape); //creates the specified Shape's array.
		TwoD(int height, int width, Shape defaultVal = Shape::Empty); 
		TwoD();
		~TwoD();
		const int getRow() const;
		const int getCol() const;
		Shape** getVec() const;
		void setCol(int);
		void setRow(int);
		bool resize(int height, int width, Shape defaultVal = Shape::Empty); //resizes as expected, maybe better.
		void setPiece(Shape shape);
		TwoD& operator+=(Tetromino&); //adds the piece to the top middle
		Shape& operator[](int);
		TwoD& operator=(TwoD&);
		Shape*& at(const int) const;
		Shape& at(const int row, const int col) const; //since we cannot use templates, to acces the second dimension's elements, TwoD::at() function has been overloaded to overcome this.
	private:
		int _width; //holding the size variables.
		int _height;
		Shape **_vec; //main holder
	};
}
#endif