#include "MyMouseInteractorStyle.h"


vtkStandardNewMacro(MouseInteractorStyle4);


void MouseInteractorStyle4::OnLeftButtonDown()
{
    std::cout << "Pressed left mouse button." << std::endl;
    // Forward events
    vtkInteractorStyleImage::OnLeftButtonDown();
}


void MouseInteractorStyle4::OnLeftButtonUp()
{
    std::cout<<"Released left mouse button. "<<std::endl;
    vtkInteractorStyleImage::OnLeftButtonUp();
}


void MouseInteractorStyle4::OnMouseMove()
{
    vtkInteractorStyleImage::OnMouseMove();
}


void MouseInteractorStyle4::OnMiddleButtonDown() 
{
    std::cout << "Pressed middle mouse button." << std::endl;
    //vtkInteractorStyleImage::OnMiddleButtonDown();
}


void MouseInteractorStyle4::OnRightButtonDown() 
{
    std::cout << "Pressed right mouse button." << std::endl;
    // Forward events
    vtkInteractorStyleImage::OnRightButtonDown();
}
