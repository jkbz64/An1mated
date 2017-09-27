#ifndef ANIMATIONDOCUMENT_HPP
#define ANIMATIONDOCUMENT_HPP

#include <document.hpp>


class AnimationDocument : public Document
{
    Q_OBJECT
public:
    AnimationDocument(const QString& fileName = QString(), QObject* parent = nullptr);
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
    //TODO when animation implemented
};



#endif
