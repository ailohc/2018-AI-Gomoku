all:

	g++ header.hpp -o header
	g++ gomoku.cpp -o gomoku


make clean:

	rm -rf header
	rm -rf ai

run:

	./gomoku

 
