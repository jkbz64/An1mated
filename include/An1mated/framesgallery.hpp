#ifndef FRAMESGALLERY_HPP
#define FRAMESGALLERY_HPP

#include <QWidget>
#include <animation.hpp>
#include <QPointer>

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

    void setFrames(const QVector<AnimationFrame>& = QVector<AnimationFrame>());
    void setSpritesheet(const QPixmap& = QPixmap());
    void selectFrame(int);
    int getSelectedFrameIndex() const;
signals:
    void frameDoubleClicked(int);
    void frameSelected(int);
    void frameMoved(int, int);
    void newFrameRequested();
    void deleteFrameRequested(int);
    void editFrameRequested(int);
protected:
    AnimationFrameWidget* createFrameWidget(const AnimationFrame&);
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;

    void clearGallery();
    QPixmap m_spritesheet;
    QVector<QPointer<AnimationFrameWidget>> m_frameWidgets;
    int m_selectedFrameIndex;
    QHBoxLayout* m_layout;

    QPoint m_startDragPos;
    AnimationFrameWidget* m_draggedFrame;
    int m_startDragIndex;
    int m_spacerIndex;
    QSpacerItem* m_dragSpacer;
};

inline int FramesGallery::getSelectedFrameIndex() const
{
    return m_selectedFrameIndex;
}

#endif
