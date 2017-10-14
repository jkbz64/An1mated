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
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

#include <animationwriter.hpp>
#include <animationreader.hpp>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    :
      QMainWindow(parent, flags),
      m_ui(new Ui::MainWindow),
      m_documentManager(new DocumentManager(this))
{
    m_ui->setupUi(this);

    m_ui->toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    m_ui->actionSave->setEnabled(false);

    //Toolbar
    //New
    connect(m_ui->actionNewAnimation, &QAction::triggered, this, &MainWindow::newAnimationDocument);
    //Open
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    ///Exit
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);


    //Main layout
    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    //Line under Toolbar
    QWidget* hLine = new QWidget(this);
    hLine->setFixedHeight(2);
    hLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    hLine->setStyleSheet("background-color: #c0c0c0;");
    layout->addWidget(hLine);
    //Document bar
    layout->addWidget(m_documentManager->getDocumentBar());
    //Editor stack - No Editor, Animation Editor and Multi Animation Editor(TODO)
    m_editorStack = new QStackedLayout;
    //0 - No editor stack layer
    QLabel* noEditorLabel = new QLabel(this);
    noEditorLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    noEditorLabel->setText("Create new animation or open existing one");
    noEditorLabel->setAlignment(Qt::AlignCenter);
    m_editorStack->addWidget(noEditorLabel);
    //1 - Editor layer
    AnimationEditor* animationEditor = new AnimationEditor(this);
    m_editorStack->addWidget(animationEditor);

    layout->addLayout(m_editorStack);

    //Connect document maanger
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, this, &MainWindow::setDocument);
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, animationEditor, &AnimationEditor::setDocument);
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
    QStringList types;
    types = AnimationReader::getReadTypes();
    if(types.isEmpty())
    {
        QMessageBox::warning(this, "No readers available", "No availabe readers, check reader directory", QMessageBox::Ok);
        return;
    }

    QString filter;
    filter.append("All Animation files (");
    for(const auto& type : types)
        filter.append("*." + type + " ");
    filter.append(");; ");
    for(const auto& type : types)
        filter.append(type.toUpper() + " (*." + type + ");; ");
    filter.chop(2);

    QFileInfo fileinfo(QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    QDir::currentPath(),
                                                    filter));
    if(fileinfo.exists())
    {
        QFile openfile(fileinfo.absoluteFilePath());
        if(openfile.open(QIODevice::ReadOnly))
        {
            try {
                auto&& animation = AnimationReader::deserialize(fileinfo.suffix(), openfile.readAll().toStdString());
                m_documentManager->addDocument<AnimationDocument>(std::move(animation));
            }
            catch(sol::error& e)
            {
                QMessageBox::warning(this, "Deserialization error", QString(e.what()), QMessageBox::Ok);
            }
            catch(std::bad_alloc& e)
            {
                QMessageBox::warning(this, "Couldn't allocate document", QString(e.what()), QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::setDocument(std::shared_ptr<Document> document)
{
    m_ui->actionSave->setEnabled(false);
    m_ui->actionEditSpritesheet->setEnabled(false);
    if(document)
    {
        setEditorType(document->getType());
        if(!document->getFileName().isEmpty())
            m_ui->actionSave->setEnabled(true);
    }
    else
        setEditorType(static_cast<Document::DocumentType>(-1));
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
        m_ui->actionEditSpritesheet->setEnabled(true);
        break;
    default:
        m_editorStack->setCurrentIndex(0);
        break;
    }
}
