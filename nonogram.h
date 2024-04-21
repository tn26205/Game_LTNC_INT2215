#ifndef NONOGRAM_H
#define NONOGRAM_H
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "solver.h"

class Nonogram {
 private:
	size_t width, height;
	int solids, dots;
	vector<size_t> field;
	vector<vector<size_t>> xAxis;
	vector<vector<size_t>> yAxis;
	void generateField();
	void generatePuzzle();
	double probability(int above, int left);

 public:
	Nonogram(int w, int h);
	~Nonogram();
	void print();
	const vector<vector<size_t>> &getXAxis() const;
	const vector<vector<size_t>> &getYAxis()const;
	const vector<size_t>& getField() const;
};
#endif
