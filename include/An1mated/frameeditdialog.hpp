#ifndef FRAMEEDITDIALOG_HPP
#define FRAMEEDITDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class FrameEditDialog;
}

class FrameEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FrameEditDialog(QWidget *parent = 0);
    ~FrameEditDialog();

private:
    Ui::FrameEditDialog *ui;
};

#endif // FRAMEEDITDIALOG_HPP
