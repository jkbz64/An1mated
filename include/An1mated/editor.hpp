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

    virtual void setDocument(QSharedPointer<Document>) = 0;
    QSharedPointer<Document> getCurrentDocument() const;
protected:
    QSharedPointer<Document> m_currentDocument;
};

inline QSharedPointer<Document> Editor::getCurrentDocument() const
{
    return m_currentDocument;
}

#endif
