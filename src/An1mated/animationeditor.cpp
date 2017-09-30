#include <animationeditor.hpp>
#include <animationpreview.hpp>
#include <animationdocument.hpp>

#include <QGridLayout>

AnimationEditor::AnimationEditor(QWidget *parent)
    :
      Editor(parent),
      m_animationPreview(new AnimationPreview(this))
{
    QGridLayout gridLayout(this);
    gridLayout.addWidget(m_animationPreview, 0, 0, 3, 1);
}

void AnimationEditor::setDocument(std::shared_ptr<Document> doc)
{
    m_currentDocument = std::move(doc);
    if(m_currentDocument)
    {
        auto&& currentDocument = qobject_cast<AnimationDocument*>(m_currentDocument.get());
        m_animationPreview->setAnimation(currentDocument->m_animation);

    }
    else
        m_animationPreview->setAnimation(std::weak_ptr<Animation>());
}


