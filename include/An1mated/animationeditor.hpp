#ifndef ANIMATIONEDITOR_HPP
#define ANIMATIONEDITOR_HPP

#include <editor.hpp>

class AnimationPreview;

class AnimationEditor : public Editor
{
    Q_OBJECT
public:
    AnimationEditor(QWidget* parent = nullptr);
    virtual ~AnimationEditor() = default;

    virtual void setDocument(std::shared_ptr<Document>) override;
signals:

protected:
    AnimationPreview* m_animationPreview;
};





#endif
