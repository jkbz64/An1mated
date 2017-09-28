#include <documentmanager.hpp>
#include <QTabBar>
#include <QVBoxLayout>

DocumentManager* DocumentManager::m_instance = nullptr;

DocumentManager::DocumentManager(QObject* parent)
    :
      QObject(parent),
      m_widget(new QWidget),
      m_documentTabBar(new QTabBar(m_widget))
{
    //Setup tab bar
    m_documentTabBar->setExpanding(true);
    m_documentTabBar->setDocumentMode(true);
    m_documentTabBar->setTabsClosable(true);
    m_documentTabBar->setMovable(true);

    connect(m_documentTabBar, &QTabBar::currentChanged, this, &DocumentManager::updateCurrentDocument);
    connect(m_documentTabBar, &QTabBar::tabCloseRequested, this, &DocumentManager::closeDocumentAt);
    connect(m_documentTabBar, &QTabBar::tabMoved, this, &DocumentManager::moveDocument);

    //Setup layout
    QVBoxLayout *layout = new QVBoxLayout(m_widget);
    layout->addWidget(m_documentTabBar);

    m_widget->setLayout(layout);
}

DocumentManager::~DocumentManager()
{
    delete m_widget;
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

