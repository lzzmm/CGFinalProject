#include "myglwidget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }*/
    MyGLWidget w;
	w.setWindowTitle("Final Project!");
    w.show();
    return a.exec();
}