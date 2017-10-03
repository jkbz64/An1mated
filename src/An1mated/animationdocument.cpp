#include <animationdocument.hpp>

AnimationDocument::AnimationDocument(const QString &animationName, const QString &fileName)
    :
      Document(DocumentType::AnimationDocument, fileName),
      m_animation(animationName)
{
    m_object = &m_animation;
    if(fileName.isEmpty())
        setFilename(QString(m_animation.getName() + "*"));
}

AnimationDocument::AnimationDocument(const Animation& animation, const QString &fileName)
    :
      Document(DocumentType::AnimationDocument, fileName),
      m_animation(animation)
{
    m_object = &m_animation;
    if(fileName.isEmpty())
        setFilename(QString(m_animation.getName() + "*"));
}

AnimationDocument::~AnimationDocument()
{

}

bool AnimationDocument::writeToFile(const QString &fileName)
{

}
