#ifndef _PET_VIEW_H_
#define _PET_VIEW_H_

#include <QDialog>

class petView
{
public:
    petView();
    ~petView();
    
    void Show();
    
private:
    QDialog* mDialog;
};

#endif /* _PET_VIEW_H_ */