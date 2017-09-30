#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <QWidget>
#include <document.hpp>


class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget* parent = nullptr) : QWidget(parent) { }
    virtual ~Editor() = default;

    virtual void setDocument(std::weak_ptr<Document>) = 0;
    std::weak_ptr<Document> getCurrentDocument() const;
protected:
    std::weak_ptr<Document> m_currentDocument;
};

inline std::weak_ptr<Document> Editor::getCurrentDocument() const
{
    return m_currentDocument;
}

#endif
