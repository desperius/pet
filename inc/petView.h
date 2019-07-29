#ifndef _PET_VIEW_H_
#define _PET_VIEW_H_

#include <QObject>
#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>

#include "petModel.h"

namespace pet
{

class petView : public QObject
{
    Q_OBJECT
    
public:
    explicit petView(QObject* parent = nullptr);
    ~petView();
    
    void Show();
    
private:
    void RemoveInvalidPaths();
    
signals:

public slots:
    void NewClicked(bool checked);
    void EditClicked(bool checked);
    void BrowseClicked(bool checked);
    void DeleteClicked(bool checked);
    void MoveUpClicked(bool checked);
    void MoveDnClicked(bool checked);
    void OkClicked(bool checked);
    void CancelClicked(bool checked);
    
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
    
    std::shared_ptr<petModel> mModel;
};

} /* namespace pet */

#endif /* _PET_VIEW_H_ */