all: clean driver

driver:  driver.cpp Dayofyear.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -g -o driver driver.cpp  Dayofyear.cpp  
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./driver
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f driver
