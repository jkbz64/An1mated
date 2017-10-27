#ifndef MOVABLERECT_HPP
#define MOVABLERECT_HPP

#include <QGraphicsRectItem>

class MovableRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MovableRect(const QRectF& size, QGraphicsItem* parent = nullptr);
signals:
    void rectModified(const QRect&);
    void rectPressed();
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
};

#endif
