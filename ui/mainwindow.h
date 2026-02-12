#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "../model/phonebookmodel.h"
#include "../filters/phonebook_proxy.h"
#include "phonebooktableview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addRecord();
    void removeRecord();
    void resetModel();

private:
    PhoneBookModel *model;
    PhoneBookProxy *proxy;
    PhoneBookTableView *view;
    QLineEdit *searchEdit;
};

#endif
