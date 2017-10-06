#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <QObject>
#include <QString>
#include <QPixmap>
#include <animationframe.hpp>
#include <vector>

class Animation : public QObject
{
    Q_OBJECT
public:
    Animation(const QString&);
    Animation(const Animation&);
    Animation(Animation&&);
    virtual ~Animation() = default;

    const QString& getName() const;
    const QPixmap& getSpritesheet() const;
    const std::vector<AnimationFrame>& getFrames() const;

    int getIndexOf(const QString&);
    int getIndexOf(const AnimationFrame&);

    void addFrame(const QString&, const QRect&);
    void addFrame(const AnimationFrame&);
    void replaceFrame(const QString&, const AnimationFrame&);
    void removeFrame(int);
    void removeFrame(const QString&);

    void moveFrameTo(int, int);
private:
    QString m_name;
    QPixmap m_spritesheet;
    std::vector<AnimationFrame> m_frames;
};

inline const QString& Animation::getName() const
{
    return m_name;
}

inline const QPixmap& Animation::getSpritesheet() const
{
    return m_spritesheet;
}

inline const std::vector<AnimationFrame>& Animation::getFrames() const
{
    return m_frames;
}

#endif
