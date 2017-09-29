#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <QString>
#include <QPixmap>
#include <animationframe.hpp>
#include <vector>

class Animation
{
public:
    Animation(const QString&);
    ~Animation() = default;

    const QString& getName() const;

    QPixmap getSpritesheet() const;

    const std::vector<AnimationFrame>& getFrames() const;

    void addFrame(const QString&, const QRect&);
    void addFrame(const AnimationFrame&);
private:
    QString m_name;
    QPixmap m_spritesheet;
    std::vector<AnimationFrame> m_frames;
};

inline const QString& Animation::getName() const
{
    return m_name;
}

inline QPixmap Animation::getSpritesheet() const
{
    return m_spritesheet;
}

inline const std::vector<AnimationFrame>& Animation::getFrames() const
{
    return m_frames;
}

#endif
