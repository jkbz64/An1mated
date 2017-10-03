#include <framesgallery.hpp>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

#include <animationframewidget.hpp>

FramesGallery::FramesGallery(QWidget *parent)
    :
      QWidget(parent),
      m_layout(new QHBoxLayout(this)),
      m_dragSpacer(new QSpacerItem(0, 0))
{
    setAcceptDrops(true);
    setLayout(m_layout);
}

FramesGallery::~FramesGallery()
{
    delete m_dragSpacer;
}

void FramesGallery::reset()
{
    setSpritesheet();
    setFrames();
}

void FramesGallery::setFrames(const std::vector<AnimationFrame>& frames)
{
    clearGallery();

    int i = 0;
    for(const AnimationFrame& frame : frames)
    {
        //Construct widget
        AnimationFrameWidget* frameWidget = new AnimationFrameWidget(frame.getName(),
                                                                     m_spritesheet.copy(frame.getRect()),
                                                                     this);
        //Make widget selectable
        connect(frameWidget, &AnimationFrameWidget::frameClicked, [this, frameWidget, i]
        {
           //selectFrame(i);
           /*m_draggedFrame = frameWidget;
           m_startDragPos = mapFromGlobal(QCursor::pos());
           auto replaceIndex = m_layout->indexOf(m_draggedFrame);
           m_layout->removeWidget(m_draggedFrame);
           m_dragSpacer->changeSize(m_draggedFrame->size().width(), m_draggedFrame->size().height());
           m_layout->insertSpacerItem(replaceIndex, m_dragSpacer);*/
        });

        connect(frameWidget, &AnimationFrameWidget::frameReleased, [this, frameWidget, i]
        {
            selectFrame(i);
            /*
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
                //if(targetIndex != i)
                 //animation->moveFrameTo(i, targetIndex);

                updateGallery();
            }*/
        });

        m_frameWidgets.push_back(frameWidget);
        m_layout->addWidget(frameWidget);
        ++i;
    }
    selectFrame(0);
}

void FramesGallery::updateGallery()
{

}

void FramesGallery::setSpritesheet(const QPixmap &spritesheet)
{
    m_spritesheet = spritesheet;
}

void FramesGallery::selectFrame(int index)
{
    if(index < m_frameWidgets.size())
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
        std::for_each(m_frameWidgets.begin(), m_frameWidgets.end(), [](AnimationFrameWidget* widget) { widget->deleteLater(); });
        m_frameWidgets.clear();
        m_layout->removeItem(m_dragSpacer);
    }
}

void FramesGallery::mouseMoveEvent(QMouseEvent *event)
{
    if(m_draggedFrame)
    {
        QPoint subPos = event->pos() - m_startDragPos;
        if(m_draggedFrame->pos().x() + subPos.x() >= pos().x() && m_draggedFrame->pos().x() + m_draggedFrame->size().width() + subPos.x() <= pos().x() + size().width())
            m_draggedFrame->move(m_draggedFrame->pos().x() + subPos.x(), m_draggedFrame->pos().y());
        m_startDragPos = event->pos();
    }
}
