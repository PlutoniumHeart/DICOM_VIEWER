#include "Window.h"


Window::Window()
    : m_glDisplay(NULL)
    , m_ScrollArea(NULL)
    , m_Timer(NULL)
    , m_MainMenu(NULL)
    , m_ResizeToolBar(NULL)
    , m_ImageWindowingDock(NULL)
{
    setWindowTitle(tr("DICOM Viewer"));
    resize(1024, 768);

    SetupMenuBar();
    
    m_glDisplay = new GLWidget(&m_Helper, this);
    m_ScrollArea = new QScrollArea;
    m_Timer = new QTimer(this);

    m_ScrollArea->setFrameShadow(QFrame::Sunken);
    m_ScrollArea->setBackgroundRole(QPalette::Dark);
    m_ScrollArea->setAlignment(Qt::AlignCenter);
    m_ScrollArea->setWidget(m_glDisplay);
    setCentralWidget(m_ScrollArea);

    m_ImageWindowingDock = new ImageWindowDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_ImageWindowingDock);

    m_FileToolBar = new FileToolBar;
    addToolBar(m_FileToolBar);

    m_ResizeToolBar = new ResizeToolBar;
    addToolBar(m_ResizeToolBar);
    
    m_Timer->start(50);
    
    connect(m_glDisplay, SIGNAL(MiddleButtonMove(int, int)),
            m_ImageWindowingDock, SLOT(UpdateWindowLevel(int, int)));
    connect(m_ImageWindowingDock->GetSliderWC(),
            SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_ImageWindowingDock->GetSliderWW(),
            SIGNAL(valueChanged(int)), this, SLOT(UpdateImage()));
    connect(m_glDisplay, SIGNAL(MiddleButtonDoubleClick()),
            this, SLOT(ResetWindow()));
    connect(m_ImageWindowingDock->GetResetButton(), SIGNAL(clicked()),
            this, SLOT(ResetWindow()));
    connect(m_glDisplay, SIGNAL(RightButtonMove(int)), this, SLOT(Pan(int)));
    connect(m_FileToolBar->GetOpenDICOMAction(), SIGNAL(triggered()), this, SLOT(OpenDICOM()));
    connect(m_ResizeToolBar->GetActionZoomIn(), SIGNAL(triggered()),
            this, SLOT(ZoomIn25Present()));
    connect(m_ResizeToolBar->GetActionZoomOut(), SIGNAL(triggered()),
            this, SLOT(ZoomOut25Present()));
    connect(m_ResizeToolBar->GetActionOriginalSize(), SIGNAL(triggered()),
            this, SLOT(ZoomOriginalSize()));
    connect(m_ResizeToolBar->GetActionFitToHeight(), SIGNAL(triggered()),
            this, SLOT(ZoomFitToHeight()));
    connect(m_ResizeToolBar->GetComboResize(), SIGNAL(currentIndexChanged(int)),
            this, SLOT(ZoomComboResize(int)));
    connect(m_ResizeToolBar->GetComboResize()->lineEdit(), SIGNAL(editingFinished()),
            this, SLOT(ZoomCustomSize()));
}


Window::~Window()
{
    delete m_glDisplay;
    delete m_ScrollArea;
    delete m_Timer;
    delete m_ImageWindowingDock;
}


void Window::SetupMenuBar()
{
    m_MainMenu = menuBar()->addMenu(tr("&File"));
    m_MainMenu->addAction(tr("&Open"), this, SLOT(OpenDICOM()));
    m_MainMenu->addAction(tr("&Quit"), this, SLOT(close()));
}


void Window::OpenDICOM()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DICOM file"), QDir::currentPath());
    m_Helper.OpenImage(fileName);

    m_glDisplay->resize(m_Helper.GetImageWidth(), m_Helper.GetImageHeight());
    
    m_ImageWindowingDock->GetSpinBoxWC()->setMinimum(0);
    m_ImageWindowingDock->GetSpinBoxWC()->setMaximum(2048);
    m_ImageWindowingDock->GetSliderWC()->setMinimum(0);
    m_ImageWindowingDock->GetSliderWC()->setMaximum(2048);
    m_ImageWindowingDock->GetSpinBoxWC()->setValue(m_Helper.GetDefaultImageWC());

    m_ImageWindowingDock->GetSpinBoxWW()->setMinimum(0);
    m_ImageWindowingDock->GetSpinBoxWW()->setMaximum(2048);
    m_ImageWindowingDock->GetSliderWW()->setMinimum(0);
    m_ImageWindowingDock->GetSliderWW()->setMaximum(2048);
    m_ImageWindowingDock->GetSpinBoxWW()->setValue(m_Helper.GetDefaultImageWW());
    
    connect(m_Timer, SIGNAL(timeout()), m_glDisplay, SLOT(Animate()));
    
    m_ImageWindowingDock->EnableWidgets();
}


void Window::UpdateImage()
{
    m_Helper.UpdateImage(m_ImageWindowingDock->GetSpinBoxWC()->value(),
                         m_ImageWindowingDock->GetSpinBoxWW()->value());
}


void Window::ResetWindow()
{
    m_ImageWindowingDock->GetSpinBoxWC()->setValue(m_Helper.GetDefaultImageWC());
    m_ImageWindowingDock->GetSpinBoxWW()->setValue(m_Helper.GetDefaultImageWW());
    m_Helper.UpdateImage(m_Helper.GetDefaultImageWC(), m_Helper.GetDefaultImageWW());
}


void Window::Pan(int scale)
{
    double presentage = scale/100.0;
    QSize temp = (1.0+presentage)*m_glDisplay->size();
    if(((double)temp.width()/(double)m_Helper.GetImageWidth())<=8.0 &&
       ((double)temp.height()/(double)m_Helper.GetImageHeight())<=8.0 &&
       ((double)temp.width()/(double)m_Helper.GetImageWidth())>=1.0/8.0 &&
       ((double)temp.height()/(double)m_Helper.GetImageHeight())>=1.0/8.0)
    {
        m_glDisplay->resize(temp);

        std::string currentSize =
            m_ResizeToolBar->GetComboResize()->currentText().toUtf8().constData();
        short tmp = atoi(currentSize.c_str());
        std::ostringstream ss;
        ss << 100.0*((double)temp.height()/(double)m_Helper.GetImageHeight());
        std::string currentText(ss.str());
        currentText = currentText + "%";
        m_ResizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
    }
}


void Window::ZoomIn25Present()
{
    Pan(25);
}


void Window::ZoomOut25Present()
{
    Pan(-25);
}


void Window::ZoomOriginalSize()
{
    m_glDisplay->resize(m_Helper.GetImageWidth(), m_Helper.GetImageHeight());
    m_ResizeToolBar->GetComboResize()->setCurrentText(QString("100%"));
}


void Window::ZoomFitToHeight()
{
    short tmp = m_ScrollArea->height();
    double temp = (double)tmp/m_glDisplay->height();
    m_glDisplay->resize(m_glDisplay->size()*temp);
    std::ostringstream ss;
    ss << 100.0*((double)m_glDisplay->size().height()/(double)m_Helper.GetImageHeight());
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_ResizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::ZoomComboResize(int index)
{
    QSize original = QSize(m_Helper.GetImageWidth(), m_Helper.GetImageHeight());
    switch(index)
    {
    case 0:
        m_glDisplay->resize(original*8.0);
        break;
    case 1:
        m_glDisplay->resize(original*7.0);
        break;
    case 2:
        m_glDisplay->resize(original*6.0);
        break;
    case 3:
        m_glDisplay->resize(original*5.0);
        break;
    case 4:
        m_glDisplay->resize(original*4.0);
        break;
    case 5:
        m_glDisplay->resize(original*3.0);
        break;
    case 6:
        m_glDisplay->resize(original*2.0);
        break;
    case 7:
        m_glDisplay->resize(original*1.0);
        break;
    case 8:
        m_glDisplay->resize(original*0.5);
        break;
    default:
        std::cout<<"Combo resize: no such index found."<<std::endl;
        break;
    }
}


void Window::ZoomCustomSize()
{
    std::string temp = m_ResizeToolBar->GetComboResize()->currentText().toUtf8().constData();

    double tmp = atof(temp.c_str());
    std::stringstream ss;
    ss<<tmp;
    std::string currentText = ss.str() + "%";
    m_ResizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
    
    QSize original = QSize(m_Helper.GetImageWidth(), m_Helper.GetImageHeight());
    m_glDisplay->resize(original*tmp/100.0);
}
