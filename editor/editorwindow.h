#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "ui_editorwindow.h"
#include "editor/project/Project.h"

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void ProjectChanged(Project* project);

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

    static EditorWindow* getInstance();
    Project* getProject();

public slots:
    void OpenEntity(const QFileInfo& entity);
    void OpenScript(const QFileInfo& script);
    void OpenWorld(const QFileInfo& world);

    void tabClosed(int index);

private slots:
    void NewProject();
    void OpenProject();
    void CloseProject();
    void tabChanged(int index);

private:
    static EditorWindow* _instance;
    Project* _project;
    Ui::EditorWindow* ui;
};

#endif // EDITORWINDOW_H
