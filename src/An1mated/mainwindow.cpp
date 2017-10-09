#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <animationdocument.hpp>
#include <QLabel>

#include <QInputDialog>
#include <newanimationdialog.hpp>

#include <animation.hpp>
#include <animationeditor.hpp>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    :
      QMainWindow(parent, flags),
      m_ui(new Ui::MainWindow),
      m_documentManager(new DocumentManager(this))
{
    m_ui->setupUi(this);

    m_ui->toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    //File bar
    //New
    connect(m_ui->actionNewAnimation, &QAction::triggered, this, &MainWindow::newAnimationDocument);
    //Open
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);


    ///Exit
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);


    //Connect document manager
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, [this](std::shared_ptr<Document> doc)
    {
        if(doc)
        {
            setEditorType(doc->getType());
            if(doc->getFileName().isEmpty())
                m_ui->actionSave->setEnabled(false);
            else
                m_ui->actionSave->setEnabled(true);
        }
        else
        {
            setEditorType(static_cast<Document::DocumentType>(-1));
            m_ui->actionSave->setEnabled(false);
        }

    });

    m_ui->actionSave->setEnabled(false);


    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    QWidget* hLine = new QWidget(this);
    hLine->setFixedHeight(2);
    hLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    hLine->setStyleSheet("background-color: #c0c0c0;");
    layout->addWidget(hLine);
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
    delete m_editorStack;
    delete m_ui;
}

void MainWindow::newAnimationDocument()
{
    QString animationName, spritesheetName;
    NewAnimationDialog dialog(animationName, spritesheetName, this);
    if(dialog.exec() == QDialog::Accepted)
        m_documentManager->addDocument<AnimationDocument>(Animation(animationName, spritesheetName));
}

void MainWindow::openFile()
{

}

void MainWindow::setEditorType(const Document::DocumentType& type)
{
    switch(type)
    {
    case Document::DocumentType::AnimationDocument:
        m_editorStack->setCurrentIndex(1);
        m_ui->actionEditSpritesheet->setEnabled(true);
        break;
    case Document::DocumentType::MultiAnimationDocument:
        m_editorStack->setCurrentIndex(2);
        break;
    default:
        m_editorStack->setCurrentIndex(0);
        m_ui->actionEditSpritesheet->setEnabled(false);
        break;
    }
}
