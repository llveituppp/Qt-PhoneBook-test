#ifndef PHONEBOOKFILTERPROXYMODEL_H
#define PHONEBOOKFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PhoneBookProxy : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit PhoneBookProxy(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool naturalLess(const QString &a, const QString &b) const;
    bool extractTrailingNumber(const QString &text, int &number) const;
};

#endif
