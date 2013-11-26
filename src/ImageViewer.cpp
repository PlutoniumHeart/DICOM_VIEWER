#include "ImageViewer.h"


ImageViewer::ImageViewer(QMainWindow *parent)
    : QMainWindow(parent)
    , image_array(NULL)
{
    ui.setupUi(this);

    std::cout<<"width: "<<this->width()<<std::endl;
    ui.imageLabel->setBackgroundRole(QPalette::Base);
    //ui.imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui.imageLabel->setMinimumSize(64, 64);
    ui.imageLabel->setScaledContents(true);

    ui.scrollArea->setBackgroundRole(QPalette::Dark);
    ui.scrollArea->setWidget(ui.imageLabel);

    //setCentralWidget(ui.scrollArea);
    
    createActions();

    setWindowTitle(tr("Image Viewer"));
}


ImageViewer::~ImageViewer()
{
    if(image_array!=NULL)
    {
        delete [] image_array;
        image_array = NULL;
    }
}


void ImageViewer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        ShortImageType::Pointer imageObj = ShortImageType::New();
        ImageIO::ReadDICOMImage(fileName.toUtf8().constData(), imageObj);
        int w = imageObj->GetLargestPossibleRegion().GetSize().GetElement(0);
        int h = imageObj->GetLargestPossibleRegion().GetSize().GetElement(1);
        ImageIO::PixelToArray(imageObj, &image_array);
        QImage image(w, h, QImage::Format_RGB32);
        for(int i=0;i<w;i++)
        {
            for(int j=0;j<h;j++)
            {
                image.setPixel(i, j, qRgb(image_array[i+w*j], image_array[i+w*j], image_array[i+w*j]));
            }
        }
        
        if(image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui.imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;
        ui.actionPrint->setEnabled(true);
        ui.actionFitToWindow->setEnabled(true);
        updateActions();

        if(!ui.actionFitToWindow->isChecked())
        {
            ui.imageLabel->adjustSize();
        }
    }
}


void ImageViewer::print()
{
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
}


void ImageViewer::normalSize()
{
    ui.imageLabel->adjustSize();
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
}


void ImageViewer::zoomOut()
{
    scaleImage(0.75);
}


void ImageViewer::createActions()
{
    ui.actionOpen_DICOM->setShortcut(tr("Ctrl+O"));
    connect(ui.actionOpen_DICOM, SIGNAL(triggered()), this, SLOT(open()));

    ui.actionPrint->setShortcut(tr("Ctrl+P"));
    ui.actionPrint->setEnabled(false);
    connect(ui.actionPrint, SIGNAL(triggered()), this, SLOT(print()));

    ui.actionExit->setShortcut(tr("Ctrl+Q"));
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    ui.actionFitToWindow->setEnabled(false);
    ui.actionFitToWindow->setShortcut(tr("Ctrl+F"));
    connect(ui.actionFitToWindow, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    ui.actionNormalSize->setShortcut(tr("Ctrl+S"));
    ui.actionNormalSize->setEnabled(false);
    connect(ui.actionNormalSize, SIGNAL(triggered()), this, SLOT(normalSize()));

    ui.actionZoom_in_25->setShortcut(tr("Ctrl++"));
    ui.actionZoom_in_25->setEnabled(false);
    connect(ui.actionZoom_in_25, SIGNAL(triggered()), this, SLOT(zoomIn()));

    ui.actionZoom_out_25->setShortcut(tr("Ctrl+-"));
    ui.actionZoom_out_25->setEnabled(false);
    connect(ui.actionZoom_out_25, SIGNAL(triggered()), this, SLOT(zoomOut()));
}


void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(ui.imageLabel->pixmap());
    scaleFactor*=factor;
    ui.imageLabel->resize(scaleFactor*ui.imageLabel->pixmap()->size());

    adjustScrollBar(ui.scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui.scrollArea->verticalScrollBar(), factor);

    ui.actionZoom_in_25->setEnabled(scaleFactor<3.0);
    ui.actionZoom_out_25->setEnabled(scaleFactor>0.333);
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
}
