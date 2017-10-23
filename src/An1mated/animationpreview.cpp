#include <animationpreview.hpp>
#include <QGraphicsItem>
#include <QResizeEvent>

AnimationPreview::AnimationPreview(QWidget *parent)
    :
      QGraphicsView(parent),
      m_background(nullptr),
      m_frame(nullptr)
{
    setSceneRect(0, 0, size().width(), size().height());
    setScene(&m_animationScene);
    reset();
}

AnimationPreview::~AnimationPreview()
{

}

void AnimationPreview::reset()
{
    m_animationScene.clear();
    m_background = nullptr;
    m_frame = nullptr;
    setBackground();
    setSpritesheet();
    m_framePosition = QPoint(size().width() / 2, size().height() / 2);
}

void AnimationPreview::setSpritesheet(const QPixmap& spritesheet)
{
    if(m_frame)
    {
        m_animationScene.removeItem(m_frame);
        m_frame = nullptr;
    }
    m_spritesheet = spritesheet;
}

void AnimationPreview::setFrame(const AnimationFrame& frame)
{
    if(m_frame)
        m_animationScene.removeItem(m_frame);
    m_frame = m_animationScene.addPixmap(m_spritesheet.copy(frame.getRect()));
    if(!m_background)
        m_framePosition = QPoint(size().width() / 2, size().height() / 2);
    m_frame->setPos(m_framePosition);
}

void AnimationPreview::setBackground(const QPixmap &pixmap)
{
    if(m_background)
        m_animationScene.removeItem(m_background);
    if(!pixmap.isNull())
    {
        setSceneRect(0, 0, pixmap.size().width(), pixmap.height());
        m_background = m_animationScene.addPixmap(pixmap);
        m_background->setZValue(-1);
        m_background->setPos(0, 0);
    }
    else
        setSceneRect(0, 0, size().width(), size().height());
}

void AnimationPreview::resizeEvent(QResizeEvent *event)
{
    if(!m_background)
    {
        setSceneRect(0, 0, event->size().width(), event->size().height());
        if(m_frame)
        {
            m_framePosition = QPoint(event->size().width() / 2, event->size().height() / 2);
            m_frame->setPos(m_framePosition);
        }
    }
    else
        setSceneRect(0, 0, m_background->sceneBoundingRect().width(), m_background->sceneBoundingRect().height());
}
