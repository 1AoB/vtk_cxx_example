当使用VTK（Visualization Toolkit）进行可视化时，vtkActor是一个非常重要的类。它代表了在3D场景中的一个可视化对象或实体，并决定了该对象在渲染过程中的外观和行为。

vtkActor包含以下几个关键方面：

1. 几何数据（Geometry Data）：
vtkActor通过与几何数据相关联来定义其形状和结构。可以使用各种VTK提供的几何数据类型，如vtkPolyData、vtkStructuredGrid等，作为vtkActor的输入数据。

**也就是说,除了Polydata,其他的一些几何数据可以是可以作为actor的输入参数!!!**

2. 显示属性（Display Properties）：
vtkActor允许您设置对象的外观属性，例如颜色、透明度、表面属性等。这些显示属性可以影响对象在渲染过程中的呈现效果。

3. 材质属性（Material Properties）：
vtkActor还支持材质属性的设置，如反射率、镜面高光、光泽等。这些属性可以影响对象在光照条件下的渲染效果。

**其实2和3可以归为一类,都是改变一些直观上的属性!!!**

4. 坐标变换（Coordinate Transformation）：
通过vtkActor的坐标变换，您可以应用平移、旋转、缩放等操作来改变对象在3D场景中的位置、姿态和尺寸。
**也就是说,Polydata和actor都可以进行坐标变换!!!**

6. 渲染阶段（Rendering Stages）：
在渲染过程中，vtkActor通常参与多个阶段，例如几何数据的剪裁、光照计算、阴影投射等。vtkActor会根据设置的属性和上下文信息，通过渲染管线（Rendering Pipeline）参与这些渲染阶段。

7. 通过创建vtkActor并将其与适当的几何数据相关联，您可以在VTK中实现各种可视化效果。然后，将vtkActor添加到vtkRenderer中，最终在屏幕上渲染出对象的可视化表示。
