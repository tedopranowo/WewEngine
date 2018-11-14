#include <Application.h>
#include <iostream>
#include <conio.h>
#include <vld.h>

int main()
{
    Application apps;
    apps.Run("Assets/main.wdata");

    std::cout << "Press any key to continue..." << std::endl;
    _getch();

    return 0;
}