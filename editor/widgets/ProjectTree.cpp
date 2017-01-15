//
// Created by Olivier on 01/08/16.
//

#include <iostream>
#include <QtCore/QDir>
#include <QtWidgets/QFileSystemModel>
#include "ProjectTree.h"
#include "EditorWindow.h"
#include <paths.h>

struct ProjectItemType {
    enum {
        Folder,
        Entity,
        World,
        Script,
    };
};

ProjectTree::ProjectTree(QWidget *parent): QTreeWidget(parent) {
    setColumnCount(1);
    QObject::connect(this, &itemActivated, this, &itemChanged);
}

void ProjectTree::ProjectChanged(Project* project) {
    clear();

    _entities = new QTreeWidgetItem(this, QStringList(QString("Entities")), ProjectItemType::Folder);
    _worlds = new QTreeWidgetItem(this, QStringList(QString("Worlds")), ProjectItemType::Folder);
    _scripts = new QTreeWidgetItem(this, QStringList(QString("Scripts")), ProjectItemType::Folder);

    populateWithDirectory(_entities, EditorWindow::getInstance()->getProject()->getLocation() + FOLDER_ENTITIES, ProjectItemType::Entity);
    populateWithDirectory(_worlds, EditorWindow::getInstance()->getProject()->getLocation() + FOLDER_WORLDS, ProjectItemType::World);
    populateWithDirectory(_scripts, EditorWindow::getInstance()->getProject()->getLocation() + FOLDER_SCRIPTS, ProjectItemType::Script);
}

void ProjectTree::populateWithDirectory(QTreeWidgetItem* item, const QString& directory, int itemType) {
    QDirIterator it(directory, QDirIterator::NoIteratorFlags);

    std::cout << "iterating in " << directory.toStdString() << std::endl;
    while (it.hasNext()) {
        it.next();

        if (it.fileInfo().isHidden()) {
            continue;
        }

        if (it.fileInfo().isDir()) {
            if (it.fileName() == "." || it.fileName() == "..")
                continue;

            populateWithDirectory(new QTreeWidgetItem(item, QStringList() << it.fileName(), ProjectItemType::Folder), it.filePath(), itemType);
        } else if (it.fileInfo().isFile()) {
            new QTreeWidgetItem(item, QStringList() << it.fileInfo().baseName() << it.filePath(), itemType);
        }
    }
}

void ProjectTree::itemChanged(QTreeWidgetItem* item, int column) {
    if (item->type() == ProjectItemType::Folder)
        return;
    else {
        QFileInfo info = QFileInfo(item->data(1, Qt::DisplayRole).toString());

        if (item->type() == ProjectItemType::Entity)
            EntityOpened(info);
        else if (item->type() == ProjectItemType::World)
            WorldOpened(info);
        else if (item->type() == ProjectItemType::Script)
            ScriptOpened(info);
    }
}
