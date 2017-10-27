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
    centerOn(viewport()->rect().center());
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
            connect(m_frame, &MovableRect::rectPressed, this, [this]{ m_isDragging = false;});
            m_scene.addItem(m_frame);
        }
        else
            m_frame->setRect(QRectF(m_frameRect));
    }
    emit rectModified(m_frameRect);
}

MovableRect* FrameEditView::getRect()
{
    return m_frame;
}

void FrameEditView::mousePressEvent(QMouseEvent *event)
{
    if(!m_frame->isUnderMouse() && event->button() == Qt::LeftButton)
    {
        m_isDragging = true;
        m_startDragPosition = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

void FrameEditView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isDragging)
    {
        QPointF center = mapToScene(viewport()->rect().center());

        QPointF oldP = mapToScene(m_startDragPosition);
        QPointF newP = mapToScene(event->pos());
        QPointF tr = newP - oldP;

        centerOn(center.x() - tr.x(), center.y() - tr.y());

        m_startDragPosition = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void FrameEditView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
        m_isDragging = false;
    QGraphicsView::mouseReleaseEvent(event);
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
