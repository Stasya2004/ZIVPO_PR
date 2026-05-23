#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Tray App");
    resize(500, 300);

    QMenu *file = menuBar()->addMenu("Файл");

    QAction *exit = new QAction("Выход", this);

    file->addAction(exit);

    connect(exit, &QAction::triggered,
            qApp, &QApplication::quit);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
