#include "main.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::unique_ptr<pet::petView> view;

    try
    {
        view = std::make_unique<pet::petView>();
        view->Init();
        view->Show();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, QObject::tr(pet::petView::APP_NAME), QObject::tr(e.what()));
        return EXIT_FAILURE;
    }
    catch (...)
    {
        QMessageBox::critical(nullptr, QObject::tr(pet::petView::APP_NAME), QObject::tr("Something went wrong :("));
        return EXIT_FAILURE;
    }

    return app.exec();
}
