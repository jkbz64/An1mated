#include <animation.hpp>

Animation::Animation(const QString &name)
    :
      m_name(name)
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
