#include <animation.hpp>

Animation::Animation(const QString &name)
    :
      QObject(nullptr),
      m_name(name)
{

}

Animation::Animation(const Animation &other)
    : QObject(this)
{
   m_name = other.m_name;
   m_frames = std::move(other.m_frames);
   m_spritesheet = other.m_spritesheet;
}

Animation::Animation(Animation &&animation)
    :
      QObject(nullptr),
      m_name(animation.getName()),
      m_frames(std::move(animation.m_frames))
{

}

void Animation::setSpritesheetName(const QString &spritesheetName)
{
    m_spritesheet = spritesheetName;
}

int Animation::getIndexOf(const QString &name)
{
    auto found = std::find_if(m_frames.begin(), m_frames.end(), [&name](const AnimationFrame& frame)
    {
        return frame.getName() == name;
    });
    if(found != m_frames.end())
        return found - m_frames.begin();
    return -1;
}

int Animation::getIndexOf(const AnimationFrame &ofFrame)
{
    auto found = std::find_if(m_frames.begin(), m_frames.end(), [&ofFrame](const AnimationFrame& frame)
    {
        return frame.getName() == ofFrame.getName();
    });
    if(found != m_frames.end())
        return found - m_frames.begin();
    return -1;
}

void Animation::addFrame(const AnimationFrame &frame)
{
    m_frames.emplace_back(frame);
}

void Animation::addFrame(const QString &name, const QRect &rect)
{
    m_frames.emplace_back(name, rect);
}

void Animation::replaceFrame(int index, const AnimationFrame &frame)
{
    m_frames[index] = frame;
}

void Animation::removeFrame(int index)
{
    if(index >= 0 && static_cast<unsigned>(index) < m_frames.size())
        m_frames.erase(m_frames.begin() + index);
}

void Animation::removeFrame(const QString &name)
{
    m_frames.erase(std::remove_if(m_frames.begin(), m_frames.end(), [&name](const AnimationFrame& frame){ return frame.getName() == name; }));
}

void Animation::moveFrameTo(int from, int to)
{
    if(to > from)
    {        
        auto fromIt = m_frames.begin() + from;
        auto toIt = m_frames.begin() + to;
        while(fromIt != toIt)
            std::iter_swap(fromIt, fromIt++);
    }

    if(to < from)
    {
        auto fromIt = m_frames.begin() + from;
        auto toIt = m_frames.begin() + to;
        while(fromIt != toIt)
            std::iter_swap(fromIt, fromIt--);
    }
}
