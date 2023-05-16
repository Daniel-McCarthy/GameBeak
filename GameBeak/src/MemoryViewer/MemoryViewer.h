#ifndef MEMORYVIEWER_H
#define MEMORYVIEWER_H

#include <QDialog>

namespace Ui {
class MemoryViewer;
}

class Memory;
class MemoryViewer : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryViewer(QWidget *parent, Memory* memory);
    void loadMemoryData();
    ~MemoryViewer();

private:
    Memory* memory;
    Ui::MemoryViewer *ui;
};

#endif // MEMORYVIEWER_H
