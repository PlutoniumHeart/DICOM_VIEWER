#ifndef IMAGELISTDOCK_H
#define IMAGELISTDOCK_H


#include <iostream>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>

#include "Helper.h"


class ImageListDock : public QDockWidget
{
    Q_OBJECT
    
public:
    ImageListDock();
    virtual ~ImageListDock();

    void InsertImageSeries(Helper* helper);
    void RemoveImageSeries(Helper* helper);
    QTableView* GetTable();
    std::string GetUID(int i);

private:
    QTableView* m_Table;
    QStandardItemModel* m_Model;
};


#endif // IMAGELISTDOCK_H
