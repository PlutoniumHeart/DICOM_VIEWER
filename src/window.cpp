#include "window.h"


Window::Window()
    : m_glDisplay(NULL)
    , m_scrollArea(NULL)
    , m_timer(NULL)
    , m_mainMenu(NULL)
    , m_resizeToolBar(NULL)
    , m_imageWindowingDock(NULL)
{
    setWindowTitle(tr("DICOM Viewer"));
    resize(1024, 768);

    setupMenuBar();
    
    m_glDisplay = new GLWidget(&helper, this);
    m_scrollArea = new QScrollArea;
    m_timer = new QTimer(this);

    m_scrollArea->setFrameShadow(QFrame::Sunken);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setAlignment(Qt::AlignCenter);
    m_scrollArea->setWidget(m_glDisplay);
    setCentralWidget(m_scrollArea);

    m_imageWindowingDock = new ImageWindowDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_imageWindowingDock);

    m_fileToolBar = new FileToolBar;
    addToolBar(m_fileToolBar);

    m_resizeToolBar = new ResizeToolBar;
    addToolBar(m_resizeToolBar);
    
    m_timer->start(50);
    
    connect(m_glDisplay, SIGNAL(middleButtonMove(int, int)), m_imageWindowingDock, SLOT(updateWindowLevel(int, int)));
    connect(m_imageWindowingDock->GetSliderWC(), SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(m_imageWindowingDock->GetSliderWW(), SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(m_glDisplay, SIGNAL(middleButtonDoubleClick()), this, SLOT(resetWindow()));
    connect(m_imageWindowingDock->GetResetButton(), SIGNAL(clicked()), this, SLOT(resetWindow()));
    connect(m_glDisplay, SIGNAL(rightButtonMove(int)), this, SLOT(pan(int)));
    connect(m_fileToolBar->GetOpenDICOMAction(), SIGNAL(triggered()), this, SLOT(openDICOM()));
    connect(m_resizeToolBar->GetActionZoomIn(), SIGNAL(triggered()), this, SLOT(zoomIn25Present()));
    connect(m_resizeToolBar->GetActionZoomOut(), SIGNAL(triggered()), this, SLOT(zoomOut25Present()));
    connect(m_resizeToolBar->GetActionOriginalSize(), SIGNAL(triggered()), this, SLOT(zoomOriginalSize()));
    connect(m_resizeToolBar->GetActionFitToHeight(), SIGNAL(triggered()), this, SLOT(zoomFitToHeight()));
    connect(m_resizeToolBar->GetComboResize(), SIGNAL(currentIndexChanged(int)), this, SLOT(zoomComboResize(int)));
    connect(m_resizeToolBar->GetComboResize()->lineEdit(), SIGNAL(editingFinished()), this, SLOT(zoomCustomSize()));
}


Window::~Window()
{
    delete m_glDisplay;
    delete m_scrollArea;
    delete m_timer;
    delete m_imageWindowingDock;
}


void Window::setupMenuBar()
{
    m_mainMenu = menuBar()->addMenu(tr("&File"));
    m_mainMenu->addAction(tr("&Open"), this, SLOT(openDICOM()));
    m_mainMenu->addAction(tr("&Quit"), this, SLOT(close()));
}


void Window::openDICOM()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DICOM file"), QDir::currentPath());
    helper.openImage(fileName);

    m_glDisplay->resize(helper.GetImageWidth(), helper.GetImageHeight());
    
    m_imageWindowingDock->GetSpinBoxWC()->setMinimum(-2048);
    m_imageWindowingDock->GetSpinBoxWC()->setMaximum(2048);
    m_imageWindowingDock->GetSliderWC()->setMinimum(-2048);
    m_imageWindowingDock->GetSliderWC()->setMaximum(2048);
    m_imageWindowingDock->GetSpinBoxWC()->setValue(helper.GetDefaultImageWC());

    m_imageWindowingDock->GetSpinBoxWW()->setMinimum(-2048);
    m_imageWindowingDock->GetSpinBoxWW()->setMaximum(2048);
    m_imageWindowingDock->GetSliderWW()->setMinimum(-2048);
    m_imageWindowingDock->GetSliderWW()->setMaximum(2048);
    m_imageWindowingDock->GetSpinBoxWW()->setValue(helper.GetDefaultImageWW());
    
    connect(m_timer, SIGNAL(timeout()), m_glDisplay, SLOT(animate()));
    
    m_imageWindowingDock->EnableWidgets();
}


void Window::updateImage()
{
    helper.updateImage(m_imageWindowingDock->GetSpinBoxWC()->value(),
                       m_imageWindowingDock->GetSpinBoxWW()->value());
}


void Window::resetWindow()
{
    m_imageWindowingDock->GetSpinBoxWC()->setValue(helper.GetDefaultImageWC());
    m_imageWindowingDock->GetSpinBoxWW()->setValue(helper.GetDefaultImageWW());
    helper.updateImage(helper.GetDefaultImageWC(), helper.GetDefaultImageWW());
}


void Window::pan(int scale)
{
    double presentage = scale/100.0;
    QSize temp = (1.0+presentage)*m_glDisplay->size();
    if(((double)temp.width()/(double)helper.GetImageWidth())<=8.0 &&
       ((double)temp.height()/helper.GetImageHeight())<=8.0 &&
       ((double)temp.width()/(double)helper.GetImageWidth())>=1.0/8.0 &&
       ((double)temp.height()/(double)helper.GetImageHeight())>=1.0/8.0)
    {
        m_glDisplay->resize(temp);

        std::string currentSize =
            m_resizeToolBar->GetComboResize()->currentText().toUtf8().constData();
        short tmp = atoi(currentSize.c_str());
        std::ostringstream ss;
        ss << 100.0*((double)temp.height()/(double)helper.GetImageHeight());
        std::string currentText(ss.str());
        currentText = currentText + "%";
        m_resizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
    }
}


void Window::zoomIn25Present()
{
    pan(25);
}


void Window::zoomOut25Present()
{
    pan(-25);
}


void Window::zoomOriginalSize()
{
    m_glDisplay->resize(helper.GetImageWidth(), helper.GetImageHeight());
    m_resizeToolBar->GetComboResize()->setCurrentText(QString("100%"));
}


void Window::zoomFitToHeight()
{
    short tmp = m_scrollArea->height();
    double temp = (double)tmp/m_glDisplay->height();
    m_glDisplay->resize(m_glDisplay->size()*temp);
    std::ostringstream ss;
    ss << 100.0*((double)m_glDisplay->size().height()/(double)helper.GetImageHeight());
    std::string currentText(ss.str());
    currentText = currentText + "%";
    m_resizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
}


void Window::zoomComboResize(int index)
{
    QSize original = QSize(helper.GetImageWidth(), helper.GetImageHeight());
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


void Window::zoomCustomSize()
{
    std::string temp = m_resizeToolBar->GetComboResize()->currentText().toUtf8().constData();

    short tmp = atoi(temp.c_str());
    std::stringstream ss;
    ss<<tmp;
    std::string currentText = ss.str() + "%";
    m_resizeToolBar->GetComboResize()->setCurrentText(QString(currentText.c_str()));
    
    QSize original = QSize(helper.GetImageWidth(), helper.GetImageHeight());
    m_glDisplay->resize(original*tmp/100.0);
}
