#ifndef __TETRIS_ARRAY_1D_HH__
#define __TETRIS_ARRAY_1D_HH__

#include "AbstractTetris.hh"

class TetrisArray1D : public AbstractTetris
{
public:
	TetrisArray1D(const int height,const int width);
	TetrisArray1D();
	TetrisArray1D(const TetrisArray1D& other);
	TetrisArray1D& operator=(const TetrisArray1D& other);
	~TetrisArray1D();

	void draw(int flag = 1) override;
	void readFromFile(const std::string& filename) override;
	void writeToFile(const std::string& filename) override;
	void operator+=(Tetromino& tetromino) override;
	bool animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) override;
	TetrominoMove lastMove() const override;
	int numberOfMoves() const override;

	const int size() const;
	const int getRow() const;
	const int getCol() const;
	int getHeight() const override {return _height;}
	int getWidth() const override {return _width;}
	Shape* getBoard() const;
	void setCol(int);
	void setRow(int);
	bool resize(int height, int width, Shape defaultVal = Shape::Empty); //resizes as expected, maybe better.
	Shape& operator[](int);
	TetrisArray1D& operator=(TetrisArray1D&);
	Shape& at(const int) const;
	Shape& at(const int row, const int col) const; //since we cannot use templates, to acces the second dimension's elements, TetrisArray1D::at() function has been overloaded to overcome this.
	
	bool assemble() override; //assembles board and placeboart into placeboard. returns true when no
	void clearTable(); //clears placeBoard.
	bool overlap(); //checks overlap between _placeBoard and _board.
	void placePieces(Tetromino &piece,int col, int row = 0, int where = 1);	//places a Tetromino to the board.
	TetrisArray1D& getPlaceBoard();
	void setPlaceBoard(vector<vector<Shape>> &placeBoard) override {_placeBoard = placeBoard;}
	void setBoard(const TetrisArray1D board);
	TetrisArray1D& getBoard();
	void syncBoard() override; //syncs the _board and _placeBoard
	void del_line() override; //deletes filled lines

private:
	int _width; //holding the size variables.
	int _height;
	Shape *_board; //main holder
	vector<vector<Shape>> _placeBoard; //for the place function.
	vector<vector<Shape>> backup;
	int _pieceCount;
	int _numberOfMoves;
	TetrominoMove _lastMove;
};

#endif