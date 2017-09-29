#include <QTest>

class AnimationReader : public QObject
{
    Q_OBJECT
private slots:
    void readMap()
    {
        QVERIFY(true);
    }
};

QTEST_MAIN(AnimationReader)
#include "test_animationreading.moc"
