#include <framesgallery.hpp>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

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
}

void FramesGallery::updateGallery()
{
   clearGallery();
   if(auto animation = m_currentAnimation.lock())
   {
       for(const AnimationFrame& frame : animation->getFrames())
       {
           //Construct widget
           QFrame* frameWidget = new QFrame(this);
           frameWidget->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
           frameWidget->setLineWidth(1);
           frameWidget->setMinimumWidth(300);
           QVBoxLayout* frameLayout = new QVBoxLayout(frameWidget);
           //Temp solution
           //Show frame in label
           QLabel* frameLabel = new QLabel(frameWidget);
           frameLabel->setAlignment(Qt::AlignHCenter);
           frameLabel->setPixmap(animation->getSpritesheet().copy(frame.getRect()));
           frameLayout->addWidget(frameLabel);

           frameLayout->addWidget(new QLabel(frame.getName(), frameWidget));
           frameWidget->setLayout(frameLayout);

           m_frameWidgets.push_back(frameWidget);
           m_layout->addWidget(frameWidget);
       }
   }
}

void FramesGallery::addFrame(const AnimationFrame &frame)
{

}

void FramesGallery::removeFrame(int index)
{

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
