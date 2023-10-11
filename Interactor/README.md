# 如何自定义交互器的实现方式?
vtkNew<vtkRenderWindowInteractor> interactor;


# 在VTK中，默认的交互器模式是旋转模式（Rotate Mode）。
1.旋转模式允许用户通过鼠标左键按下并拖动来旋转视图中的对象。按住鼠标右键并拖动可以平移视图(向上拖动是变大,
向下拖动是变小)，滚动鼠标滚轮可以缩放视图。这是VTK中最基本的交互器模式，适用于大多数可视化场景。

但是，和meshlab相比，原装的交互模式不是很合理：比如，你按下了左键，他就不停旋转，
而meshlab是选择到左键指定的位置，然后停下。
（包括右键，中键都是一样，原配交互器只能不停的我们按下的操作，而我们只是想执行一次就好，就像meshlab一样）

# 其实想要实现和meshlab一样的交互效果并不难：
我们只需要借助vtkInteractorStyleTrackballCamera类：
```cpp
vtkNew<vtkInteractorStyleTrackballCamera> style;
interactor->SetInteractorStyle(style);
```
上面两行代码即可搞定！！！

# 关于vtkInteractorStyleTrackballCamera类
可以参考官方文档：
https://vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html

vtkInteractorStyleTrackballCamera 翻译一下：大概是 ： 摄像机的交互式操作
vtkInteractorStyleTrackballCamera允许用户交互操作（旋转、平移等）相机，场景的视角。在轨迹球交互中，鼠标运动的幅度与与特定鼠标绑定关联的相机运动成比例。例如，**小的左键运动**会导致相机围绕其焦点旋转的**微小变化**。
对于3键鼠标：左键用于旋转，右键用于缩放，中键用于平移，Ctrl +左键用于旋转，Shift +右键用于环境旋转。(**官方文档说：shift + right button for environment rotation，暂时我还不知道什么是“环境旋转”？如何触发环境旋转？反正我按下shift+右键没有任何效果**)
(With更少的鼠标按钮，Ctrl + Shift +左键用于缩放，Shift +左键用于平移。）
