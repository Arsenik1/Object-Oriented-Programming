package HW.HW7;

import java.util.Vector;

public class Tetromino {
	
	private char _type;
	private Vector<Vector<Character>> _piece;
	
	public Tetromino(char shape) //initializes tetromino with given shape
		{
			_type = shape;
			_piece = new Vector<Vector<Character>>(5);
			for(int i = 0; i < 5; i++)
				_piece.add(new Vector<Character>(5));
			_piece.setSize(5);
			for(int i = 0; i < 5; i++)
				_piece.get(i).setSize(5);
			complete(_piece);
			setPiece(shape);
			trim(_piece);
		}
		public void rotate(String dir)	//rotates the tetromino
		{
			if(_type == 'O')
				return;

			int loopCount = 1;
			int height = _piece.size();
			int width = _piece.get(0).size();

			if(dir == "left")
				loopCount = 3;
			resize(_piece, 4, 4);
			Vector<Vector<Character>> rotationTemp = new Vector<Vector<Character>>(10);	
			resize(rotationTemp, _piece.size(), _piece.size());
			// System.out.println("rotationTemp size: " + rotationTemp.size() + " " + rotationTemp.get(0).size()); //DEBUG
			// System.out.println("piece size: " + _piece.size() + " " + _piece.get(0).size());
			while(loopCount-- != 0)
			{
				for(int i = 0; i < _piece.size(); i++)
					for(int j = 0; j < _piece.get(i).size(); j++)
						rotationTemp.get(j).set(i, _piece.get(i).get(j));

				int size = _piece.size();
				for(int i = 0; i < size; i++)
				{
					for(int j = 0; j < size; j++)
						_piece.get(i).set(j, rotationTemp.get(i).get(size - 1 - j));
				}
			}
			moveCorner();
			resize(_piece, width, height);
		}
		public void printPiece()
		{
			for(int i = _piece.size() - 1; i >= 0; i--)
			{
				for(int j = 0; j < _piece.get(i).size(); j++)
					System.out.print((char)_piece.get(i).get(j));
				System.out.println();
			}
		}
		public void setPiece(char shape)
		{
			if(shape == 'I')
			{
				for(int i = 0; i < 4; i++)
					_piece.get(i).set(0, 'I');
			}
			else if(shape == 'O')
			{
				_piece.get(0).set(0, 'O');
				_piece.get(0).set(1, 'O');
				_piece.get(1).set(0, 'O');
				_piece.get(1).set(1, 'O');
			}
			else if(shape == 'T')
			{
				for(int i = 0; i < 3; i++)
					_piece.get(0).set(i, 'T');
				_piece.get(1).set(1, 'T');
			}
			else if(shape == 'J')
			{
				_piece.get(0).set(0, 'J');
				_piece.get(0).set(1, 'J');
				_piece.get(1).set(1, 'J');
				_piece.get(2).set(1, 'J');
			}
			else if(shape == 'L')
			{
				for(int i = 0; i < 3; i++)
					_piece.get(i).set(0, 'L');
				_piece.get(0).set(1, 'L');
			}
			else if(shape == 'S')
			{
				_piece.get(0).set(0, 'S');
				_piece.get(0).set(1, 'S');
				_piece.get(1).set(1, 'S');
				_piece.get(1).set(2, 'S');
			}
			else if(shape == 'Z')
			{
				_piece.get(0).set(2, 'Z');
				_piece.get(0).set(1, 'Z');
				_piece.get(1).set(1, 'Z');
				_piece.get(1).set(0, 'Z');
			}
			complete(_piece);
		}
		public Vector<Vector<Character>> getPiece()
		{
			return _piece;
		}
		public char getType()
		{
			return _type;
		}
		public void setType(char type)
		{
			if(type == 'S' || type == 'Z' || type == 'O' || type == 'I' || type == 'L' || type == 'J' || type == 'T')
			_type = type;
		}
		public int height()	//returns the height of the piece
		{
			return _piece.size();
		}
		public int width()	//returns the width of the piece
		{
			return _piece.get(0).size();
		}
		public Tetromino()
		{
			_type = '*';
			_piece = new Vector<Vector<Character>>(10);
			System.out.println("\nWARNING: NO PARAMETER CONSTRUCTOR CALLED FOR TETROMINO.\n");
		}
		public void moveCorner()	//moves the piece to the top left in the square shaped array
		{
			int size = _piece.size();
			boolean up = true, left = true;
			int i, j;

			while(up || left)
			{
				for(var a : _piece.get(0))
					if(a != '*')
						up = false;
				for(int a = 0; a < size; a++)
					if(_piece.get(a).get(0) != '*')
						left = false;

				for(i = 1; i < size && up == true; i++)
					for(j = 0; j < size; j++)
						_piece.get(i - 1).set(j, _piece.get(i).get(j));
				if(up == true)
					for(i = 0; i < size && up == true; i++)
						_piece.get(size - 1).set(i, '*');

				for(i = 0; i < size && left == true; i++)
					for(j = 1; j < size; j++)
						_piece.get(i).set(j - 1, _piece.get(i).get(j));
				if(left == true)
					for(i = 0; i < size; i++)
						_piece.get(i).set(size - 1, '*');
			}
		}
		public void resize(Vector<Vector<Character>> piece, int height, int width)
		{
			if(height <= 0 || width <= 0)
				System.out.println("\nERROR - HEIGHT OR WIDTH SIZE IS TOO SMALL\n");
			piece.setSize(height);
			for(int i = 0; i < height; i++)
			{
				if(piece.get(i) == null)
				{
					piece.set(i, new Vector<Character>(width));
				}
				piece.get(i).setSize(width);
				for(int j = 0; j < width; j++)
					if(piece.get(i).get(j) == null)
						piece.get(i).set(j, '*');
			}
		}
		public void complete(Vector<Vector<Character>> piece) //fills the resized piece
		{
			int biggestWidth = 0;

			for(int i = 0; i < piece.size(); i++)
			{
				if(biggestWidth < piece.get(i).size())
					biggestWidth = piece.get(i).size();
			}

			if(biggestWidth == 0)
				System.out.println("\nERROR - MAXIMUM WIDTH OF TETROMINO IS ZERO.\n");

			for(int i = 0; i < piece.size(); i++)
			{
				if(piece.get(i) == null)
				{
					Vector<Character> temp = new Vector<Character>(biggestWidth);
					piece.set(i, temp);
				}
				for(int j = 0; j < biggestWidth; j++)
					if(piece.get(i).get(j) == null)
						piece.get(i).set(j, '*');
			}
		}
		public void trim(Vector<Vector<Character>> piece)
		{
			int count = 0;
			int newHeight = piece.size();
			int newWidth = 0;
			int tempWidth = 0;
			for(int i = piece.size() - 1; i >= 0; i--)
			{
				count = 0;
				tempWidth = 0;

				for(int j = 0; j < piece.get(i).size(); j++)
					if(piece.get(i).get(j) == '*')
						++count;
				for(int j = piece.get(i).size() - 1; j >= 0; j--)
				{
					if(piece.get(i).get(j) == '*')
						tempWidth = j;
					else
						break;
				}
				if(newWidth < tempWidth)
					newWidth = tempWidth;
				if(count == piece.get(i).size())
					--newHeight;
			}
			// System.out.println(newHeight + " " + newWidth); //DEBUG
			resize(piece, newHeight, newWidth);
		}
		public String toString()
		{
			String ret = "";
			for(int i = 0; i < _piece.size(); i++)
			{
				for(int j = 0; j < _piece.get(i).size(); j++)
					ret += _piece.get(i).get(j);
				ret += "\n";
			}
			return ret;
		}

		public static char returnShape(char shape)
		{
			switch(shape)
			{
				case 'I': return 'I';
				case 'O': return 'O';
				case 'J': return 'J';
				case 'L': return 'L';
				case 'S': return 'S';
				case 'Z': return 'Z';
				case 'T': return 'T';
				default: return '*';
			}
		}
}
