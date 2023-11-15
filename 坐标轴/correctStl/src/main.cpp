#include<QtWidgets/QApplication>
#include<MainWindow.h>


#include <vtkSmartPointer.h>
#include <vtkSTLWriter.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();

    
	return app.exec();
}