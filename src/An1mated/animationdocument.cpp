#include <animationdocument.hpp>

AnimationDocument::AnimationDocument(std::shared_ptr<Animation> animation, const QString &fileName)
    :
      Document(DocumentType::AnimationDocument, fileName),
      m_animation(std::move(animation))
{
    m_object = m_animation.get();
    if(fileName.isEmpty())
        setFilename(QString(m_animation->getName() + "*"));
}

AnimationDocument::~AnimationDocument()
{

}

bool AnimationDocument::writeToFile(const QString &fileName)
{

}
