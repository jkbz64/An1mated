#include <animationpreview.hpp>
#include <QGraphicsItem>
#include <QResizeEvent>

AnimationPreview::AnimationPreview(QWidget *parent)
    :
      QGraphicsView(parent),
      m_frame(nullptr),
      m_background(nullptr),
      m_framePosition(size().width() / 2, size().height() / 2)
{
    setSceneRect(0, 0, size().width(), size().height());
    setScene(&m_animationScene);
}

AnimationPreview::~AnimationPreview()
{

}

void AnimationPreview::reset()
{
    m_animationScene.clear();
    setBackground();
    setSpritesheet();
    m_framePosition = QPoint(size().width() / 2, size().height() / 2);
    m_background = nullptr;
    m_frame = nullptr;
}

void AnimationPreview::setSpritesheet(const QPixmap& spritesheet)
{
    m_animationScene.clear();
    m_spritesheet = spritesheet;
    if(m_frame)
        m_animationScene.removeItem(m_frame);
}

void AnimationPreview::setFrame(const AnimationFrame& frame)
{
    if(m_frame)
        m_animationScene.removeItem(m_frame);
    m_frame = m_animationScene.addPixmap(m_spritesheet.copy(frame.getRect()));
    m_frame->setPos(m_framePosition);
}

void AnimationPreview::setBackground(const QPixmap &pixmap)
{
    if(m_background)
        m_animationScene.removeItem(m_background);

    setSceneRect(0, 0, pixmap.size().width(), pixmap.height());
    m_background = m_animationScene.addPixmap(pixmap);
    m_background->setZValue(-1);
    m_background->setPos(0, 0);
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
