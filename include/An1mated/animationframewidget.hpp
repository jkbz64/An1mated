#ifndef ANIMATIONFRAMEWIDGET_HPP
#define ANIMATIONFRAMEWIDGET_HPP

#include <QFrame>

class QLabel;

class AnimationFrameWidget : public QFrame
{
    Q_OBJECT
public:
    AnimationFrameWidget(const QString& frameName, QPixmap framePixmap, QWidget* parent = nullptr);
    virtual ~AnimationFrameWidget() = default;
signals:
    void frameClicked();
protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
private:
    QLabel* m_frameNameLabel;
    QLabel* m_framePreview;
};


#endif
