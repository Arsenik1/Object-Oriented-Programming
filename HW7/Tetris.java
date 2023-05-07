package HW.HW7;

import java.util.Vector;

public class Tetris {
	private int _height;
	private int _width;
	private Vector<Vector<Character>> _board;
	private Vector<Vector<Character>> _placeBoard;
	private Vector<Vector<Character>> backup; //it is used for the assemble() function. when _placeBoard and _board are assembled to _placeBoard, the old version of _placeBoard is backed up in this variable.
	
	public Tetris(int height,int width)
	{
		_board = new Vector<Vector<Character>>(height);
		_placeBoard = new Vector<Vector<Character>>(height);
		backup = new Vector<Vector<Character>>(height);
		for(int i = 0; i < height; i++)
		{
			_board.add(new Vector<Character>(width));
			_placeBoard.add(new Vector<Character>(width));
			backup.add(new Vector<Character>(width));
		}
		for(int i = 0; i < height; i++)
		{
			_board.get(i).setSize(width);
			_placeBoard.get(i).setSize(width);
			backup.get(i).setSize(width);
		}

		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
			{
				_board.get(i).set(j, '*');
				_placeBoard.get(i).set(j, '*');
				backup.get(i).set(j, '*');
			}
		_width = width;
		_height = height;
	}
	public Vector<Vector<Character>> getBoard()
	{
		return _board;
	}
	public void setBoard(Vector<Vector<Character>> board)
	{
		for(int i = 0; i < _height; i++)
			for(int j = 0; j < _width; j++)
				_board.get(i).set(j, board.get(i).get(j));
	}
	public Vector<Vector<Character>> getPlaceBoard()
	{
		return _placeBoard;
	}
	public void setPlaceBoard(Vector<Vector<Character>> placeBoard)
	{
		for(int i = 0; i < _height; i++)
			for(int j = 0; j < _width; j++)
				_placeBoard.get(i).set(j, placeBoard.get(i).get(j));
	}
	public int getHeight()
	{
		return _height;
	}
	public int getWidth()
	{
		return _width;
	}
	public void placePieces(Vector<Vector<Character>> piece,int col, int row, int where)	//places a Tetromino to the board.
	{
		int size1 = piece.size();

		if(where != 0)
			for(int i = 0; i < size1; i++)
			{
				int size2 = piece.get(0).size();
				for(int j = 0; j < size2; j++)
					if(piece.get(i).get(j) != '*')
						_board.get(row + i).set(col + j, piece.get(i).get(j));
			}
		else
			for(int i = 0; i < size1; i++)
			{
				int size2 = piece.get(0).size();
				for(int j = 0; j < size2; j++)
					if(piece.get(i).get(j) != '*')
					{
						System.out.println(piece.get(i).get(j));
						_placeBoard.get(row + i).set(col + j, piece.get(i).get(j));
					}
			}
	}
	public boolean overlap() //checks overlap between _placeBoard and _board.
	{
		int size1 = getHeight(), size2;
		for(int i = 0; i < size1; i++)
		{
			size2 = getWidth();
			for(int j = 0; j < size2; j++)
			{
				if(_board.get(i).get(j) != '*' && _placeBoard.get(i).get(j) != '*')
				{
					// System.out.println("sdklvnsdvklsndvklsnvdls\nasknsak adfasd");
					// try{Thread.sleep(2000000);}catch(InterruptedException e){} //intcreased time from 50000 because it was too fast.
					return true;
				}
			}
		}
		
		return false;
	}
	public void draw(int flag)
	{
		if(flag != 0)
		{
			for(int k = 0; k < _board.get(0).size() + 2; k++)
				System.out.print('#');
			System.out.println();
			for(int i = _board.size() - 1; i >= 0; i--)
			{
				System.out.print('#');
				for(int j = 0; j < _board.get(0).size(); j++)
					System.out.print(_board.get(i).get(j));
				System.out.print('#');
				System.out.println();
			}
			for(int k = 0; k < _board.get(0).size() + 2; k++)
				System.out.print('#');
			System.out.println();
			System.out.println();
			return;
		}

		for(int k = 0; k < _placeBoard.get(0).size() + 2; k++)
			System.out.print('#');
		System.out.println();
		for(int i = _placeBoard.size() - 1; i >= 0; i--)
		{
			System.out.print('#');
			for(int j = 0; j < _placeBoard.get(0).size(); j++)
				System.out.print(_placeBoard.get(i).get(j));
			System.out.print('#');
			System.out.println();
		}
		for(int k = 0; k < _placeBoard.get(0).size() + 2; k++)
			System.out.print('#');
		System.out.println();
		return ;
	}
	public void clearTable() //clears placeBoard.
	{
		for(int i = 0; i < _placeBoard.size(); i++)
			for(int j = 0; j < _placeBoard.get(0).size(); j++)
				_placeBoard.get(i).set(j, '*');
	}
	public boolean animate(Tetromino piece, char rotateDir, int rotateCount, char moveDir, int moveCount) //after adding, it animates and places the piece.
	{
		int	height = getHeight() - piece.getPiece().size();				//setting the initial places, which means top middle in here.
		int	width = _board.get(0).size() / 2 - (piece.getPiece().get(0).size() / 2);
		
		addMiddle(piece, _placeBoard);
		if(overlap())	//initial overlap check
			return false;
		clearTable();
		

		while(rotateCount > 0)
		{
			if(rotateDir == 'L')
				piece.rotate("left");
			else if(rotateDir == 'R')
				piece.rotate("right");
			--rotateCount;
		}		//ROTATION COMPLETE
		// piece.printPiece();
		
		addMiddle(piece, _placeBoard);
		if(overlap())
			return false;
		clearTable();
	
		while(!overlap() && moveCount > 0 && width >= 0 && width < _board.get(0).size() - piece.getPiece().get(0).size())	//horizontal animation part
		{
			clearTable();
			try{Thread.sleep(200);}catch(InterruptedException e){} //intcreased time from 50000 because it was too fast.
			System.out.println("\nDSLVKNMLKVNSDV\nSDFNVKLSLKVD");
			placePieces(piece.getPiece(), width, height, 0);
			--moveCount;
			if(moveDir == 'L')
				--width;
				else if(moveDir == 'R')
				++width;
			System.out.print("\033[2J" + "\033[0;0f");
			if(assemble())
			draw(0);
			for(int i = 0; i < _height; i++)
				for(int j = 0; j < _width; j++)
				{
					char temp = backup.get(i).get(j);
					_placeBoard.get(i).set(j, temp);
				}
					// cout << "\nleft-right\n";
			try{Thread.sleep(200);}catch(InterruptedException e){} //intcreased time from 50000 because it was too fast.
		}
	
		if(height < 0 || overlap())	//this is a check for vertical animation. when going horizontal, if height somehow becomes negative or especially when an overlap occurs, it means that there is not much space left.
		{							//returning false will cause the game to end.
			if(overlap())
			{
				if(moveDir == 'L')	//restoring to the place one step before by going in reverse direction for once.
				++width;
				else if(moveDir == 'R')
				--width;
				clearTable();
				placePieces(piece.getPiece(), width, height, 0);
				assemble();
				draw(0);		//drawing the last state of the board before the game ends.
				_placeBoard = backup;
				try{Thread.sleep(300);}catch(InterruptedException e){}
			}
			clearTable();
			return false;
		}
		else //vertical animation part
		{
			while(!overlap() && height > 0) //overlapping here will not cause this function to return false because most probably game has still some room to play because it passed vertical animation part,
			{								//which means it has plenty of space.
				// cout << "\nANIMATE\n";
				clearTable();
				placePieces(piece.getPiece(), width, height, 0);
				System.out.print("\033[2J" + "\033[0;0f");
				if(assemble())	//if no overlapping occcurs when assembling _placeBoard and _board, the assembled board will be printed to the screen. this is used for the prevention of invalid draw() calls where two pieces overlap.
					draw(0);
				_placeBoard = backup;
				try{Thread.sleep(200);}catch(InterruptedException e){}
				--height;
			}
			if(overlap())
				height += 2;
			// cout << " \033[u";
			placePieces(piece.getPiece(), width, height, 1);
			clearTable();
			return true;
		}
	}
	public boolean assemble() //assembles board and placeboard into placeboard. returns true when no
	{
		backup = new Vector<Vector<Character>>(_placeBoard.size());
		for(int i = 0; i < _placeBoard.size(); i++)
			backup.add(_placeBoard.get(i));
		for(int i = 0; i < _placeBoard.size(); i++)
			for(int j = 0; j < _placeBoard.get(0).size(); j++)
				backup.get(i).set(j, _placeBoard.get(i).get(j));
		for(int i = 0; i < getHeight(); i++)
			for(int j = 0; j < getWidth(); j++)
			{
				if(_placeBoard.get(i).get(j) == '*' && _board.get(i).get(j) != '*')
					_placeBoard.get(i).set(j, _board.get(i).get(j));
				else if(_placeBoard.get(i).get(j) != '*' && _board.get(i).get(j) != '*')
					return false;
			}
		return true;
	}

	public Vector<Vector<Character>> addMiddle(Tetromino piece, Vector<Vector<Character>> place)
	{
		int middle = place.get(0).size() / 2 - (piece.getPiece().get(0).size() / 2);
		if(piece.getType() != '*')
		{
			for(int i = 0; i < piece.getPiece().size(); i++)
				{
					for(int j = 0; j < piece.getPiece().get(0).size(); j++)
						if(piece.getPiece().get(i).get(j) != '*' )
							place.get(place.size() - piece.getPiece().size() + i).set(middle + j, piece.getPiece().get(i).get(j));
				}
		}
		return place;
	}
	public void complete(Vector<Vector<Character>> piece) //fills the piece
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
	public void resize(Vector<Vector<Character>> piece, int height, int width)
	{
		if(height <= 0 || width <= 0)
			System.out.println("\nERROR - HEIGHT OR WIDTH SIZE IS TOO SMALL\n");
		piece.setSize(height);
		for(int i = 0; i < height; i++)
		{
			// if(piece.get(i) == null)
			// {
			// 	Vector<Character> temp = new Vector<Character>(width);
			// 	piece.set(i, temp);
			// }
			piece.get(i).setSize(width);
			for(int j = 0; j < width; j++)
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
}
