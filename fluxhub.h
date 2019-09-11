#ifndef FLUXHUB_H
#define FLUXHUB_H

#include <QObject>
#include <QVariant>
#include <QtDebug>
#include "simplepromise.h"

class FluxHub : public QObject
{
    Q_OBJECT
public:
    explicit FluxHub(QObject *parent = nullptr);

signals:

public slots:
    SimplePromise *promise();
    QFuture<Result> asyncFuncA(QString msg);
    QFuture<Result> asyncFuncB(QString msg);
    QFuture<Result> asyncFuncC(QString msg);
    QFuture<Result> asyncFuncD(int val);
    QFuture<Result> asyncFuncE(QString msg, int val);
    QFuture<Result> asyncFuncF(QString msg);
};

#endif // FLUXHUB_H
