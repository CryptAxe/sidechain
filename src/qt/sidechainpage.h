#ifndef SIDECHAINPAGE_H
#define SIDECHAINPAGE_H

#include <QWidget>

namespace Ui {
class SidechainPage;
}

class SidechainPage : public QWidget
{
    Q_OBJECT

public:
    explicit SidechainPage(QWidget *parent = 0);
    ~SidechainPage();

private Q_SLOTS:
    void on_pushButtonWithdraw_clicked();

    void on_pushButtonDeposit_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonNew_clicked();

private:
    Ui::SidechainPage *ui;
};

#endif // SIDECHAINPAGE_H
