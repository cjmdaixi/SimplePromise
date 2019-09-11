#ifndef SIMPLEPROMISE_H
#define SIMPLEPROMISE_H

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include <QtDebug>
#include <QJSValue>
#include <QJSEngine>
#include <QVariantMap>
#include <QException>
#include <QList>
#include <QVector>

class Result
{
    Q_GADGET

public:
    Q_PROPERTY(bool success READ success)
    Q_PROPERTY(QString reason READ reason)
    Q_PROPERTY(QVariant data READ data)

    Result() = default;
    Result(QString reason)
        : m_success(false), m_reason(reason)
    {}
    Result(QVariant data)
        : m_success(true), m_data(data)
    {}
    bool success() const
    {
        return m_success;
    }
    QVariant data() const
    {
        return m_data;
    }
    QString reason() const
    {
        return m_reason;
    }

private:
    bool m_success;

    QVariant m_data;
    QString m_reason;
};

class PromiseException : public QException
{
public:
    PromiseException(const char *why);
    virtual const char *what() const noexcept;
private:
    const char *m_why;
};

class SimplePromise : public QObject
{
    Q_OBJECT
public:
    typedef QFutureWatcher<Result> AsyncResultWatcher;

    enum Status{
        Undefined,
        Pending,
        Resolved,
        Rejected
    };
    Q_ENUM(Status)

    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    explicit SimplePromise(QObject *parent = nullptr);

    Status status() const;
    void setStatus(Status status);
signals:
    void resolved(QVariantList results);
    void rejected(QString reason);
    void statusChanged(Status status);

public slots:
    void resolveWhen(QVariant prerequsite);
    void resolveWhen(QVariantList prerequsites);
    void resolve(QVariantList results);
    void reject(QString reason);
    void onResolved(QJSValue callable);
    void onRejected(QJSValue callable);
private:
    void prerequsiteResolved(int idx, QVariant result);
private:
    Status m_status = Undefined;
    int m_totalCount = 0, m_currentCount = 0;
    QVector<QVariant> m_results;
    QJSValue m_resolvedHandler, m_rejectedHandler;
};

Q_DECLARE_METATYPE(QFuture<Result>)
#endif // SIMPLEPROMISE_H
