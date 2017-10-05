#include <animationframe.hpp>

AnimationFrame::AnimationFrame(const QString &frameName, const QRect &rect)
    :
      m_name(frameName),
      m_rect(rect)
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
