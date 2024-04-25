#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "nonogram.h"

#define MIN_PUZZLE_SIZE 3
#define MAX_PUZZLE_SIZE 30
#define DEFAULT_PUZZLE_SIZE 10
#define UNKNOWN 2
#define DOT 1
#define SOLID 0

class SolverNonogram
{
public:
    SolverNonogram();
    ~SolverNonogram();
    void generatePuzzle();

private:
    Nonogram* ngram;

    size_t width, height;
    vector<vector<size_t>> xAxisClue;
    vector<vector<size_t>> yAxisClue;
};

