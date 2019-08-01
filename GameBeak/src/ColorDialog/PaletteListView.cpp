#include "PaletteListView.h"

PaletteListView::PaletteListView(QGroupBox*& groupBox) : QListView(groupBox)
{
}

void PaletteListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    emit selectedIndexChanged(current.row(), current.column());
}
