runMovies: movies.cpp main.cpp
	g++ --std=c++20 -Wall movies.cpp main.cpp -o runMovies

clean:
	rm runMovies