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

    QPen pen(Qt::white, 1, Qt::DotLine);
    setPen(pen);
}

void MovableRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragged = true;
    QGraphicsRectItem::mousePressEvent(event);
}

void MovableRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_dragged)
        emit rectModified(QRect(sceneBoundingRect().topLeft().toPoint(), rect().toRect().size()));
    QGraphicsRectItem::mouseMoveEvent(event);
}

void MovableRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragged = false;
    QGraphicsRectItem::mouseReleaseEvent(event);
}
