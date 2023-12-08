// movies.cpp

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "movies.h"

using namespace std;

void movieStuff::printInAlph(const vector<Movie>& movies) {
    vector<Movie> sortedMovies = movies; // sort in alphabetical order
    sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
        return a.getName() < b.getName();
    });
    for (const Movie& movie : sortedMovies) {
        cout << movie.getName() << ",  " << movie.getRating() << endl;
    }
}
