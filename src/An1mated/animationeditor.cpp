#include <animationeditor.hpp>
#include "ui_animationeditor.h"

#include <animationpreview.hpp>
#include <animationdocument.hpp>

#include <QGridLayout>
#include <QLabel>

#include <QFileDialog>
#include <QTimer>

#include <frameeditdialog.hpp>

AnimationEditor::AnimationEditor(QWidget *parent)
    :
      Editor(parent),
      m_ui(new Ui::AnimationEditor)
{
    m_ui->setupUi(this);
    connect(m_ui->framesGallery, &FramesGallery::frameSelected, [this](int index)
    {
       m_ui->frameSlider->setValue(index);
    });

    connect(m_ui->frameSlider, &QSlider::valueChanged, [this](int index)
    {
        m_ui->currentFrameLabel->setText(QString::number(m_ui->frameSlider->value()));
        if(m_currentDocument)
            m_ui->animationPreview->setFrame(qobject_cast<AnimationDocument*>(m_currentDocument.get())->getFrame(index));
    });

    connect(m_ui->frameSlider, &QSlider::sliderMoved, [this](int index)
    {
       m_ui->framesGallery->selectFrame(index);
    });


    connect(m_ui->playAnimationButton, &QPushButton::released, [this]()
    {
        if(m_currentDocument)
        {
            const auto&& document = qobject_cast<AnimationDocument*>(m_currentDocument.get());
            QTimer::singleShot(document->getFrame(m_ui->frameSlider->value()).getDelay() * 1000, this, [this, document]()
            {
                m_ui->framesGallery->selectFrame(m_ui->frameSlider->value() + 1);
                if(m_ui->frameSlider->value() + 1 <= document->getFrames().size() - 1)
                    m_ui->playAnimationButton->click();
                else
                {
                    if(m_ui->loopCheckBox->isChecked())
                        QTimer::singleShot(document->getFrame(m_ui->frameSlider->value()).getDelay() * 1000, this, [this]{ m_ui->framesGallery->selectFrame(0); m_ui->playAnimationButton->click(); });
                }
            });
        }
    });

    connect(m_ui->framesGallery, &FramesGallery::newFrameRequested, this, &AnimationEditor::newFrame);
    connect(m_ui->framesGallery, &FramesGallery::editFrameRequested, this, &AnimationEditor::editFrame);
    connect(m_ui->framesGallery, &FramesGallery::frameDoubleClicked, this, &AnimationEditor::editFrame);


    //TODO connect(m_ui->framesGallery, &FramesGallery::deleteFrameRequested, this, &AnimationEditor::deleteFrame);
    /*connect(m_ui->setBackgroundButton, &QPushButton::released, this, [this]()
    {
       QString bgPath = QFileDialog::getOpenFileName(this, tr("Set background"), QDir::current().dirName(), tr("Images (*.png *.jpg)"));
       if(!bgPath.isEmpty())
           m_ui->animationPreview->setBackground(QPixmap(bgPath));
    });*/
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
        const auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        //From document
        //Spritesheet
        connect(currentDocument, &AnimationDocument::spritesheetChanged, [this](const QPixmap& spritesheet)
        {
           m_ui->animationPreview->setSpritesheet(spritesheet);
           m_ui->framesGallery->setSpritesheet(spritesheet);
        });
        //Frames
        connect(currentDocument, &AnimationDocument::framesModified, [this](const std::vector<AnimationFrame>& frames)
        {
            const int selectedFrameIndex = m_ui->framesGallery->getSelectedFrameIndex();
            m_ui->framesGallery->setFrames(frames);
            m_ui->framesGallery->selectFrame(selectedFrameIndex);
            m_ui->frameSlider->setValue(selectedFrameIndex);
            m_ui->frameSlider->setMinimum(0);
            m_ui->frameSlider->setMaximum(frames.size() - 1);
            m_ui->maxFramesLabel->setText(QString::number(frames.size() - 1));
        });
        connect(m_ui->framesGallery, &FramesGallery::frameMoved, currentDocument, &AnimationDocument::moveFrame);

        m_ui->animationPreview->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->framesGallery->setSpritesheet(currentDocument->getSpritesheet());
        m_ui->framesGallery->setFrames(currentDocument->getFrames());
        m_ui->framesGallery->selectFrame(0);
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

void AnimationEditor::editFrame(int index)
{
    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        AnimationFrame editedFrame = currentDocument->getFrame(index);
        FrameEditDialog dialog(currentDocument->getSpritesheet(), editedFrame, this);
        if(dialog.exec() == QDialog::Accepted)
            currentDocument->replaceFrame(index, editedFrame);
    }
}

