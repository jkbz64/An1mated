#ifndef FRAMEEDITVIEW_H
#define FRAMEEDITVIEW_H

#include <QGraphicsView>


class FrameEditView : public QGraphicsView
{
    Q_OBJECT
public:
    FrameEditView(QWidget* parent = nullptr);
    virtual ~FrameEditView();
    void setSpritesheet(const QPixmap&);
    void setRect(const QRect&);
signals:
    void rectModified(QRect&);
protected:
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;
    QGraphicsScene m_scene;
    QRect m_frameRect;
    QGraphicsItem* m_background;
    QGraphicsItem* m_frame;
    bool m_isDragging;
    QPoint m_startDragPosition;
};

#endif // FRAMEEDITVIEW_H
