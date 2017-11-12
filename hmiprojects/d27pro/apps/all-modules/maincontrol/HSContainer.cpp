﻿#include "HSContainer.h"

HSContainer::HSContainer(void)
    : m_signalPrefix("item")
{
#define __CONTAINER_CONNECT(SIGNAL_NAME) \
    connect(this, &HSContainer::SIGNAL_NAME, [this](const QString& id){ __dispatchSignal(&HSControl::SIGNAL_NAME, id); });

    __CONTAINER_CONNECT(itemBeforeCreated)
    __CONTAINER_CONNECT(itemAfterCreated)
    __CONTAINER_CONNECT(itemBeforeDestroyed)
    __CONTAINER_CONNECT(itemAfterDestroyed)
    __CONTAINER_CONNECT(itemReadyShow)
    __CONTAINER_CONNECT(itemShowing)
    __CONTAINER_CONNECT(itemShown)
    __CONTAINER_CONNECT(itemFirstShown)
    __CONTAINER_CONNECT(itemReadyHide)
    __CONTAINER_CONNECT(itemHiding)
    __CONTAINER_CONNECT(itemHiden)
    __CONTAINER_CONNECT(itemFirstHiden)

#undef __CONTAINER_CONNECT
}

const QString& HSContainer::getCurrentId(void) const
{
    return m_currentId;
}

void HSContainer::setCurrentId(const QString& str)
{
    if (m_currentId == str) return;
    emit currentIdChanging(str);
    m_currentId = str;
    emit currentIdChanged();
}

const QString& HSContainer::getSignalPrefix(void) const
{
    return m_signalPrefix;
}

void HSContainer::setSignalPrefix(const QString& str)
{
    if (m_signalPrefix == str) return;
    m_signalPrefix = str;
    emit signalPrefixChanged();
}

void HSContainer::dispatch(SignalId signal)
{
    if (m_currentId.isEmpty()) return;
    __dispatchSignal(signal, m_currentId);
}

void HSContainer::__dispatchSignal(SignalId, const QString&)
{
    // Do Nothing.
}
