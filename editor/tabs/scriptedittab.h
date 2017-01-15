#ifndef SCRIPTEDITTAB_H
#define SCRIPTEDITTAB_H

#include <QWidget>
#include <QtCore/QFileInfo>
#include "basetab.h"

namespace Ui {
class ScriptEditTab;
}

class ScriptEditTab : public BaseTab
{
    Q_OBJECT

public:
    explicit ScriptEditTab(QWidget *parent, QFileInfo script);
    ~ScriptEditTab();

    virtual void save();
    virtual void close();
    virtual void reload();
    virtual bool hasChanged();

protected slots:
    void textHasChanged();

private:
    QFileInfo _info;
    Ui::ScriptEditTab *ui;
    bool _hasChanged;
};

#endif // SCRIPTEDITTAB_H
