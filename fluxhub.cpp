#include "fluxhub.h"
#include <QRunnable>
#include <QThreadPool>
#include <QFutureInterface>

FluxHub::FluxHub(QObject *parent) : QObject(parent)
{

}

SimplePromise * FluxHub::promise()
{
    return new SimplePromise(this);
}

QFuture<Result> FluxHub::asyncFuncA(QString msg)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(QString msg, QFutureInterface<Result> futureInterface)
            : m_msg(msg), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func A running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_msg + " funcA"));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func A stopped...";
            m_futureInterface.reportFinished();
        }
        QString m_msg;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(msg, futureInterface));
    auto future = futureInterface.future();
    return future;
}

QFuture<Result> FluxHub::asyncFuncB(QString msg)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(QString msg, QFutureInterface<Result> futureInterface)
            : m_msg(msg), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func B running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_msg + " funcB"));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func B stopped...";
            m_futureInterface.reportFinished();
        }
        QString m_msg;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(msg, futureInterface));
    auto future = futureInterface.future();
    return future;
}

QFuture<Result> FluxHub::asyncFuncC(QString msg)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(QString msg, QFutureInterface<Result> futureInterface)
            : m_msg(msg), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func C running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_msg + " funcC"));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func C stopped...";
            m_futureInterface.reportFinished();
        }
        QString m_msg;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(msg, futureInterface));
    auto future = futureInterface.future();
    return future;
}

QFuture<Result> FluxHub::asyncFuncD(int val)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(int val, QFutureInterface<Result> futureInterface)
            : m_val(val), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func D running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_val + 1));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func D stopped...";
            m_futureInterface.reportFinished();
        }
        int m_val;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(val, futureInterface));
    auto future = futureInterface.future();
    return future;
}

QFuture<Result> FluxHub::asyncFuncE(QString msg, int val)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(QString msg, int val, QFutureInterface<Result> futureInterface)
            : m_msg(msg), m_val(val), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func E running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_msg + " funcE" + QString(" %1").arg(m_val)));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func E stopped...";
            m_futureInterface.reportFinished();
        }
        QString m_msg;
        int m_val;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(msg, val, futureInterface));
    auto future = futureInterface.future();
    return future;
}

QFuture<Result> FluxHub::asyncFuncF(QString msg)
{
    class Runnable: public QRunnable
    {
    public:
        Runnable(QString msg, QFutureInterface<Result> futureInterface)
            : m_msg(msg), m_futureInterface(futureInterface)
        {}
        virtual void run() override{
            m_futureInterface.reportStarted();
            qDebug()<<"async func F running...";
            QThread::currentThread()->msleep(3000);
            Result result(QVariant::fromValue(m_msg + " funcF"));
            m_futureInterface.reportResult(&result);
            qDebug()<<"async func F stopped...";
            m_futureInterface.reportFinished();
        }
        QString m_msg;
        QFutureInterface<Result> m_futureInterface;

    };

    QFutureInterface<Result> futureInterface;
    QThreadPool::globalInstance()->start(new Runnable(msg, futureInterface));
    auto future = futureInterface.future();
    return future;
}
