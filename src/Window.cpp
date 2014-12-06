#include "Window.h"


Window::Window()
{
    CreateMenus();
    CreateToolbars();
    CreateCenterWidgets();
    CreateDocks();

    setWindowTitle(tr("DICOM Viewer"));
    resize(1600, 900);
}


Window::~Window()
{
    delete m_pFileToolbar;
    delete m_pResizeToolbar;
    delete m_pDisplay;
    delete m_pScrollArea;
    delete m_pTimer;
    delete m_pImageListDock;
    delete m_pImageWindowingDock;
}


void Window::CreateMenus()
{
    m_pMenu = menuBar()->addMenu(tr("&File"));
    m_pMenu->addAction(tr("&Open Dicom Image"), this, SLOT(OpenDicomImage()));
    m_pMenu->addAction(tr("&Open Dicom Series"), this, SLOT(OpenDicomSeries()));
    m_pMenu->addAction(tr("&Close"), this, SLOT(CloseDicomImage()));
    m_pMenu->addAction(tr("&Quit"), this, SLOT(close()));
}


void Window::CreateToolbars()
{
    m_pFileToolbar = new FileToolbar;
    addToolBar(m_pFileToolbar);
    connect(m_pFileToolbar->GetOpenDICOMAction(), SIGNAL(triggered()), this, SLOT(OpenDicomImage()));

    m_pResizeToolbar = new ResizeToolbar;
    addToolBar(m_pResizeToolbar);
}


void Window::CreateCenterWidgets()
{
    m_pDisplay = new DisplayWidget(&m_ImageHandler, this);
    m_pScrollArea = new QScrollArea;
    m_pTimer = new QTimer(this);

    m_pScrollArea->setFrameShadow(QFrame::Sunken);
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setAlignment(Qt::AlignCenter);
    m_pScrollArea->setWidget(m_pDisplay);
    m_pScrollArea->setWidgetResizable(false);
    m_pScrollArea->ensureWidgetVisible(m_pDisplay);
    setCentralWidget(m_pScrollArea);

    m_pTimer->start(50);
}


void Window::CreateDocks()
{
    m_pImageListDock = new ImageListDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_pImageListDock);


    m_pImageWindowingDock = new ImageWindowDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_pImageWindowingDock);

    m_pImageWindowingDock->GetSpinBoxWC()->setMinimum(0);
    m_pImageWindowingDock->GetSpinBoxWC()->setMaximum(4096);
    m_pImageWindowingDock->GetSliderWC()->setMinimum(0);
    m_pImageWindowingDock->GetSliderWC()->setMaximum(4096);

    m_pImageWindowingDock->GetSpinBoxWW()->setMinimum(0);
    m_pImageWindowingDock->GetSpinBoxWW()->setMaximum(4096);
    m_pImageWindowingDock->GetSliderWW()->setMinimum(0);
    m_pImageWindowingDock->GetSliderWW()->setMaximum(4096);
}


void Window::CreateConnections()
{
    connect(m_pTimer, SIGNAL(timeout()), m_pDisplay, SLOT(Animate()));

    connect(m_pDisplay, SIGNAL(MiddleButtonMove(float, float)), m_pImageWindowingDock, SLOT(UpdateWindowLevel(float, float)));
    connect(m_pImageWindowingDock->GetSliderWC(), SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_pImageWindowingDock->GetSliderWW(), SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_pImageWindowingDock->GetResetButton(), SIGNAL(clicked()), this, SLOT(ResetWindow()));
    connect(m_pDisplay, SIGNAL(MiddleButtonDoubleClick()), this, SLOT(ResetWindow()));
    connect(m_pDisplay, SIGNAL(WheelMovement(int,int)), this, SLOT(UpdateActiveSlice(int,int)));

    connect(m_pDisplay, SIGNAL(RightButtonMove(float)), this, SLOT(Pan(float)));

    connect(m_pResizeToolbar->GetActionZoomIn(), SIGNAL(triggered()), this, SLOT(ZoomIn25Present()));
    connect(m_pResizeToolbar->GetActionZoomOut(), SIGNAL(triggered()), this, SLOT(ZoomOut25Present()));
    connect(m_pResizeToolbar->GetActionOriginalSize(), SIGNAL(triggered()), this, SLOT(ZoomOriginalSize()));
    connect(m_pResizeToolbar->GetActionFitToHeight(), SIGNAL(triggered()), this, SLOT(ZoomFitToHeight()));
    connect(m_pResizeToolbar->GetComboResize(), SIGNAL(currentIndexChanged(int)), this, SLOT(ZoomComboResize(int)));
    connect(m_pResizeToolbar->GetComboResize()->lineEdit(), SIGNAL(editingFinished()), this, SLOT(ZoomCustomSize()));

    connect(m_pImageListDock, SIGNAL(SelectionChanged(int)), this, SLOT(UpdateImage(int)));
}


// ====== slots ====== //
void Window::OpenDicomImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open DICOM file"), QDir::currentPath());

    if(!m_ImageHandler.AddImage(filename))
        return;
    m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    ZoomOriginalSize();
    ZoomFitToHeight();
    m_pImageWindowingDock->SetWidgetsDisabled(false);
    m_pResizeToolbar->SetWidgetsDisabled(false);

    m_pImageListDock->InsertImageSeries(&m_ImageHandler);

    CreateConnections();
}


void Window::OpenDicomSeries()
{
    QString folderPath = QFileDialog::getExistingDirectory(0, tr("Open DICOM folder"), QDir::currentPath(), QFileDialog::ShowDirsOnly);

    if(!m_ImageHandler.AddImageSeries(folderPath))
        return;
    m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    ZoomOriginalSize();
    ZoomFitToHeight();
    m_pImageWindowingDock->SetWidgetsDisabled(false);
    m_pResizeToolbar->SetWidgetsDisabled(false);

    m_pImageListDock->InsertImageSeries(&m_ImageHandler);

    CreateConnections();
}


void Window::CloseDicomImage()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;

    m_pImageListDock->RemoveImageSeries(&m_ImageHandler);
    m_ImageHandler.RemoveImage();

    if(m_ImageHandler.GetNumberOfOpenedImages()<=0)
    {
        m_pDisplay->resize(0, 0);
        m_pImageWindowingDock->SetWidgetsDisabled(true);
        m_pResizeToolbar->SetWidgetsDisabled(true);
    }
    else
    {
        short tmp1 = m_ImageHandler.GetImageObj()->GetCurrentWC();
        short tmp2 = m_ImageHandler.GetImageObj()->GetCurrentWW();
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(tmp1);
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(tmp2);
    }
    m_pScrollArea->viewport()->update();
}


void Window::Pan(float scale)
{
    double presentage = 10.0*scale;
    QSize temp = (1.0+presentage)*m_pDisplay->size();

    m_pDisplay->resize(temp);

    std::string currentSize = m_pResizeToolbar->GetComboResize()->currentText().toStdString();

    std::ostringstream ss;
    ss << 100.0*((double)temp.height()/(double)m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::UpdateImage()
{
    short tmp1 = m_pImageWindowingDock->GetSpinBoxWC()->value();
    short tmp2 = m_pImageWindowingDock->GetSpinBoxWW()->value();
    m_ImageHandler.UpdateImage(tmp1, tmp2);
}


void Window::UpdateImage(int index)
{
    m_ImageHandler.SetActiveIndex(index);
    short tmp1 = m_ImageHandler.GetImageObj()->GetCurrentWC();
    short tmp2 = m_ImageHandler.GetImageObj()->GetCurrentWW();
    m_pImageWindowingDock->GetSpinBoxWC()->setValue(tmp1);
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(tmp2);
    UpdateImage();
}


void Window::UpdateActiveSlice(int deltaX, int deltaY)
{
    int slice = m_ImageHandler.GetImageObj()->GetActiveSlice() - deltaY;

    if(slice>=m_ImageHandler.GetImageObj()->GetMinSliceNum() &&
       slice<=m_ImageHandler.GetImageObj()->GetMaxSliceNum())
    {
        m_ImageHandler.GetImageObj()->SetActiveSlice(slice);
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        UpdateImage();
    }
    else if(slice<m_ImageHandler.GetImageObj()->GetMinSliceNum())
    {
        m_ImageHandler.GetImageObj()->SetActiveSlice(m_ImageHandler.GetImageObj()->GetMinSliceNum());
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        UpdateImage();
    }
    else if(slice>m_ImageHandler.GetImageObj()->GetMaxSliceNum())
    {
        m_ImageHandler.GetImageObj()->SetActiveSlice(m_ImageHandler.GetImageObj()->GetMaxSliceNum());
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
        UpdateImage();
    }
}


void Window::ResetWindow()
{
    m_pImageWindowingDock->GetSpinBoxWC()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_ImageHandler.UpdateImage(m_ImageHandler.GetImageObj()->GetDefaultWC(m_ImageHandler.GetImageObj()->GetActiveSlice()),
                               m_ImageHandler.GetImageObj()->GetDefaultWW(m_ImageHandler.GetImageObj()->GetActiveSlice()));
}


void Window::ZoomIn25Present()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    Pan(0.025);
}


void Window::ZoomOut25Present()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    Pan(-0.025);
}


void Window::ZoomOriginalSize()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    int temp = m_ImageHandler.GetImageObj()->GetWidth(m_ImageHandler.GetImageObj()->GetActiveSlice());
    int temp1 = m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice());
    m_pDisplay->resize(m_ImageHandler.GetImageObj()->GetWidth(m_ImageHandler.GetImageObj()->GetActiveSlice()),
                       m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString("100%"));
}


void Window::ZoomFitToHeight()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    short tmp = m_pScrollArea->height();
    double temp = (double)tmp/m_pDisplay->height();
    m_pDisplay->resize(m_pDisplay->size()*temp);
    std::ostringstream ss;
    ss << 100.0*((double)m_pDisplay->size().height()/(double)m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::ZoomCustomSize()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    std::string temp = m_pResizeToolbar->GetComboResize()->currentText().toStdString();

    double tmp = atof(temp.c_str());
    std::stringstream ss;
    ss<<tmp;
    std::string currentText = ss.str() + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));

    QSize original = QSize(m_ImageHandler.GetImageObj()->GetWidth(m_ImageHandler.GetImageObj()->GetActiveSlice()),
                           m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    m_pDisplay->resize(original*tmp/100.0);
}


void Window::ZoomComboResize(int index)
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    QSize original = QSize(m_ImageHandler.GetImageObj()->GetWidth(m_ImageHandler.GetImageObj()->GetActiveSlice()),
                           m_ImageHandler.GetImageObj()->GetHeight(m_ImageHandler.GetImageObj()->GetActiveSlice()));
    switch(index)
    {
    case 0:
        m_pDisplay->resize(original*8.0);
        break;
    case 1:
        m_pDisplay->resize(original*7.0);
        break;
    case 2:
        m_pDisplay->resize(original*6.0);
        break;
    case 3:
        m_pDisplay->resize(original*5.0);
        break;
    case 4:
        m_pDisplay->resize(original*4.0);
        break;
    case 5:
        m_pDisplay->resize(original*3.0);
        break;
    case 6:
        m_pDisplay->resize(original*2.0);
        break;
    case 7:
        m_pDisplay->resize(original*1.0);
        break;
    case 8:
        m_pDisplay->resize(original*0.5);
        break;
    default:
        std::cout<<"Combo resize: no such index found."<<std::endl;
        break;
    }
}
