#ifndef ANIMATIONEDITOR_HPP
#define ANIMATIONEDITOR_HPP

#include <editor.hpp>

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
protected:
    Ui::AnimationEditor* m_ui;
};





#endif
