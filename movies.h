// movies.h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Movie {
    public:
        Movie(const string& n, double r) {
            name = n;
            rating = r;
        }
        string getName() const {
            return name;
        }
        double getRating() const {
            return rating;
        }
    private:
        string name;
        double rating;
};

class movieStuff {
public:
    void printInAlph(const vector<Movie>& movies);
};