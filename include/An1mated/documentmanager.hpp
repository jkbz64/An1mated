#ifndef DOCUMENTMANAGER_HPP
#define DOCUMENTMANAGER_HPP

#include <QObject>
#include <document.hpp>
#include <list>
#include <memory>

class QTabBar;

class DocumentManager : public QObject
{
    Q_OBJECT
public:
    static DocumentManager *instance();
    static void deleteInstance();

    QTabBar* getDocumentBar() const;
    int getDocumentCount() const;
signals:
    void currentDocumentChanged(Document* document);
private slots:
    void updateCurrentDocument(int);
    void closeDocumentAt(int);
    void moveDocument(int, int);
private:
    DocumentManager(QObject *parent = nullptr);
    ~DocumentManager();

    //Documents
    std::list<std::unique_ptr<Document>> m_documents;
    //Document tab bar
    QTabBar* m_documentTabBar;
    static DocumentManager* m_instance;
};


inline QTabBar* DocumentManager::getDocumentBar() const
{
    return m_documentTabBar;
}

inline int DocumentManager::getDocumentCount() const
{
    return m_documents.size();
}



#endif
