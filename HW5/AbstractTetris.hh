#ifndef __ABSTRACT_TETRIS_HH__
#define __ABSTRACT_TETRIS_HH__

#include "Tetromino.hh"

struct TetrominoMove
{
	Tetromino piece;
	char rotateDir;
	char moveDir;
	int moveCount;
	int rotateCount;
};

class AbstractTetris
{
public:
	// Pure virtual function to draw the Tetris board
	virtual void draw(int flag = 1) = 0;

	// Pure virtual function to read the Tetris game from a file
	virtual void readFromFile(const std::string& filename) = 0;

	// Pure virtual function to write the Tetris game to a file
	virtual void writeToFile(const std::string& filename) = 0;

	// Pure virtual function to add a Tetromino to the board
	virtual void operator+=(Tetromino& tetromino) = 0;

	// Pure virtual function to animate the Tetromino dropping to the bottom of the board
	virtual bool animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) = 0;

	// Pure virtual function to return the last move
	virtual TetrominoMove lastMove() const = 0; 

	// Pure virtual function to return the number of moves
	virtual int numberOfMoves() const = 0;

	//Pure virtual function to set the placeBoard
	virtual void setPlaceBoard(vector<vector<Shape>>& placeBoard) = 0;

	//Pure virtual function to clear the board
	virtual void clearTable() = 0;

	//Pure virtual function to sync the board
	virtual void syncBoard() = 0;

	//Pure virtual function to get the width
	virtual int getWidth() const = 0;

	//Pure virtual function to get the height
	virtual int getHeight() const = 0;

	//Pure virtual function to assemble the boards together into the placeBoard
	virtual bool assemble() = 0;

	//Pure virtual function to erease filled line
	virtual void del_line() = 0;
};

#endif