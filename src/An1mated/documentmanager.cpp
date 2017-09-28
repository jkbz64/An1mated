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
    connect(m_documentTabBar, &QTabBar::tabCloseRequested, this, &DocumentManager::closeDocumentAt);
    connect(m_documentTabBar, &QTabBar::tabMoved, this, &DocumentManager::moveDocument);


}

DocumentManager::~DocumentManager()
{
    delete m_documentTabBar;
}

DocumentManager* DocumentManager::instance()
{
    if(!m_instance)
        m_instance = new DocumentManager(nullptr);
    return m_instance;
}

void DocumentManager::deleteInstance()
{
    delete m_instance;
    m_instance = nullptr;
}

void DocumentManager::updateCurrentDocument(int index)
{
    if(index != -1)
        emit currentDocumentChanged(*(m_documents.begin() + index));
    else
        emit currentDocumentChanged(std::weak_ptr<Document>());
}

void DocumentManager::closeDocumentAt(int index)
{
    m_documents.erase(m_documents.begin() + index);
    m_documentTabBar->removeTab(index);
}

void DocumentManager::moveDocument(int from, int to)
{
    std::swap(*(m_documents.begin() + from),*(m_documents.begin() + to));
}

void DocumentManager::addDocument(std::shared_ptr<Document> doc)
{
    m_documents.emplace_back(doc);
    m_documentTabBar->addTab(doc->getFileName());
    m_documentTabBar->setCurrentIndex(m_documents.size() - 1);
}