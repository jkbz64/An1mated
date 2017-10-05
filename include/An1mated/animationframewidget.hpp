#ifndef ANIMATIONFRAMEWIDGET_HPP
#define ANIMATIONFRAMEWIDGET_HPP

#include <QFrame>
#include <animationframe.hpp>

class QLabel;

class AnimationFrameWidget : public QFrame
{
    Q_OBJECT
public:
    AnimationFrameWidget(const QString& frameName, QPixmap framePixmap, QWidget* parent = nullptr);
    virtual ~AnimationFrameWidget() = default;
signals:
    void framePressed();
    void frameClicked();
    void frameDoubleClicked();
    void frameReleased();
protected:
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;
private:
    QLabel* m_frameNameLabel;
    QLabel* m_framePreview;
};


#endif
