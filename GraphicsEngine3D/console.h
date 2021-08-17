#pragma once
#include<windows.h>
#include<winuser.h>
#include<iostream>
#include<wingdi.h>

class console {
private:
	HWND myconsole;
	HDC mydc;
	HANDLE hConsoleOutput;
	HPEN mypen;
public:
	//constructors
	console();
	~console();
	//utility functions
	COORD getDimensions();
	void drawLine(RECT bounds);
	void drawLine(long x1, long x2, long y1, long y2);
};