#ifndef IMAGELISTDOCK_H
#define IMAGELISTDOCK_H


#include <iostream>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>

#include "ImageHandler.h"


class ImageListDock : public QDockWidget
{
    Q_OBJECT
    
public:
    ImageListDock();
    virtual ~ImageListDock();

    void InsertImageSeries(ImageHandler* handler);
    void RemoveImageSeries(ImageHandler* handler);
    QTableView* GetTable();
    std::string GetUID(int i);

private:
    QTableView* m_Table;
    QStandardItemModel* m_Model;

private slots:
    void UpdateSelection(QModelIndex index);

signals:
    void SelectionChanged(int index);

};


#endif // IMAGELISTDOCK_H
