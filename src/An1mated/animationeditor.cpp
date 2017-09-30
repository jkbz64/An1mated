#include <animationeditor.hpp>
#include "ui_animationeditor.h"

#include <animationpreview.hpp>
#include <animationdocument.hpp>

#include <QGridLayout>
#include <QLabel>


AnimationEditor::AnimationEditor(QWidget *parent)
    :
      Editor(parent),
      m_ui(new Ui::AnimationEditor)
{
    m_ui->setupUi(this);
}

void AnimationEditor::setDocument(std::shared_ptr<Document> doc)
{
    m_currentDocument = std::move(doc);
    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        m_ui->m_animationPreview->setAnimation(currentDocument->m_animation);

    }
    else
        m_ui->m_animationPreview->setAnimation(std::weak_ptr<Animation>());
}


