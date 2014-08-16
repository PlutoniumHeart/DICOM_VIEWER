#include "ImageListDock.h"


ImageListDock::ImageListDock()
{
    setWindowTitle("Opened Image Series List");
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    m_Model = new QStandardItemModel();
    QString line = tr("Patient, StudyInstanceUID");
    QStringList list = line.simplified().split(",");
    m_Model->setHorizontalHeaderLabels(list);
    m_Table = new QTableView;
    m_Table->setModel(m_Model);
    m_Table->setSelectionBehavior(QAbstractItemView::SelectRows);
    setMinimumSize(QSize(560, 160));
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setWidget(m_Table);
}


ImageListDock::~ImageListDock()
{
    delete m_Table;
}


void ImageListDock::InsertImageSeries(ImageHandler* handler)
{
    std::string patientName
        = handler->GetImageObj()->GetPatientName();
    std::string studyInstanceUID = handler->GetImageObj()->GetStudyInstanceUID();
    QStandardItem *newItem = new QStandardItem(tr(patientName.c_str()));
    QStandardItem *newItem1 = new QStandardItem(tr(studyInstanceUID.c_str()));
    newItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    m_Model->setItem(handler->GetNumberOfOpenedImages()-1,0,newItem);
    m_Model->setItem(handler->GetNumberOfOpenedImages()-1,1,newItem1);
}


void ImageListDock::RemoveImageSeries(ImageHandler* handler)
{
    int temp = handler->GetActiveIndex();
    if(temp>=0)
        m_Model->removeRows(temp, 1);
}


QTableView* ImageListDock::GetTable()
{
    return m_Table;
}


std::string ImageListDock::GetUID(int i)
{
    return m_Model->item(i, 1)->text().toUtf8().constData();
}
