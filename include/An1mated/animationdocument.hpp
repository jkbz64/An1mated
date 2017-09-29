#ifndef ANIMATIONDOCUMENT_HPP
#define ANIMATIONDOCUMENT_HPP

#include <document.hpp>
#include <animation.hpp>
#include <bits/unique_ptr.h>

class AnimationDocument : public Document
{
    Q_OBJECT
public:
    AnimationDocument(Animation&&, const QString& fileName = QString());
    virtual ~AnimationDocument();

    virtual bool writeToFile(const QString& = QString()) override;
signals:
    void animationChanged();
    void animationNameChanged(const QString&);

    /*
    //Frame signals
    void currentFrameChanged(Frame*);
    void frameAdded(Frame*);
    void frameRemoved(Frame*);
    void frameModified(Frame*);

    //Spritesheet signals
    //TODO
    */

private:
    Animation& m_animation;
};



#endif
