#ifndef ENTITYEDITTAB_H
#define ENTITYEDITTAB_H

#include <QWidget>
#include <QtCore/QFileInfo>
#include "tabs/basetab.h"

namespace Ui {
class EntityEditTab;
}

class EntityEditTab : public BaseTab
{
    Q_OBJECT

public:
    explicit EntityEditTab(QWidget *parent, QFileInfo entity);
    ~EntityEditTab();

    virtual void save();
    virtual void close();
    virtual void reload();
    virtual bool hasChanged();

private:
    QFileInfo _info;
    Ui::EntityEditTab *ui;
    bool _hasChanged;
};

#endif // ENTITYEDITTAB_H
