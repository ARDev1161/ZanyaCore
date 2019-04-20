#ifndef SYNTHEZISE_H
#define SYNTHEZISE_H

#include <QObject>

class Synthezise : public QObject
{
    Q_OBJECT
public:
    explicit Synthezise(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SYNTHEZISE_H