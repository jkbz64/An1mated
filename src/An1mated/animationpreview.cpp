#include <animationpreview.hpp>

AnimationPreview::AnimationPreview(QWidget *parent)
    :
      QGraphicsView(parent)
{

}

AnimationPreview::~AnimationPreview()
{

}

void AnimationPreview::setAnimation(std::weak_ptr<Animation> a)
{
    m_currentAnimation = a;
    if(auto animation = m_currentAnimation.lock())
    {
        m_animationScene.clear();
        m_animationScene.addPixmap(animation->getSpritesheet());
        //m_animationScene.setSceneRect(0, 0, 0 ,0);
        setScene(&m_animationScene);
    }
}

void AnimationPreview::drawFrame(int index)
{
    if(auto animation = m_currentAnimation.lock())
    {
        const auto frame = animation->getFrames()[index];
        m_animationScene.setSceneRect(frame.getRect());
    }
    else
    {
        m_animationScene.clear();
        setScene(&m_animationScene);
    }
}

