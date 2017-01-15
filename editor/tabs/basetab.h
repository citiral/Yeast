//
// Created by Olivier on 02/08/16.
//

#ifndef YEAST_BASETAB_H
#define YEAST_BASETAB_H

#include <QWidget>

class BaseTab: public QWidget {
    Q_OBJECT

public:
    BaseTab(QWidget* parent = nullptr);
    virtual ~BaseTab();

    virtual void save() = 0;
    virtual void close() = 0;
    virtual void reload() = 0;
    virtual bool hasChanged() = 0;

    void setIndex(int index);
    int getIndex() const;

signals:
    void changed(int index);

private:
    int _index;
};


#endif //YEAST_BASETAB_H
