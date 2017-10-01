#ifndef ANIMATIONDOCUMENT_HPP
#define ANIMATIONDOCUMENT_HPP

#include <document.hpp>
#include <animation.hpp>
#include <memory>

class AnimationDocument : public Document
{
    Q_OBJECT
public:
    AnimationDocument(std::shared_ptr<Animation>, const QString& = QString());
    virtual ~AnimationDocument();

    virtual bool writeToFile(const QString& = QString()) override;
signals:
    void animationChanged();
    void animationNameChanged(const QString&);

    /*
    //Frame signals
    void frameAdded(Frame*);
    void frameRemoved(Frame*);
    void frameModified(Frame*);

    //Spritesheet signals
    //TODO
    */

public:
    std::shared_ptr<Animation> m_animation;
};



#endif
