#ifndef NEWANIMATIONDIALOG_HPP
#define NEWANIMATIONDIALOG_HPP

#include <QDialog>

namespace Ui
{
class NewAnimationDialog;
}

class NewAnimationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAnimationDialog(QString&, QString&, QWidget *parent = 0);
    ~NewAnimationDialog();
protected:
    virtual void accept() override;
private:
    Ui::NewAnimationDialog *m_ui;
    QString &m_name;
    QString &m_spritesheetName;
};

#endif // NEWANIMATIONDIALOG_HPP
