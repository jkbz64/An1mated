#include "frameeditview.hpp"
#include <QGraphicsItem>
#include <QResizeEvent>

FrameEditView::FrameEditView(QWidget* parent)
    :
      QGraphicsView(parent),
      m_background(nullptr),
      m_frame(nullptr),
      m_isDragging(false),
      m_startDragPosition(0, 0)
{
    setScene(&m_scene);
}

FrameEditView::~FrameEditView()
{
    m_scene.clear();
    m_background = nullptr;
    m_frame = nullptr;
}

void FrameEditView::setSpritesheet(const QPixmap &spritesheet)
{
    m_background = m_scene.addPixmap(spritesheet);
}

void FrameEditView::setRect(const QRect &rect)
{
    m_frameRect = rect;
    if(m_background)
    {
        if(m_frame)
            m_scene.removeItem(m_frame);
        m_frame = m_scene.addRect(m_frameRect);
    }
    emit rectModified(m_frameRect);
}


void FrameEditView::mousePressEvent(QMouseEvent* event)
{
    if(m_frame->isUnderMouse())
    {
        m_startDragPosition = event->pos();
        m_isDragging = true;
    }
}

void FrameEditView::mouseMoveEvent(QMouseEvent* event)
{
    if(m_isDragging)
    {
        QPoint newPos = event->pos() - m_startDragPosition;
        if(m_frameRect.x() + newPos.x() >= 0 &&
           m_frameRect.right() + newPos.x() <= m_background->sceneBoundingRect().right() &&
           m_frameRect.top() + newPos.y() >= 0 &&
           m_frameRect.bottom() + newPos.y() <= m_background->sceneBoundingRect().bottom())
        {
            m_frameRect.adjust(newPos.x(), newPos.y(), 0, 0);
            emit rectModified(m_frameRect);
        }
        m_startDragPosition = event->pos();
    }
}

void FrameEditView::mouseReleaseEvent(QMouseEvent*)
{
    if(m_isDragging)
        m_isDragging = false;
}

void FrameEditView::resizeEvent(QResizeEvent*)
{
    if(m_background)
        setSceneRect(0, 0, m_background->sceneBoundingRect().width(), m_background->sceneBoundingRect().height());
}
