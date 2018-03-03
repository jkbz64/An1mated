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

// Writers and readers
#include <jsoncast.hpp>
#include <QJsonDocument>

namespace
{
    QString getFilter(const QStringList& types)
    {
        QString filter;
        filter.append("All Animation files (");
        for(const auto& type : types)
            filter.append("*." + type + " ");
        filter.append(");; ");
        for(const auto& type : types)
            filter.append(type + " (*." + type + ");; ");
        filter.chop(2);
        return filter;
    }
}

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
    //Save
    connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    ///Exit
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);


    //Main layout
    auto* layout = new QVBoxLayout(centralWidget());
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
    auto* animationEditor = new AnimationEditor(this);
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

#include <iostream>

void MainWindow::openFile()
{
    auto filter = getFilter({"json"});
    QFileInfo fileinfo(QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    QDir::currentPath(),
                                                    filter)
    );
    if(fileinfo.exists())
    {
        QFile openfile(fileinfo.absoluteFilePath());
        if(openfile.open(QIODevice::ReadOnly))
        {
            QJsonDocument document = QJsonDocument::fromJson(openfile.readAll());
            Animation animation;
            auto object = document.object();
            from_json(object.value("Animation"), animation);
            m_documentManager->addDocument<AnimationDocument>(std::move(animation));
        }
    }
}

void MainWindow::saveFile()
{
    auto filter = getFilter({"json"});
    QFileInfo fileinfo(QFileDialog::getSaveFileName(this,
                                           tr("Save file"),
                                           QDir::currentPath(),
                                           filter)
    );
    
    QFile openfile(fileinfo.absoluteFilePath());
    if(openfile.open(QIODevice::WriteOnly))
    {
        json exported;
        to_json(exported, qobject_cast<AnimationDocument*>(m_currentDocument.data())->getAnimation());
        QJsonObject obj;
        obj.insert("Animation", exported);
        QJsonDocument document(obj);
        openfile.write(document.toJson());
    }
}

void MainWindow::setDocument(QSharedPointer<Document> document)
{
    m_currentDocument = document;
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
