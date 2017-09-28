#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>
#include <QStackedLayout>
#include <QVBoxLayout>

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

    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    layout->addWidget(m_documentManager->getDocumentBar());
    m_editorStack = new QStackedLayout;
    QWidget* spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_editorStack->addWidget(spacerWidget);
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

}

void MainWindow::openFile()
{

}
