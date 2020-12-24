#ifndef ACCESS_DIALOG_H
#define ACCESS_DIALOG_H

#include <QDialog>

namespace Ui {
class access_dialog;
}

class access_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit access_dialog(QWidget *parent = nullptr);
    ~access_dialog();

private:
    Ui::access_dialog *ui;
};

#endif // ACCESS_DIALOG_H
