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
    m_Table->setColumnWidth(0, 100);
    m_Table->setColumnWidth(1, 500);
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
    std::string patientName = handler->GetImageObj()->GetPatientName();
    std::string studyInstanceUID = handler->GetImageObj()->GetStudyInstanceUID();
    QStandardItem *newItem = new QStandardItem(tr(patientName.c_str()));
    QStandardItem *newItem1 = new QStandardItem(tr(studyInstanceUID.c_str()));
    newItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    m_Model->insertRow(0);
    m_Model->setItem(0,0,newItem);
    m_Model->setItem(0,1,newItem1);
    m_Table->setCurrentIndex(m_Table->model()->index(0,0));
}


void ImageListDock::RemoveImageSeries(ImageHandler* handler)
{
    int temp = handler->GetActiveIndex();
    if(temp>=0)
    {
        m_Model->removeRows(temp, 1);
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
    std::cout<<"Currently selected: "<<index.row()<<std::endl;
    emit(SelectionChanged(m_Model->rowCount()-index.row() - 1));
}
