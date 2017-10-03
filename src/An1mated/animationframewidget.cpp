#include <animationframewidget.hpp>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

AnimationFrameWidget::AnimationFrameWidget(const QString& frameName, QPixmap framePixmap, QWidget* parent)
    :
      QFrame(parent),
      m_frameNameLabel(new QLabel(frameName, parent)),
      m_framePreview(new QLabel(parent))
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setLineWidth(1);

    QVBoxLayout* frameLayout = new QVBoxLayout(this);
    m_framePreview->setScaledContents(true);
    m_framePreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    if(framePixmap.size().width() + framePixmap.size().height() < 300)
        framePixmap = framePixmap.scaled(200, 200);
    m_framePreview->setPixmap(framePixmap);
    frameLayout->addWidget(m_framePreview, 4, Qt::AlignCenter);
    frameLayout->addWidget(m_frameNameLabel, 0, Qt::AlignHCenter);
}

void AnimationFrameWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
        emit frameClicked();
}

void AnimationFrameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit frameReleased();
}

void AnimationFrameWidget::resizeEvent(QResizeEvent *event)
{

}
