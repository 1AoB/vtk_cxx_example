```cpp
const char* stlFilePath = "./upper.stl";
// 创建STL文件读取器
vtkSmartPointer<vtkSTLReader> reader =
vtkSmartPointer<vtkSTLReader>::New();
reader->SetFileName(stlFilePath);
reader->Update();

// 获取STL数据
vtkSmartPointer<vtkPolyData> inputPolyData = reader->GetOutput();

// Compute the bounding box
double bounds[6];
inputPolyData->GetBounds(bounds);

// Bounds are in the form [xmin, xmax, ymin, ymax, zmin, zmax]
double xmin = bounds[0];
double xmax = bounds[1];
double ymin = bounds[2];
double ymax = bounds[3];
double zmin = bounds[4];
double zmax = bounds[5];

// Calculate the corner points
double corners[8][3] = {
    {xmin, ymin, zmin},
    {xmax, ymin, zmin},
    {xmin, ymax, zmin},
    {xmax, ymax, zmin},
    {xmin, ymin, zmax},
    {xmax, ymin, zmax},
    {xmin, ymax, zmax},
    {xmax, ymax, zmax}
};
cout << "xmin:" << xmin << ",max:" << xmax <<
    ",ymin:" << ymin << ",ymax:" << ymax <<
    ",zmin:" << zmin << ",zmax" << zmax << endl;
//y轴长度
double Ylen = ymax - ymin;
    //z轴长度
double Zlen = zmax - zmin;
if (Ylen > Zlen) {
    //异常;
    cout << "此病例坐标轴异常" << endl;
}

// 创建Mapper和Actor
vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputData(inputPolyData);

vtkSmartPointer<vtkActor> actor =
vtkSmartPointer<vtkActor>::New();
actor->SetMapper(mapper);

// 创建渲染器和窗口
vtkSmartPointer<vtkRenderer> renderer =
vtkSmartPointer<vtkRenderer>::New();
renderer->AddActor(actor);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();
renderWindow->AddRenderer(renderer);

vtkSmartPointer<vtkRenderWindowInteractor> interactor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
interactor->SetRenderWindow(renderWindow);

//调整相机位置,调整显示范围
renderer->ResetCamera();


//鼠标移动方式
vtkNew<vtkInteractorStyleTrackballCamera> style;
interactor->SetInteractorStyle(style);

//设置坐标轴
vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
//创建方向标记小部件,将坐标轴添加到渲染器
vtkSmartPointer<vtkOrientationMarkerWidget> widget =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
widget->SetOrientationMarker(axes);
widget->SetInteractor(interactor);
widget->SetViewport(0.0, 0.0, 0.2, 0.2);
widget->SetEnabled(true);
widget->InteractiveOn();

// 启动交互式窗口
interactor->Initialize();
interactor->Start();
```
