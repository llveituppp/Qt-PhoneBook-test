#ifndef PHONEBOOKTABLEVIEW_H
#define PHONEBOOKTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>

class PhoneBookTableView : public QTableView {
    Q_OBJECT
public:
    explicit PhoneBookTableView(QWidget *parent = nullptr)
        : QTableView(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif
