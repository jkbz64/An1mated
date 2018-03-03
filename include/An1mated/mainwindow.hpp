#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <document.hpp>
#include <memory>
#include <QPointer>

namespace Ui
{
    class MainWindow;
}

class DocumentManager;
class QStackedLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    ~MainWindow();
    void setEditorType(const Document::DocumentType&);
public slots:
    void newAnimationDocument();
    void openFile();
    void saveFile();
    void setDocument(QSharedPointer<Document>);
private:
    Ui::MainWindow* m_ui;
    QPointer<DocumentManager> m_documentManager;
    QSharedPointer<Document> m_currentDocument;
    QPointer<QStackedLayout> m_editorStack;
};


#endif
