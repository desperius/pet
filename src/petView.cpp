#include "petView.h"

#include <QDebug>
#include <QFileDialog>

#define RELEASE_PTR(var) do { delete var; var = nullptr; } while(0)

petView::petView(QObject* parent) 
    : QObject(parent)
    , mDialog(nullptr)
    , mList(nullptr)
    , mNewBtn(nullptr)
    , mEditBtn(nullptr)
    , mBrowseBtn(nullptr)
    , mDeleteBtn(nullptr)
    , mMoveUpBtn(nullptr)
    , mMoveDnBtn(nullptr)
    , mOkBtn(nullptr)
    , mCancelBtn(nullptr)
    , mGrid(nullptr)
{
    mDialog = new (std::nothrow) QDialog(nullptr, Qt::WindowCloseButtonHint);
    
    mList = new (std::nothrow) QListWidget();
    mList->addItem("Item 0");
    mList->addItem("Item 1");
    mList->addItem("Item 2");
    
    // Makes all items editable
    for (int i = 0; i < mList->count(); ++i)
    {
        QListWidgetItem* item = mList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
    
    mList->item(0)->setSelected(true);
    
    //QObject::connect(mList, &QListWidget::itemChanged, this, &petView::ItemEdited);
    
    mNewBtn = new (std::nothrow) QPushButton("New");
    mNewBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mNewBtn, &QPushButton::clicked, this, &petView::NewClicked);
    
    mEditBtn = new (std::nothrow) QPushButton("Edit");
    mEditBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mEditBtn, &QPushButton::clicked, this, &petView::EditClicked);
    
    mBrowseBtn = new (std::nothrow) QPushButton("Browse...");
    mBrowseBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mBrowseBtn, &QPushButton::clicked, this, &petView::BrowseClicked);
    
    mDeleteBtn = new (std::nothrow) QPushButton("Delete");
    mDeleteBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mMoveUpBtn = new (std::nothrow) QPushButton("Move Up");
    mMoveUpBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mMoveDnBtn = new (std::nothrow) QPushButton("Move Down");
    mMoveDnBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mOkBtn = new (std::nothrow) QPushButton("OK");
    mOkBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mCancelBtn = new (std::nothrow) QPushButton("Cancel");
    mCancelBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mGrid = new (std::nothrow) QGridLayout();
    mGrid->addWidget(mList, 0, 0, 7, 4);
    mGrid->addWidget(mNewBtn, 0, 4);
    mGrid->addWidget(mEditBtn, 1, 4);
    mGrid->addWidget(mBrowseBtn, 2, 4);
    mGrid->addWidget(mDeleteBtn, 3, 4);
    mGrid->addWidget(mMoveUpBtn, 4, 4);
    mGrid->addWidget(mMoveDnBtn, 5, 4);
    
    mGrid->addWidget(mOkBtn, 7, 3);
    mGrid->addWidget(mCancelBtn, 7, 4);
    
    mDialog->setLayout(mGrid);
}

petView::~petView()
{
    RELEASE_PTR(mDialog);
    RELEASE_PTR(mList);
    RELEASE_PTR(mNewBtn);
    RELEASE_PTR(mEditBtn);
    RELEASE_PTR(mBrowseBtn);
    RELEASE_PTR(mDeleteBtn);
    RELEASE_PTR(mMoveUpBtn);
    RELEASE_PTR(mMoveDnBtn);
    RELEASE_PTR(mGrid);
}

void petView::Show()
{
    if (mDialog)
    {
        mDialog->show();
    }
}

//void petView::ItemEdited(QListWidgetItem* item)
//{
//    qDebug() << __func__ << "clicked";
//    qDebug() << item->text();
//    
//    if (item->text().isEmpty())
//    {
//        mList->removeItemWidget(item);
//    }
//}

void petView::NewClicked(bool checked)
{
    (void)checked;
    qDebug() << __func__ << "clicked";
    mList->addItem("");
    int count = mList->count();
    QListWidgetItem* item = mList->item(count - 1);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setSelected(true);
    mList->setCurrentItem(item);
    mList->editItem(item);
}

void petView::EditClicked(bool checked)
{
    (void)checked;
    qDebug() << __func__ << "clicked";
    QListWidgetItem* item = mList->currentItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    mList->editItem(item);
}

void petView::BrowseClicked(bool checked)
{
    (void)checked;
    qDebug() << __func__ << "clicked";
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("Directory Dialog"), "", QFileDialog::ShowDirsOnly);
    
    if (!dir.isEmpty())
    {
        mList->currentItem()->setText(dir);
    }
}
