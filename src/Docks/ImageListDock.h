#ifndef IMAGELISTDOCK_H
#define IMAGELISTDOCK_H


#include <iostream>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>

#include "ImageData.h"


class ImageListDock : public QDockWidget
{
    Q_OBJECT
    
public:
    ImageListDock();
    virtual ~ImageListDock();

    void InsertImageData(std::shared_ptr<ImageData> imageData);
    void EraseImageData(int i);
    std::shared_ptr<ImageData> GetSeries(int idx);
    std::shared_ptr<ImageData> GetActiveSeries();
    QTableView* GetTable();
    std::string GetUID(int i);
    void SetActiveSeriesIndex(int idx);
    int GetActiveSeriesIndex();
    int GetNumOpenedSeries();

private:
    QTableView* m_pTable;
    QStandardItemModel* m_pModel;

    int m_iActiveSeries;
    std::vector<std::shared_ptr<ImageData>> m_vImages;

private slots:
    void UpdateSelection(QModelIndex index);

signals:
    void SelectionChanged(int index);

};


#endif // IMAGELISTDOCK_H
