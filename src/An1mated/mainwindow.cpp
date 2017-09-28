#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    :
      QMainWindow(parent, flags),
      m_ui(new Ui::MainWindow),
      m_documentManager(DocumentManager::instance())
{
    m_ui->setupUi(this);

    //File bar
    //New
    connect(m_ui->actionNew, &QAction::triggered, this, &MainWindow::newDocument);
    //Open
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);

    setCentralWidget(m_documentManager->widget());
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::newDocument()
{

}

void MainWindow::openFile()
{

}
