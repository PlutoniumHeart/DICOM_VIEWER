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
    
    m_imageWindowingDock->GetSpinBoxWC()->setMinimum(helper.GetLowerBound());
    m_imageWindowingDock->GetSpinBoxWC()->setMaximum(helper.GetUpperBound());
    m_imageWindowingDock->GetSliderWC()->setMinimum(helper.GetLowerBound());
    m_imageWindowingDock->GetSliderWC()->setMaximum(helper.GetUpperBound());
    m_imageWindowingDock->GetSpinBoxWC()->setValue(helper.GetDefaultImageWC());

    m_imageWindowingDock->GetSpinBoxWW()->setMinimum(helper.GetLowerBound());
    m_imageWindowingDock->GetSpinBoxWW()->setMaximum(helper.GetUpperBound());
    m_imageWindowingDock->GetSliderWW()->setMinimum(helper.GetLowerBound());
    m_imageWindowingDock->GetSliderWW()->setMaximum(helper.GetUpperBound());
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
    if(m_glDisplay->width()+scale<=8*helper.GetImageWidth() &&
       m_glDisplay->height()+scale<=8*helper.GetImageHeight() &&
       m_glDisplay->width()+scale>=helper.GetImageWidth()/8 &&
       m_glDisplay->height()+scale>=helper.GetImageHeight()/8)
    {
        m_glDisplay->resize(m_glDisplay->width()+scale, m_glDisplay->height()+scale);
    }
}
