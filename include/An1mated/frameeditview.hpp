#ifndef FRAMEEDITVIEW_H
#define FRAMEEDITVIEW_H

#include <QGraphicsView>

class MovableRect;

class FrameEditView : public QGraphicsView
{
    Q_OBJECT
public:
    FrameEditView(QWidget* parent = nullptr);
    virtual ~FrameEditView();
    void setSpritesheet(const QPixmap&);
    void setRect(const QRect&);
signals:
    void rectModified(QRect);
    void rectChangedPosition(QPoint);
private slots:
    void scalingTime(qreal);
    void animFinished();
protected:
    virtual void resizeEvent(QResizeEvent*) override;
    virtual void wheelEvent(QWheelEvent*) override;
    QGraphicsScene m_scene;
    QRect m_frameRect;
    QGraphicsItem* m_background;
    MovableRect* m_frame;
    bool m_isDragging;
    QPoint m_startDragPosition;
    qreal factor;
    int _numScheduledScalings;
};

#endif // FRAMEEDITVIEW_H
