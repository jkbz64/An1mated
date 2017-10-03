#include <animationeditor.hpp>
#include "ui_animationeditor.h"

#include <animationpreview.hpp>
#include <animationdocument.hpp>

#include <QGridLayout>
#include <QLabel>

#include <QFileDialog>

AnimationEditor::AnimationEditor(QWidget *parent)
    :
      Editor(parent),
      m_ui(new Ui::AnimationEditor)
{
    m_ui->setupUi(this);

    connect(m_ui->m_framesGallery, &FramesGallery::frameSelected, [this](int index)
    {
        m_ui->m_animationPreview->setFrame(qobject_cast<AnimationDocument*>(m_currentDocument.get())->getFrame(index));
    });


    connect(m_ui->m_setBackgroundButton, &QPushButton::released, this, [this]()
    {
       QString bgPath = QFileDialog::getOpenFileName(this, tr("Set background"), QDir::current().dirName(), tr("Images (*.png *.jpg)"));
       if(!bgPath.isEmpty())
           m_ui->m_animationPreview->setBackground(QPixmap(bgPath));
    });
}

AnimationEditor::~AnimationEditor()
{
    delete m_ui;
}

void AnimationEditor::setDocument(std::shared_ptr<Document> doc)
{
    if(m_currentDocument && m_currentDocument != doc) // Disconnect old document from this editor
        m_currentDocument->disconnect();

    m_currentDocument = std::move(doc);

    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        connect(currentDocument, &AnimationDocument::spritesheetChanged, m_ui->m_animationPreview, &AnimationPreview::setSpritesheet);
        connect(currentDocument, &AnimationDocument::spritesheetChanged, m_ui->m_framesGallery, &FramesGallery::setSpritesheet);
        connect(currentDocument, &AnimationDocument::framesModified, m_ui->m_framesGallery, &FramesGallery::setFrames);

        m_ui->m_animationPreview->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->m_framesGallery->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->m_framesGallery->setFrames(currentDocument->getFrames());
    }
    else
    {
        m_ui->m_animationPreview->setSpritesheet();
        m_ui->m_framesGallery->setSpritesheet();
        m_ui->m_framesGallery->setFrames();
    }
}


