#include <mainwindow.hpp>
#include "ui_mainwindow.h"
#include <documentmanager.hpp>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <animationdocument.hpp>
#include <QLabel>

#include <QInputDialog>

#include <animation.hpp>
#include <animationpreview.hpp>

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
    //Place document bar at the top
    layout->addWidget(m_documentManager->getDocumentBar());
    m_editorStack = new QStackedLayout;
    //0 - No editor stack layer
    QLabel* noEditorLabel = new QLabel(this);
    noEditorLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    noEditorLabel->setText("Create new animation or open existing one");
    noEditorLabel->setAlignment(Qt::AlignHCenter);
    m_editorStack->addWidget(noEditorLabel);
    //1 - Editor layer
    AnimationPreview* animationPreview = new AnimationPreview(this);
    m_editorStack->addWidget(animationPreview);

    //TEMPORARY SOLUTION FOR CERTAIN EDITOR
    connect(m_documentManager, &DocumentManager::currentDocumentChanged, [animationPreview](std::weak_ptr<Document> doc)
    {
        if(auto document = doc.lock())
            animationPreview->setAnimation(qobject_cast<AnimationDocument*>(doc.lock().get())->m_animation);
    });


    //END TEMPORARY SOLUTION

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
        m_documentManager->addDocument<AnimationDocument>(std::make_shared<Animation>(animationName));
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
