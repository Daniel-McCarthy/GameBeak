#include "PaletteListView.h"

PaletteListView::PaletteListView(QGroupBox*& groupBox) : QListView(groupBox)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void PaletteListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    emit selectedIndexChanged(current.row(), current.column());
}

void PaletteListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    QListView::dataChanged(topLeft, bottomRight, roles);
    emit paletteDataChanged();
}
