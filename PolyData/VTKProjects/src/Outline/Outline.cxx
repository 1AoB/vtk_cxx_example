#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSTLWriter.h>

int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;// 创建vtkNameColors对象，用于存储颜色信息

  // 创建一个圆锥体
  vtkNew<vtkConeSource> source;
  source->SetCenter(0.0, 0.0, 0.0);//设置圆锥体中心坐标
  source->SetResolution(100);//设置圆锥体的分辨率
  source->Update();//更新圆锥体的几何数据

  vtkNew<vtkPolyDataMapper> mapper;//创建vtkPolyDataMapper对象，用于将几何数据映射到图像数据
  mapper->SetInputConnection(source->GetOutputPort());//设置输入连接为圆锥体的输出端口

  vtkNew<vtkActor> actor;//创建vtkActor对象，用于表示可视化场景中的一个可渲染对象
  actor->SetMapper(mapper);//设置渲染对象的引射器为上面创建的mapper对象
  actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());//设置渲染对象的颜色

  // 创建一个轮廓
  vtkNew<vtkOutlineFilter> outline;
  outline->SetInputConnection(source->GetOutputPort());

  vtkNew<vtkPolyDataMapper> outlineMapper;
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  vtkNew<vtkActor> outlineActor;
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());

  // 设置窗口
  vtkNew<vtkRenderer> renderer;//创建vtkRenderer对象，用于渲染可视化场景中的3D图像数据
  vtkNew<vtkRenderWindow> renderWindow;//创建vtkRenderWindow对象，用于显示渲染的图形数据
  renderWindow->AddRenderer(renderer);//将渲染器添加到渲染窗口中
  renderWindow->SetWindowName("Outline");//设置窗口的名称

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;//创建vtkRenderWindowInteractor对象，用于处理交互操作
  renderWindowInteractor->SetRenderWindow(renderWindow);//设置交互器所属的渲染窗口

  // 将渲染对象添加到场景中
  renderer->AddActor(actor);//将圆锥体渲染对象添加到渲染器中
  renderer->AddActor(outlineActor);// 将轮廓渲染对象添加到渲染器中
  renderer->SetBackground(colors->GetColor3d("MidnightBlue").GetData());// 设置渲染器的背景颜色

  // 渲染和交互
  renderWindow->Render();// 渲染窗口显示图形数据
  vtkNew<vtkInteractorStyleTrackballCamera> style;// 创建vtkInteractorStyleTrackballCamera对象，设置交互器的样式
  renderWindowInteractor->SetInteractorStyle(style);// 设置交互器的样式为TrackballCamera样式
  renderWindowInteractor->Start();// 开始交互

  vtkNew<vtkSTLWriter> stlWriter;
  stlWriter->SetFileName("output.stl"); // 设置要保存的文件名
  stlWriter->SetInputConnection(source->GetOutputPort()); // 设置输入连接为圆锥体的输出端口
  stlWriter->Write(); // 执行写入操作
  
  return EXIT_SUCCESS;
}