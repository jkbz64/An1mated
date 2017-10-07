#include <animationeditor.hpp>
#include "ui_animationeditor.h"

#include <animationpreview.hpp>
#include <animationdocument.hpp>

#include <QGridLayout>
#include <QLabel>

#include <QFileDialog>

#include <frameeditdialog.hpp>

AnimationEditor::AnimationEditor(QWidget *parent)
    :
      Editor(parent),
      m_ui(new Ui::AnimationEditor)
{
    m_ui->setupUi(this);

    connect(m_ui->framesGallery, &FramesGallery::frameSelected, m_ui->animationPreview, &AnimationPreview::setFrame);
    connect(m_ui->setBackgroundButton, &QPushButton::released, this, [this]()
    {
       QString bgPath = QFileDialog::getOpenFileName(this, tr("Set background"), QDir::current().dirName(), tr("Images (*.png *.jpg)"));
       if(!bgPath.isEmpty())
           m_ui->animationPreview->setBackground(QPixmap(bgPath));
    });

    connect(m_ui->newFrameButton, &QPushButton::released, this, &AnimationEditor::newFrame);
    connect(m_ui->framesGallery, &FramesGallery::frameDoubleClicked, this, &AnimationEditor::editFrame);
}

AnimationEditor::~AnimationEditor()
{
    delete m_ui;
}

void AnimationEditor::setDocument(std::shared_ptr<Document> doc)
{
    if(m_currentDocument) // Disconnect old document from this editor
    {
        m_currentDocument->disconnect();
        //TODO fix it better
        disconnect(m_ui->framesGallery, &FramesGallery::frameMoved, m_currentDocument.get(), 0);
    }

    m_currentDocument = std::move(doc);

    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        //From document
        connect(currentDocument, &AnimationDocument::spritesheetChanged, m_ui->animationPreview, &AnimationPreview::setSpritesheet);
        connect(currentDocument, &AnimationDocument::spritesheetChanged, m_ui->framesGallery, &FramesGallery::setSpritesheet);
        connect(currentDocument, &AnimationDocument::frameAdded, m_ui->framesGallery, &FramesGallery::addFrame);
        connect(currentDocument, &AnimationDocument::framesModified, m_ui->framesGallery, &FramesGallery::setFrames);
        connect(currentDocument, &AnimationDocument::frameChanged, [this, currentDocument](int index)
        {
            m_ui->framesGallery->updateFrame(index, currentDocument->getFrame(index));
        });
        //To document
        connect(m_ui->framesGallery, &FramesGallery::frameMoved, currentDocument, &AnimationDocument::moveFrame);

        m_ui->animationPreview->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->framesGallery->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->framesGallery->setFrames(currentDocument->getFrames());
    }
    else
    {
        m_ui->animationPreview->reset();
        m_ui->framesGallery->reset();
    }
}

void AnimationEditor::newFrame()
{
    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        AnimationFrame frame("");
        FrameEditDialog dialog(currentDocument->getSpritesheet(), frame, this);
        if(dialog.exec() == QDialog::Accepted)
            currentDocument->addFrame(frame);
    }
}

void AnimationEditor::editFrame(const AnimationFrame& frame)
{
    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        AnimationFrame editedFrame = frame;
        FrameEditDialog dialog(currentDocument->getSpritesheet(), editedFrame, this);
        if(dialog.exec() == QDialog::Accepted)
            currentDocument->replaceFrame(frame.getName(), editedFrame);
    }
}

