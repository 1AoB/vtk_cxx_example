如何自定义交互器的实现方式?
vtkNew<vtkRenderWindowInteractor> interactor;


在VTK中，默认的交互器模式是旋转模式（Rotate Mode）。
1.旋转模式允许用户通过鼠标左键按下并拖动来旋转视图中的对象。按住鼠标右键并拖动可以平移视图(向上拖动是变大,
向下拖动是变小)，滚动鼠标滚轮可以缩放视图。这是VTK中最基本的交互器模式，适用于大多数可视化场景。

但是，和meshlab相比，原装的交互模式不是很合理：比如，你按下了左键，他就不停旋转，
而meshlab是选择到左键指定的位置，然后停下。
（包括右键，中键都是一样，原配交互器只能不停的我们按下的操作，而我们只是想执行一次就好，就像meshlab一样）

其实想要实现和meshlab一样的交互效果并不难：
我们只需要借助vtkInteractorStyleTrackballCamera类：
```cpp
vtkNew<vtkInteractorStyleTrackballCamera> style;
interactor->SetInteractorStyle(style);
```
上面两行代码即可搞定！！！
