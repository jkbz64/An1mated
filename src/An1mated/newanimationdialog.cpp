#include "newanimationdialog.hpp"
#include "ui_newanimationdialog.h"
#include <QMessageBox>
#include <QFileDialog>

NewAnimationDialog::NewAnimationDialog(QString& name, QString& spritesheetName, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NewAnimationDialog),
    m_name(name),
    m_spritesheetName(spritesheetName)
{
    m_ui->setupUi(this);
    connect(m_ui->animationNameLineEdit, &QLineEdit::textChanged, [this](const QString& newName){ m_name = newName; });
    connect(m_ui->spritesheetSelectToolButton, &QToolButton::released, [this]()
    {
       QString newName = QFileDialog::getOpenFileName(parentWidget(), tr("Select spritesheet image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));
       if(!newName.isEmpty())
       {
           m_ui->spritesheetSelectToolButton->setText(newName);
           m_spritesheetName = newName;
       }
    });
}

NewAnimationDialog::~NewAnimationDialog()
{
    delete m_ui;
}

void NewAnimationDialog::accept()
{
    if(!m_name.isEmpty() && !m_spritesheetName.isEmpty())
        QDialog::accept();
    else
        QMessageBox::warning(parentWidget(), tr("Failed to create new animation"), tr("Animation name or spritesheet is empty"), QMessageBox::Ok);
}
