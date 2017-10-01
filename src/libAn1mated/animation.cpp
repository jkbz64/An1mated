#include <animation.hpp>

Animation::Animation(const QString &name)
    :
      QObject(nullptr),
      m_name(name)
{
    m_spritesheet.load("/home/jkbz/test.png");
    m_frames.emplace_back("test1", QRect(0, 0, 64, 64));
    m_frames.emplace_back("test2", QRect(64, 0, 64, 64));
    m_frames.emplace_back("test3", QRect(128, 0, 64, 64));
    m_frames.emplace_back("test4", QRect(0, 64, 64, 64));
    m_frames.emplace_back("test5", QRect(64, 64, 64, 64));
    m_frames.emplace_back("test6", QRect(128, 64, 64, 64));
}

Animation::Animation(Animation &&animation)
    :
      QObject(nullptr),
      m_name(animation.getName()),
      m_frames(std::move(animation.m_frames))
{

}

void Animation::addFrame(const AnimationFrame &frame)
{
    m_frames.emplace_back(frame);
}

void Animation::addFrame(const QString &name, const QRect &rect)
{
    m_frames.emplace_back(name, rect);
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
