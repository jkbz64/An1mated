#ifndef DOCUMENTMANAGER_HPP
#define DOCUMENTMANAGER_HPP

#include <QObject>
#include <document.hpp>
#include <QVector>
#include <QSharedPointer>

class QTabBar;

class DocumentManager : public QObject
{
    Q_OBJECT
public:
    DocumentManager(QObject *parent = nullptr);
    virtual ~DocumentManager();

    QTabBar* getDocumentBar() const;
    int getDocumentCount() const;

    template<class T, typename... Args>
    void addDocument(Args&&... arguments);
signals:
    void documentAdded(QSharedPointer<Document>);
    void documentRemoved(QSharedPointer<Document>);
    void currentDocumentChanged(QSharedPointer<Document>);
private slots:
    void updateCurrentDocument(int);
    void closeDocumentAt(int);
    void moveDocument(int, int);
private:
    //Documents
    QVector<QSharedPointer<Document>> m_documents;
    //Document tab bar
    QTabBar* m_documentTabBar;
};


inline QTabBar* DocumentManager::getDocumentBar() const
{
    return m_documentTabBar;
}

inline int DocumentManager::getDocumentCount() const
{
    return m_documents.size();
}

//Some kind of syntax sugar, it looks really ugly when you write make shared in make shared parentheses
template<class T, typename... Args>
inline void DocumentManager::addDocument(Args&&... arguments)
{
    m_documents.push_back(QSharedPointer<T>(new T(std::forward<Args>(arguments)...)));
    emit documentAdded(m_documents.back());
}

#endif
