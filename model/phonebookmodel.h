#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H

#include <QAbstractTableModel>
#include "phonebookentry.h"

class PhoneBookModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit PhoneBookModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &, int role) const override;
    QVariant headerData(int, Qt::Orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &) const override;
    bool setData(const QModelIndex &, const QVariant &, int role) override;

    void addEntry(const PhoneBookEntry &entry);
    void removeEntry(int row);
    void resetToDefault();

private:
    QVector<PhoneBookEntry> entries;
};

#endif
