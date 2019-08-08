#include "petView.h"

#include <QFileDialog>
#include <QMessageBox>

namespace pet
{

#define RELEASE_PTR(var) do { delete var; var = nullptr; } while(0)

petView::petView(QObject* parent) 
    : QObject(parent)
    , mModel(std::make_unique<petModel>())
{
}

petView::~petView()
{    
    // Deletes only parent object here
    // because Qt handles the situation with child objects
    RELEASE_PTR(mDialog);
}

void petView::Init()
{
    if (!mModel->Init())
    {
        throw std::runtime_error("Failed to get Environment Variable value!");
    }
    
    CreateListWidget();
    CreateButtons();
    CreateGridLayout();
    CreateWinDialog();
}

void petView::Show()
{
    if (mDialog)
    {
        mDialog->show();
    }
}

void petView::CreateListWidget()
{
    mList = new QListWidget();
    
    std::list<std::string> paths = mModel->GetPaths();
        
    for (auto& path : paths)
    {
        mList->addItem(path.c_str());
    }
    
    // Makes all items editable
    for (int i = 0; i < mList->count(); ++i)
    {
        QListWidgetItem* item = mList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
    
    mList->item(0)->setSelected(true);
}

void petView::CreateButtons()
{
    mNewBtn = new QPushButton("New");
    mNewBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mNewBtn, &QPushButton::clicked, this, &petView::NewClicked);
    
    mEditBtn = new QPushButton("Edit");
    mEditBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mEditBtn, &QPushButton::clicked, this, &petView::EditClicked);
    
    mBrowseBtn = new QPushButton("Browse...");
    mBrowseBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mBrowseBtn, &QPushButton::clicked, this, &petView::BrowseClicked);
    
    mDeleteBtn = new QPushButton("Delete");
    mDeleteBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mDeleteBtn, &QPushButton::clicked, this, &petView::DeleteClicked);
    
    mMoveUpBtn = new QPushButton("Move Up");
    mMoveUpBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mMoveUpBtn, &QPushButton::clicked, this, &petView::MoveUpClicked);
    
    mMoveDnBtn = new QPushButton("Move Down");
    mMoveDnBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mMoveDnBtn, &QPushButton::clicked, this, &petView::MoveDnClicked);
    
    mOkBtn = new QPushButton("OK");
    mOkBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mOkBtn, &QPushButton::clicked, this, &petView::OkClicked);
    
    mCancelBtn = new QPushButton("Cancel");
    mCancelBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(mCancelBtn, &QPushButton::clicked, this, &petView::CancelClicked);
}

void petView::CreateGridLayout()
{
    mGrid = new QGridLayout();
    mGrid->addWidget(mList, 0, 0, 7, 4);
    mGrid->addWidget(mNewBtn, 0, 4);
    mGrid->addWidget(mEditBtn, 1, 4);
    mGrid->addWidget(mBrowseBtn, 2, 4);
    mGrid->addWidget(mDeleteBtn, 3, 4);
    mGrid->addWidget(mMoveUpBtn, 4, 4);
    mGrid->addWidget(mMoveDnBtn, 5, 4);
    
    mGrid->addWidget(mOkBtn, 7, 3);
    mGrid->addWidget(mCancelBtn, 7, 4);
}

void petView::CreateWinDialog()
{
    mDialog = new QDialog(nullptr, Qt::WindowCloseButtonHint);
    mDialog->setLayout(mGrid);
    mDialog->setWindowTitle(APP_NAME);
}

void petView::RemoveInvalidPaths()
{
    int row = 0;
    
    while (row < mList->count())
    {
        auto item = mList->item(row);
        
        if (!QDir(item->text()).exists())
        {
            delete mList->takeItem(row);
        }
        else
        {
            ++row;
        }
    }
}

void petView::NewClicked(bool checked)
{
    (void)checked;
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
    QListWidgetItem* item = mList->currentItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    mList->editItem(item);
}

void petView::BrowseClicked(bool checked)
{
    (void)checked;
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("Directory Dialog"), "", QFileDialog::ShowDirsOnly);
    
    if (!dir.isEmpty())
    {
        mList->currentItem()->setText(dir);
    }
}

void petView::DeleteClicked(bool checked)
{
    (void)checked;
    delete mList->currentItem();
}

void petView::MoveUpClicked(bool checked)
{
    (void)checked;
    int row = mList->currentRow();
    
    if ((row - 1) >= 0)
    {
        QListWidgetItem* currentItem = mList->takeItem(row);
        mList->insertItem(row - 1, currentItem);
        mList->setCurrentRow(row - 1);
    }
}

void petView::MoveDnClicked(bool checked)
{
    (void)checked;
    int row = mList->currentRow();
    
    if ((row + 1) < mList->count())
    {
        QListWidgetItem* currentItem = mList->takeItem(row);
        mList->insertItem(row + 1, currentItem);
        mList->setCurrentRow(row + 1);
    }
}

void petView::OkClicked(bool checked)
{
    (void)checked;
    
    // Ask user by message about removing clTabCtrlinvalid paths
    QMessageBox::StandardButton reply;
    const std::string msg("Invalid paths detected!\nDo you want to remove them?");
    reply = QMessageBox::question(nullptr, tr(APP_NAME), tr(msg.c_str()), QMessageBox::Yes | QMessageBox::No);
    
    if (QMessageBox::Yes == reply)
    {
        // Delete lines which does not contain a valid or existing directory path
        RemoveInvalidPaths();
    }
    
    std::list<std::string> paths;
    
    for (int i = 0; i < mList->count(); ++i)
    {
        std::string path = mList->item(i)->text().toStdString();
        
        if (QDir(path.c_str()).exists())
        {
            paths.push_back(path);
        }
    }
    
    if (mModel->Update(paths))
    {
        QMessageBox::information(nullptr, tr(APP_NAME), tr("SUCCESS"));
    }
    else
    {
        QMessageBox::critical(nullptr, tr(APP_NAME), tr("FAILURE"));
    }
}

void petView::CancelClicked(bool checked)
{
    (void)checked;
    mDialog->hide();
}

} /* namespace pet */
