#include <fstream>
#include <engine/blueprints/EntityBlueprint.h>
#include "entityedittab.h"
#include "ui_entityedittab.h"

EntityEditTab::EntityEditTab(QWidget *parent, QFileInfo entity) :
        BaseTab(parent),
    ui(new Ui::EntityEditTab), _info(entity), _hasChanged(false)
{
    ui->setupUi(this);

    reload();
}

EntityEditTab::~EntityEditTab()
{
    delete ui;
}

void EntityEditTab::reload() {
    std::ifstream file;
    file.open(_info.absoluteFilePath().toStdString(), std::ifstream::in);

    if (file.is_open()) {
        json j(file);

        ui->nameEdit->setText(_info.baseName());

        file.close();
    }
}

void EntityEditTab::save() {

}

void EntityEditTab::close() {

}

bool EntityEditTab::hasChanged() {
    return _hasChanged;
}