#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <QWidget>
#include <document.hpp>
#include <memory>

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget* parent = nullptr) : QWidget(parent) { }
    virtual ~Editor() = default;

    virtual void setDocument(std::shared_ptr<Document>) = 0;
    std::shared_ptr<Document> getCurrentDocument() const;
protected:
    std::shared_ptr<Document> m_currentDocument;
};

inline std::shared_ptr<Document> Editor::getCurrentDocument() const
{
    return m_currentDocument;
}

#endif
