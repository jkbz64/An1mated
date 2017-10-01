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
        setScene(&m_animationScene);
    }
}

void AnimationPreview::drawFrame(int index)
{
    m_animationScene.clear();
    if(auto animation = m_currentAnimation.lock())
    {
        const auto frame = animation->getFrames()[index];
        m_animationScene.addPixmap(animation->getSpritesheet().copy(frame.getRect()));
    }
}

