#include "ImageListDock.h"


ImageListDock::ImageListDock()
{
    setWindowTitle("Opened Image Series List");
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    m_Model = new QStandardItemModel();
    QString line = tr("# Images, Patient Name, Patient ID, Accession, Study Description, Study Date, Series Description, Acquisition Date, Acquisition Time");
    QStringList list = line.simplified().split(",");
    m_Model->setHorizontalHeaderLabels(list);

    m_Table = new QTableView;
    m_Table->setModel(m_Model);
    m_Table->setColumnWidth(0, 70);
    m_Table->setColumnWidth(1, 100);
    m_Table->setColumnWidth(2, 100);
    m_Table->setColumnWidth(3, 100);
    m_Table->setColumnWidth(4, 150);
    m_Table->setColumnWidth(5, 120);
    m_Table->setColumnWidth(6, 150);
    m_Table->setColumnWidth(7, 150);
    m_Table->setColumnWidth(8, 150);
    m_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_Table->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(m_Table, SIGNAL(clicked(QModelIndex)), this, SLOT(UpdateSelection(QModelIndex)));

    setMinimumSize(QSize(560, 160));
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setWidget(m_Table);
}


ImageListDock::~ImageListDock()
{
    delete m_Model;
    delete m_Table;
}


void ImageListDock::InsertImageSeries(ImageHandler* handler)
{
    std::shared_ptr<ImageContainer> imageObj = handler->GetImageObj();
    int slice = handler->GetImageObj()->GetActiveSlice();

    std::string imagesInSeries = std::to_string(imageObj->GetMaxSliceNum()+1);
    std::string patientName = imageObj->GetPatientName(slice);
    std::string patientID = imageObj->GetPatientID(slice);
    std::string accession = imageObj->GetAccession(slice);
    std::string studyDescription = imageObj->GetStudyDescription(slice);
    std::string studyDate = imageObj->GetStudyDate(slice);
    std::string seriesDescription = imageObj->GetSeriesDescription(slice);
    std::string acquisitionDate = imageObj->GetAcqusitionDate(slice);
    std::string acquisitionTime = imageObj->GetAcqusitionTime(slice);

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
    m_Model->insertRow(0);
    m_Model->setItem(0,0,newItem);
    m_Model->setItem(0,1,newItem1);
    m_Model->setItem(0,2,newItem2);
    m_Model->setItem(0,3,newItem3);
    m_Model->setItem(0,4,newItem4);
    m_Model->setItem(0,5,newItem5);
    m_Model->setItem(0,6,newItem6);
    m_Model->setItem(0,7,newItem7);
    m_Model->setItem(0,8,newItem8);
    m_Table->setCurrentIndex(m_Table->model()->index(0,0));
}


void ImageListDock::RemoveImageSeries(ImageHandler* handler)
{
    int temp = handler->GetActiveIndex();
    int TotalOpened = handler->GetNumberOfOpenedImages();
    if(temp>=0)
    {
        m_Model->removeRows(TotalOpened - temp - 1, 1);
        m_Table->setCurrentIndex(m_Table->model()->index(0,0));
    }
}


QTableView* ImageListDock::GetTable()
{
    return m_Table;
}


std::string ImageListDock::GetUID(int i)
{
    return m_Model->item(i, 1)->text().toUtf8().constData();
}


void ImageListDock::UpdateSelection(QModelIndex index)
{
    int temp = m_Model->rowCount()-index.row() - 1;
    emit(SelectionChanged(m_Model->rowCount()-index.row() - 1));
}
