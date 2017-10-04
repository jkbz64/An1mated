#include "frameeditdialog.hpp"
#include "ui_frameeditdialog.h"

FrameEditDialog::FrameEditDialog(const QPixmap& spritesheet, AnimationFrame& frame, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FrameEditDialog),
    m_frame(frame)
{
    m_ui->setupUi(this);
    m_ui->frameEditView->setSpritesheet(spritesheet);
    m_ui->frameEditView->setRect(frame.getRect());
}

FrameEditDialog::~FrameEditDialog()
{
    delete m_ui;
}
