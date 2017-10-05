#ifndef ANIMATIONDOCUMENT_HPP
#define ANIMATIONDOCUMENT_HPP

#include <document.hpp>
#include <animation.hpp>
#include <memory>

class AnimationDocument : public Document
{
    Q_OBJECT
public:
    AnimationDocument(const QString&, const QString& = QString());
    AnimationDocument(const Animation&, const QString& = QString());
    virtual ~AnimationDocument();

    virtual bool writeToFile(const QString& = QString()) override;

    const AnimationFrame& getFrame(int) const;
    const std::vector<AnimationFrame>& getFrames() const;
    void addFrame(const QString&, const QRect&);
    void addFrame(const AnimationFrame&);
    void replaceFrame(const QString&, const AnimationFrame&);
    void removeFrame(int);
    void removeFrame(const QString&);

    void setSpritesheet();
    const QPixmap& getSpritesheet() const;
signals:
    void animationChanged();
    void frameAdded(const AnimationFrame&);
    void frameChanged(int);
    void framesModified(const std::vector<AnimationFrame>&);
    void spritesheetChanged(const QPixmap&);
    void animationNameChanged(const QString&);
public:
    Animation m_animation;
};

inline const QPixmap& AnimationDocument::getSpritesheet() const
{
    return m_animation.getSpritesheet();
}

inline const AnimationFrame& AnimationDocument::getFrame(int index) const
{
    return m_animation.getFrames()[index];
}

inline const std::vector<AnimationFrame>& AnimationDocument::getFrames() const
{
    return m_animation.getFrames();
}


#endif
