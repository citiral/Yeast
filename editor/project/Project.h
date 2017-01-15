//
// Created by Olivier on 01/08/16.
//

#ifndef YEAST_PROJECT_H
#define YEAST_PROJECT_H

#include <QtCore/QString>
#include <QList>

class Project {
public:
    Project(QString location);

    const QString& getLocation() const;



private:
    QString _location;
};


#endif //YEAST_PROJECT_H
