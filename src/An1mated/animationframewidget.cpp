#include <animationframewidget.hpp>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

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
    m_framePreview->setPixmap(framePixmap.scaled(500, 500));
    frameLayout->addWidget(m_framePreview, 4, Qt::AlignCenter);
    frameLayout->addWidget(m_frameNameLabel, 0, Qt::AlignHCenter);
}

void AnimationFrameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
        emit frameClicked();
}
