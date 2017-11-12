﻿#pragma once

#include "HSControl.h"
#include "HSDispatchable.h"

#include <QQuickItem>
#include <QString>

class HSContainer : public QQuickItem, public HSDispatchable
{
    Q_OBJECT

    Q_PROPERTY(QString currentId    READ getCurrentId                          NOTIFY currentIdChanged)
    Q_PROPERTY(QString signalPrefix READ getSignalPrefix WRITE setSignalPrefix NOTIFY signalPrefixChanged)

public:
    HSContainer(void);

    const QString& getCurrentId(void) const;
    void setCurrentId(const QString& str);

    const QString& getSignalPrefix(void) const;
    void setSignalPrefix(const QString& str);

    Q_INVOKABLE virtual void foreachEl(QJSValue cb) const = 0;
    Q_INVOKABLE virtual QJSValue findById(QString id) const = 0;
    Q_INVOKABLE virtual void clear(void) = 0;
    Q_INVOKABLE virtual void remove(QString id) = 0;
    Q_INVOKABLE virtual void changeTo(QString id, QJSValue opts) = 0;
    Q_INVOKABLE virtual void back(void) = 0;
    Q_INVOKABLE virtual int depth(void) const = 0;

    void dispatch(SignalId signal) override;

protected:
    virtual void __dispatchSignal(SignalId signal, const QString& id);

signals:
    void currentIdChanging(QString newId);
    void currentIdChanged(void);
    void signalPrefixChanged(void);

    void itemBeforeCreated(QString id);
    void itemAfterCreated(QString id);
    void itemBeforeDestroyed(QString id);
    void itemAfterDestroyed(QString id);
    void itemReadyShow(QString id);
    void itemShowing(QString id);
    void itemShown(QString id);
    void itemFirstShown(QString id);
    void itemReadyHide(QString id);
    void itemHiding(QString id);
    void itemHiden(QString id);
    void itemFirstHiden(QString id);

private:
    QString m_currentId;
    QString m_signalPrefix;
};
