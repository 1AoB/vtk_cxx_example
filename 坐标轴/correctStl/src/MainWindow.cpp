#include <MainWindow.h>

#include "ui_MainWindow.h"

#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

#include <vtkRenderer.h>




#include <iostream>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkInteractorStyleTrackballCamera.h>
class CVector3d {
public:
    float x;
    float y;
    float z;

    const char* getInfo()
    {
        QString information;
        information = "x:" + QString::number(x)+",y:"+QString::number(y)+",z:"+QString::number(z);

        QByteArray byteArray = information.toUtf8(); // 将 QString 转换为 UTF-8 编码的 QByteArray

        return byteArray.constData();
    }
    
};


 



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
    mRenderer(vtkSmartPointer<vtkRenderer> ::New()),
    mInteractor(vtkSmartPointer<QVTKInteractor> ::New()),
    mInteractorStyle(vtkSmartPointer<vtkInteractorStyle> ::New())
{
    ui->setupUi(this);


    mRenderWindow->AddRenderer(mRenderer);
    mRenderWindow->SetInteractor(mInteractor);

    ui->openGLWidget->setRenderWindow(mRenderWindow);
    mInteractor->SetInteractorStyle(mInteractorStyle);
    mInteractor->Initialize();

    // Set the background color
    //mRenderer->SetBackground(1, 0, 0);

    //Set the UI connections
    QObject::connect(ui->drawSphere_button, &QPushButton::clicked,
        this, &MainWindow::onDrawSphereClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDrawSphereClick()
{
    // Create sphere
    //vtkSmartPointer<vtkSphereSource> sphereSource =
    //    vtkSmartPointer<vtkSphereSource>::New();
    //sphereSource->SetRadius(5);
    //sphereSource->Update();

    ////Create the actor where the sphere is rendered
    //vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    //    vtkSmartPointer<vtkPolyDataMapper>::New();
    //sphereMapper->SetInputData(sphereSource->GetOutput());

    //vtkSmartPointer<vtkActor> sphere = vtkSmartPointer<vtkActor>::New();
    //sphere->SetMapper(sphereMapper);

    ////Add the sphere actor to the OpenGL
    //mRenderer->AddViewProp(sphere);
    //mRenderer->ResetCamera();
    //mRenderWindow->Render();
    ///////////////////

    const char* stlFilePath = "./lower.stl";
    // 创建STL文件读取器
    vtkSmartPointer<vtkSTLReader> reader =
        vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(stlFilePath);
    reader->Update();

    // 获取STL数据
    vtkSmartPointer<vtkPolyData> inputPolyData = reader->GetOutput();

    // 创建Mapper和Actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(inputPolyData);

    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建渲染器和窗口
    /*vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();*/
    mRenderer->AddActor(actor);

    /*vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();*/
    mRenderWindow->AddRenderer(mRenderer);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(mRenderWindow);

    //调整相机位置,调整显示范围
    //mRenderer->ResetCamera();


    //鼠标移动方式
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor->SetInteractorStyle(style);

    //设置坐标轴
    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    
    //创建方向标记小部件,将坐标轴添加到渲染器
    widget =
        vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    widget->SetOrientationMarker(axes);
    widget->SetInteractor(interactor);
    widget->SetViewport(0.0, 0.0, 0.2, 0.2);
    widget->SetEnabled(true);
    widget->InteractiveOn();
    
    
    // 启动交互式窗口
    /*interactor->Initialize();
    interactor->Start();*/

    //////Add the sphere actor to the OpenGL
    //mRenderer->AddViewProp(sphere);
    mRenderer->ResetCamera();

    mRenderWindow->Render();
}