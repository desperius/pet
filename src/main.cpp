#include "main.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    pet::petView view;
    
    try
    {
        view.Init();
        view.Show();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, QObject::tr(pet::petView::APP_NAME), QObject::tr(e.what()));
    }
    catch (...)
    {
        QMessageBox::critical(nullptr, QObject::tr(pet::petView::APP_NAME), QObject::tr("Something went wrong :("));
    }
	
    return app.exec();
}
