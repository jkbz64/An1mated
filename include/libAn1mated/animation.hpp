#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <QObject>
#include <QString>
#include <animationframe.hpp>
#include <QVector>

class Animation : public QObject
{
    Q_OBJECT
public:   
    Animation();
    Animation(const QString&, const QString& = QString());
    Animation(const Animation&);
    Animation(Animation&&);
    virtual ~Animation() = default;

    void setName(const QString&);
    void setSpritesheetName(const QString&);
    void setFrames(const QVector<AnimationFrame>& frames);
    
    const QString& getName() const;
    const QString& getSpritesheetName() const;
    const QVector<AnimationFrame>& getFrames() const;

    int getIndexOf(const QString&);
    int getIndexOf(const AnimationFrame&);

    void addFrame(const QString&, const QRect&);
    void addFrame(const AnimationFrame&);
    void replaceFrame(int, const AnimationFrame&);
    void removeFrame(int);
    void removeFrame(const QString&);

    void moveFrameTo(int, int);
private:
    QString m_name;
    QString m_spritesheet;
    QVector<AnimationFrame> m_frames;
};

inline const QString& Animation::getName() const
{
    return m_name;
}

inline const QString& Animation::getSpritesheetName() const
{
    return m_spritesheet;
}

inline const QVector<AnimationFrame>& Animation::getFrames() const
{
    return m_frames;
}

#include <Meta.h>

namespace meta
{
    template<>
    inline auto registerMembers<Animation>()
    {
        return members(
                member("name", &Animation::getName, &Animation::setName),
                member("spritesheet", &Animation::getSpritesheetName, &Animation::setSpritesheetName),
                member("frames", &Animation::getFrames, &Animation::setFrames)
        );
    }
}

#endif
