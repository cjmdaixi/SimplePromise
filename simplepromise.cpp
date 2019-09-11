#include "simplepromise.h"
#include <QCoreApplication>
#include <QtDebug>

static int RESULT_TYPE = qRegisterMetaType<QFuture<Result> >();

SimplePromise::SimplePromise(QObject *parent) : QObject(parent)
{
}

SimplePromise::Status SimplePromise::status() const
{
    return m_status;
}

void SimplePromise::resolveWhen(QVariant prerequsite)
{
    QVariantList prerequsites;
    prerequsites<<prerequsite;
    resolveWhen(prerequsites);
}

void SimplePromise::resolveWhen(QVariantList prerequsites)
{
    if(m_status != Undefined){
        throw PromiseException("status invalid!");
    }
    m_currentCount = 0;
    m_totalCount = prerequsites.size();
    m_results.resize(m_totalCount);

    for(auto i = 0; i != m_totalCount; ++i){
        const auto variant = prerequsites[i];
        auto const t = int(variant.type());
        if(t == QMetaType::QObjectStar){
            auto promiseObj = qobject_cast<SimplePromise*>(variant.value<QObject*>());
            if(promiseObj != nullptr){
                connect(promiseObj, &SimplePromise::resolved, this, [i, this](QVariantList results){
                    if(status() == Pending){
                        auto var = QVariant::fromValue(results);
                        prerequsiteResolved(i, var);
                    }
                });
                connect(promiseObj, &SimplePromise::rejected, this, [&](QString reason){
                    reject(reason);
                });
            }else{
                throw PromiseException("resolveWhen can only handle future or promise type!");
            }
        }
        else if(t == RESULT_TYPE){
            auto watcher = new AsyncResultWatcher(this);
            connect(watcher, &AsyncResultWatcher::finished, [watcher, i, this]{
                auto result = watcher->result();
                if(result.success()){
                    prerequsiteResolved(i, result.data());
                }
                else{
                    reject(result.reason());
                }
            });
            watcher->setFuture(variant.value<QFuture<Result> >());
        }
    }
    setStatus(Pending);
}

void SimplePromise::resolve(QVariantList results)
{
    if(m_resolvedHandler.isCallable()){
        auto engine = qjsEngine(this);
        QJSValueList params;
        for(const auto &result : results){
            auto jsValue = engine->toScriptValue(result);
            params<<jsValue;
        }
        m_resolvedHandler.call(params);
    }
    m_results = results.toVector();
    emit resolved(results);
}

void SimplePromise::reject(QString reason)
{
    if(m_rejectedHandler.isCallable()){
        auto engine = qjsEngine(this);
        auto jsValue = engine->toScriptValue<QString>(reason);
        m_rejectedHandler.call({jsValue});
    }
    setStatus(Rejected);
    emit rejected(reason);
}

void SimplePromise::onResolved(QJSValue callable)
{
    if(callable.isCallable() == false){
        throw PromiseException("Not a callable jsvalue!");
    }
    m_resolvedHandler = callable;
}

void SimplePromise::onRejected(QJSValue callable)
{
    if(callable.isCallable() == false){
        throw PromiseException("Not a callable jsvalue!");
    }
    m_rejectedHandler = callable;
}

void SimplePromise::prerequsiteResolved(int idx, QVariant result)
{
    m_results[idx] = result;
    m_currentCount++;
    if(m_currentCount == m_totalCount){
        setStatus(Resolved);
        resolve(m_results.toList());
    }
}

void SimplePromise::setStatus(SimplePromise::Status status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

PromiseException::PromiseException(const char *why)
    : m_why(why)
{

}

const char *PromiseException::what() const noexcept
{
    return  m_why;
}
