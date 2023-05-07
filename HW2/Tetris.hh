#ifndef _HEADER_
#define _HEADER_
#include "Tetromino.hh"

class Tetris
{
	public:
		//in this paragraph these all are getter&setters.
		void setPieceCount(const int pieceCount);
		int getPieceCount() const;
		vector<vector<Shape>> getBoard() const;
		void setBoard(const vector<vector<Shape>> board);
		vector<vector<Shape>> getPlaceBoard() const;
		void setPlaceBoard(const vector<vector<Shape>> placeBoard);
		int getHeight() const;
		int getWidth() const;
		void placePieces(vector<vector<Shape>> piece,int col, int row = 0, int where = 1);	//places a Tetromino to the board.
		bool overlap() const;
		vector<int> fit(Tetromino &piece); //returns the fitted place of the added shape
		Tetris(const int height,const int width);
		void draw() const;
		void clearTable();
		bool add(Tetromino piece);

	private:
		int _height;
		int _width;
		int _pieceCount;
		vector<vector<Shape>> _board;
		vector<vector<Shape>> _placeBoard;
};



#endif
