# k210人脸识别

![](https://img.shields.io/badge/star-welcome!-red)
![](https://img.shields.io/badge/%20welcome_to_pull_your_requests!-8A2BE2)

[![Top Langs](https://github-readme-stats.vercel.app/api/top-langs/?username=MildRainJayden&hide=jupyter notebook)](https://github.com/anuraghazra/github-readme-stats)

## 引言

随着深度学习技术的发展，人脸识别已经成为了一个热门的领域。人脸识别技术已广泛应用于安全、金融、零售等领域。在传统的人脸识别方法中，需要使用大量的计算资源和时间，且在实时性方面存在较大的限制。而使用深度学习算法进行人脸识别，则可以提高识别精度和响应速度，通过裁剪，优化算法，使得人脸识别在嵌入式系统中得以落地实现。

首先，我们准备了一个包含不同人脸图像的数据集，并使用该数据集训练了YOLOv2模型。然后，我们将模型部署到K210芯片中。最后，我们对实现的结果进行了评估和总结，证明了使用K210搭载YOLOv2进行人脸识别是一种有效的解决方案。

## 准备数据集以及模型训练

本项目使用的是MTFL公开数据集进行训练（如图1），MTFL数据集是一个用于人脸关键点检测和人脸属性识别的数据集，由Multi-Task Facial Landmark (MTFL) Challenge组织提供，其中包含了来自3755个人的120345个人脸图像。MTFL数据集包括多个任务，包括：人脸关键点检测：目标是对人脸图像中的68个关键点进行精确定位，包括眼睛、鼻子、嘴巴等部位；年龄估计：目标是预测人脸图像的年龄；性别识别：目标是确定人脸图像中的性别；种族识别：目标是识别人脸图像中的种族。本项目仅使用人脸关键点作为训练的标签。

![图1](k210%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%208e4ca7f57b714c63b45645d53cd6952c/Untitled.png)

图1

在数据集的准备过程中，我们需要进行一些预处理，模型输入层的大小通常应该和K210的神经网络加速器的输入大小相匹配，以便于实现高效的神经网络计算和推理，在嵌入式设备和物联网应用中，由于计算资源受到限制，使用较小的图像输入大小是常见的做法，本模型在输入层前将图像进行裁剪处理至240×240×3的图像尺寸RGB图像，经测试，能够提高运行的性能等指标。

在模型的训练中，本项目采用了YOLOv2算法，YOLOv2是一个基于卷积神经网络的目标检测算法，其输出层包含多个大小不同的特征图。每个特征图代表着输入图像中不同尺度和不同位置的目标检测结果。在最后一层输出中，YOLOv2通过一个1×1的卷积层将所有特征图的通道数降低到256，然后将这些特征图连接起来形成一个1×1×256的张量，作为模型的最终输出。在人脸识别任务中，这个256维的特征向量可以用于人脸特征的比较和匹配，通常使用欧氏距离等指标进行比较，以判断两张人脸是否属于同一个人。通过不断优化网络结构和训练方法，可以获得更好的人脸识别性能，同时保持较快的推理速度和较低的计算资源消耗。

本项目采用了NNCase框架，NNCase是一种用于深度神经网络推理的轻量级框架，可以将深度神经网络模型转换为在边缘设备上执行的高效代码，如在嵌入式设备上进行推理。NNCase支持多种深度学习框架的模型转换，包括TensorFlow、ONNX和PyTorch等，能够将它们转换为K210芯片能够理解和执行的指令集。NNCase的主要优点是：

- 轻量级：NNCase本身的代码很小，可以在资源受限的设备上运行，同时转换后的模型也具有较小的体积和内存占用；
- 多框架支持：NNCase支持多种深度学习框架的模型转换，具有很强的兼容性和灵活性；
- 高效性：NNCase使用了一系列的优化和转换算法，可以在边缘设备上实现高效的深度神经网络推理；
- 易用性：NNCase具有简单易用的命令行接口和图形化界面，使得模型转换和推理变得容易和快速。

## 模型部署和项目开发

在模型训练完成后，我们将模型部署到K210芯片中。K210芯片具有较强的计算能力和低功耗的特点，适合用于嵌入式深度学习应用。为了将YOLOv2模型部署到K210芯片中，我们使用了K210提供的开发环境和工具链。具体来说，我们使用了K210提供的SDK和工具包MaixPy，集成OpenMV的开源代码库，将YOLOv2模型编译成K210芯片可以运行的固件（如图2）。

![图2](k210%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%208e4ca7f57b714c63b45645d53cd6952c/Untitled%201.png)

图2

在对开源代码进行修改、剪裁、适配、编译后，烧录到K210开发板，即可实现对人脸的识别及显示基本信息，如图3识别到了人脸，并显示其学号与姓名（人脸信息已提前录入），图4为本人脸识别门禁部分项目使用的模块。

![图3](k210%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%208e4ca7f57b714c63b45645d53cd6952c/Untitled%202.png)

图3

![图4](k210%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%208e4ca7f57b714c63b45645d53cd6952c/image4.jpeg)

图4

## 评估和总结

为了评估我们的人脸识别系统的性能，我们进行了一系列的实验，对于人脸识别功能有较好的准确度实现。具体来说，我们的系统在人脸检测和识别的准确率方面可以达到95%以上，而且响应速度非常快，可以实现实时的人脸检测和识别，此外，我们的系统也具有较低的功耗，适合用于嵌入式应用，可基本满足智能识别门禁的需求。
