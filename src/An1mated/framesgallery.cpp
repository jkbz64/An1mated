#include <framesgallery.hpp>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>

#include <animationframewidget.hpp>

FramesGallery::FramesGallery(QWidget *parent)
    :
      QWidget(parent),
      m_selectedFrameIndex(0),
      m_layout(new QHBoxLayout(this)),
      m_draggedFrame(nullptr),
      m_startDragIndex(-1),
      m_spacerIndex(-1),
      m_dragSpacer(new QSpacerItem(0, 0))
{
    setLayout(m_layout);
}

FramesGallery::~FramesGallery()
{
    delete m_dragSpacer;
}

void FramesGallery::reset()
{
    m_selectedFrameIndex = 0;
    setSpritesheet();
    setFrames();
}

void FramesGallery::setFrames(const QVector<AnimationFrame>& frames)
{
    clearGallery();
    for(const AnimationFrame& frame : frames)
    {
        m_frameWidgets.push_back(QPointer<AnimationFrameWidget>(createFrameWidget(frame)));
        m_layout->addWidget(m_frameWidgets.back());
    }
}

void FramesGallery::selectFrame(int at)
{
    if(at >= 0 && at < m_frameWidgets.size())
    {
        emit m_frameWidgets[at]->framePressed();
        emit m_frameWidgets[at]->frameReleased();
        m_selectedFrameIndex = at;
    }
}

AnimationFrameWidget* FramesGallery::createFrameWidget(const AnimationFrame &frame)
{
    AnimationFrameWidget* frameWidget = new AnimationFrameWidget(frame.getName(),
                                                                 m_spritesheet.copy(frame.getRect()),
                                                                 this);

    connect(frameWidget, &AnimationFrameWidget::framePressed, [this, frame, frameWidget]
    {
        //Reset all widgets stylesheet
        std::for_each(m_frameWidgets.begin(), m_frameWidgets.end(), [](QWidget* w) { w->setStyleSheet(""); });
        frameWidget->setStyleSheet("background: #ADD8E6;");
        emit frameSelected(m_layout->indexOf(frameWidget));
        m_draggedFrame = frameWidget;
        m_startDragPos = mapFromGlobal(QCursor::pos());
        //Get index of frame in layout so we can replace it with spacer item
        m_startDragIndex = m_spacerIndex = m_layout->indexOf(m_draggedFrame);
        m_layout->removeWidget(m_draggedFrame);
        //Make spacer width and height same as dragged frame
        m_dragSpacer->changeSize(m_draggedFrame->size().width() + 5, m_draggedFrame->size().height());
        m_layout->insertSpacerItem(m_spacerIndex, m_dragSpacer);
    });

    connect(frameWidget, &AnimationFrameWidget::frameReleased, [this, frameWidget]
    {
        if(m_draggedFrame == frameWidget)
        {
            //Insert dragged frame at spacer position
            m_layout->removeItem(m_dragSpacer);
            m_layout->insertWidget(m_spacerIndex, m_draggedFrame);
            m_selectedFrameIndex = m_layout->indexOf(frameWidget);
            if(m_spacerIndex != m_startDragIndex)
                emit frameMoved(m_startDragIndex, m_spacerIndex);
            m_startDragIndex = m_spacerIndex = -1;
            m_draggedFrame = nullptr;
        }
    });

    connect(frameWidget, &AnimationFrameWidget::frameRightClicked, [this, frame, frameWidget]
    {
        std::for_each(m_frameWidgets.begin(), m_frameWidgets.end(), [](QWidget* w) { w->setStyleSheet(""); });
        frameWidget->setStyleSheet("background: #ADD8E6;");
        emit frameSelected(m_layout->indexOf(frameWidget));
        QMenu contextMenu(tr("Frame context"), this);
        QAction newFrameAction(tr("New frame"), this);
        connect(&newFrameAction, &QAction::triggered, [this](bool){ emit newFrameRequested(); });
        QAction removeFrameAction(tr("Remove frame"), this);
        connect(&removeFrameAction, &QAction::triggered, [this, frameWidget](bool){ emit deleteFrameRequested(m_layout->indexOf(frameWidget)); });
        QAction editFrameAction(tr("Edit frame"), this);
        connect(&editFrameAction, &QAction::triggered, [this, frameWidget](bool){ emit editFrameRequested(m_layout->indexOf(frameWidget)); });


        contextMenu.addAction(&newFrameAction);
        contextMenu.addAction(&removeFrameAction);
        contextMenu.addSeparator();
        contextMenu.addAction(&editFrameAction);

        contextMenu.exec(QCursor::pos());
    });

    connect(frameWidget, &AnimationFrameWidget::frameDoubleClicked, [this, frameWidget]
    {
        emit frameDoubleClicked(m_layout->indexOf(frameWidget));
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

void FramesGallery::mouseReleaseEvent(QMouseEvent *event)
{   
    if(event->button() == Qt::MouseButton::RightButton)
    {
        QMenu contextMenu(tr("New frame context"), this);
        QAction newFrameAction(tr("New frame"), this);
        connect(&newFrameAction, &QAction::triggered, [this](bool){ emit newFrameRequested(); });
        contextMenu.addAction(&newFrameAction);
        contextMenu.exec(QCursor::pos());
    }
}

void FramesGallery::wheelEvent(QWheelEvent *event)
{
    // Move to the next frame
    if(event->delta() > 0)
        selectFrame(m_selectedFrameIndex + 1);
    else
       selectFrame(m_selectedFrameIndex - 1);
    event->accept();
}

void FramesGallery::mouseMoveEvent(QMouseEvent *event)
{
    if(m_draggedFrame)
    {
        QPoint subPos = event->pos() - m_startDragPos;
        if(m_draggedFrame->pos().x() + subPos.x() >= pos().x() - (m_draggedFrame->size().width() / 2) &&
           m_draggedFrame->pos().x() + m_draggedFrame->size().width() + subPos.x() < pos().x() + size().width() + (m_draggedFrame->size().width() / 2))
            m_draggedFrame->move(m_draggedFrame->pos().x() + subPos.x(), m_draggedFrame->pos().y());
        {
            m_startDragPos = event->pos();
        }


        //TODO I believe this can look better
        if(m_layout->count() > 1)
        {
            //When spacer is in middle of frames but not at the beggining and end
            if(m_spacerIndex > 0 && m_spacerIndex < m_layout->count() - 1)
            {
                const auto widgetAfterSpacer = m_layout->itemAt(m_spacerIndex + 1)->widget();
                //Handle after spacer
                if(m_draggedFrame->pos().x() > widgetAfterSpacer->pos().x())
                {
                    m_layout->removeItem(m_dragSpacer);
                    m_layout->insertSpacerItem(++m_spacerIndex, m_dragSpacer);
                }
                const auto widgetBeforeSpacer = m_layout->itemAt(m_spacerIndex - 1)->widget();
                //Handle before spacer
                if(m_draggedFrame->pos().x() < widgetBeforeSpacer->pos().x())
                {
                    m_layout->removeItem(m_dragSpacer);
                    m_layout->insertSpacerItem(--m_spacerIndex, m_dragSpacer);
                }
            }
            else if(m_spacerIndex == 0) // Spacer at the beginning
            {
                 const auto widgetAfterSpacer = m_layout->itemAt(m_spacerIndex + 1)->widget();
                 if(m_draggedFrame->pos().x() > widgetAfterSpacer->pos().x())
                 {
                     m_layout->removeItem(m_dragSpacer);
                     m_layout->insertSpacerItem(++m_spacerIndex, m_dragSpacer);
                 }
            }
            else if(m_spacerIndex == m_layout->count() - 1) // Spacer at the end
            {
                const auto widgetBeforeSpacer = m_layout->itemAt(m_spacerIndex - 1)->widget();
                if(m_draggedFrame->pos().x() < widgetBeforeSpacer->pos().x())
                {
                    m_layout->removeItem(m_dragSpacer);
                    m_layout->insertSpacerItem(--m_spacerIndex, m_dragSpacer);
                }
            }
        }
    }
}
