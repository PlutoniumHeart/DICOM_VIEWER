#ifndef FILETOOLBAR_H
#define FILETOOLBAR_H


#include <QToolBar>
#include <QIcon>


class FileToolBar : public QToolBar
{
    Q_OBJECT

public:
    FileToolBar();
    ~FileToolBar();

    QAction* GetOpenDICOMAction();

private:
    QAction *openDICOM;
};


#endif // FILETOOLBAR_H
