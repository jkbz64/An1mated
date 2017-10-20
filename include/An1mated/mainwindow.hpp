#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <document.hpp>
#include <memory>


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
    void setDocument(std::shared_ptr<Document>);
private:
    Ui::MainWindow* m_ui;
    DocumentManager* m_documentManager;
    std::shared_ptr<Document> m_currentDocument;
    QStackedLayout* m_editorStack;
};


#endif
