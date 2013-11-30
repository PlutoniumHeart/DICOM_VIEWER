#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H


#include <QMainWindow>
#include <QtWidgets>
#include <QImage>
#include <QPrinter>
#include <QPrintDialog>
#include <itkImageToVTKImageFilter.h>
#include "ImageIO.h"
#include "ImageFilter.h"
#include "VTKRenderCommon.h"
#include "MyMouseInteractorStyle.h"
#include "ui_ImageViewer.h"


QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE


class ImageViewer : public QMainWindow
{
    Q_OBJECT
public:
    ImageViewer(QMainWindow *parent = 0);
    ~ImageViewer();

    bool eventFilter(QObject *obj, QEvent* event);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void openImage();
    void print();
    void fitToWindow();
    void normalSize();
    void zoomIn();
    void zoomOut();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);
    void windowReset();
    void updateDisplay();
    //void updateTextOverlay();

private:
    void createActions();
    void updateActions();

    double scaleFactor;
    QPrinter printer;
    QAction *printAct;
    QLabel *labelUpperLeft;
    QLabel *labelUpperRight;

    ShortImageType::Pointer m_imageObj;
    DICOMIOType::Pointer m_dicomIO;

    short m_sWidth;
    short m_sHeight;
    short m_sWC;
    short m_sWW;
    short m_mouseMiddleStartPos[2];
    short m_mouseMiddleCurrentPos[2];
    std::string m_patientName;
    std::string m_sex;
    std::string m_birthday;
    bool m_mouseLeftButtonDown;
    bool m_mouseMiddleButtonDown;

    vtkSmartPointer<vtkResliceImageViewer> m_imageView;
    vtkSmartPointer<vtkWindowLevelLookupTable> windowLevelLookupTable;
    vtkSmartPointer<vtkImageData> image;
    
    Ui::ImageViewer ui;
};


#endif // IMAGEVIEWER_H
