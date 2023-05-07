#include "TwoD.hh"

#ifndef __TETROMINO__
#define __TETROMINO__

namespace Stetris
{
	class Tetromino
	{
		public:
			Tetromino(const Shape shape); //initializes tetromino with given shape
			void rotate(string dir = "right");	//rotates the tetromino
			void printPiece();

			void setPiece(Shape shape);
			TwoD& getPiece();
			Shape getType() const;
			void setType(Shape type);

			static Shape returnShape(char shape); //returns the corresponding char
			Tetromino();
			void moveCorner();	//moves the piece to the top left in the square shaped array
			friend class TwoD;
		private:
			Shape _type;
			TwoD _piece;
	};
}
#endif
