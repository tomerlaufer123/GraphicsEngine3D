#pragma once
#include <iostream>
#include <utility>
#include <string>

using namespace std;

class matrix {
public:
	/*-----PUBLIC MEMBERS-----*/
	uint64_t r, c;
	int** data;

	/*-----CONSTRUCTORS-----*/
	//null constructor
	matrix();
	//constructor using dimensions
	matrix(uint64_t _r, uint64_t _c);
	//copy constructor
	matrix(const matrix& other);
	//destructor
	~matrix();

	/*-----UTILITY FUNCTIONS-----*/
	void operator=(const matrix& other);
	/*allows for[] and [][] access to matrix*/
	int* operator[](int index) const; 
	matrix operator*(const matrix& other) const;
	
	
	/*-----MISC FUNCTIONS-----*/
	//print matrix
	friend ostream& operator << (ostream& out, const matrix& m);
};

class matrix4x4 : public matrix {
public:
	matrix4x4() : matrix(4, 4) {}
};

class vector : public matrix {
public:
	vector(uint64_t d) : matrix(d, 1) {}
};

class coord : public vector {
public:
	coord() : vector(4) {}
};