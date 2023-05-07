all: clean driver

driver: driver.cpp SKArray.cpp
	@echo "-------------------------------------------"
	@echo "Compiling...\n"
	@g++ -std=c++11 -g -o driver driver.cpp SKArray.cpp
	@echo "-------------------------------------------"
	@echo "Running the program...."
	@echo "================================================================================="
	./driver
	@echo "\n================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f driver
