#ifndef __TETRIS_VECTOR_HH__
#define __TETRIS_VECTOR_HH__

#include "AbstractTetris.hh"

class TetrisVector : public AbstractTetris
{
public:
	TetrisVector(const int height,const int width);
	TetrisVector(const TetrisVector& other);
	TetrisVector& operator=(const TetrisVector& other);

	void readFromFile(const std::string& filename) override;
	void writeToFile(const std::string& filename) override;
	TetrominoMove lastMove() const override;
	int numberOfMoves() const override;

	vector<vector<Shape>>& getBoard();
	void setBoard(const vector<vector<Shape>> board);
	vector<vector<Shape>>& getPlaceBoard();
	void setPlaceBoard(vector<vector<Shape>>& placeBoard) override;
	int getHeight() const override;
	int getWidth() const override;
	void placePieces(vector<vector<Shape>> &piece,int col, int row = 0, int where = 1);	//places a Tetromino to the board.
	bool overlap(); //checks overlap between _placeBoard and _board.
	void draw(int flag = 1) override;
	void clearTable() override; //clears placeBoard.
	bool animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) override; //after adding, it animates and places the piece.
	bool assemble() override; //assembles board and placeboard into placeboard. returns true when no overlap happens
	void operator+=(Tetromino&) override; //adds the piece to the top middle
	const int getPieceCount() const;
	TetrominoMove getLastMove() const;
	void setLastMove(TetrominoMove lastMove);
	void setNumberOfMoves(int numberOfMoves);
	void syncBoard(); //syncs the _board and _placeBoard
	void del_line() override; //deletes filled lines

private:
	int _width;
	int _height;
	int _pieceCount;
	int _numberOfMoves;
	TetrominoMove _lastMove;
	vector<vector<Shape>> _board;
	vector<vector<Shape>> _placeBoard;
	vector<vector<Shape>> backup; //it is used for the assemble() function. when _placeBoard and _board are assembled to _placeBoard, the old version of _placeBoard is backed up in this variable.
};

#endif