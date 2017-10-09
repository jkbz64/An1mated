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

AnimationDocument::AnimationDocument(Animation&& animation, const QString &fileName)
    :
      Document(DocumentType::AnimationDocument, fileName),
      m_animation(std::move(animation))
{
    m_object = &m_animation;

    if(fileName.isEmpty())
        setFilename(QString(m_animation.getName() + "*"));
}

void AnimationDocument::setSpritesheet(const QString &spritesheetName)
{
    m_animation.setSpritesheetName(spritesheetName);
    emit spritesheetChanged(getSpritesheet());
}

AnimationDocument::~AnimationDocument()
{

}

bool AnimationDocument::writeToFile(const QString&)
{
    return true;
}

void AnimationDocument::addFrame(const QString &frame, const QRect &rect)
{
    m_animation.addFrame(frame, rect);
    emit frameAdded(m_animation.getFrames().back());
}

void AnimationDocument::addFrame(const AnimationFrame &frame)
{
    m_animation.addFrame(frame);
    emit frameAdded(m_animation.getFrames().back());
}

void AnimationDocument::replaceFrame(int index, const AnimationFrame& newFrame)
{
    m_animation.replaceFrame(index, newFrame);
    emit frameChanged(index);
}

void AnimationDocument::removeFrame(int index)
{
    m_animation.removeFrame(index);
}

void AnimationDocument::removeFrame(const QString &name)
{
    m_animation.removeFrame(name);
}

void AnimationDocument::moveFrame(int from, int to)
{
    m_animation.moveFrameTo(from, to);
}
