#include <documentmanager.hpp>
#include <QTabBar>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QSpacerItem>


DocumentManager* DocumentManager::m_instance = nullptr;

DocumentManager::DocumentManager(QObject* parent)
    :
      QObject(parent),
      m_documentTabBar(new QTabBar(nullptr))
{
    //Setup tab bar
    m_documentTabBar->setExpanding(true);
    m_documentTabBar->setDocumentMode(true);
    m_documentTabBar->setTabsClosable(true);
    m_documentTabBar->setMovable(true);


    connect(m_documentTabBar, &QTabBar::currentChanged, this, &DocumentManager::updateCurrentDocument);
    connect(this, &DocumentManager::documentAdded, [this](std::shared_ptr<Document> document)
    {
        m_documentTabBar->addTab(document->getFileName());
        m_documentTabBar->setCurrentIndex(m_documents.size() - 1);
    });
    connect(m_documentTabBar, &QTabBar::tabCloseRequested, this, &DocumentManager::closeDocumentAt);
    connect(m_documentTabBar, &QTabBar::tabMoved, this, &DocumentManager::moveDocument);


}

DocumentManager::~DocumentManager()
{
    delete m_documentTabBar;
}

void DocumentManager::updateCurrentDocument(int index)
{
    if(index != -1)
        emit currentDocumentChanged(*(m_documents.begin() + index));
    else
        emit currentDocumentChanged(std::shared_ptr<Document>());
}

void DocumentManager::closeDocumentAt(int index)
{
    emit documentRemoved(m_documents[index]);
    m_documents.erase(m_documents.begin() + index);
    m_documentTabBar->removeTab(index);
    m_documentTabBar->setCurrentIndex(m_documents.size() - 1);
}

void DocumentManager::moveDocument(int from, int to)
{
    std::swap(*(m_documents.begin() + from),*(m_documents.begin() + to));
}
