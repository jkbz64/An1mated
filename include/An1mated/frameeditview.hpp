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
    MovableRect* getRect();
signals:
    void rectModified(QRect);
    void rectChangedPosition(QPoint);
private slots:
    void scalingTime(qreal);
    void animFinished();
protected:
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;
    virtual void wheelEvent(QWheelEvent*) override;
    QGraphicsScene m_scene;
    QGraphicsItem* m_background;
    MovableRect* m_frame;
    bool m_isDragging;
    QPoint m_startDragPosition;
    int m_numScheduledScalings;
};

#endif // FRAMEEDITVIEW_H
