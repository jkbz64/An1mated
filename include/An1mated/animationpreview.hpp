#ifndef ANIMATIONPREVIEW_HPP
#define ANIMATIONPREVIEW_HPP

#include <QGraphicsView>
#include <animation.hpp>
#include <memory>

class AnimationPreview : public QGraphicsView
{
    Q_OBJECT
public:
    AnimationPreview(QWidget* parent = nullptr);
    virtual ~AnimationPreview();
signals:

public slots:
    void setAnimation(std::weak_ptr<Animation>);
    void drawFrame(int);
protected:

private:
    QGraphicsScene m_animationScene;
    std::weak_ptr<Animation> m_currentAnimation;
};



#endif
