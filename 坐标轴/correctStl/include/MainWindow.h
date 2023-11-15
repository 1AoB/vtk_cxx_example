#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>

#include <QDebug>

#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkProperty.h>

#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkSTLWriter.h>

#include <vtkPolygon.h>

#include <vtkSmartPointer.h>
#include <vtkWeakPointer.h>
#include <vtkLight.h>
#include <vtkTransform.h>
#include <vtkOrientationMarkerWidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
    vtkSmartPointer<vtkRenderer> mRenderer;
    vtkSmartPointer<QVTKInteractor> mInteractor;
    vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;

    vtkSmartPointer<vtkOrientationMarkerWidget> widget;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void onDrawSphereClick();
};

#endif // MAINWINDOW_H
