#include "phonebookmodel.h"

PhoneBookModel::PhoneBookModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetToDefault();
}

int PhoneBookModel::rowCount(const QModelIndex &) const {
    return entries.size();
}

int PhoneBookModel::columnCount(const QModelIndex &) const {
    return 5;
}

QVariant PhoneBookModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    const auto &e = entries[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0: return index.row() + 1;
        case 1: return e.fio;
        case 2: return e.email;
        case 3: return e.birthDate.toString("dd.MM.yyyy");
        case 4: return e.createdAt.toString("dd.MM.yyyy hh:mm");
        }
    }
    return {};
}

QVariant PhoneBookModel::headerData(int section, Qt::Orientation o, int role) const {
    if (o == Qt::Horizontal && role == Qt::DisplayRole) {
        return QStringList{
            "№", "ФИО", "Email", "День рождения", "Дата внесения"
        }[section];
    }
    return {};
}

Qt::ItemFlags PhoneBookModel::flags(const QModelIndex &index) const {
    if (index.column() == 0)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool PhoneBookModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole)
        return false;

    auto &e = entries[index.row()];
    switch (index.column()) {
    case 1: e.fio = value.toString(); break;
    case 2: e.email = value.toString(); break;
    case 3: e.birthDate = QDate::fromString(value.toString(), "dd.MM.yyyy"); break;
    default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

void PhoneBookModel::addEntry(const PhoneBookEntry &entry) {
    beginInsertRows({}, entries.size(), entries.size());
    entries.push_back(entry);
    endInsertRows();
}

void PhoneBookModel::removeEntry(int row) {
    if (row < 0 || row >= entries.size()) return;
    beginRemoveRows({}, row, row);
    entries.removeAt(row);
    endRemoveRows();
}

void PhoneBookModel::resetToDefault() {
    beginResetModel();
    entries.clear();

    for (int i = 0; i < 10; ++i) {
        entries.push_back({
            QString("Иванов Иван Иванович %1").arg(i + 1),
            QString("ivan%1@example.com").arg(i + 1),
            QDate(1980 + i, 1 + i % 12, 1 + i % 28),
            QDateTime::currentDateTime()
        });
    }
    endResetModel();
}
