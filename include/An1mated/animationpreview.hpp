#ifndef ANIMATIONPREVIEW_HPP
#define ANIMATIONPREVIEW_HPP

#include <QGraphicsView>
#include <animation.hpp>
#include <memory>

class AnimationPreview : public QGraphicsView
{
    Q_OBJECT
public:
    AnimationPreview(QWidget* parent = nullptr);
    virtual ~AnimationPreview();

    void setBackground(const QPixmap& = QPixmap());
    void setSpritesheet(const QPixmap& = QPixmap());
    void setFrame(const AnimationFrame&);
protected:
    virtual void resizeEvent(QResizeEvent*) override;
    QGraphicsScene m_animationScene;
    QPixmap m_spritesheet;
    QGraphicsItem* m_background;
    QGraphicsItem* m_frame;
    QPoint m_framePosition;
};

#endif
