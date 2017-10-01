#include <framesgallery.hpp>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

#include <animationframewidget.hpp>

FramesGallery::FramesGallery(QWidget *parent)
    :
      QWidget(parent),
      m_layout(new QHBoxLayout(this))
{
    setAcceptDrops(true);
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
           connect(frameWidget, &AnimationFrameWidget::frameClicked, [this, frameWidget, i]
           {
              selectFrame(i);
              m_draggedFrame = frameWidget;
              m_startDragPos = mapFromGlobal(QCursor::pos());
           });

           connect(frameWidget, &AnimationFrameWidget::frameReleased, [this, frameWidget, animation, i]
           {
               if(m_draggedFrame == frameWidget)
               {
                   m_draggedFrame = nullptr;
                   //Resolve where to place widget
                   int targetIndex = m_frameWidgets.size() - 1;
                   auto it = m_frameWidgets.rbegin();
                   for(; it != m_frameWidgets.rend(); ++it)
                   {
                       if(m_startDragPos.x() > (*it)->pos().x() + (*it)->size().width())
                           break;
                       --targetIndex;
                   }
                   if(targetIndex  != i)
                    animation->moveFrameTo(i, targetIndex);

                   updateGallery();
               }
           });


           m_frameWidgets.push_back(frameWidget);
           m_layout->addWidget(frameWidget);
           ++i;
       }
   }
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

void FramesGallery::mouseMoveEvent(QMouseEvent *event)
{
    if(m_draggedFrame)
    {
        m_layout->removeWidget(m_draggedFrame);
        QPoint subPos = event->pos() - m_startDragPos;
        m_draggedFrame->move(m_draggedFrame->pos().x() + subPos.x(), m_draggedFrame->pos().y() + subPos.y());
        m_startDragPos = event->pos();
    }
}
