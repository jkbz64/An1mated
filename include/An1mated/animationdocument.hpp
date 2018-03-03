#ifndef ANIMATIONDOCUMENT_HPP
#define ANIMATIONDOCUMENT_HPP

#include <document.hpp>
#include <animation.hpp>
#include <QPixmap>

class AnimationDocument : public Document
{
    Q_OBJECT
public:
    AnimationDocument(const QString&, const QString& = QString());
    AnimationDocument(Animation&&, const QString& = QString());
    virtual ~AnimationDocument();

    virtual bool writeToFile(const QString& = QString()) override;

    const Animation& getAnimation() const;
    const AnimationFrame& getFrame(int) const;
    const QVector<AnimationFrame>& getFrames() const;
    void addFrame(const QString&, const QRect&);
    void addFrame(const AnimationFrame&);
    void replaceFrame(int, const AnimationFrame&);
    void removeFrame(int);
    void removeFrame(const QString&);
    void moveFrame(int, int);

    void setSpritesheet(const QString&);
    QPixmap getSpritesheet() const;
signals:
    void animationChanged();
    void framesModified(const QVector<AnimationFrame>&);
    void spritesheetChanged(const QPixmap&);
    void animationNameChanged(const QString&);
public:
    Animation m_animation;
};

inline const Animation& AnimationDocument::getAnimation() const
{
    return m_animation;
}

inline QPixmap AnimationDocument::getSpritesheet() const
{
    return m_animation.getSpritesheetName();
}

inline const AnimationFrame& AnimationDocument::getFrame(int index) const
{
    if(index < m_animation.getFrames().size())
        return m_animation.getFrames()[index];
    else
    {
        static AnimationFrame nullFrame;
        return nullFrame;
    }
}

inline const QVector<AnimationFrame>& AnimationDocument::getFrames() const
{
    return m_animation.getFrames();
}

#endif
