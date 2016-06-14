#include "ImageListDock.h"


ImageListDock::ImageListDock()
    : m_iActiveSeries(-1)
{
    setWindowTitle("Document List");
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    m_pModel = new QStandardItemModel();
    QString line = tr("# Images, Patient Name, Patient ID, Accession, Study Description, Study Date, Series Description, Acquisition Date, Acquisition Time");
    QStringList list = line.simplified().split(",");
    m_pModel->setHorizontalHeaderLabels(list);

    m_pTable = new QTableView;
    m_pTable->setModel(m_pModel);
    m_pTable->setColumnWidth(0, 70);
    m_pTable->setColumnWidth(1, 100);
    m_pTable->setColumnWidth(2, 100);
    m_pTable->setColumnWidth(3, 100);
    m_pTable->setColumnWidth(4, 150);
    m_pTable->setColumnWidth(5, 120);
    m_pTable->setColumnWidth(6, 150);
    m_pTable->setColumnWidth(7, 150);
    m_pTable->setColumnWidth(8, 150);
    m_pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(m_pTable, SIGNAL(clicked(QModelIndex)), this, SLOT(UpdateSelection(QModelIndex)));

    setMinimumSize(QSize(560, 160));
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setWidget(m_pTable);
}


ImageListDock::~ImageListDock()
{
    delete m_pModel;
    delete m_pTable;
}


void ImageListDock::InsertImageData(std::shared_ptr<ImageData> imageData)
{
    int slice = 0;

    std::string imagesInSeries = std::to_string(imageData->GetDepth());
    std::string patientName = imageData->GetPatientName(slice);
    std::string patientID = imageData->GetPatientID(slice);
    std::string accession = imageData->GetAccession(slice);
    std::string studyDescription = imageData->GetStudyDescription(slice);
    std::string studyDate = imageData->GetStudyDate(slice);
    std::string seriesDescription = imageData->GetSeriesDescription(slice);
    std::string acquisitionDate = imageData->GetAcqusitionDate(slice);
    std::string acquisitionTime = imageData->GetAcqusitionTime(slice);

    QStandardItem *newItem = new QStandardItem(tr(imagesInSeries.c_str()));
    QStandardItem *newItem1 = new QStandardItem(tr(patientName.c_str()));
    QStandardItem *newItem2 = new QStandardItem(tr(patientID.c_str()));
    QStandardItem *newItem3 = new QStandardItem(tr(accession.c_str()));
    QStandardItem *newItem4 = new QStandardItem(tr(studyDescription.c_str()));
    QStandardItem *newItem5 = new QStandardItem(tr(studyDate.c_str()));
    QStandardItem *newItem6 = new QStandardItem(tr(seriesDescription.c_str()));
    QStandardItem *newItem7 = new QStandardItem(tr(acquisitionDate.c_str()));
    QStandardItem *newItem8 = new QStandardItem(tr(acquisitionTime.c_str()));

    newItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    m_pModel->insertRow(0);
    m_pModel->setItem(0,0,newItem);
    m_pModel->setItem(0,1,newItem1);
    m_pModel->setItem(0,2,newItem2);
    m_pModel->setItem(0,3,newItem3);
    m_pModel->setItem(0,4,newItem4);
    m_pModel->setItem(0,5,newItem5);
    m_pModel->setItem(0,6,newItem6);
    m_pModel->setItem(0,7,newItem7);
    m_pModel->setItem(0,8,newItem8);
    m_pTable->setCurrentIndex(m_pTable->model()->index(0,0));

    m_vImages.push_back(imageData);
    m_iActiveSeries = m_vImages.size()-1;
}


void ImageListDock::EraseImageData(int i)
{
    std::vector<std::shared_ptr<ImageData>>::iterator itr = m_vImages.begin() + i;

    m_pModel->removeRows(m_vImages.size()-i-1, 1);
    m_vImages.erase(itr);

    if (m_vImages.size() == 0)
    {
        m_iActiveSeries = -1;
    }
    else
    {
        if (m_iActiveSeries>=m_vImages.size())
            m_iActiveSeries = m_vImages.size()-1;
        m_pTable->setCurrentIndex(m_pTable->model()->index(m_vImages.size()-m_iActiveSeries-1, 0));
        emit(SelectionChanged(m_iActiveSeries));
    }
}


std::shared_ptr<ImageData> ImageListDock::GetSeries(int idx)
{
    return m_vImages[idx];
}


std::shared_ptr<ImageData> ImageListDock::GetActiveSeries()
{
    return m_vImages[m_iActiveSeries];
}


QTableView* ImageListDock::GetTable()
{
    return m_pTable;
}


std::string ImageListDock::GetUID(int i)
{
    return m_pModel->item(i, 1)->text().toUtf8().constData();
}


void ImageListDock::UpdateSelection(QModelIndex index)
{
    emit(SelectionChanged(m_pModel->rowCount()-index.row() - 1));
}


void ImageListDock::SetActiveSeriesIndex(int idx)
{
    m_iActiveSeries = idx;
}


int ImageListDock::GetActiveSeriesIndex()
{
    return m_iActiveSeries;
}


int ImageListDock::GetNumOpenedSeries()
{
    return m_vImages.size();
}
