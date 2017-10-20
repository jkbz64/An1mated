#include "frameeditview.hpp"
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QTimeLine>
#include <movablerect.hpp>

FrameEditView::FrameEditView(QWidget* parent)
    :
      QGraphicsView(parent),
      m_background(nullptr),
      m_frame(nullptr),
      m_isDragging(false),
      m_startDragPosition(0, 0),
      factor(1.0),
      _numScheduledScalings(0)
{
    setScene(&m_scene);
    setRenderHint(QPainter::Antialiasing, true);
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
    m_background->setZValue(-1);
}

void FrameEditView::setRect(const QRect &rect)
{
    m_frameRect = rect;
    if(m_background)
    {
        if(!m_frame)
        {
            m_frame = new MovableRect(rect);
            connect(m_frame, &MovableRect::rectModified, this, [this](const QRect &rect)
            {
                emit rectModified(rect);
            });
            m_scene.addItem(m_frame);
        }
        else  m_frame->setRect(QRectF(rect));
    }
    emit rectModified(m_frameRect);
}

void FrameEditView::resizeEvent(QResizeEvent* event)
{
    if(m_background)
        setSceneRect(0, 0, m_background->sceneBoundingRect().width(), m_background->sceneBoundingRect().height());
    QGraphicsView::resizeEvent(event);
}

void FrameEditView::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0)
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, &QTimeLine::valueChanged, this, &FrameEditView::scalingTime);
    connect(anim, &QTimeLine::finished, this, &FrameEditView::animFinished);
    anim->start();
}

void FrameEditView::scalingTime(qreal x)
{
    factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void FrameEditView::animFinished()
{
    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;
    sender()->deleteLater();
}
