#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>

/*
* 这个示例程序演示了如何使用VTK创建并可视化多个球体，并对球体进行连接性分析。具体来说，程序创建了三个球体，
* 并将它们连接在一起。然后，使用连接性过滤器（vtkPolyDataConnectivityFilter）对连接后的球体进行分析，并为每个连接区域分配不同的颜色。
*/
int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;

  // Create some spheres.
  vtkNew<vtkSphereSource> sphereSource1;
  sphereSource1->Update();

  vtkNew<vtkSphereSource> sphereSource2;
  sphereSource2->SetCenter(5, 0, 0);
  sphereSource2->Update();

  vtkNew<vtkSphereSource> sphereSource3;
  sphereSource3->SetCenter(10, 0, 0);
  sphereSource3->Update();

  vtkNew<vtkAppendPolyData> appendFilter;
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource3->GetOutputPort());
  appendFilter->Update();

  vtkNew<vtkPolyDataConnectivityFilter> connectivityFilter;
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize.
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->SetScalarRange(connectivityFilter->GetOutput()
                             ->GetPointData()
                             ->GetArray("RegionId")
                             ->GetRange());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);
  renderWindow->SetWindowName("ColorDisconnectedRegions");

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  vtkNew<vtkInteractorStyleTrackballCamera> style;
  interactor->SetInteractorStyle(style);
  interactor->Start();

  return EXIT_SUCCESS;
}