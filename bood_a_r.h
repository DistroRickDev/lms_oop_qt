#ifndef BOOD_A_R_H
#define BOOD_A_R_H

#include <QDialog>

namespace Ui {
class Bood_A_R;
}

class Bood_A_R : public QDialog
{
    Q_OBJECT

public:
    explicit Bood_A_R(QWidget *parent = nullptr);
    ~Bood_A_R();

private:
    Ui::Bood_A_R *ui;
};

#endif // BOOD_A_R_H
