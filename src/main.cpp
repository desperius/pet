#include "main.h"
#include <iostream>
#include <QApplication>

int main(int argc, char **argv)
{
    std::cout << "Wake up, Neo!" << std::endl;
    
    QApplication app(argc, argv);
	
    return app.exec();
}
