all: clean compile run

compile: main.cpp lib.cpp header.hh
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o program main.cpp lib.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./program
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f program
