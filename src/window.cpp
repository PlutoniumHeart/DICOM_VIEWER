#include "window.h"


Window::Window()
    : m_glDisplay(NULL)
    , m_scrollArea(NULL)
    , m_timer(NULL)
    , m_mainMenu(NULL)
    , m_lowerDock(NULL)
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

    m_lowerDock = new ImageWindowDock;
    addDockWidget(Qt::BottomDockWidgetArea, m_lowerDock);
    
    m_timer->start(50);
    
    connect(m_glDisplay, SIGNAL(middleButtonMove(int, int)), m_lowerDock, SLOT(updateWindowLevel(int, int)));
    connect(m_lowerDock->GetSliderWC(), SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(m_lowerDock->GetSliderWW(), SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(m_glDisplay, SIGNAL(middleButtonDoubleClick()), this, SLOT(resetWindow()));
    connect(m_lowerDock->GetResetButton(), SIGNAL(clicked()), this, SLOT(resetWindow()));
    connect(m_glDisplay, SIGNAL(rightButtonMove(int)), this, SLOT(pan(int)));
}


Window::~Window()
{
    delete m_glDisplay;
    delete m_scrollArea;
    delete m_timer;
    delete m_lowerDock;
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
    
    m_lowerDock->GetSpinBoxWC()->setMinimum(helper.GetLowerBound());
    m_lowerDock->GetSpinBoxWC()->setMaximum(helper.GetUpperBound());
    m_lowerDock->GetSliderWC()->setMinimum(helper.GetLowerBound());
    m_lowerDock->GetSliderWC()->setMaximum(helper.GetUpperBound());
    m_lowerDock->GetSpinBoxWC()->setValue(helper.GetDefaultImageWC());

    m_lowerDock->GetSpinBoxWW()->setMinimum(helper.GetLowerBound());
    m_lowerDock->GetSpinBoxWW()->setMaximum(helper.GetUpperBound());
    m_lowerDock->GetSliderWW()->setMinimum(helper.GetLowerBound());
    m_lowerDock->GetSliderWW()->setMaximum(helper.GetUpperBound());
    m_lowerDock->GetSpinBoxWW()->setValue(helper.GetDefaultImageWW());
    
    connect(m_timer, SIGNAL(timeout()), m_glDisplay, SLOT(animate()));
    
    m_lowerDock->EnableWidgets();
}


void Window::updateImage()
{
    helper.updateImage(m_lowerDock->GetSpinBoxWC()->value(), m_lowerDock->GetSpinBoxWW()->value());
}


void Window::resetWindow()
{
    m_lowerDock->GetSpinBoxWC()->setValue(helper.GetDefaultImageWC());
    m_lowerDock->GetSpinBoxWW()->setValue(helper.GetDefaultImageWW());
    helper.updateImage(helper.GetDefaultImageWC(), helper.GetDefaultImageWW());
}


void Window::pan(int scale)
{
    m_glDisplay->resize(m_glDisplay->width()+scale, m_glDisplay->height()+scale);
}
