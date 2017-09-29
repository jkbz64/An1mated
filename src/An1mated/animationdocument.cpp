#include <animationdocument.hpp>

AnimationDocument::AnimationDocument(Animation&& animation, const QString &fileName)
    :
      Document(DocumentType::AnimationDocument, fileName),
      m_animation(animation)
{
    m_object = &m_animation;
    if(fileName.isEmpty())
        setFilename(QString(animation.getName() + "*"));
}

AnimationDocument::~AnimationDocument()
{

}

bool AnimationDocument::writeToFile(const QString &fileName)
{

}
