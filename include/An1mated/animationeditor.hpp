#ifndef ANIMATIONEDITOR_HPP
#define ANIMATIONEDITOR_HPP

#include <editor.hpp>
#include <animationframe.hpp>

namespace Ui
{
    class AnimationEditor;
}

class AnimationPreview;

class AnimationEditor : public Editor
{
    Q_OBJECT
public:
    AnimationEditor(QWidget* parent = nullptr);
    virtual ~AnimationEditor();

    virtual void setDocument(std::shared_ptr<Document>) override;
signals:

public slots:
    void newFrame();
    void editFrame(const AnimationFrame&);
protected:
    Ui::AnimationEditor* m_ui;
};

#endif
