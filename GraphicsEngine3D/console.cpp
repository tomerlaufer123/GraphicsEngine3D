#include "console.h"

#define WHITE RGB(255,255,255)

console::console() {
    //get handles
    myconsole = GetConsoleWindow();
    mydc = GetDC(myconsole);
    hConsoleOutput = GetStdHandle((DWORD)-11);
    mypen = CreatePen(PS_SOLID,1,WHITE);
    if (!SelectObject(mydc, mypen))
        std::cout << "could not select pen" << std::endl;

    //hide cursor
    CONSOLE_CURSOR_INFO cursor_info;
    try {
        if (!GetConsoleCursorInfo(hConsoleOutput, (PCONSOLE_CURSOR_INFO)&cursor_info))
            throw("could not retrieve cursor info");
    }
    catch (const char msg[]) {
        std::cout << "Exception: " << msg << std::endl;
    }
    cursor_info.bVisible = !cursor_info.bVisible;
    SetConsoleCursorInfo(hConsoleOutput, (PCONSOLE_CURSOR_INFO)&cursor_info);
    //remove scroll bar (make window size = buffer size)
    try {
        //read in the window size
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        if (!GetConsoleScreenBufferInfo(hConsoleOutput, (PCONSOLE_SCREEN_BUFFER_INFO)&buffer_info))
            throw("could not get buffer info");
        //make buffer size same as window size
        const COORD buffer_coord = { buffer_info.srWindow.Right + 1, buffer_info.srWindow.Bottom + 1 };
        if (!SetConsoleScreenBufferSize(hConsoleOutput, buffer_coord))
            throw("could not set buffer size");
    }
    catch (const char msg[]) {
        std::cout << "Exception: " << msg << std::endl;
    }
}

console::~console() {
    ReleaseDC(myconsole, mydc);
    std::cin.ignore();
}

COORD console::getDimensions()
{
    BITMAP structBitmapHeader;
    memset(&structBitmapHeader, 0, sizeof(BITMAP));

    HGDIOBJ hBitmap = GetCurrentObject(mydc, OBJ_BITMAP);
    GetObject(hBitmap, sizeof(BITMAP), &structBitmapHeader);
    
    //too big to fit in coord
    try {
        if (structBitmapHeader.bmWidth > SHRT_MAX || structBitmapHeader.bmHeight > SHRT_MAX)
            throw("dimensions too large to fit in coord struct");
    }
    catch (const char msg[]) {
        std::cout << "Exception: " << msg << std::endl;
    }

    //return
    return COORD{ (short)structBitmapHeader.bmWidth, (short)structBitmapHeader.bmHeight};
}

void console::drawLine(RECT bounds)
{
    drawLine(bounds.left,bounds.top,bounds.right,bounds.bottom);
}



void console::drawLine(long x1, long y1, long x2, long y2)
{
    const POINT line[] = { {x1,y1}, {x2,y2} };
    if (!Polyline(mydc, (const POINT*)line, 2))
        std::cout << "line failed" << std::endl;
}
