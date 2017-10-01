#include <framesgallery.hpp>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

#include <animationframewidget.hpp>

FramesGallery::FramesGallery(QWidget *parent)
    :
      QWidget(parent),
      m_layout(new QHBoxLayout(this))
{
    setLayout(m_layout);
}

void FramesGallery::setAnimation(std::weak_ptr<Animation> animation)
{
    m_currentAnimation = animation;
    updateGallery();
    selectFrame(0);
}

void FramesGallery::updateGallery()
{
   clearGallery();
   if(auto animation = m_currentAnimation.lock())
   {
       int i = 0;
       for(const AnimationFrame& frame : animation->getFrames())
       {
           //Construct widget
           AnimationFrameWidget* frameWidget = new AnimationFrameWidget(frame.getName(),
                                                                                 animation->getSpritesheet().copy(frame.getRect()),
                                                                                 this);
           //Make widget selectable
           connect(frameWidget, &AnimationFrameWidget::frameClicked, [this, i]
           {
              selectFrame(i);
           });

           m_frameWidgets.push_back(frameWidget);
           m_layout->addWidget(frameWidget);
           ++i;
       }
   }
}

void FramesGallery::addFrame(const AnimationFrame &frame)
{

}

void FramesGallery::removeFrame(int index)
{

}

void FramesGallery::selectFrame(int index)
{
    if(index <= m_frameWidgets.size() - 1)
    {
        for(QWidget* frame : m_frameWidgets)
            frame->setStyleSheet("");
        m_frameWidgets[index]->setStyleSheet("background: #ADD8E6;");
        emit frameSelected(index);
    }
}

void FramesGallery::clearGallery()
{
    if(m_frameWidgets.size() > 0)
    {
        for(auto& widget : m_frameWidgets)
            widget->deleteLater();
        m_frameWidgets.clear();
    }
}
