#ifndef BOOKSELECTIONFILTER_H
#define BOOKSELECTIONFILTER_H

#include <QDialog>

namespace Ui {
class BookSelectionFilter;
}

class BookSelectionFilter : public QDialog
{
    Q_OBJECT

public:
    explicit BookSelectionFilter(QWidget *parent = nullptr);
    ~BookSelectionFilter();

private:
    Ui::BookSelectionFilter *ui;
};

#endif // BOOKSELECTIONFILTER_H
