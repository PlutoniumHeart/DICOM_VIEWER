#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H


#include <QMainWindow>
#include <QtWidgets>
#include <QImage>
#include <QPrinter>
#include <QPrintDialog>
#include "ImageIO.h"
#include "ImageFilter.h"
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

protected:
    void resizeEvent(QResizeEvent *event);

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

private:
    void createActions();
    void updateActions();

    double scaleFactor;
    QPrinter printer;
    QAction *printAct;

    ShortImageType::Pointer m_imageObj;
    DICOMIOType::Pointer m_dicomIO;

    short m_sWidth;
    short m_sHeight;
    short m_sWC;
    short m_sWW;
    
    Ui::ImageViewer ui;
};


#endif // IMAGEVIEWER_H
