#include <QTest>
#include <animation.hpp>
#include <iostream>

class AnimationTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        animation = new Animation("testAnimation");
    }

    void checkConstructorTest()
    {
        QVERIFY(animation->getName() == "testAnimation");
    }

    void addFrameTest()
    {
        animation->addFrame("testFrame1", QRect());
        animation->addFrame("testFrame2", QRect());
        QVERIFY(animation->getFrames().size() > 0);
        QVERIFY(animation->getFrames().back().getName() == "testFrame2");
    }

    void locateFrameTest()
    {
        QVERIFY(animation->getIndexOf("testFrame2") == 1);
        const auto& frame = animation->getFrames().back();
        QVERIFY(animation->getIndexOf(frame) == 1);
    }

    void removeFrameTest()
    {
        animation->removeFrame("testFrame1");
        QVERIFY(animation->getFrames().size() == 1);
        animation->removeFrame(0);
        QVERIFY(animation->getFrames().size() == 0);
    }

    void moveFrameTest()
    {
        animation->addFrame("f1", QRect());
        animation->addFrame("f2", QRect());
        animation->addFrame("f3", QRect());

        //Test moving forward to end
        animation->moveFrameTo(0, 2);
        QVERIFY(animation->getFrames().front().getName() == "f2");
        QVERIFY(animation->getFrames()[1].getName() == "f3");
        QVERIFY(animation->getFrames().back().getName() == "f1");
        //Test moving backward to start
        animation->moveFrameTo(2, 0);
        QVERIFY(animation->getFrames().front().getName() == "f1");
        QVERIFY(animation->getFrames()[1].getName() == "f2");
        QVERIFY(animation->getFrames().back().getName() == "f3");

        animation->addFrame("f4", QRect());
        //Test moving in middle forward f2 to f3
        animation->moveFrameTo(1, 2);
        QVERIFY(animation->getFrames()[1].getName() == "f3");
        QVERIFY(animation->getFrames()[2].getName() == "f2");

        //Test moving in middle backwards f2 to f3
        animation->moveFrameTo(2, 1);
        QVERIFY(animation->getFrames()[1].getName() == "f2");
        QVERIFY(animation->getFrames()[2].getName() == "f3");

        animation->addFrame("f5", QRect());
        //Test moving f2 to end
        animation->moveFrameTo(1, 4);
        QVERIFY(animation->getFrames()[1].getName() == "f3");
        QVERIFY(animation->getFrames()[2].getName() == "f4");
        QVERIFY(animation->getFrames()[3].getName() == "f5");
        QVERIFY(animation->getFrames()[4].getName() == "f2");
    }

    void cleanupTestCase()
    {
        delete animation;
    }

private:
    Animation *animation;
};

QTEST_MAIN(AnimationTest)
#include "test_animation.moc"
