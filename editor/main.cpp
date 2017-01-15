#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "editorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Just Doing This For Beer");
    QCoreApplication::setApplicationName("Yeast");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    EditorWindow mainWin;
    mainWin.show();

    return app.exec();
}