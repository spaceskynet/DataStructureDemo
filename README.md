<img src="assets/icon.webp" align="right" width="120px">

# 🧱Data Structure Demo

利用自实现的内存分配与回收操作，完成的七种数据结构的演示程序。

本项目是北理工数院的数据结构大作业，~~比预计的要求多了亿点细节~~，相关的细节可查看[设计文档](./assets/设计文档.md).

## 使用说明

> 注：建议先阅读设计文档后再观看本说明.

首次进入界面如下:

![DSD_UI_comment](assets/DSD_UI_comment.webp)

左侧部分为分区相关信息，单元大小可点击`Label`修改，内存的分配算法提供常见的三种内存分配算法（首次适应、最佳适应、最差适应）进行选择。分区空闲情况按照块的空闲情况采用不同颜色着色标志（空闲为绿色，已使用的块按照数据结构的不同使用不同的颜色），每项中间的文字代表这个空闲或非空闲块所包含的单元的标号范围（左闭右开），鼠标悬停在某项上可查看对应块的使用情况.

右侧部分是数据结构的操作区和输出信息区，数据结构在建立、使用、释放过程中的输出信息都会输出到下方的文本编辑框中，上方的操作区可以对数据结构进行一系列的操作，包括新建对象（可选择是否加载默认数据）、默认的展示项、数据结构对应的基础操作、销毁对象等。其它操作中，提供了在分区空闲情况中定位指定单元所在块、清除分区所有数据、将分区数据写入文件的功能.

如果想要查看我们提供的各种数据结构的默认展示项，可以新建加载了默认数据的对象后点击默认展示即可.

---

🧱 **Data Structure Demo** ©2022 SpaceSkyNet. Released under the [MIT License](./LICENSE).

由~~不知道叫什么名字的、临时组成~~的大作业小组所完成~

[@BIT](https://www.bit.edu.cn) · [@BIT MATH](https://math.bit.edu.cn)
