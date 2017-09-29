#include <animation.hpp>

Animation::Animation(const QString &name)
    :
      QObject(nullptr),
      m_name(name)
{

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
