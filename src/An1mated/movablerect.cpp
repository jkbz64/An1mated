#include <movablerect.hpp>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QtGlobal>
#include <QPen>

MovableRect::MovableRect(const QRectF& size, QGraphicsItem *parent) :
    QObject(nullptr),
    QGraphicsRectItem(size, parent),
    m_dragged(false)
{
    setFlags(QGraphicsItem::ItemIsMovable);
    setSelected(true);

    QPen pen(Qt::white, 1, Qt::DotLine);
    setPen(pen);
}

void MovableRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragged = true;
    setSelected(true);
    offset = event->pos();
}

void MovableRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_dragged)
    {
        const auto newPos = event->pos() - offset;
        setPos(pos().x() + newPos.x(), pos().y() + newPos.y());
        emit rectModified(QRect(pos().toPoint(), rect().toRect().size()));
        offset = event->pos();
    }
    QGraphicsRectItem::mouseMoveEvent(event);
}

void MovableRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragged = false;
    QGraphicsRectItem::mouseReleaseEvent(event);
}
