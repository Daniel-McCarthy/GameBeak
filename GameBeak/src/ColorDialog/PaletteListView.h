#ifndef PALETTELISTVIEW_H
#define PALETTELISTVIEW_H

#include <QAbstractItemView>
#include <QListView>
#include <QGroupBox>
#include <QInputDialog>

class PaletteListView : public QListView
{
    Q_OBJECT
public:
    explicit PaletteListView(QGroupBox*& groupBox);

protected:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) override;

signals:
    void selectedIndexChanged(int rowIndex, int colIndex);
    void paletteDataChanged();

public slots:
};

#endif // PALETTELISTVIEW_H
