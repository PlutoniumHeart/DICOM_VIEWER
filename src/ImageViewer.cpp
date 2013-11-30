#include "ImageViewer.h"


ImageViewer::ImageViewer(QMainWindow *parent)
    : QMainWindow(parent)
    , m_sWidth(0)
    , m_sHeight(0)
    , m_sWC(0)
    , m_sWW(0)
    , m_mouseLeftButtonDown(false)
    , m_mouseMiddleButtonDown(false)
{
    ui.setupUi(this);

    ui.scrollArea->setBackgroundRole(QPalette::Dark);
    ui.scrollArea->setWidget(ui.qvtkWidget);
    ui.scrollArea->setWidgetResizable(true);
    ui.scrollArea->setMouseTracking(true);
    ui.scrollArea->installEventFilter(this);
    ui.scrollArea->viewport()->setMouseTracking(true);
    ui.scrollArea->viewport()->installEventFilter(this);
    ui.qvtkWidget->setMouseTracking(true);
    ui.qvtkWidget->installEventFilter(this);

    m_imageObj = ShortImageType::New();
    m_dicomIO = DICOMIOType::New();
    image = vtkSmartPointer<vtkImageData>::New();
    m_imageView = vtkSmartPointer<vtkResliceImageViewer>::New();
    windowLevelLookupTable = vtkSmartPointer<vtkWindowLevelLookupTable>::New();
    
    setCentralWidget(ui.scrollArea);
    
    //QSize size = this->size();
    //std::cout<<size.width()<<" "<<size.height()<<std::endl;
    //ui.qvtkWidget->resize(size);
    ui.qvtkWidget->GetRenderWindow()->SetSize(0,0);

    //
    ImageIO::CreateBlankImage<ShortImageType::Pointer, ShortImageType::RegionType>(m_imageObj, 512, 512);
    typedef itk::ImageToVTKImageFilter<ShortImageType> ConnectorType;
    ConnectorType::Pointer connector = ConnectorType::New();
    connector->SetInput(m_imageObj);
    connector->Update();

    image->DeepCopy(connector->GetOutput());
    ui.qvtkWidget->SetRenderWindow(m_imageView->GetRenderWindow());
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = ui.qvtkWidget->GetInteractor();

    m_imageView->SetInputData(image);
    m_imageView->SetLookupTable(windowLevelLookupTable);

    m_imageView->SetupInteractor(interactor);
    m_imageView->Render();
    interactor->Disable();
    ui.qvtkWidget->update();
    ui.qvtkWidget->adjustSize();
    //
    
    createActions();
    
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

        ShortImageType::Pointer imageObj_flip = ShortImageType::New();
        ImageFilter::FlipImageFilter<ShortImageType, ShortImageType,
                                     ShortImageType::Pointer, ShortImageType::Pointer>
            (m_imageObj, imageObj_flip, 0, 1);
        typedef itk::ImageToVTKImageFilter<ShortImageType> ConnectorType;
        ConnectorType::Pointer connector = ConnectorType::New();
        connector->SetInput(imageObj_flip);
        connector->Update();
        
        windowLevelLookupTable->SetWindow(ui.spinBoxWW->value());
        windowLevelLookupTable->SetLevel(ui.spinBoxWC->value());
        windowLevelLookupTable->SetRampToLinear();
        windowLevelLookupTable->Build();
        
        image->DeepCopy(connector->GetOutput());
        ui.qvtkWidget->SetRenderWindow(m_imageView->GetRenderWindow());
        vtkSmartPointer<vtkRenderWindowInteractor> interactor = ui.qvtkWidget->GetInteractor();

        m_imageView->SetInputData(image);
        m_imageView->SetSlice(m_imageView->GetSliceMax()/2);
        m_imageView->SetLookupTable(windowLevelLookupTable);
        m_imageView->GetRenderer()->ResetCamera();

        //
        vtkCamera* camera = m_imageView->GetRenderer()->GetActiveCamera();
        //m_imageView->GetRenderer()->SetBackground(1,0,0);
        int extent[6];
        double origin[3];
        double spacing[3];
        image->GetExtent(extent);
        image->GetOrigin(origin);
        image->GetSpacing(spacing);
        float xc = origin[0] + 0.5*(extent[0] + extent[1])*spacing[0];
        float yc = origin[1] + 0.5*(extent[2] + extent[3])*spacing[1];
        float yd = (extent[3] - extent[2] + 1)*spacing[1];
        float d = camera->GetDistance();
        camera->SetParallelScale(0.5f*static_cast<float>(yd));
        camera->SetFocalPoint(xc,yc,0.0);
        camera->SetPosition(xc,yc,+d);

        m_imageView->GetRenderer()->SetActiveCamera(camera);
        //

        m_imageView->SetupInteractor(interactor);
        m_imageView->Render();
        interactor->Disable();
        ui.qvtkWidget->update();

        ui.qvtkWidget->adjustSize();
        
        scaleFactor = 1;
        
        ui.actionPrint->setEnabled(true);
        ui.actionFitToWindow->setEnabled(true);
        ui.spinBoxWC->setEnabled(true);
        ui.spinBoxWW->setEnabled(true);
        ui.windowCenter->setEnabled(true);
        ui.windowWidth->setEnabled(true);
        ui.pushButtonReset->setEnabled(true);
        updateActions();

        fitToWindow();

        double scale = (double)(ui.scrollArea->size().height()/(double)m_sWidth);
        //std::cout<<scaleFactor<<std::endl;
        scaleImage(scale);
        std::cout<<(double)ui.scrollArea->size().height()<<" "<<m_sWidth<<" "<<scaleFactor<<std::endl;
        updateDisplay();
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
    ui.qvtkWidget->adjustSize();
    scaleFactor = 1.0;
    scaleImage(scaleFactor);
}


void ImageViewer::fitToWindow()
{
    bool fitToWindow = ui.actionFitToWindow->isChecked();
    ui.scrollArea->setWidgetResizable(fitToWindow);
    if(!fitToWindow)
        normalSize();
    else
    {
        scaleImage(scaleFactor);
        updateDisplay();
    }
    updateActions();
}


void ImageViewer::zoomIn()
{
    scaleImage(1.25);
    updateDisplay();
}


void ImageViewer::zoomOut()
{
    scaleImage(0.75);
    updateDisplay();
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
    ui.qvtkWidget->update();
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
    connect(ui.scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateDisplay()));
    connect(ui.scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateDisplay()));
}


void ImageViewer::scaleImage(double factor)
{
    
    scaleFactor*=factor;
    //Q_ASSERT(ui.imageLabel->pixmap());
    ui.qvtkWidget->GetRenderWindow()->SetSize(m_sWidth*scaleFactor, m_sHeight*scaleFactor);
    //std::cout<<m_sWidth<<std::endl;
    m_imageView->Render();
    ui.qvtkWidget->update();

    adjustScrollBar(ui.scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui.scrollArea->verticalScrollBar(), factor);

    //ui.actionZoom_in_25->setEnabled(scaleFactor<3.0);
    //ui.actionZoom_out_25->setEnabled(scaleFactor>0.333);
    
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
    /*
    if(m_sWidth!=0)
    {
        double scale = (double)(ui.scrollArea->size().height()/(double)(m_sWidth*scaleFactor));
        std::cout<<scaleFactor<<std::endl;
        scaleImage(scale);
        //std::cout<<(double)ui.scrollArea->size().height()<<" "<<m_sWidth<<" "<<scaleFactor<<std::endl;
    }
    */
    updateDisplay();    
}


void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    //std::cout<<"Mouse moved."<<std::endl;
}


void ImageViewer::wheelEvent(QWheelEvent *event)
{
    //std::cout<<"Update"<<std::endl;
    //updateDisplay();
}


bool ImageViewer::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui.qvtkWidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            const QMouseEvent* const mouseEvent = static_cast<const QMouseEvent*>(event);
            if(mouseEvent->button()==Qt::MiddleButton)
            {
                m_mouseMiddleStartPos[0]=mouseEvent->x();
                m_mouseMiddleStartPos[1]=mouseEvent->y();
                m_mouseMiddleButtonDown = true;
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            const QMouseEvent* const mouseEvent = static_cast<const QMouseEvent*>(event);
            if(mouseEvent->button()==Qt::MiddleButton)
            {
                m_mouseMiddleButtonDown = false;
            }
        }
        else if(event->type() == QEvent::MouseMove)
        {
            const QMouseEvent* const mouseEvent = static_cast<const QMouseEvent*>(event);
            if(m_mouseMiddleButtonDown)
            {
                m_mouseMiddleCurrentPos[0] = mouseEvent->pos().x();
                m_mouseMiddleCurrentPos[1] = mouseEvent->pos().y();
                if(ui.spinBoxWC->isEnabled())
                {
                    int temp = ui.spinBoxWC->value() + m_mouseMiddleCurrentPos[0]-m_mouseMiddleStartPos[0];
                    if(temp<ui.spinBoxWC->minimum())
                        temp = ui.spinBoxWC->minimum();
                    else if(temp>ui.spinBoxWC->maximum())
                        temp = ui.spinBoxWC->maximum();
                    ui.spinBoxWC->setValue(temp);
                    m_mouseMiddleStartPos[0]=mouseEvent->x();
                }
                if(ui.spinBoxWW->isEnabled())
                {
                    int temp = ui.spinBoxWW->value() + m_mouseMiddleCurrentPos[1]-m_mouseMiddleStartPos[1];
                    if(temp<ui.spinBoxWW->minimum())
                        temp = ui.spinBoxWW->minimum();
                    else if(temp>ui.spinBoxWW->maximum())
                        temp = ui.spinBoxWW->maximum();
                    ui.spinBoxWW->setValue(temp);
                    m_mouseMiddleStartPos[1]=mouseEvent->y();
                }
            }
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            const QMouseEvent* const mouseEvent = static_cast<const QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::MiddleButton)
            {
                ui.spinBoxWC->setValue(m_sWC);
                ui.spinBoxWW->setValue(m_sWW);
            }
        }
    }

    if(obj == ui.scrollArea || obj == ui.scrollArea->viewport())
    {
        updateDisplay();
    }

    return QMainWindow::eventFilter(obj, event);
}
