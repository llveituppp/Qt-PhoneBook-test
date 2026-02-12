#include "phonebook_proxy.h"
#include <QRegularExpression>

PhoneBookProxy::PhoneBookProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool PhoneBookProxy::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    if (!sourceModel())
        return true;

    for (int col = 0; col < sourceModel()->columnCount(); ++col) {
        QModelIndex idx = sourceModel()->index(row, col, parent);
        if (sourceModel()->data(idx).toString()
                .contains(filterRegularExpression()))
            return true;
    }
    return false;
}

bool PhoneBookProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant l = sourceModel()->data(left, Qt::DisplayRole);
    QVariant r = sourceModel()->data(right, Qt::DisplayRole);

    if (left.column() == 0)
        return l.toInt() < r.toInt();

    if (left.column() == 1 || left.column() == 2) {
        return naturalLess(l.toString(), r.toString());
    }

    return QString::localeAwareCompare(l.toString(), r.toString()) < 0;
}
bool PhoneBookProxy::extractTrailingNumber(
    const QString &text, int &number) const
{
    static QRegularExpression re("(\\d+)\\s*$");
    auto match = re.match(text);

    if (!match.hasMatch())
        return false;

    number = match.captured(1).toInt();
    return true;
}

bool PhoneBookProxy::naturalLess(
    const QString &a,
    const QString &b) const
{
    QRegularExpression re(R"(^(.*?)(\d+)(\D*)$)");

    auto ma = re.match(a);
    auto mb = re.match(b);

    if (ma.hasMatch() && mb.hasMatch()) {
        QString prefixA = ma.captured(1);
        QString prefixB = mb.captured(1);

        if (prefixA != prefixB)
            return prefixA < prefixB;

        int numA = ma.captured(2).toInt();
        int numB = mb.captured(2).toInt();

        return numA < numB;
    }

    return QString::localeAwareCompare(a, b) < 0;
}

