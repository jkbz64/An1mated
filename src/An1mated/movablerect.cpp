#include <movablerect.hpp>
#include <QPen>
#include <QGraphicsScene>

MovableRect::MovableRect(const QRectF& size, QGraphicsItem *parent) :
    QObject(nullptr),
    QGraphicsRectItem(size, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);
    QPen pen(Qt::white, 1, Qt::DotLine);
    setPen(pen);
}

QVariant MovableRect::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
    {
        const auto newPos = value.toPoint();
        if(newPos.x() >= 0 && newPos.x() + rect().width() <= scene()->width() && newPos.y() >= 0 && newPos.y() + rect().height() <= scene()->height())
            emit rectModified(QRect(value.toPoint(), rect().toRect().size()));
        else
            return pos();
        return value.toPointF();
    }
    return QGraphicsRectItem::itemChange(change, value);
}
