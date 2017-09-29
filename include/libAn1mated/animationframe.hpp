#ifndef ANIMATIONFRAME_HPP
#define ANIMATIONFRAME_HPP

#include <QString>
#include <QRect>

class AnimationFrame
{
public:
    AnimationFrame(const QString&, const QRect& = QRect());

    const QString& getName() const;
    const QRect& getRect() const;

    void setName(const QString&);
    void setRect(const QRect&);
private:
    QString m_name;
    QRect m_rect;
};

inline const QString& AnimationFrame::getName() const
{
    return m_name;
}

inline const QRect& AnimationFrame::getRect() const
{
    return m_rect;
}


#endif
