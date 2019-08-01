#ifndef _PET_VIEW_H_
#define _PET_VIEW_H_

#include <QObject>
#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <string>

#include "petModel.h"

namespace pet
{

class petView : public QObject
{
    Q_OBJECT
    
public:
    explicit petView(QObject* parent = nullptr);
    ~petView();
    
    petView(const petView&) = delete;
    petView(petView&&) = delete;
    
    petView& operator=(const petView&) = delete;
    petView& operator=(petView&&) = delete;
    
    void Init();
    void Show();
    
public:
    static constexpr const char* APP_NAME = "PET";
    
private:
    void CreateListWidget();
    void CreateButtons();
    void CreateGridLayout();
    void CreateWinDialog();
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
    QDialog* mDialog = nullptr;
    QListWidget* mList = nullptr;
    QPushButton* mNewBtn = nullptr;
    QPushButton* mEditBtn = nullptr;
    QPushButton* mBrowseBtn = nullptr;
    QPushButton* mDeleteBtn = nullptr;
    QPushButton* mMoveUpBtn = nullptr;
    QPushButton* mMoveDnBtn = nullptr;
    QPushButton* mOkBtn = nullptr;
    QPushButton* mCancelBtn = nullptr;
    QGridLayout* mGrid = nullptr;
    
    std::unique_ptr<petModel> mModel;
};

} /* namespace pet */

#endif /* _PET_VIEW_H_ */