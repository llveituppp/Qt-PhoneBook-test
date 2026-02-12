#ifndef PHONEBOOKENTRY_H
#define PHONEBOOKENTRY_H

#include <QString>
#include <QDate>
#include <QDateTime>

struct PhoneBookEntry {
    QString fio;
    QString email;
    QDate birthDate;
    QDateTime createdAt;
};

#endif
