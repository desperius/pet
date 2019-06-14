#include "petView.h"

#define RELEASE_PTR(var) do { delete var; var = nullptr; } while(0)

petView::petView() 
    : mDialog(nullptr)
    , mList(nullptr)
    , mNew(nullptr)
    , mEdit(nullptr)
    , mGrid(nullptr)
{
    mDialog = new (std::nothrow) QDialog(nullptr, Qt::WindowCloseButtonHint);
    
    mList = new (std::nothrow) QListWidget();
    mList->addItem("Item 0");
    mList->addItem("Item 1");
    mList->item(0)->setSelected(true);
    
    mNew = new (std::nothrow) QPushButton("New");
    mNew->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mEdit = new (std::nothrow) QPushButton("Edit");
    mEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mGrid = new (std::nothrow) QGridLayout();
    mGrid->addWidget(mList, 0, 0, 4, 4);
    mGrid->addWidget(mNew, 0, 4);
    mGrid->addWidget(mEdit, 1, 4);
    
    mDialog->setLayout(mGrid);
}

petView::~petView()
{
    RELEASE_PTR(mDialog);
    RELEASE_PTR(mList);
    RELEASE_PTR(mGrid);
}

void petView::Show()
{
    if (mDialog)
    {
        mDialog->show();
    }
}