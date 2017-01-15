#include <QFileDialog>
#include <QtCore/QSettings>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include "editorwindow.h"
#include "tabs/scriptedittab.h"
#include "tabs/entityedittab.h"

EditorWindow* EditorWindow::_instance = nullptr;

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    _project(nullptr),
    ui(new Ui::EditorWindow)
{
    _instance = this;
    ui->setupUi(this);
    QSettings settings;

    // setup all links
    QObject::connect(ui->actionOpen_Project, SIGNAL(triggered()), this, SLOT(OpenProject()));
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered()), this, SLOT(NewProject()));
    QObject::connect(this, &ProjectChanged, (ProjectTree*)ui->projectTree, &ProjectTree::ProjectChanged);
    QObject::connect((ProjectTree*)ui->projectTree, &ProjectTree::EntityOpened, this, &OpenEntity);
    QObject::connect((ProjectTree*)ui->projectTree, &ProjectTree::WorldOpened, this, &OpenWorld);
    QObject::connect((ProjectTree*)ui->projectTree, &ProjectTree::ScriptOpened, this, &OpenScript);
    QObject::connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &tabClosed);

    // open the last project if there was one
    if (settings.value("Project_open", false) == true) {
        _project = new Project(settings.value("Project_dir").toString());
        ProjectChanged(_project);
    }
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::NewProject() {

}

void EditorWindow::OpenProject() {
    QSettings settings;
    QString location = QFileDialog::getExistingDirectory(this, tr("Open Project"), settings.value("Project_dir", "C:/").toString());
    settings.setValue("Project_dir", location);
    settings.setValue("Project_open", true);
    _project = new Project(location);
    emit ProjectChanged(_project);
}

void EditorWindow::CloseProject() {
    QSettings settings;
    settings.setValue("Project_open", false);
}

Project* EditorWindow::getProject() {
    return _project;
}

EditorWindow* EditorWindow::getInstance() {
    return _instance;
}

void EditorWindow::OpenEntity(const QFileInfo& entity) {
    EntityEditTab* tab = new EntityEditTab(ui->tabWidget, entity);
    int i = ui->tabWidget->addTab(tab, entity.fileName());
    ui->tabWidget->setCurrentIndex(i);
    tab->setIndex(i);
    QObject::connect(tab, &BaseTab::changed, this, &tabChanged);
}

void EditorWindow::OpenScript(const QFileInfo& script) {
    ScriptEditTab* tab = new ScriptEditTab(ui->tabWidget, script);
    int i = ui->tabWidget->addTab(tab, script.fileName());
    ui->tabWidget->setCurrentIndex(i);
    tab->setIndex(i);
    QObject::connect(tab, &BaseTab::changed, this, &tabChanged);
}

void EditorWindow::OpenWorld(const QFileInfo& world) {

}

void EditorWindow::tabClosed(int index) {
    BaseTab* tab = static_cast<BaseTab*>(ui->tabWidget->widget(index));

    if (tab->hasChanged() && QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Save file", "Do you want to save the file before closing it?", QMessageBox::Yes|QMessageBox::No).exec())
        tab->save();

    tab->close();
    ui->tabWidget->removeTab(index);
}

void EditorWindow::tabChanged(int index) {
    QString name = ui->tabWidget->tabText(index);
    if (name.endsWith('*'))
        return;
    else
        ui->tabWidget->setTabText(index, name + " *");
}