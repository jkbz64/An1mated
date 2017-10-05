#include "frameeditview.hpp"
#include <QGraphicsItem>
#include <QResizeEvent>

FrameEditView::FrameEditView(QWidget* parent)
    :
      QGraphicsView(parent),
      m_background(nullptr),
      m_frame(nullptr)
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

void FrameEditView::mousePressEvent(QMouseEvent *)
{

}

void FrameEditView::mouseMoveEvent(QMouseEvent *)
{

}

void FrameEditView::mouseReleaseEvent(QMouseEvent *)
{

}

void FrameEditView::resizeEvent(QResizeEvent *event)
{
    if(m_background)
        setSceneRect(0, 0, m_background->sceneBoundingRect().width(), m_background->sceneBoundingRect().height());
}
