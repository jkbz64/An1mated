#ifndef FRAMEEDITVIEW_H
#define FRAMEEDITVIEW_H

#include <QGraphicsView>


class FrameEditView : public QGraphicsView
{
public:
    FrameEditView(QWidget* parent = nullptr);
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
};

#endif // FRAMEEDITVIEW_H
