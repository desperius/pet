#ifndef _PET_VIEW_H_
#define _PET_VIEW_H_

#include <QObject>
#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>

class petView : public QObject
{
    Q_OBJECT
    
public:
    explicit petView(QObject* parent = nullptr);
    ~petView();
    
    void Show();
    
signals:

public slots:
    //void ItemEdited(QListWidgetItem* item);
    void NewClicked(bool checked);
    void EditClicked(bool checked);
    void BrowseClicked(bool checked);
    
private:
    QDialog* mDialog;
    QListWidget* mList;
    QPushButton* mNewBtn;
    QPushButton* mEditBtn;
    QPushButton* mBrowseBtn;
    QPushButton* mDeleteBtn;
    QPushButton* mMoveUpBtn;
    QPushButton* mMoveDnBtn;
    QPushButton* mOkBtn;
    QPushButton* mCancelBtn;
    QGridLayout* mGrid;
};

#endif /* _PET_VIEW_H_ */