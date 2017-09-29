#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <animationdocument.hpp>
#include <QLabel>

#include <animation.hpp>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    :
      QMainWindow(parent, flags),
      m_ui(new Ui::MainWindow),
      m_documentManager(DocumentManager::instance())
{
    m_ui->setupUi(this);

    //File bar
    //New
    connect(m_ui->actionNewAnimation, &QAction::triggered, this, &MainWindow::newAnimationDocument);
    //Open
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);

    //Connect document manager
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, this, &MainWindow::updateEditor);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    layout->addWidget(m_documentManager->getDocumentBar());
    m_editorStack = new QStackedLayout;
    QWidget* spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_editorStack->addWidget(spacerWidget);
    m_editorStack->addWidget(new QLabel("lol"));
    m_editorStack->addWidget(new QLabel("DOTA"));
    layout->addLayout(m_editorStack);
}

MainWindow::~MainWindow()
{
    DocumentManager::deleteInstance();
    delete m_editorStack;
    delete m_ui;
}

void MainWindow::newAnimationDocument()
{
    m_documentManager->addDocument(std::make_shared<AnimationDocument>(Animation("lul")));
}

void MainWindow::openFile()
{

}

void MainWindow::updateEditor(std::weak_ptr<Document> doc)
{
    if(auto document = doc.lock())
    {
        switch(document->getType())
        {
        case Document::DocumentType::AnimationDocument:
            m_editorStack->setCurrentIndex(1);
        break;
        case Document::DocumentType::MultiAnimationDocument:
            m_editorStack->setCurrentIndex(2);
        break;
        default:
            m_editorStack->setCurrentIndex(0);
        break;
        }
    }
    else
        m_editorStack->setCurrentIndex(0);
}
