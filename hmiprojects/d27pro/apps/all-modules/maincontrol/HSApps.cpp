﻿#include "HSApps.h"
#include "HSStore.h"

#include <QQuickItem>
#include <QVector>
#include <QPair>
#include <QDebug>

HSApps* HSApps::instance(void)
{
    static HSApps apps;
    return &apps;
}

void HSApps::anchorFill(QQuickItem* item1, QQuickItem* item2)
{
    if (item1 == Q_NULLPTR || item2 == Q_NULLPTR) return;
    auto adjustW = [item1, item2]{ item2->setWidth (item1->width() ); };
    auto adjustH = [item1, item2]{ item2->setHeight(item1->height()); };
    connect(item1, &QQuickItem::widthChanged , item2, adjustW); adjustW();
    connect(item1, &QQuickItem::heightChanged, item2, adjustH); adjustH();
}

HSApps::HSApps(QObject *parent)
    : QObject(parent)
    , m_engine(Q_NULLPTR)
    , m_root(Q_NULLPTR)
    , m_context(Q_NULLPTR)
{

}

void HSApps::registQmlEngine(QQmlEngine* engine)
{
    m_engine = engine;
    HSStore::instance()->loadDatas();
}

QQmlEngine* HSApps::getQmlEngine(void) const
{
    return m_engine;
}

QQmlContext* HSApps::getContext(void)
{
    if (m_context == Q_NULLPTR)
    {
        if (m_engine == Q_NULLPTR) return Q_NULLPTR;
        if (m_root == Q_NULLPTR) return Q_NULLPTR;
        m_context = new QQmlContext(m_engine->rootContext());
        m_context->setContextObject(m_root);
    }
    return m_context;
}

void HSApps::initRootItem(QJSValue item)
{
    if (item.isQObject())
    {
        m_root = item.toQObject();
    }
}

void HSApps::startToShow(void)
{
    system("touch /tmp/eglCreateWindowSurface_flag");
}

QQmlComponent* HSApps::createComponent(QUrl url)
{
    if (m_engine == Q_NULLPTR) return Q_NULLPTR;
    return new QQmlComponent(m_engine, url, QQmlComponent::PreferSynchronous, m_root);
}

QQmlComponent* HSApps::createComponentAsync(QUrl url, QJSValue cb)
{
    return __createComponentAsync(url, [this, cb](const QString& err, QQmlComponent* com) mutable
    {
        if (cb.isCallable())
        {
            cb.call({ err, m_engine->newQObject(com) });
        }
    });
}

struct QmlIncubator : public QQmlIncubator
{
    QObject* parent = Q_NULLPTR;
    QJSValue properties;

    QmlIncubator(IncubationMode mode = Asynchronous)
        : QQmlIncubator(mode)
    {
        qDebug("######## QmlIncubator: mode = %d", mode);
    }

    void setInitialState(QObject* obj) override
    {
        qDebug("######## QmlIncubator::setInitialState %p", obj);
        if (obj == Q_NULLPTR) return;

        obj->setParent(parent);
        QQuickItem* item = qobject_cast<QQuickItem*>(obj);
        if (item != Q_NULLPTR) item->setParentItem(qobject_cast<QQuickItem*>(parent));

        qDebug() << "######## QmlIncubator::foreachJSValue:" << properties.toVariant();
        HSApps::foreachJSValue(properties, &QJSValue::isObject, [obj](const QString& name, const QJSValue& value)
        {
            qDebug() << "#### updating:" << name;
            obj->setProperty(name.toLocal8Bit().data(), value.toVariant());
            return true;
        });
    }
};

QObject* HSApps::createObject(QQmlComponent* com, QJSValue opts)
{
    if (com == Q_NULLPTR) return Q_NULLPTR;

    // Enumerating all property-settings.
    QmlIncubator incubator(QmlIncubator::Synchronous);
    if (opts.isObject())
    {
        incubator.parent = opts.property("parent").toQObject();
        incubator.properties = opts.property("properties");
    }
    if (incubator.parent == Q_NULLPTR) incubator.parent = m_root;

    // Create new object.
    QQmlContext* context = com->creationContext();
    if (context == Q_NULLPTR)
    {
        context = new QQmlContext(m_engine->rootContext());
        context->setContextObject(incubator.parent);
    }
    com->create(incubator, context);
    if (!incubator.isReady())
    {
        qWarning("[HSApps] createObject failed!!");
    }
    return incubator.object();
}

QObject* HSApps::createComponentObject(QUrl url, QJSValue opts)
{
    QQmlComponent* com = createComponent(url);
    if (com == Q_NULLPTR) return Q_NULLPTR;
    QObject* obj = createObject(com, opts);
    com->deleteLater();
    return obj;
}

void HSApps::createComponentObjectAsync(QUrl url, QJSValue opts, QJSValue cb)
{
    __createComponentObjectAsync(url, opts, [this, cb](const QString& err, QObject* obj) mutable
    {
        if (cb.isCallable()) cb.call({ err, m_engine->newQObject(obj) });
    });
}