all: clean driver1 driver2

driver2: driver2.cpp TetrisVector.cpp TetrisAdapter.cpp TetrisArray1D.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Compiling... Hocam durun bekleyin yavas compile ediyo bi 15 saniye falan suruyo. Compile edilirken bu yaziyi okuyabilirsiniz tesekkurler :)"
	@g++ -std=c++11 -g -O3 -o driver2 TetrisVector.cpp TetrisAdapter.cpp TetrisArray1D.cpp Tetromino.cpp driver2.cpp
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./driver2
	@echo "================================================================================="
	@echo "Completed tests...."

driver1: driver1.cpp TetrisVector.cpp TetrisAdapter.cpp TetrisArray1D.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Compiling... Hocam durun bekleyin yavas compile ediyo bi 15 saniye falan suruyo. Compile edilirken bu yaziyi okuyabilirsiniz tesekkurler :)"
	@g++ -std=c++11 -g -O3 -o driver1 TetrisVector.cpp TetrisAdapter.cpp TetrisArray1D.cpp Tetromino.cpp driver1.cpp
	@echo "-------------------------------------------"
	@echo "Running the program...."
	@echo "================================================================================="
	./driver1
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f driver1 driver2
