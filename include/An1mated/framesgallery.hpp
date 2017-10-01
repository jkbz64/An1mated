#ifndef FRAMESGALLERY_HPP
#define FRAMESGALLERY_HPP

#include <QWidget>
#include <animation.hpp>
#include <memory>

class AnimationFrameWidget;
class QHBoxLayout;

class FramesGallery : public QWidget
{
    Q_OBJECT
public:
    FramesGallery(QWidget* parent = nullptr);
    virtual ~FramesGallery() = default;
signals:
    void frameSelected(int);
public slots:
    void setAnimation(std::weak_ptr<Animation>);
    void addFrame(const AnimationFrame&);
    void removeFrame(int);

    void updateGallery();
protected:
    void clearGallery();
    std::weak_ptr<Animation> m_currentAnimation;
    std::vector<AnimationFrameWidget*> m_frameWidgets;
    QHBoxLayout* m_layout;
};

#endif