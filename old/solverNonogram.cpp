#include "SolverNonogram.hpp"

SolverNonogram::SolverNonogram()
{
}

SolverNonogram::~SolverNonogram()
{
}

/*void SolverNonogram::generatePuzzle()
{
    ngram = new Nonogram(width, height);
	xAxisClue = ngram->getXAxis();
	yAxisClue = ngram->getYAxis();
	Solver* solv = new Solver(width, height, xAxisClue, yAxisClue);

	// Retry puzzle creation until we get a solvable one.
	while (!solv->solve()) {
		delete solv;
		delete ngram;
		ngram = new Nonogram(width, height);
		xAxisClue = ngram->getXAxis();
		yAxisClue = ngram->getYAxis();
		solv = new Solver(width, height, xAxisClue, yAxisClue);
	}
	delete solv;

	// Create and add the clue labels
	int spacer_x = 0;
	int spacer_y = 0;
	for (int i = 0; i < width; ++i) {
		string str = "";
        string num = "";
		for (size_t j = 0; j < xAxisClue[i].size(); ++j) {
			num = to_string(xAxisClue[i][j]);
			str.append(num);
			if (j < xAxisClue[i].size() - 1) {
				str.append("\n");
			}
		}
		xAxis.push_back(str);
		xAxis.at(i)->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
		// We want to separate the UI buttons in 5 x 5 chunks, so that counting
		// blocks becomes easier for the user.
		if (i > 0 && i % 5 == 0) {
			++spacer_x;
			grid->setColumnMinimumWidth(i + spacer_x, 2);
		}
		grid->addWidget(xAxis.at(i), 0, i + spacer_x + 1);
	}
}*/
