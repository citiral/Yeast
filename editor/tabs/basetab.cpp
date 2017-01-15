//
// Created by Olivier on 05/08/16.
//

#include "basetab.h"


BaseTab::BaseTab(QWidget* parent): QWidget(parent) {

};

BaseTab::~BaseTab() {

}

void BaseTab::setIndex(int index) {
    _index = index;
}

int BaseTab::getIndex() const {
    return _index;
};