﻿#pragma once

#include "HSControl.h"
#include "HSElementContainer.h"

class QQuickWindow;

class HSContainerControl : public HSControl
{
    Q_OBJECT

    Q_PROPERTY(QVariant appWindow READ getAppWindow WRITE setAppWindow NOTIFY appWindowChanged)

public:
    HSContainerControl(void);

    const QVariant& getAppWindow(void) const;
    void setAppWindow(const QVariant& var);

    QJSValue stack(void) const;

    const QJSValue& getElements(void) const;
    void setElements(QJSValue var);

    const QString& getCurrent(void) const;
    void setCurrent(const QString& str);

    const QString& getInitial(void) const;
    void setInitial(const QString& str);

    bool getInitialOnStart(void) const;
    void setInitialOnStart(bool val);

    const QVariant& getInitialOpts(void) const;
    void setInitialOpts(const QVariant& var);

    Q_INVOKABLE QJSValue getInfo(QString id) const;
    Q_INVOKABLE int size(void) const;
    Q_INVOKABLE void remove(QString id);
    Q_INVOKABLE void back(void);
    Q_INVOKABLE void changeTo(QString id, QJSValue opts);
    Q_INVOKABLE void changeTo(QString id);
    Q_INVOKABLE QJSValue currentInfo(void) const;

    virtual void elementsChanged(void) = 0;
    virtual void currentChanged(void) = 0;
    virtual void initialChanged(void) = 0;
    virtual void initialOnStartChanged(void) = 0;
    virtual void initialOptsChanged(void) = 0;

signals:
    void appWindowChanged(void);
    void stackWillEmpty(void);

protected:
    void componentComplete(void) override;

protected:
    HSElementContainer m_elements;

    QVariant m_appWindowVar;
    QQuickWindow* m_appWindow;
};
