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
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

    bool m_dragged;
    QPointF offset;
};




#endif
