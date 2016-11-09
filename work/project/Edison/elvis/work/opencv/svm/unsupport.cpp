#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include "time.h"  
  
using namespace cv;  
using namespace std;  
//程序说明：  
//一共两个样本集每个样本集有100个样本，其中90个是线性可分的，10个线型不可分  
//这200个样本数据储存在trainData内：trainData是一个200行2列的矩阵，其中第一列储存样本的X值，第二列储存的是样本的Y值  
//每一列的前90个元素是第一类的线性可分部分，后90个元素是第二类的线性可分部分，中间的20个元素是线性不可分部分  
//第一类样本的X值分布在整幅图像的[0,0.4]范围内，第二类样本的X值分布在整幅图像的[0.6,1]范围内，中间的[0.4,0.6]是线性不可分的部分；这三部分的Y值都在整幅图像的高度内自由分布  
  
  
//每个样本集的数量  
#define NTRAINING_SAMPLES 100  
  
//其中的线性部分  
#define FRAC_LINEAR_SEP   0.9f  
  
int main()  
{  
    //定义显示结果的图像  
    //图像的宽度、高度  
    const int WIDTH = 512,HEIGHT = 512;  
    Mat image = Mat::zeros(HEIGHT,WIDTH,CV_8UC3);  
  
    //************第一步：设定训练数据***********  
    //************1.设定数据结构****************  
    //承载训练数据的结构  
    Mat trainData(2*NTRAINING_SAMPLES,2,CV_32FC1);  
    //承载这些数据分类的结构  
    Mat labels(2*NTRAINING_SAMPLES,1,CV_32FC1);  
    //设定随机数种子  
    RNG rng(100);  
    //设定线性可分部分的数据量  
    int nLinearSamples = (int) (NTRAINING_SAMPLES*FRAC_LINEAR_SEP);  
  
    //**************2.设定第一类中的数据*********  
    //从整个数据集中取出前[0,89]行  
    //注：*Range的范围是[a,b)  
    Mat trainClass = trainData.rowRange(0,nLinearSamples);  
    //取出第一列  
    Mat c = trainClass.colRange(0,1);  
    //随机生成X的值：[0,0.4*WIDTH]  
    rng.fill(c,RNG::UNIFORM,Scalar(1),Scalar(0.4*WIDTH));  
    //取出第二列  
    c = trainClass.colRange(1,2);  
    //随机生成Y的值  
    rng.fill(c,RNG::UNIFORM,Scalar(1),Scalar(HEIGHT));  
  
    //**************2.设定第二类的数据*************  
    //从整个数据中取出[110,199]行  
    trainClass = trainData.rowRange(2*NTRAINING_SAMPLES-nLinearSamples,2*NTRAINING_SAMPLES);  
    //取出第一列  
    c = trainClass.colRange(0,1);  
    //随机生成X的值[0.6*WIDTH,WIDTH]  
    rng.fill(c,RNG::UNIFORM,Scalar(0.6*WIDTH),Scalar(WIDTH));  
    //取出第二列  
    c = trainClass.colRange(1,2);  
    //随机生成Y的值  
    rng.fill(c,RNG::UNIFORM,Scalar(1),Scalar(HEIGHT));  
  
    //***************3.设定线性不可分的数据***********  
    //取出[90,109]行  
    trainClass = trainData.rowRange(nLinearSamples,2*NTRAINING_SAMPLES-nLinearSamples);  
    //取出第一列  
    c = trainClass.colRange(0,1);  
    //随机生成X的值[0.4*WIDTH,0.6*WIDTH]  
    rng.fill(c,RNG::UNIFORM,Scalar(0.4*WIDTH),Scalar(0.6*WIDTH));  
    //取出第二列  
    c = trainClass.colRange(1,2);  
    //随机生成Y的值  
    rng.fill(c,RNG::UNIFORM,Scalar(1),Scalar(HEIGHT));  
  
  
    //***************4.为所有数据设置标签**********  
    //前100个数据设为第一类  
    labels.rowRange(0,NTRAINING_SAMPLES).setTo(1);  
    //后100个数据设为第二类  
    labels.rowRange(NTRAINING_SAMPLES,2*NTRAINING_SAMPLES).setTo(2);  
  
  
    //**************第二步：设置SVM参数***********  
    CvSVMParams params;  
    //SVM类型： C-Support Vector Classification  
    params.svm_type     = SVM::C_SVC;  
  
    params.C            = 0.1;  
    //和函数类型：Linear kernel  
    params.kernel_type  = SVM::LINEAR;  
    //终止准则：当迭代次数到达最大值后终止  
    params.term_crit    = TermCriteria(CV_TERMCRIT_ITER,(int) 1e7,1e-6);  
  
  
  
    //**************第三步：训练SVM***********  
    cout<<"开始训练过程"<<endl;  
    //开始计时  
    clock_t start,finish;  
    double duration;  
    start = clock();  
    //*************1.建立一个SVM实例**********  
    CvSVM svm;  
    //*************2.调用训练函数*************  
    svm.train(trainData,labels,Mat(),Mat(),params);  
    //结束计时  
    finish = clock();  
    duration = (double)(finish-start) / CLOCKS_PER_SEC;  
    cout<<"训练过程结束,共耗时："<<duration<<"秒"<<endl;  
  
  
  
  
    //************第四步：显示判决域************  
    //第一类用绿色；第二类用蓝色  
    Vec3b green(0,100,0),blue(100,0,0);  
    for(int i = 0; i < image.rows; ++i)  
    {  
        for(int j = 0; j < image.cols; ++j)  
        {  
            Mat sampleMat = (Mat_<float>(1,2)<<i,j);  
            float response = svm.predict(sampleMat);  
            if (response == 1)  
            {  
                image.at<Vec3b>(j,i) = green;  
            }  
            else if (response == 2)  
            {  
                image.at<Vec3b>(j,i) = blue;  
            }  
        }  
    }  
  
  
  
    //************第五步：显示训练数据************  
    //红色  
    //负数会导致画出的图型是实心的  
    int thick = -1;  
    int lineType = 8;  
    float px,py;  
    //************1.第一类*************  
    for(int i = 0; i < NTRAINING_SAMPLES; ++i)  
    {  
        px = trainData.at<float>(i,0);  
        py = trainData.at<float>(i,1);  
        circle(image,Point((int)px,(int)py),3,Scalar(0,255,0));  
    }  
    //***********2.第二类****************  
    for(int i = NTRAINING_SAMPLES; i < 2*NTRAINING_SAMPLES; ++i)  
    {  
        px = trainData.at<float>(i,0);  
        py = trainData.at<float>(i,1);  
        circle(image,Point((int)px,(int)py),3,Scalar(255,0,0));       
    }  
  
  
  
    //***********第六步：显示支持向量*************  
    thick = 2;  
    lineType = 8;  
    //获取支持向量的个数  
    int x = svm.get_support_vector_count();  
    for(int i = 0; i < x; ++i)  
    {  
        const float* v = svm.get_support_vector(i);  
        circle(image,Point((int)v[0],(int)v[1]),6,Scalar(128,128,128),thick,lineType);  
    }  
    imshow("分类结果",image);  
    waitKey(0);  
    return 0;  
}  
