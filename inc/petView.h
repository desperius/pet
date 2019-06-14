#ifndef _PET_VIEW_H_
#define _PET_VIEW_H_

#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>

class petView
{
public:
    petView();
    ~petView();
    
    void Show();
    
private:
    QDialog* mDialog;
    QListWidget* mList;
    QPushButton* mNew;
    QPushButton* mEdit;
    QGridLayout* mGrid;
};

#endif /* _PET_VIEW_H_ */