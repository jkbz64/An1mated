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

}

void DocumentManager::closeDocumentAt(int index)
{
    auto it = m_documents.begin();
    std::advance(it, index);
    m_documents.erase(it);
}

void DocumentManager::moveDocument(int from, int to)
{
    auto itFrom = m_documents.begin();
    std::advance(itFrom, from);
    auto itTo = m_documents.begin();
    std::advance(itTo, to);

    std::swap(itTo, itFrom);
}

