#include "MemoryViewer.h"
#include "ui_MemoryViewer.h"
#include "../Memory.h"
#include <QDebug>
#include <QHeaderView>

MemoryViewer::MemoryViewer(QWidget *parent, Memory* memory) :
    QDialog(parent),
    ui(new Ui::MemoryViewer)
{
    ui->setupUi(this);

    // Assuming you have a pointer to an object named "memory" with a member variable "beakRam" containing the memory data
    int rowLength = 16;
    int numColumns = rowLength + 1;

    // Get a reference to the QTableWidget
    QTableWidget* memoryTable = ui->memoryTable;

    // Set the number of rows and columns in the table
    int numRows = (memory->beakRam.size() + rowLength - 1) / rowLength;
    memoryTable->setRowCount(numRows);
    memoryTable->setColumnCount(numColumns);

    // Set the column width for the address column
    memoryTable->setColumnWidth(0, 55);

    // Set the horizontal header labels
    QStringList headerLabels;
    headerLabels << "Address" << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7"
                 << "8" << "9" << "A" << "B" << "C" << "D" << "E" << "F";
    memoryTable->setHorizontalHeaderLabels(headerLabels);

    // Hide the vertical header that counts from 1 and increments
    memoryTable->verticalHeader()->setVisible(false);

    // Set the grid style to have thin lines between cells
    memoryTable->setShowGrid(true);
    memoryTable->setGridStyle(Qt::DotLine);

    // Populate the memory values in the table
    for (int row = 0; row < numRows; row++) {
        // Set the address value in the first column
        QString addressRowHex = QString("%1").arg(row * rowLength, 3, rowLength, QChar('0')).toUpper();
        QTableWidgetItem* addressItem = new QTableWidgetItem(addressRowHex);

        addressItem->setFlags(addressItem->flags() ^ Qt::ItemIsEditable); // Make the cell non-editable
        memoryTable->setItem(row, 0, addressItem);

        // Set the memory values in the remaining columns (from 1 to 16)
        for (int col = 1; col < numColumns; ++col) {
            int index = (row * rowLength) + (col - 1);
            if (index < memory->beakRam.size()) {
                QTableWidgetItem* dataItem = new QTableWidgetItem(QString("%1").arg(memory->beakRam[index], 2, 16, QChar('0')).toUpper());
                memoryTable->setItem(row, col, dataItem);

                // Set the alignment to center
                dataItem->setTextAlignment(Qt::AlignCenter);

                // Set the column width to fit the content
                memoryTable->setColumnWidth(col, 10);
            }
        }
    }

    // Calculate the total width required by the columns
    int totalWidth = memoryTable->verticalHeader()->width();
    for (int col = 0; col < numColumns; ++col) {
        totalWidth += memoryTable->columnWidth(col);
    }

    // Adjust the window width to fit the table width
    int minWidth = qMax(totalWidth + 10, memoryTable->minimumWidth());
    resize(minWidth, height());
}

MemoryViewer::~MemoryViewer()
{
    delete ui;
}
