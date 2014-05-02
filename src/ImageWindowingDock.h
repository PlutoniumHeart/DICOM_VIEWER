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
    void UpdateWindowLevel(int x, int y);
    void SetFloatingProperty(bool floating);

private:
    QWidget *m_DockContents;
    QWidget *m_LayoutWidget;
    
    QGridLayout *m_Layout;
    QLabel *m_LabelWC;
    QLabel *m_LabelWW;
    QSlider *m_SliderWC;
    QSlider *m_SliderWW;
    QSpinBox *m_SpinBoxWC;
    QSpinBox *m_SpinBoxWW;
    QPushButton *m_PushButtonReset;
};


#endif // IMAGEWINDOWDOCK_H
