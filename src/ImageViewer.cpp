#include "ImageViewer.h"


ImageViewer::ImageViewer(QMainWindow *parent)
    : QMainWindow(parent)
    , m_sWidth(0)
    , m_sHeight(0)
    , m_sWC(0)
    , m_sWW(0)
{
    ui.setupUi(this);

    ui.scrollArea->setBackgroundRole(QPalette::Dark);
    ui.scrollArea->setWidget(ui.qvtkWidget);
    m_imageView = vtkSmartPointer<vtkResliceImageViewer>::New();

    setCentralWidget(ui.scrollArea);
    
    createActions();

    m_imageObj = ShortImageType::New();
    m_dicomIO = DICOMIOType::New();
    
    setWindowTitle(tr("Image Viewer"));
}


ImageViewer::~ImageViewer()
{
}


void ImageViewer::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        ImageIO::ReadDICOMImage(fileName.toUtf8().constData(), m_imageObj, m_dicomIO);
        std::string temp;
        m_dicomIO->GetValueFromTag("0028|1050", temp);
        m_sWC = atoi(temp.c_str());
        ui.spinBoxWC->setValue(m_sWC);
        m_dicomIO->GetValueFromTag("0028|1051", temp);
        m_sWW = atoi(temp.c_str());
        ui.spinBoxWW->setValue(m_sWW);
        m_dicomIO->GetValueFromTag("0028|0106", temp);
        ui.spinBoxWC->setMinimum(atoi(temp.c_str()));
        ui.spinBoxWW->setMinimum(atoi(temp.c_str()));
        ui.windowCenter->setMinimum(atoi(temp.c_str()));
        ui.windowWidth->setMinimum(atoi(temp.c_str()));
        m_dicomIO->GetValueFromTag("0028|0107", temp);
        ui.spinBoxWC->setMaximum(atoi(temp.c_str()));
        ui.spinBoxWW->setMaximum(atoi(temp.c_str()));
        ui.windowCenter->setMaximum(atoi(temp.c_str()));
        ui.windowWidth->setMaximum(atoi(temp.c_str()));
        m_sWidth = m_imageObj->GetLargestPossibleRegion().GetSize().GetElement(0);
        m_sHeight = m_imageObj->GetLargestPossibleRegion().GetSize().GetElement(1);

        m_dicomIO->GetValueFromTag("0010|0010", m_patientName);
        m_dicomIO->GetValueFromTag("0010|0040", m_sex);
        m_dicomIO->GetValueFromTag("0010|0030", m_birthday);

        typedef itk::ImageToVTKImageFilter<ShortImageType> ConnectorType;
        ConnectorType::Pointer connector = ConnectorType::New();
        connector->SetInput(m_imageObj);
        connector->Update();

        windowLevelLookupTable = vtkSmartPointer<vtkWindowLevelLookupTable>::New();
        windowLevelLookupTable->SetWindow(ui.spinBoxWW->value());
        windowLevelLookupTable->SetLevel(ui.spinBoxWC->value());
        windowLevelLookupTable->SetRampToLinear();
        windowLevelLookupTable->Build();
        
        vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
        image->DeepCopy(connector->GetOutput());
        ui.qvtkWidget->SetRenderWindow(m_imageView->GetRenderWindow());
        vtkSmartPointer<vtkRenderWindowInteractor> interactor = ui.qvtkWidget->GetInteractor();

        m_imageView->SetInputData(image);
        m_imageView->SetSlice(m_imageView->GetSliceMax()/2);
        m_imageView->GetRenderer()->ResetCamera();
        m_imageView->SetLookupTable(windowLevelLookupTable);
        m_imageView->GetRenderer()->ResetCamera();
        m_imageView->SetupInteractor(interactor);
        m_imageView->Render();
        interactor->Disable();
        
        ui.qvtkWidget->update();
        
        scaleFactor = 1.0;
        ui.actionPrint->setEnabled(true);
        ui.actionFitToWindow->setEnabled(true);
        ui.spinBoxWC->setEnabled(true);
        ui.spinBoxWW->setEnabled(true);
        ui.windowCenter->setEnabled(true);
        ui.windowWidth->setEnabled(true);
        ui.pushButtonReset->setEnabled(true);
        updateActions();

        fitToWindow();
    }
}


void ImageViewer::print()
{
    /*
    Q_ASSERT(ui.imageLabel->pixmap());
    QPrintDialog dialog(&printer, this);
    if(dialog.exec())
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = ui.imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(ui.imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *ui.imageLabel->pixmap());
    }
    */
}


void ImageViewer::normalSize()
{
    //ui.imageLabel->adjustSize();
    scaleFactor = 1.0;
}


void ImageViewer::fitToWindow()
{
    bool fitToWindow = ui.actionFitToWindow->isChecked();
    ui.scrollArea->setWidgetResizable(fitToWindow);
    if(!fitToWindow)
        normalSize();
    updateActions();
}


void ImageViewer::zoomIn()
{
    scaleImage(1.25);
    //updateDisplay();
}


void ImageViewer::zoomOut()
{
    scaleImage(0.75);
    //updateDisplay();
}


void ImageViewer::windowReset()
{
    ui.spinBoxWC->setValue(m_sWC);
    ui.spinBoxWW->setValue(m_sWW);
}


void ImageViewer::updateDisplay()
{
    m_imageView->SetColorWindow(ui.spinBoxWW->value());
    m_imageView->SetColorLevel(ui.spinBoxWC->value());
    m_imageView->Render();
}


void ImageViewer::createActions()
{
    connect(ui.actionOpen_DICOM, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui.actionPrint, SIGNAL(triggered()), this, SLOT(print()));
    connect(ui.actionFitToWindow, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(ui.actionNormalSize, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(ui.actionZoom_in_25, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui.actionZoom_out_25, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui.pushButtonReset, SIGNAL(clicked()), this, SLOT(windowReset()));
    connect(ui.spinBoxWC, SIGNAL(valueChanged(int)), this, SLOT(updateDisplay()));
    connect(ui.spinBoxWW, SIGNAL(valueChanged(int)), this, SLOT(updateDisplay()));
}


void ImageViewer::scaleImage(double factor)
{
    /*
    scaleFactor*=factor;
    Q_ASSERT(ui.imageLabel->pixmap());
    ui.imageLabel->resize(scaleFactor*ui.imageLabel->pixmap()->size());

    adjustScrollBar(ui.scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui.scrollArea->verticalScrollBar(), factor);

    ui.actionZoom_in_25->setEnabled(scaleFactor<3.0);
    ui.actionZoom_out_25->setEnabled(scaleFactor>0.333);
    */
}


void ImageViewer::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor*scrollBar->value()+((factor-1)*scrollBar->pageStep()/2)));
}


void ImageViewer::updateActions()
{
    ui.actionZoom_in_25->setEnabled(!ui.actionFitToWindow->isChecked());
    ui.actionZoom_out_25->setEnabled(!ui.actionFitToWindow->isChecked());
    ui.actionNormalSize->setEnabled(!ui.actionFitToWindow->isChecked());
}


void ImageViewer::resizeEvent(QResizeEvent * /* event */)
{
    /*
    int scrollAreaPosX = (this->width()/2-(ui.scrollArea->width()/2));
    int scrollAreaPosY = (((this->height()-ui.dockWidgetBottom->height())/2-(ui.scrollArea->height()/2)));
    int scrollAreaWidth = ui.scrollArea->width();
    int scrollAreaHeight = ui.scrollArea->height();
    ui.scrollArea->setGeometry(QRect(scrollAreaPosX, scrollAreaPosY, scrollAreaWidth, scrollAreaHeight));
    */
}
