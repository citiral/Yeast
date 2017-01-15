//
// Created by Olivier on 01/08/16.
//

#ifndef YEAST_PROJECTTREE_H
#define YEAST_PROJECTTREE_H

#include <QTreeWidget>
#include <editor/project/Project.h>
#include <QTreeWidgetItem>
#include <memory>
#include <QFileInfo>

class ProjectTree : public QTreeWidget {
Q_OBJECT
public:
    ProjectTree(QWidget *parent = nullptr);

signals:
    void EntityOpened(const QFileInfo& entity);
    void ScriptOpened(const QFileInfo& script);
    void WorldOpened(const QFileInfo& world);

public slots:
    void ProjectChanged(Project* project);

private slots:
    void itemChanged(QTreeWidgetItem* item, int column);

private:
    void populateWithDirectory(QTreeWidgetItem* item, const QString& directory, int itemType);

    QTreeWidgetItem* _worlds;
    QTreeWidgetItem* _entities;
    QTreeWidgetItem* _scripts;
};


#endif //YEAST_PROJECTTREE_H
