#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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


private slots:
    void newAnimationDocument();
    void openFile();

private:
    Ui::MainWindow* m_ui;
    DocumentManager* m_documentManager;
    QStackedLayout* m_editorStack;
};


#endif
