#include "phonebooktableview.h"

void PhoneBookTableView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex idx = indexAt(event->pos());

    if (!idx.isValid()) {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }

    QTableView::mousePressEvent(event);
}
