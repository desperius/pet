#include "petView.h"

petView::petView() : mDialog(nullptr)
{
    mDialog = new (std::nothrow) QDialog(nullptr, Qt::WindowCloseButtonHint);
}

petView::~petView()
{
    delete mDialog;
    mDialog = nullptr;
}

void petView::Show()
{
    if (mDialog)
    {
        mDialog->show();
    }
}