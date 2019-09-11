#include "fluxhub.h"
#include <QRunnable>
#include <QThreadPool>
#include <QtConcurrent>

FluxHub::FluxHub(QObject *parent) : QObject(parent)
{

}

SimplePromise * FluxHub::promise()
{
    return new SimplePromise(this);
}

QFuture<Result> FluxHub::asyncFuncA(QString msg)
{
    auto future = QtConcurrent::run([](QString msg)->Result{
            qDebug()<<"async func A running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(msg + " funcA"));
            qDebug()<<"async func A stopped...";
            return result;
}, msg);
    return future;
}

QFuture<Result> FluxHub::asyncFuncB(QString msg)
{
    auto future = QtConcurrent::run([](QString msg)->Result{
            qDebug()<<"async func B running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(msg + " funcB"));
            qDebug()<<"async func B stopped...";
            return result;
}, msg);
    return future;
}

QFuture<Result> FluxHub::asyncFuncC(QString msg)
{
    auto future = QtConcurrent::run([](QString msg)->Result{
            qDebug()<<"async func C running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(msg + " funcC"));
            qDebug()<<"async func C stopped...";
            return result;
}, msg);
    return future;
}

QFuture<Result> FluxHub::asyncFuncD(int val)
{
    auto future = QtConcurrent::run([](int val)->Result{
        qDebug()<<"async func D running...";
        QThread::currentThread()->msleep(3000);
        Result result(QVariant::fromValue(val + 1));
        qDebug()<<"async func D stopped...";
        return result;
    }, val);
    return future;
}

QFuture<Result> FluxHub::asyncFuncE(QString msg, int val)
{
    auto future = QtConcurrent::run([](QString msg, int val)->Result{
            qDebug()<<"async func E running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(msg + " funcE" + QString(" %1").arg(val)));
            qDebug()<<"async func E stopped...";
            return result;
}, msg, val);
    return future;
}

QFuture<Result> FluxHub::asyncFuncF(QString msg)
{
    auto future = QtConcurrent::run([](QString msg)->Result{
            qDebug()<<"async func F running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(msg + " funcF"));
            qDebug()<<"async func F stopped...";
            return result;
}, msg);
    return future;
}
