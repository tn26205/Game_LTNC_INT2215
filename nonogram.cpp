#include "nonogram.h"

/*Nonogram::Nonogram(int w, int h) : width(w), height(h), solids(0), dots(0), field(new size_t[h]) {
if ((xAxis = (vector<size_t>**)malloc(width * sizeof(vector<size_t>*))) == NULL ||
		(yAxis = (vector<size_t>**)malloc(height * sizeof(vector<size_t>*))) == NULL) {
	cerr << "ERROR: Malloc failed." << endl;
	exit(1);
 }
	generateField();
	generatePuzzle();
}*/// malloc tronng C
// Chuyen sang vector trong C++

Nonogram::Nonogram(int w, int h) : width(h), height(h), solids(0), dots(0), field(h)
{
    xAxis.resize(width);
    yAxis.resize(height);

    generateField();
    generatePuzzle();
}


Nonogram::~Nonogram() {
	/*delete[] field;
	for (size_t i = 0; i < width; ++i) {
		delete xAxis[i];
	}
	for (size_t i = 0; i < height; ++i) {
		delete yAxis[i];
	}
	free(xAxis);
	free(yAxis);*/ //Khong can giai phong bo nho vi vector tu dong giai phong
}

const vector<vector<size_t>>& Nonogram::getXAxis() const{
	return xAxis;
}

const vector<vector<size_t>>& Nonogram::getYAxis() const{
	return yAxis;
}

const vector<size_t>& Nonogram::getField() const{
	return field;
}

// Prints the puzzle. Mostly usable for debugging.
void Nonogram::print() {
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = (1 << (width - 1)); j > 0; j >>= 1) {
			if (field[i] & j) {
				cout << "X";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

// Generates the puzzle (i.e. the numbers shown to the user) from the existing field.
void Nonogram::generatePuzzle() {
	size_t temp;
	for (size_t i = 0; i < height; ++i) {
		temp = 0;
		//yAxis[i] = new vector<size_t>;
		for (size_t j = (1 << (width - 1)); j > 0; j >>= 1) {
			if (!(field[i] & j)) {
				if (temp > 0) {
					yAxis[i].push_back(temp);
				}
				temp = 0;
			}
			else {
				++temp;
			}
		}
		if (temp > 0 || yAxis[i].empty()) {
			yAxis[i].push_back(temp);
		}
	}
	size_t mask = 1 << width;
	for(size_t i = 0; i < width; ++i) {
		mask >>= 1;
		//xAxis[i] = new vector<size_t>;
		temp = 0;
		for (size_t j = 0; j < height; ++j) {
			if (!(field[j] & mask)) {
				if (temp > 0) {
					xAxis[i].push_back(temp);
				}
				temp = 0;
			}
			else {
				++temp;
			}
		}
		if (temp > 0 || xAxis[i].empty()) {
			xAxis[i].push_back(temp);
		}
	}
}

// Generate a semi-random playing field.
void Nonogram::generateField() { // tao ra mot truong choi dua tren mot so xac suat va quy tac nhat dinh
	int random, above, left;
	size_t mask = 1 << (width - 1);
	double prob;
	srand(time(NULL)); // khoi tao sheet ngau nhien dua tren tg htai
	for (size_t i = 0; i < height; ++i) {
		field[i] = 0;
		for (size_t j = mask; j > 0; j >>=1) {
			if (i == 0) {
				above = -1; //dai dien cho dong tren do
			}
			else {
				above = ((field[i - 1] & j) > 0);
			}
			if (j == mask) { //ktra xem bit trai co ton tai k
				left = -1;
			}
			else {
				left = ((field[i] & (j << 1)) > 0);
			}
			prob = probability(above, left); //tinh xac suat cua viec bit tiep theo tren dong hien tai se la mau den
			random = rand();
			if (random > prob * RAND_MAX) {
				++dots;
			}
			else {
				field[i] |= j;
				++solids;
			}
		}
	}
}

/* Calculates the probability for the next block being black.
	 The purpose of this function is to have the generated field be random, but
	 not too random. We want a (roughly) 50-50 split between white and black fields,
	 and we'd rather see that the black & white fields are (again roughly) collected
	 in "islands" rather than a chessboard-type distribution.
*/
double Nonogram::probability(int above, int left) { // tinh xac suat cho cac khoi tiep theo se la mau den(solid block)
	double p = 0.5;
	switch (above + left) { // tinh xac suat dua tren tong gtri bit tren dong va gia tri bit ben trai gia tri hien tai
	case -2: // ca hai o xq (trai va tren)deu la mau trang
	case 1:  // co chinh xac mot o xq mau den
		break;
	case -1: // xq 1 den va 1 trang
		p = 0.25;
		break;
	case 0: // khong co o nao xung quanh la den
		if (above == 0) {// o tren dong truoc do la trang
			p = 0.1;
		}
		else {
			p = 0.75;
		}
		break;
	case 2: // ca hai deu la mau den
		p = 0.9;
		break;
	}
	p += (1.0 / (width * height)) * (dots - solids);
	// 1.0/(width*height) phan tram cua toan bo truong choi ma moi o dong gop vao su thay doi cua xac suat p
	return p;
}
