#include <iostream>
#include <vector>

using namespace std;

enum class Shape
{
	I = 'I',
	O = 'O',
	T = 'T',
	J = 'J',
	L = 'L',
	S = 'S',
	Z = 'Z',
	Empty = ' '
};

class Tetromino
{
	public:
		Tetromino(Shape shape); //initializes tetromino with given shape
		void rotate(string dir);	//rotates the tetromino
		bool canFit(Tetromino &otherOne, string pos);	//compares two tetrominos
		void printPiece();
		void setPiece(Shape shape);
		vector<vector<Shape>> getPiece();
		const Shape getType();
		void setType(Shape type);
		const Shape returnShape(char shape);
		Tetromino();
		void moveCorner();	//moves the piece to the top left in the square shaped array
	private:
		Shape _type;
		vector<vector<Shape>> _piece;
};

class Board : public Tetromino
{
	public:
		const void printBoard();
		void placePieces(vector<vector<Shape>> piece,int col, int row = 0);	//places a Tetromino to the board.
		vector<vector<Shape>>& getBoard();
		void setBoard(vector<vector<Shape>> board);
		Board(int pieceCount, vector<Tetromino> allPieces);	//constructs the game
		const int getPieceCount();
		void setPieceCount(int pieceCount);
		vector<Tetromino> getAllPieces();
		void setAllPieces(vector<Tetromino> allPieces);
	private:
		int _pieceCount;
		vector<Tetromino> _allPieces;
		vector<vector<Shape>> _board;
		static vector<vector<Shape>> placeBoard;
};