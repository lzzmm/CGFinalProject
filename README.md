# CGFinalProject 

(或许可以起一些酷炫的中文名和英文名)

Final Project of DCS304 - Computer Graphics 2021 Fall



本项目基于 `OpenGL`，使用 `Qt5` 和 `msvc2019_64 (msvc2017_64)`

~~首先更改 `.pro` 文件中的 `INCLUDEPATH`~~

需要的一些外部依赖头文件请放到 `include` 文件夹中；需要的一些库请放到 `lib` 文件夹中，并在 `.pro` 文件中的 `LIBS` 添加相对路径；项目添加的头文件和源文件，请在 `.pro` 中的 `HEADERS` 和 `SOURCES` 添加相对路径；项目添加的资源文件（如 shader ）请放在 `resource` 中，有需要的话可以更新 `resource.qrc`。


在文件夹中打开终端，输入命令

```powershell
qmake -tp vc
```

生成 `.vcxproj` 文件。使用 `msvc2017` 工具生成的项目文件在 Visual studio 2019 中打开可能需要升级工具集。



若生成 Debug 程序时出现找不到 `Qt5OpenGL.lib` 的错误，可以在项目的库目录添加上 Qt 库路径。如 `C:\Qt\5.15.2\msvc2019_64\lib`.



