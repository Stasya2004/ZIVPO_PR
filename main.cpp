#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QSharedMemory>
#include <QIcon>
#include <QAbstractNativeEventFilter>

#include <windows.h>

#include "MainWindow.h"

class WinTaskbarFilter : public QAbstractNativeEventFilter
{
public:
    QSystemTrayIcon *trayIcon = nullptr;

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override
    {
        Q_UNUSED(eventType)
        Q_UNUSED(result)

        MSG *msg = static_cast<MSG *>(message);

        static UINT WM_TASKBARCREATED =
            RegisterWindowMessage(TEXT("TaskbarCreated"));

        if (msg->message == WM_TASKBARCREATED)
        {
            if (trayIcon)
            {
                trayIcon->show();
                trayIcon->setVisible(true);
            }
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Защита от второго запуска
    QSharedMemory shared("MyUniqueTrayApp");

    if (!shared.create(1))
    {
        return 0;
    }

    // Главное окно
    MainWindow window;

    // Иконка трея
    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":/icon.ico"));
    trayIcon.setToolTip("Tray Application");

    // Меню трея
    QMenu trayMenu;

    QAction openAction("Открыть");
    QAction exitAction("Выход");

    trayMenu.addAction(&openAction);
    trayMenu.addAction(&exitAction);

    trayIcon.setContextMenu(&trayMenu);

    // Открыть окно
    QObject::connect(&openAction, &QAction::triggered, [&]()
                     {
                         window.show();
                         window.raise();
                         window.activateWindow();
                     });

    // Выход
    QObject::connect(&exitAction, &QAction::triggered, [&]()
                     {
                         QApplication::quit();
                     });

    // ЛКМ по трею
    QObject::connect(&trayIcon, &QSystemTrayIcon::activated,
                     [&](QSystemTrayIcon::ActivationReason reason)
                     {
                         if (reason == QSystemTrayIcon::Trigger)
                         {
                             window.show();
                             window.raise();
                             window.activateWindow();
                         }
                     });

    // Восстановление иконки после перезапуска панели задач
    WinTaskbarFilter *filter = new WinTaskbarFilter;
    filter->trayIcon = &trayIcon;

    app.installNativeEventFilter(filter);

    // Запуск трея
    trayIcon.show();

    // Окно не показываем при старте
    // window.show();

    return app.exec();
}