#include "matrix.h"
#include "console.h"


int main() {
	console c;

	COORD crd = c.getDimensions();
	c.drawLine(RECT{ 0, 0, crd.X, crd.Y });
	cout << "done!" << endl;
}