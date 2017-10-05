#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <animationdocument.hpp>
#include <QLabel>

#include <QInputDialog>

#include <animation.hpp>
#include <animationeditor.hpp>

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


    ///Exit
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    //Connect document manager
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, this, &MainWindow::updateEditor);



    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    //Place document bar at the top
    layout->addWidget(m_documentManager->getDocumentBar());
    m_editorStack = new QStackedLayout;
    //0 - No editor stack layer
    QLabel* noEditorLabel = new QLabel(this);
    noEditorLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    noEditorLabel->setText("Create new animation or open existing one");
    noEditorLabel->setAlignment(Qt::AlignCenter);
    m_editorStack->addWidget(noEditorLabel);
    //1 - Editor layer
    AnimationEditor* animationEditor = new AnimationEditor(this);
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, animationEditor, &AnimationEditor::setDocument);

    m_editorStack->addWidget(animationEditor);

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
    bool ok;
    QString animationName = QInputDialog::getText(this, QString("Type new animation name:"), QString("Animation name:"),
                                                  QLineEdit::Normal, "", &ok);
    if(ok && !animationName.isEmpty())
        m_documentManager->addDocument<AnimationDocument>(animationName);
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
