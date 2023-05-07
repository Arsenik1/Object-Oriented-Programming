#include "Tetromino.hh"
#ifndef _TETRIS_
#define _TETRIS_

namespace Stetris
{
	class Tetris
	{
		public:
			//in this paragraph these all are getter&setters.
			Tetris(const int height,const int width);
			TwoD& getBoard();
			void setBoard(const TwoD board);
			TwoD& getPlaceBoard();
			void setPlaceBoard(TwoD& placeBoard);
			int getHeight() const;
			int getWidth() const;
			void placePieces(TwoD &piece,int col, int row = 0, int where = 1);	//places a Tetromino to the board.
			bool overlap(); //checks overlap between _placeBoard and _board.
			void draw(int flag = 1);
			void clearTable(); //clears placeBoard.
			bool animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount); //after adding, it animates and places the piece.
			bool assemble(); //assembles board and placeboart into placeboard. returns true when no

		private:
			int _height;
			int _width;
			int _pieceCount;
			TwoD _board;
			TwoD _placeBoard;
			TwoD backup; //it is used for the assemble() function. when _placeBoard and _board are assembled to _placeBoard, the old version of _placeBoard is backed up in this variable.
	};
}

using namespace Stetris; //defined it in here because it is the end of the namespace declaration chain.

#endif
