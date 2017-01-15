#include "scriptedittab.h"
#include "ui_scriptedittab.h"
#include <QFile>
#include <iostream>

ScriptEditTab::ScriptEditTab(QWidget *parent, QFileInfo script) :
    BaseTab(parent),
    _info(script),
    ui(new Ui::ScriptEditTab)
{
    ui->setupUi(this);
    reload();

    QObject::connect(ui->codeEdit, QTextEdit::textChanged, this, ScriptEditTab::textHasChanged);
}

ScriptEditTab::~ScriptEditTab()
{
    delete ui;
}

void ScriptEditTab::reload() {
    ui->codeEdit->clear();

    QFile file(_info.filePath());

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while (!file.atEnd()) {
        QString line = file.readLine();
        ui->codeEdit->insertPlainText(line);
    }

    _hasChanged = false;
}

void ScriptEditTab::save() {

}

void ScriptEditTab::close() {

}

bool ScriptEditTab::hasChanged() {
    return _hasChanged;
}

void ScriptEditTab::textHasChanged() {
    emit changed(getIndex());
    _hasChanged = true;
}



