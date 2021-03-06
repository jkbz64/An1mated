#include <animationframe.hpp>

AnimationFrame::AnimationFrame()
    : m_name(""),
      m_rect(QRect()),
      m_delay(0.5)
{

}

AnimationFrame::AnimationFrame(const QString &frameName, const QRect &rect, float delay)
    :
      m_name(frameName),
      m_rect(rect),
      m_delay(delay)
{

}

void AnimationFrame::setName(const QString &name)
{
    m_name = name;
}

void AnimationFrame::setRect(const QRect &rect)
{
    m_rect = rect;
}

void AnimationFrame::setDelay(float delay)
{
    m_delay = delay;
}
