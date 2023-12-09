// main.cpp
// Student name: John Hagedorn
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include "movies.h"

using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);

    if (movieFile.fail()) {
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    vector<Movie> movies;

    string line, movieName;
    double movieRating;

    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)) {
        movies.emplace_back(movieName, movieRating);
    }

    movieFile.close();

    if (argc == 2) {
        sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
            return a.getName() < b.getName();
        });

        for (const Movie &movie : movies) {
            cout << movie.getName() << ", " << movie.getRating() << endl;
        }

        return 0;
    }

    ifstream prefixFile(argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    prefixFile.close();

    vector<Movie> bestMoviesByPrefix;
    set<string> usedPrefixes;

    for (const string &prefix : prefixes) {
        vector<Movie> matchingMovies;
        bool foundMovies = false;

        for (const Movie &movie : movies) {
            if (movie.getName().find(prefix) == 0) {
                matchingMovies.push_back(movie);
                foundMovies = true;
            }
        }

        if (foundMovies) {
            usedPrefixes.insert(prefix);

            sort(matchingMovies.begin(), matchingMovies.end(), [](const Movie &a, const Movie &b) {
    if (a.getRating() == b.getRating()) {
        string nameA = a.getName();
        string nameB = b.getName();
        int minLength = min(nameA.size(), nameB.size());

        for (int i = 0; i < minLength; ++i) {
            if (nameA[i] != nameB[i]) {
                return nameA[i] < nameB[i];
            }
        }

        // If we reach here, one name is a prefix of the other, so the shorter one comes first
        return nameA.size() < nameB.size();
    }

    return a.getRating() > b.getRating();
});

            for (const Movie &movie : matchingMovies) {
                cout << movie.getName() << ", " << movie.getRating() << endl;
            }
            cout << endl;

            auto highestRated = max_element(matchingMovies.begin(), matchingMovies.end(), [](const Movie &a, const Movie &b) {
                return a.getRating() < b.getRating();
            });

            bestMoviesByPrefix.push_back(*highestRated);
        } else {
            cout << "No movies found with prefix " << prefix << endl;
        }
    }

    // Print best movie for each used prefix
    for (const string &prefix : prefixes) {
        if (usedPrefixes.find(prefix) != usedPrefixes.end()) {
            auto it = find_if(bestMoviesByPrefix.begin(), bestMoviesByPrefix.end(), [&prefix](const Movie &movie) {
                return movie.getName().find(prefix) == 0;
            });

            if (it != bestMoviesByPrefix.end()) {
                cout << "Best movie with prefix " << prefix << " is: " << it->getName()
                     << " with rating " << fixed << setprecision(1) << it->getRating()
                     << endl;
            } else {
                cout << "No movies found with prefix " << prefix << endl;
            }
        }
    }
    return 0;
}

/*
Part 3a: Time Complexity (TC) Analysis: 

Iterating over Movies: loop reads movies, has TC of O(n), where n is num of movies
Sorting Movies: sorting operation has TC of O(n log n), where n is num movies
Finding Best Movie for Each Prefix: for each prefix, algorithm iterates over movies once,
inner loop complexity is O(n) with m prefixes, so the TC is O(m * n).
Printing Results: printing operation has TC O(m * k * l), where m is num of prefixes, 
k is max num of movies per prefix, and l is the max length of movie name.

The overall time complexity is O(m * n). 

Running times for prefix_large.txt:
input_20_random.csv: 350 ms
input_100_random.csv: 596 ms
input_1000_random.csv: 2,795 ms
input_76920_random.csv: 208,551 ms


Part 3b: space complexity

Space Complexity Analysis:
n: num of movies
m: num of prefixes
k: max num of movies with a prefix
l: max num of characters in a movie name

The space complexity of the algorithm is dominated by:
movies vector: O(n * l) for storing names of all movies
prefixes vector: O(m * l) for storing prefixes
matchingMovies vector: O(k * l) for storing movies with a specific prefix
bestMoviesByPrefix vector: O(m * l) for storing the best movie for each prefix
usedPrefixes set: O(m * l) for storing used prefixes

Therefore, the overall space complexity is O(n * l + m * l + k * l + m * l + m * l) = O((n + 3m + k) * l).
Since k and l are constant factors in Big-O notation, the final space complexity is O((n + m) * l).


Part 3c: tradeoffs between time/space complexity

Tradeoff:
The algorithm is designed to prioritize low time complexity by efficiently searching for movies with a specific prefix.
The space complexity is affected by storing additional data structures like vectors and sets.

Answers to Questions:
I designed the algorithm for low time complexity, but space complexity was also considered.
Achieving low space complexity was challenging due to the need to store certain prefixes and matching movies.
While I tried my best to optimize space, my main focus was on optimizing time complexity.

Overall, getting a low time complexity was prioritized over having low space complexity.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    size_t commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex + 1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
