#include "matrix.h"

matrix::matrix(){
	r = c = 0;
	data = nullptr;
}

matrix::matrix(uint64_t _r, uint64_t _c) : r(_r), c(_c) {
	data = new int* [(size_t)r];
	for (int i = 0; i < r; i++) {
		data[i] = new int[(size_t)c];
		for (int j = 0; j < c; j++)
			data[i][j] = 0;
	}
}

matrix::matrix(const matrix& other) {
	r = other.r;
	c = other.c;
	data = new int* [(size_t)r];
	for (int i = 0; i < r; i++) {
		data[i] = new int[(size_t)c];
		for (int j = 0; j < c; j++)
			data[i][j] = 0;
	}
}

void matrix::operator=(const matrix& other)
{
	r = other.r;
	c = other.c;
	data = new int* [(size_t)r];
	for (int i = 0; i < r; i++) {
		data[i] = new int[(size_t)c];
		for (int j = 0; j < c; j++)
			data[i][j] = 0;
	}
}

matrix::~matrix() {
	for (int i = 0; i < r; i++)
		delete[] data[i];
	delete[] data;
}

int* matrix::operator[](int index) const
{
	return this->data[index];
}

matrix matrix::operator*(const matrix& other) const{
	//dimension mismatch
	try {
		if (c != other.r)
			throw "matrix dimension mismatch";
	}
	catch (const char msg[]) {
		std::cout << "Exception: " << msg << std::endl;
	}
	//otherwise allocate
	uint64_t r_new = r, c_new = other.c;
	matrix result(r_new,c_new);

	//multiply
	for (int i = 0; i < r_new; i++) {
		for (int j = 0; j < c_new; j++) {
			for (int k = 0; k < c; k++) {
				result[i][j] += data[i][k] * other[k][j];
			}
		}
	}
	return result;
}

ostream& operator<<(ostream& out, const matrix& m)
{
	for (int i = 0; i < m.r; i++) {
		out << "|\t";
		for (int j = 0; j < m.c; j++)
			out << m[i][j] << "\t\t";
		out << "|"<<endl;
	}
	return out;
}
