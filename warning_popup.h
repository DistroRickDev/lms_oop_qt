#ifndef WARNING_POPUP_H
#define WARNING_POPUP_H

#include <QDialog>

namespace Ui {
class warning_popup;
}

class warning_popup : public QDialog
{
    Q_OBJECT

public:
    explicit warning_popup(QWidget *parent = nullptr);
    ~warning_popup();

private:
    Ui::warning_popup *ui;
};

#endif // WARNING_POPUP_H
