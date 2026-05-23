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
}