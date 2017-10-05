#include <animation.hpp>

Animation::Animation(const QString &name)
    :
      QObject(nullptr),
      m_name(name)
{
    m_spritesheet.load("/home/jkbz/test.png");
    m_frames.emplace_back("test2", QRect(64, 0, 64, 64));
    m_frames.emplace_back("test1", QRect(0, 0, 1000, 1000));
    m_frames.emplace_back("test3", QRect(128, 0, 64, 64));
    m_frames.emplace_back("test4", QRect(0, 64, 64, 64));
    m_frames.emplace_back("test5", QRect(64, 64, 64, 64));
    m_frames.emplace_back("test6", QRect(128, 64, 64, 64));
}

Animation::Animation(const Animation &other)
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

void Animation::replaceFrame(const QString& name, const AnimationFrame &frame)
{
    std::replace_if(m_frames.begin(), m_frames.end(), [&name](const AnimationFrame& f)
    {
        return f.getName() == name;
    }, frame);
}

void Animation::removeFrame(int index)
{
    if(index >= 0 && index < m_frames.size())
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
        auto toIt = m_frames.begin() + to + 1;
        while(fromIt != toIt)
            std::iter_swap(fromIt, fromIt--);
    }
}
