#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H


#include <QWidget>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QMouseEvent>

#include "TextOverlayWidget.h"
#include "ImageData.h"


class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent);
    virtual ~DisplayWidget();

    void SetUpperLeftAnnotation(std::string text);
    void SetUpperRightAnnotation(std::string text);
    void SetLowerLeftAnnotation(std::string text);
    void SetLowerRightAnnotation(std::string text);

    int GetActiveSliceIndex();
    void SetActiveSliceIndex(int index);

    void SetImageData(std::shared_ptr<ImageData> imageData);
    std::shared_ptr<ImageData> GetImageData();

public slots:
    void Animate();

private:
    void InitializeAnnotation();
    void ShowAnnotation();
    void UpdateAnnotation();
    void Paint(QPainter *painter, const QRect& rect);

signals:
    void MiddleButtonMove(float x, float y);
    void RightButtonMove(float y);
    void MiddleButtonDoubleClick();
    void WheelMovement(int x, int y);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

protected:
    float m_MouseMiddleStartPos[2];
    float m_MouseMiddleCurrentPos[2];
    float m_MouseRightStartPos[2];
    float m_MouseRightCurrentPos[2];
    
    bool m_bMiddleButtonDown;
    bool m_bRightButtonDown;
    
private:
    int m_iElapsed;
    int m_iActiveSlice;
    bool m_bShowAnnotation;
    TextOverlayWidget* m_pUpperLeft;
    TextOverlayWidget* m_pUpperRight;
    TextOverlayWidget* m_pLowerLeft;
    TextOverlayWidget* m_pLowerRight;
    std::shared_ptr<ImageData> m_pImageData;

};


#endif // DISPLAYWIDGET_H
