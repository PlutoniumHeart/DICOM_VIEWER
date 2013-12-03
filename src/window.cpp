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
    resize(800, 600);

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
    QSize temp = presentage*m_glDisplay->size();
    if(m_glDisplay->size().width()+temp.width()<=8*helper.GetImageWidth() &&
       m_glDisplay->size().height()+temp.height()<=8*helper.GetImageHeight() &&
       m_glDisplay->size().width()+temp.width()>=helper.GetImageWidth()/8 &&
       m_glDisplay->size().height()+temp.height()>=helper.GetImageHeight()/8)
    {
        m_glDisplay->resize(m_glDisplay->size()+temp);
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
}


void Window::zoomFitToHeight()
{
    short tmp = m_scrollArea->height();
    double temp = (double)tmp/m_glDisplay->height();
    m_glDisplay->resize(m_glDisplay->size()*temp);
}
