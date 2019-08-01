#ifndef PALETTELISTVIEW_H
#define PALETTELISTVIEW_H

#include <QAbstractItemView>
#include <QListView>
#include <QGroupBox>

class PaletteListView : public QListView
{
    Q_OBJECT
public:
    explicit PaletteListView(QGroupBox*& groupBox);

protected:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

signals:
    void selectedIndexChanged(int rowIndex, int colIndex);

public slots:
};

#endif // PALETTELISTVIEW_H
