﻿#include "HSContainerControl.h"
#include "HSApps.h"

#include <QQuickWindow>
#include <QDebug>

HSContainerControl::HSContainerControl(void)
    : m_appWindow(Q_NULLPTR)
{
    m_elements.setParentItem(this);
    m_elements.setVisible(this->isVisible());

    connect(this, &QQuickItem::visibleChanged, [this]{ m_elements.setVisible(this->isVisible()); });

    connect(&m_elements, &HSElementContainer::elementsChanged      , this, &HSContainerControl::elementsChanged);
    connect(&m_elements, &HSElementContainer::currentChanged       , this, &HSContainerControl::currentChanged);
    connect(&m_elements, &HSElementContainer::initialChanged       , this, &HSContainerControl::initialChanged);
    connect(&m_elements, &HSElementContainer::initialOnStartChanged, this, &HSContainerControl::initialOnStartChanged);
    connect(&m_elements, &HSElementContainer::initialOptsChanged   , this, &HSContainerControl::initialOptsChanged);

    connect(&m_elements, SIGNAL(stackWillEmpty()), this, SIGNAL(stackWillEmpty()));

    HSApps::anchorFill(this, &m_elements);
}

const QVariant& HSContainerControl::getAppWindow(void) const
{
    return m_appWindowVar;
}

void HSContainerControl::setAppWindow(const QVariant& var)
{
    if (m_appWindowVar == var) return;
    m_appWindowVar = var;
    m_appWindow = Q_NULLPTR;
    if (var.canConvert<QQuickWindow*>())
    {
        m_appWindow = var.value<QQuickWindow*>();
    }
    emit appWindowChanged();
}

QJSValue HSContainerControl::stack(void) const
{
    return m_elements.stack();
}

const QJSValue& HSContainerControl::getElements(void) const
{
    return m_elements.getElements();
}

const QString& HSContainerControl::getCurrent(void) const
{
    return m_elements.getCurrent();
}

void HSContainerControl::setCurrent(const QString& str)
{
    m_elements.setCurrent(str);
}

void HSContainerControl::setElements(QJSValue var)
{
    m_elements.setElements(var);
}

const QString& HSContainerControl::getInitial(void) const
{
    return m_elements.getInitial();
}

void HSContainerControl::setInitial(const QString& str)
{
    m_elements.setInitial(str);
}

bool HSContainerControl::getInitialOnStart(void) const
{
    return m_elements.getInitialOnStart();
}

void HSContainerControl::setInitialOnStart(bool val)
{
    m_elements.setInitialOnStart(val);
}

const QVariant& HSContainerControl::getInitialOpts(void) const
{
    return m_elements.getInitialOpts();
}

void HSContainerControl::setInitialOpts(const QVariant& var)
{
    m_elements.setInitialOpts(var);
}

QJSValue HSContainerControl::getInfo(QString id) const
{
    return m_elements.findInfo(id);
}

int HSContainerControl::size(void) const
{
    return m_elements.size();
}

void HSContainerControl::remove(QString id)
{
    m_elements.remove(id);
}

void HSContainerControl::back(void)
{
    m_elements.back();
}

void HSContainerControl::changeTo(QString id, QJSValue opts)
{
    m_elements.changeTo(id, opts);
}

void HSContainerControl::changeTo(QString id)
{
    m_elements.changeTo(id);
}

QJSValue HSContainerControl::currentInfo(void) const
{
    return m_elements.currentInfo();
}

void HSContainerControl::componentComplete(void)
{
    HSControl::componentComplete();
    qDebug("[HSContainerControl] componentComplete...");
    m_elements.init();
}