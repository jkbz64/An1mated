#ifndef FRAMESGALLERY_HPP
#define FRAMESGALLERY_HPP

#include <QWidget>
#include <animation.hpp>
#include <memory>

class AnimationFrameWidget;
class QHBoxLayout;
class QSpacerItem;

class FramesGallery : public QWidget
{
    Q_OBJECT
public:
    FramesGallery(QWidget* parent = nullptr);
    virtual ~FramesGallery();
    void reset();

    void setFrames(const std::vector<AnimationFrame>& = std::vector<AnimationFrame>());
    void setSpritesheet(const QPixmap& = QPixmap());
signals:
    void frameDoubleClicked(const AnimationFrame&);
    void frameSelected(const AnimationFrame&);
public slots:
    void updateGallery();
    void addFrame(const AnimationFrame&);
    void updateFrame(int, const AnimationFrame&);
protected:
    AnimationFrameWidget* createFrameWidget(const AnimationFrame&);
    virtual void mouseMoveEvent(QMouseEvent*) override;

    void clearGallery();
    QPixmap m_spritesheet;
    std::vector<AnimationFrameWidget*> m_frameWidgets;
    QHBoxLayout* m_layout;

    QPoint m_startDragPos;
    AnimationFrameWidget* m_draggedFrame = nullptr;
    QSpacerItem* m_dragSpacer;
};

#endif
