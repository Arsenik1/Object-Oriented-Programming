all: clean driver1 driver2

driver2: driver2.cpp Tetris.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o driver2 driver2.cpp Tetris.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./driver2
	@echo "================================================================================="
	@echo "Completed tests...."

driver1: driver1.cpp Tetris.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o driver1 driver1.cpp Tetris.cpp Tetromino.cpp
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
