#ifndef ANIMATIONFRAME_HPP
#define ANIMATIONFRAME_HPP

#include <QString>
#include <QRect>
#include <QObject>

class AnimationFrame
{
public:
    AnimationFrame(const QString&, const QRect& = QRect(), float = 0.5f);
    AnimationFrame();

    const QString& getName() const;
    const QRect& getRect() const;
    const float& getDelay() const;

    void setName(const QString&);
    void setRect(const QRect&);
    void setDelay(float);
private:
    QString m_name;
    QRect m_rect;
    float m_delay;
};

inline const QString& AnimationFrame::getName() const
{
    return m_name;
}

inline const QRect& AnimationFrame::getRect() const
{
    return m_rect;
}

inline const float& AnimationFrame::getDelay() const
{
    return m_delay;
}

#endif
