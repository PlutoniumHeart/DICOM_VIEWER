#include "Window.h"


Window::Window()
    : m_bConnected(false)
{
    QIcon appIcon;
    appIcon.addFile(":Resources/icons/DICOM_Tool.png");
    this->setWindowIcon(appIcon);

    CreateToolbars();
    CreateCenterWidgets();
    CreateDocks();
    CreateMenus();

    setAcceptDrops(true);
    setWindowTitle(tr("DICOM Viewer"));
    resize(1600, 900);
}


Window::~Window()
{
    delete m_pFileToolbar;
    delete m_pResizeToolbar;
    delete m_pScrollArea;
    delete m_pTimer;
    delete m_pImageListDock;
    delete m_pImageWindowingDock;
    delete m_pImageLayoutDock;
}


void Window::CreateMenus()
{
    m_pFileMenu = menuBar()->addMenu(tr("&File"));
    m_pFileMenu->addAction(tr("&Open Dicom Image"), this, SLOT(OpenDicomImage()));
    m_pFileMenu->addAction(tr("Open Dicom &Series"), this, SLOT(OpenDicomSeries()));
    m_pFileMenu->addAction(tr("&Close"), this, SLOT(CloseDicomImage()));
    m_pFileMenu->addAction(tr("&Quit"), this, SLOT(close()));

    m_pViewMenu = menuBar()->addMenu(tr("&View"));
    m_pViewMenu->addAction(m_pImageListDock->toggleViewAction());
    m_pViewMenu->addAction(m_pImageWindowingDock->toggleViewAction());
}


void Window::CreateToolbars()
{
    m_pFileToolbar = new FileToolbar;
    addToolBar(m_pFileToolbar);
    connect(m_pFileToolbar->GetOpenDICOMAction(), SIGNAL(triggered()), this, SLOT(OpenDicomImage()));
    connect(m_pFileToolbar->GetOpenDICOMSeriesAction(), SIGNAL(triggered()), this, SLOT(OpenDicomSeries()));

    m_pResizeToolbar = new ResizeToolbar;
    addToolBar(m_pResizeToolbar);
}


void Window::CreateCenterWidgets()
{
    m_pCanvas = new CanvasWidget(&m_ImageHandler, this);
    m_pScrollArea = new QScrollArea;
    m_pTimer = new QTimer(this);

    m_pScrollArea->setFrameShadow(QFrame::Sunken);
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setAlignment(Qt::AlignCenter);
    m_pScrollArea->setWidget(m_pCanvas);
    m_pScrollArea->setWidgetResizable(false);
    m_pScrollArea->ensureWidgetVisible(m_pCanvas);
    setCentralWidget(m_pScrollArea);

    m_pTimer->start(50);
}


void Window::CreateDocks()
{
    m_pImageListDock = new ImageListDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_pImageListDock);

    m_pImageWindowingDock = new ImageWindowDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_pImageWindowingDock);

    m_pImageLayoutDock = new ImageLayoutControlDock;
    addDockWidget(Qt::RightDockWidgetArea, m_pImageLayoutDock);

    m_pImageWindowingDock->GetSpinBoxWC()->setMinimum(0);
    m_pImageWindowingDock->GetSpinBoxWC()->setMaximum(4096);
    m_pImageWindowingDock->GetSliderWC()->setMinimum(0);
    m_pImageWindowingDock->GetSliderWC()->setMaximum(4096);

    m_pImageWindowingDock->GetSpinBoxWW()->setMinimum(0);
    m_pImageWindowingDock->GetSpinBoxWW()->setMaximum(4096);
    m_pImageWindowingDock->GetSliderWW()->setMinimum(0);
    m_pImageWindowingDock->GetSliderWW()->setMaximum(4096);

    m_pImageLayoutDock->GetSpinBoxVertical()->setMinimum(1);
    m_pImageLayoutDock->GetSpinBoxVertical()->setMaximum(8);
    m_pImageLayoutDock->GetSpinBoxHorizontal()->setMinimum(1);
    m_pImageLayoutDock->GetSpinBoxHorizontal()->setMaximum(8);
}


void Window::CreateConnections()
{
    connect(m_pTimer, SIGNAL(timeout()), m_pCanvas, SLOT(Animate()));

    for (int i=0;i<m_pCanvas->GetNumDisplays();i++)
    {
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(MiddleButtonMove(float, float)), m_pImageWindowingDock, SLOT(UpdateWindowLevel(float, float)));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(MiddleButtonDoubleClick()), this, SLOT(ResetWindow()));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(WheelMovement(int,int)), this, SLOT(UpdateActiveSlice(int,int)));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(RightButtonMove(float)), this, SLOT(Pan(float)));
    }

    connect(m_pImageWindowingDock->GetSliderWC(), SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_pImageWindowingDock->GetSliderWW(), SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_pImageWindowingDock->GetResetButton(), SIGNAL(clicked()), this, SLOT(ResetWindow()));

    connect(m_pImageLayoutDock, SIGNAL(NewLayout(int, int)), m_pCanvas, SLOT(Rearrange(int, int)));
    connect(m_pImageLayoutDock, SIGNAL(NewLayout(int, int)), this, SLOT(UpdateDisplayLayout()));

    connect(m_pResizeToolbar->GetActionZoomIn(), SIGNAL(triggered()), this, SLOT(ZoomIn25Present()));
    connect(m_pResizeToolbar->GetActionZoomOut(), SIGNAL(triggered()), this, SLOT(ZoomOut25Present()));
    connect(m_pResizeToolbar->GetActionOriginalSize(), SIGNAL(triggered()), this, SLOT(ZoomOriginalSize()));
    connect(m_pResizeToolbar->GetActionFitToHeight(), SIGNAL(triggered()), this, SLOT(ZoomFitToHeight()));
    connect(m_pResizeToolbar->GetComboResize(), SIGNAL(currentIndexChanged(int)), this, SLOT(ZoomComboResize(int)));
    connect(m_pResizeToolbar->GetComboResize()->lineEdit(), SIGNAL(editingFinished()), this, SLOT(ZoomCustomSize()));

    connect(m_pImageListDock, SIGNAL(SelectionChanged(int)), this, SLOT(UpdateImage(int)));

    m_bConnected = true;
}


void Window::SetupAnnotation()
{
    int slice = m_ImageHandler.GetImageObj()->GetActiveSlice();
    DICOMIOType::Pointer io = *m_ImageHandler.GetImageObj()->GetIOObject(slice);

    std::string temp;
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    io->GetValueFromTag("0010|0010", temp);  //Patient name
    std::string UpperLeftText = temp + "\n";
    temp = "";
    io->GetValueFromTag("0010|0030", temp);  // Birthday
    UpperLeftText += DateFormat(temp) + ", ";
    temp = "";
    io->GetValueFromTag("0010|0040", temp);  // Sex
    UpperLeftText += temp + ", ";
    temp = "";
    io->GetValueFromTag("0010|1010", temp);  // Age
    UpperLeftText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0008|103e", temp);  // Series Description
    UpperLeftText += temp +"\n";
    temp = "";
    io->GetValueFromTag("0008|0012", temp);  // Instance Creation Day
    UpperLeftText += DateFormat(temp) + "\n";
    temp = "";
    io->GetValueFromTag("0008|0013", temp);  // Instance Creation Time
    UpperLeftText += TimeFormat(temp) + "\n";
    temp = "";
    temp = std::to_string(imageObj->GetActiveSlice()+1);
    UpperLeftText += temp + "/";
    temp = "";
    temp = std::to_string(imageObj->GetMaxSliceNum()+1);  // Number of Slices
    UpperLeftText += temp + "\n";
    temp = "";


    io->GetValueFromTag("0008|0080", temp);  // Institution Name
    std::string UpperRightText = temp + "\n";
    temp = "";
    io->GetValueFromTag("0008|1090", temp);  // Manufacturer Model Name
    UpperRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0018|1020", temp);  // Software Versions
    UpperRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0018|5100", temp);  // Patient Position
    UpperRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|1013", temp);  //
    UpperRightText += temp + "\n";
    temp = "";


    io->GetValueFromTag("0018|0080", temp);  // TR
    std::string LowerLeftText = "TR " + temp + "\n";
    temp = "";
    io->GetValueFromTag("0018|0081", temp);  // TE
    LowerLeftText += "TE " + temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100a", temp);  // TA
    LowerLeftText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0018|0095", temp);  // BW
    LowerLeftText += "BW " + temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|1016", temp);  //
    LowerLeftText += temp + "\n\n";
    temp = "";
    io->GetValueFromTag("0051|1019", temp);  //
    LowerLeftText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100f", temp);  //
    LowerLeftText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0018|0024", temp);  // Sequence Name
    LowerLeftText += temp + "\n";
    temp = "";


    io->GetValueFromTag("0051|1012", temp);  //
    std::string LowerRightText = temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100d", temp);  //
    LowerRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|1017", temp);  //
    LowerRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100c", temp);  // FOV
    LowerRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100b", temp);  // Matrix Size
    LowerRightText += temp + "\n";
    temp = "";
    io->GetValueFromTag("0051|100e", temp);  //
    LowerRightText += temp + "\n";
    temp = "";
    temp = std::to_string(imageObj->GetCurrentWW());  // WW
    LowerRightText += "W " + temp + "\n";
    temp = "";
    temp = std::to_string(imageObj->GetCurrentWC());  // WC
    LowerRightText += "C " + temp + "\n";
    temp = "";

    m_pCanvas->SetupAnnotations(UpperLeftText, UpperRightText,
                                LowerLeftText, LowerRightText);
}


void Window::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}


void Window::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();

    foreach(QUrl url, urls)
    {
        QString path = url.toLocalFile();
        QFileInfo fileInfo(path);
        if(fileInfo.isFile())
            OpenImage(path.toStdString());
        else if(fileInfo.isDir())
            OpenSeries(path.toStdString());
        else
            std::cout<<"Unknown drop"<<std::endl;
    }
}


std::string Window::DateFormat(std::string string)
{
    if(string != "")
    {
        std::string year = string.substr(0, 4);
        std::string month = string.substr(4, 2);
        std::string date = string.substr(6, 2);

        return month + "/" + date + "/" + year;
    }
    else
        return "";
}


std::string Window::TimeFormat(std::string string)
{
    if(string != "")
    {
        std::string hour = string.substr(0, 2);
        std::string min = string.substr(2, 2);
        std::string sec = string.substr(4, 2);

        return hour + ":" + min + ":" + sec;
    }
    else
        return "";
}


void Window::OpenImage(std::string filepath)
{
    if(!m_ImageHandler.AddImage(QString(filepath.c_str())))
        return;

    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    m_pImageWindowingDock->GetSpinBoxWC()->setValue(imageObj->GetDefaultWC(imageObj->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(imageObj->GetDefaultWW(imageObj->GetActiveSlice()));
//    ZoomOriginalSize();
    ZoomFitToHeight();
    m_pImageWindowingDock->SetWidgetsDisabled(false);
    m_pResizeToolbar->SetWidgetsDisabled(false);

    m_pImageListDock->InsertImageSeries(&m_ImageHandler);

    if(!m_bConnected)
        CreateConnections();
    SetupAnnotation();
}


void Window::OpenSeries(std::string path)
{
    if(!m_ImageHandler.AddImageSeries(QString(path.c_str())))
        return;

    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    m_pImageWindowingDock->GetSpinBoxWC()->setValue(imageObj->GetDefaultWC(imageObj->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(imageObj->GetDefaultWW(imageObj->GetActiveSlice()));
//    ZoomOriginalSize();
    ZoomFitToHeight();
    m_pImageWindowingDock->SetWidgetsDisabled(false);
    m_pResizeToolbar->SetWidgetsDisabled(false);

    m_pImageListDock->InsertImageSeries(&m_ImageHandler);

    if(!m_bConnected)
        CreateConnections();
    SetupAnnotation();
}


// ====== slots ====== //
void Window::OpenDicomImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open DICOM file"), QDir::currentPath());
    OpenImage(filename.toStdString());
}


void Window::OpenDicomSeries()
{
    QString folderPath = QFileDialog::getExistingDirectory(0, tr("Open DICOM folder"), QDir::currentPath(), QFileDialog::ShowDirsOnly);
    OpenSeries(folderPath.toStdString());
}


void Window::CloseDicomImage()
{
    if(m_ImageHandler.GetActiveIndex()<0)
        return;

    m_pImageListDock->RemoveImageSeries(&m_ImageHandler);
    m_ImageHandler.RemoveImage();

    if(m_ImageHandler.GetNumberOfOpenedImages()<=0)
    {
        m_pCanvas->Resize(0, 0);
        m_pImageWindowingDock->SetWidgetsDisabled(true);
        m_pResizeToolbar->SetWidgetsDisabled(true);
    }
    else
    {
        std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

        short tmp1 = imageObj->GetCurrentWC();
        short tmp2 = imageObj->GetCurrentWW();
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(tmp1);
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(tmp2);
    }
    m_pScrollArea->viewport()->update();
}


void Window::Pan(float scale)
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    double presentage = 10.0*scale;
    QSize temp = (1.0+presentage)*m_pCanvas->GetDisplayWidget(0)->size();
    temp.setHeight(temp.height());
    temp.setWidth(temp.width());

    m_pCanvas->Resize(temp);

    double size = (double)m_pCanvas->GetDisplayWidget(0)->size().height()/(double)imageObj->GetHeight(imageObj->GetActiveSlice());
    imageObj->SetCurrentSizeFactor(size);

    std::ostringstream ss;
    ss << 100.0*((double)temp.height()/(double)imageObj->GetHeight(imageObj->GetActiveSlice()));
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::UpdateImage()
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    short tmp1 = m_pImageWindowingDock->GetSpinBoxWC()->value();
    short tmp2 = m_pImageWindowingDock->GetSpinBoxWW()->value();
    m_pCanvas->Resize(imageObj->GetWidth(imageObj->GetActiveSlice())*imageObj->GetCurrentSizeFactor(),
                      imageObj->GetHeight(imageObj->GetActiveSlice())*imageObj->GetCurrentSizeFactor());
    m_ImageHandler.UpdateImage(tmp1, tmp2);

    SetupAnnotation();
}


void Window::UpdateImage(int index)
{
    m_ImageHandler.SetActiveIndex(index);
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    short tmp1 = imageObj->GetCurrentWC();
    short tmp2 = imageObj->GetCurrentWW();
    m_pImageWindowingDock->GetSpinBoxWC()->setValue(tmp1);
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(tmp2);
    UpdateImage();
    SetupAnnotation();
}


void Window::UpdateActiveSlice(int deltaX, int deltaY)
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();
    int slice = m_ImageHandler.GetImageObj()->GetActiveSlice() - deltaY;

    if(slice>=imageObj->GetMinSliceNum() &&
       slice<=imageObj->GetMaxSliceNum())
    {
        imageObj->SetActiveSlice(slice);
        m_pImageWindowingDock->GetSpinBoxWC()->setValue(imageObj->GetDefaultWC(imageObj->GetActiveSlice()));
        m_pImageWindowingDock->GetSpinBoxWW()->setValue(imageObj->GetDefaultWW(imageObj->GetActiveSlice()));
        UpdateImage();
    }

    SetupAnnotation();
}


void Window::ResetWindow()
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    m_pImageWindowingDock->GetSpinBoxWC()->setValue(imageObj->GetDefaultWC(imageObj->GetActiveSlice()));
    m_pImageWindowingDock->GetSpinBoxWW()->setValue(imageObj->GetDefaultWW(imageObj->GetActiveSlice()));
    m_ImageHandler.UpdateImage(imageObj->GetDefaultWC(imageObj->GetActiveSlice()),
                               imageObj->GetDefaultWW(imageObj->GetActiveSlice()));
    SetupAnnotation();
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
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    int temp = imageObj->GetWidth(imageObj->GetActiveSlice());
    int temp1 = imageObj->GetHeight(imageObj->GetActiveSlice());

    m_pCanvas->Resize(imageObj->GetWidth(imageObj->GetActiveSlice()),
                      imageObj->GetHeight(imageObj->GetActiveSlice()));
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString("100%"));

    double size = (double)((m_pCanvas->size().height()+10)/m_pCanvas->GetVerticalNum())/(double)imageObj->GetHeight(imageObj->GetActiveSlice());
    imageObj->SetCurrentSizeFactor(size);
}


void Window::ZoomFitToHeight()
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    if(m_ImageHandler.GetActiveIndex()<0)
        return;

    double size = (double)m_pScrollArea->height()/((double)imageObj->GetHeight(imageObj->GetActiveSlice()+10)*m_pCanvas->GetVerticalNum());
    m_pCanvas->Resize(imageObj->GetWidth(imageObj->GetActiveSlice())*size,
                      imageObj->GetHeight(imageObj->GetActiveSlice())*size);


    imageObj->SetCurrentSizeFactor(size);
    std::ostringstream ss;
    ss << 100.0*size;
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::ZoomCustomSize()
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    std::string temp = m_pResizeToolbar->GetComboResize()->currentText().toStdString();

    double tmp = atof(temp.c_str());
    std::stringstream ss;
    ss<<tmp;
    std::string currentText = ss.str() + "%";
    m_pResizeToolbar->GetComboResize()->setCurrentText(QString(currentText.c_str()));

    QSize original = QSize(imageObj->GetWidth(imageObj->GetActiveSlice()),
                           imageObj->GetHeight(imageObj->GetActiveSlice()));
    m_pCanvas->Resize(original*tmp/100.0);

    double size = tmp/100.0;
    imageObj->SetCurrentSizeFactor(size);
}


void Window::ZoomComboResize(int index)
{
    std::shared_ptr<ImageContainer> imageObj = m_ImageHandler.GetImageObj();

    if(m_ImageHandler.GetActiveIndex()<0)
        return;
    QSize original = QSize(imageObj->GetWidth(imageObj->GetActiveSlice()),
                           imageObj->GetHeight(imageObj->GetActiveSlice()));
    switch(index)
    {
    case 0:
        m_pCanvas->Resize(original*8.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 1:
        m_pCanvas->Resize(original*7.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 2:
        m_pCanvas->Resize(original*6.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 3:
        m_pCanvas->Resize(original*5.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 4:
        m_pCanvas->Resize(original*4.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 5:
        m_pCanvas->Resize(original*3.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 6:
        m_pCanvas->Resize(original*2.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 7:
        m_pCanvas->Resize(original*1.0);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    case 8:
        m_pCanvas->Resize(original*0.5);
        imageObj->SetCurrentSizeFactor(8.0);
        break;
    default:
        std::cout<<"Combo resize: no such index found."<<std::endl;
        break;
    }
}


void Window::UpdateDisplayLayout()
{
    ZoomFitToHeight();
    for (int i=0;i<m_pCanvas->GetNumDisplays();i++)
    {
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(MiddleButtonMove(float, float)), m_pImageWindowingDock, SLOT(UpdateWindowLevel(float, float)));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(MiddleButtonDoubleClick()), this, SLOT(ResetWindow()));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(WheelMovement(int,int)), this, SLOT(UpdateActiveSlice(int,int)));
        connect(m_pCanvas->GetDisplayWidget(i), SIGNAL(RightButtonMove(float)), this, SLOT(Pan(float)));
    }
    SetupAnnotation();
}
