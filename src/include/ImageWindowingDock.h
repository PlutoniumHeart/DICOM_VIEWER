#ifndef IMAGEWINDOWDOCK_H
#define IMAGEWINDOWDOCK_H


#include <iostream>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>


class ImageWindowDock : public QDockWidget
{
    Q_OBJECT
    
public:
    ImageWindowDock();
    ~ImageWindowDock();

    QSlider* GetSliderWC();
    QSlider* GetSliderWW();
    QSpinBox* GetSpinBoxWC();
    QSpinBox* GetSpinBoxWW();
    QPushButton* GetResetButton();

    void EnableWidgets();

public slots:
    void updateWindowLevel(int x, int y);
    void setFloatingProperty(bool floating);

private:
    QWidget *m_DockContents;
    QWidget *m_layoutWidget;
    
    QGridLayout *m_layout;
    QLabel *m_labelWC;
    QLabel *m_labelWW;
    QSlider *m_sliderWC;
    QSlider *m_sliderWW;
    QSpinBox *m_spinBoxWC;
    QSpinBox *m_spinBoxWW;
    QPushButton *m_pushButtonReset;
};


#endif // IMAGEWINDOWDOCK_H
