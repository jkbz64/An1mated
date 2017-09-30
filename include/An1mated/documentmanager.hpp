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

    template<class T, typename... Args>
    void addDocument(Args&&... arguments);
signals:
    void documentAdded(std::shared_ptr<Document>);
    void documentRemoved(std::shared_ptr<Document>);
    void currentDocumentChanged(std::shared_ptr<Document>);
private slots:
    void updateCurrentDocument(int);
    void closeDocumentAt(int);
    void moveDocument(int, int);
private:
    DocumentManager(QObject *parent = nullptr);
    ~DocumentManager();

    //Documents
    std::vector<std::shared_ptr<Document>> m_documents;
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

//Some kind of syntax sugar, it looks really ugly when you write make shared in make shared parentheses
template<class T, typename... Args>
inline void DocumentManager::addDocument(Args&&... arguments)
{
    m_documents.emplace_back(std::make_shared<T>(std::forward<Args>(arguments)...));
    emit documentAdded(m_documents.back());
}

#endif
