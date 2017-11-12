﻿#pragma once

#include "HSDispatchable.h"

#include <QQuickItem>
#include <QString>

class HSControl : public QQuickItem, public HSDispatchable
{
    Q_OBJECT

    Q_PROPERTY(QString name  READ getName  WRITE setName  NOTIFY nameChanged)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged)

public:
    HSControl(void);

    const QString& getName(void) const;
    void setName(const QString& str);

    const QString& getTitle(void) const;
    void setTitle(const QString& str);

    void dispatch(SignalId signal) override;

signals:
    void nameChanged(void);
    void titleChanged(void);

    void itemBeforeCreated(void);
    void itemAfterCreated(void);
    void itemBeforeDestroyed(void);
    void itemAfterDestroyed(void);
    void itemReadyShow(void);
    void itemShowing(void);
    void itemShown(void);
    void itemFirstShown(void);
    void itemReadyHide(void);
    void itemHiding(void);
    void itemHiden(void);
    void itemFirstHiden(void);

private:
    QString m_name;
    QString m_title;
};

QML_DECLARE_TYPE(HSControl)