#ifndef FRAMEEDITDIALOG_HPP
#define FRAMEEDITDIALOG_HPP

#include <QDialog>
#include <animationframe.hpp>

namespace Ui
{
    class FrameEditDialog;
}

class FrameEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FrameEditDialog(const QPixmap&, AnimationFrame&, QWidget *parent = 0);
    ~FrameEditDialog();
public slots:
    void updateRectValues(const QRect&);
    virtual void accept() override;
protected:
    Ui::FrameEditDialog *m_ui;
    AnimationFrame& m_frame;
};

#endif // FRAMEEDITDIALOG_HPP
