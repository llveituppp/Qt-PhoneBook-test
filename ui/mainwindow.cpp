#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new PhoneBookModel(this);
    proxy = new PhoneBookProxy(this);
    proxy->setSourceModel(model);

    view = new PhoneBookTableView(this);
    view->setModel(proxy);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setStretchLastSection(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Поиск по любой колонке...");

    connect(searchEdit, &QLineEdit::textChanged,
            proxy, &QSortFilterProxyModel::setFilterFixedString);

    QPushButton *addBtn   = new QPushButton("Добавить");
    QPushButton *delBtn   = new QPushButton("Удалить");
    QPushButton *resetBtn = new QPushButton("Сброс");

    connect(addBtn,   &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(delBtn,   &QPushButton::clicked, this, &MainWindow::removeRecord);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::resetModel);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(addBtn);
    topLayout->addWidget(delBtn);
    topLayout->addWidget(resetBtn);
    topLayout->addSpacing(20);
    topLayout->addWidget(searchEdit, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(view, 1);

    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    resize(1000, 600);
    view->clearSelection();
    view->setCurrentIndex(QModelIndex());
}

void MainWindow::addRecord()
{
    model->addEntry({
        "Новая запись",
        "email@example.com",
        QDate::currentDate(),
        QDateTime::currentDateTime()
    });
}

void MainWindow::removeRecord()
{
    QModelIndex idx = view->currentIndex();
    if (!idx.isValid())
        return;

    model->removeEntry(proxy->mapToSource(idx).row());
}

void MainWindow::resetModel()
{
    model->resetToDefault();
    searchEdit->clear();

    view->clearSelection();
    view->setCurrentIndex(QModelIndex());
}

