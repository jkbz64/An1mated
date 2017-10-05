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

void AnimationDocument::addFrame(const QString &frame, const QRect &rect)
{
    m_animation.addFrame(frame, rect);
    emit frameAdded(m_animation.getFrames().back());
}

void AnimationDocument::addFrame(const AnimationFrame &frame)
{
    m_animation.addFrame(frame);
    emit frameAdded(frame);
}

void AnimationDocument::replaceFrame(const QString& name, const AnimationFrame& newFrame)
{
    m_animation.replaceFrame(name, newFrame);
    emit frameChanged(m_animation.getIndexOf(name));
}

void AnimationDocument::removeFrame(int index)
{
    m_animation.removeFrame(index);
}

void AnimationDocument::removeFrame(const QString &name)
{
    m_animation.removeFrame(name);
}

