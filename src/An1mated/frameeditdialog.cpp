#include "frameeditdialog.hpp"
#include "ui_frameeditdialog.h"
#include <QMessageBox>

FrameEditDialog::FrameEditDialog(const QPixmap& spritesheet, AnimationFrame& frame, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FrameEditDialog),
    m_frame(frame)
{
    m_ui->setupUi(this);
    m_ui->frameNameEdit->setText(frame.getName());
    connect(m_ui->frameEditView, &FrameEditView::rectModified, this, &FrameEditDialog::updateRectValues);
    connect(m_ui->xSpin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value)
    {
       m_ui->frameEditView->setRect(QRect(value, m_frame.getRect().y(), m_frame.getRect().width(), m_frame.getRect().height()));
    });

    connect(m_ui->ySpin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value)
    {
       m_ui->frameEditView->setRect(QRect(m_frame.getRect().x(), value, m_frame.getRect().width(), m_frame.getRect().height()));
    });

    connect(m_ui->wSpin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value)
    {
       m_ui->frameEditView->setRect(QRect(m_frame.getRect().x(), m_frame.getRect().y(), value, m_frame.getRect().height()));
    });

    connect(m_ui->hSpin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value)
    {
       m_ui->frameEditView->setRect(QRect(m_frame.getRect().x(), m_frame.getRect().y(), m_frame.getRect().width(), value));
    });

    connect(m_ui->frameNameEdit, &QLineEdit::textChanged, [this, &frame](const QString& name)
    {
        frame.setName(name);
    });

    m_ui->xSpin->setMaximum(spritesheet.width());
    m_ui->ySpin->setMaximum(spritesheet.height());
    m_ui->wSpin->setMaximum(spritesheet.width());
    m_ui->hSpin->setMaximum(spritesheet.height());

    m_ui->frameEditView->setSpritesheet(spritesheet);
    m_ui->frameEditView->setRect(frame.getRect());
}

FrameEditDialog::~FrameEditDialog()
{
    delete m_ui;
}

void FrameEditDialog::updateRectValues(const QRect& rect)
{
    m_ui->xSpin->setValue(rect.x());
    m_ui->ySpin->setValue(rect.y());
    m_ui->wSpin->setValue(rect.width());
    m_ui->hSpin->setValue(rect.height());
    m_frame.setRect(QRect(m_ui->xSpin->value(), m_ui->ySpin->value(), m_ui->wSpin->value(), m_ui->hSpin->value()));
}

void FrameEditDialog::accept()
{
    if(!m_ui->frameNameEdit->text().isEmpty())
        QDialog::accept();
    else
        QMessageBox::warning(this, tr("Empty frame name"), tr("Frame name is not specified, cannot create/modify frame"), QMessageBox::Ok);
}
