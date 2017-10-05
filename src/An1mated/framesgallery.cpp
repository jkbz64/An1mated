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
        m_frameWidgets.push_back(createFrameWidget(frame));
        m_layout->addWidget(m_frameWidgets.back());
        ++i;
    }

    if(!m_frameWidgets.empty())
    {
        m_frameWidgets.front()->setStyleSheet("background: #ADD8E6;");
        emit frameSelected(frames.front());
    }
}

void FramesGallery::updateGallery()
{

}

void FramesGallery::addFrame(const AnimationFrame& frame)
{
    auto&& frameWidget = createFrameWidget(frame);
    m_frameWidgets.emplace_back(frameWidget);
    m_layout->addWidget(m_frameWidgets.back());
}

void FramesGallery::updateFrame(int at, const AnimationFrame &updatedFrame)
{
    if(at >= 0 && at < m_frameWidgets.size())
    {
        m_frameWidgets[at]->deleteLater();
        auto&& frameWidget = createFrameWidget(updatedFrame);
        m_layout->replaceWidget(m_frameWidgets[at], frameWidget);
        m_frameWidgets[at] = frameWidget;
    }
}

AnimationFrameWidget *FramesGallery::createFrameWidget(const AnimationFrame &frame)
{
    AnimationFrameWidget* frameWidget = new AnimationFrameWidget(frame.getName(),
                                                                 m_spritesheet.copy(frame.getRect()),
                                                                 this);

    connect(frameWidget, &AnimationFrameWidget::framePressed, [this, frame, frameWidget]
    {
        //Reset all widgets style
        std::for_each(m_frameWidgets.begin(), m_frameWidgets.end(), [](QWidget* w) { w->setStyleSheet(""); });
        frameWidget->setStyleSheet("background: #ADD8E6;");
        emit frameSelected(frame);
       /*m_draggedFrame = frameWidget;
       m_startDragPos = mapFromGlobal(QCursor::pos());
       auto replaceIndex = m_layout->indexOf(m_draggedFrame);
       m_layout->removeWidget(m_draggedFrame);
       m_dragSpacer->changeSize(m_draggedFrame->size().width(), m_draggedFrame->size().height());
       m_layout->insertSpacerItem(replaceIndex, m_dragSpacer);*/
    });

    connect(frameWidget, &AnimationFrameWidget::frameReleased, [this]
    {
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

    connect(frameWidget, &AnimationFrameWidget::frameDoubleClicked, [this, frame]()
    {
        emit frameDoubleClicked(frame);
    });

    return frameWidget;
}

void FramesGallery::setSpritesheet(const QPixmap &spritesheet)
{
    m_spritesheet = spritesheet;
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
