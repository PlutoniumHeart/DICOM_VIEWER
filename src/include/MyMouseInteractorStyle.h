#ifndef MYMOUSEINTERACTORSTYLE_H
#define MYMOUSEINTERACTORSTYLE_H


#include "VTKRenderCommon.h"
#include <vtkCommand.h>
#include <vtkCallbackCommand.h>


class MouseInteractorStyle4 : public vtkInteractorStyleImage
{
  public:
    static MouseInteractorStyle4* New();
    vtkTypeMacro(MouseInteractorStyle4, vtkInteractorStyleTrackballCamera);
 
    virtual void OnLeftButtonDown();
    virtual void OnLeftButtonUp();
    virtual void OnMouseMove();
 
    virtual void OnMiddleButtonDown();
    
    virtual void OnRightButtonDown();
};


#endif // MYMOUSEINTERACTORSTYLE_H
