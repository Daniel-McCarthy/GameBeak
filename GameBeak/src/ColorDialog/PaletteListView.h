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

public slots:
};

#endif // PALETTELISTVIEW_H
