#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib> //to generate random number.
#include <time.h> //random number seed is taken from here.
#include <unistd.h> //to sleep the program.
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std;

#define INT_MAX 2147483647


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


class Tetromino
{
	public:
		Tetromino(const Shape shape); //initializes tetromino with given shape
		void rotate(string dir = "right");	//rotates the tetromino
		bool canFit(Tetromino &otherOne, string pos);	//compares two tetrominos, used in hw1 but not in hw2 so it has been deleted. it has no use here so it wont also be tested in driver2.
		void printPiece() const;

		void setPiece(Shape shape);
		vector<vector<Shape>> &getPiece();
		Shape getType() const;
		void setType(Shape type);
		int height() const;	//returns the height of the piece
		int width() const;	//returns the width of the piece

		static Shape returnShape(char shape); //returns the corresponding char
		Tetromino();
		void moveCorner();	//moves the piece to the top left in the square shaped array
		vector<Shape> &operator[](int index);	//returns the piece in the given index
	private:
		Shape _type;
		vector<vector<Shape>> _piece;
};