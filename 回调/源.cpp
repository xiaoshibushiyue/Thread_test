//#pragma once//打印姓名相当于上面例子中的未完成的工作<br>#include <stdio.h>
//#include <string>
//#include<memory>
//using namespace std;//定义一个函数指针
//typedef void(*PrintName)(string strName);
//
//enum CallType
//{
//    NAME,
//    AGE,
//    GRADE,
//};
//
//class CallBack
//{
//public:
//    CallBack();
//    ~CallBack();
//public:
//    void TestCallBack(CallType type);
//public:
//    PrintName m_PrintName;
//};
//
//CallBack::CallBack()
//{
//}
//
//CallBack::~CallBack()
//{
//}
//
//void CallBack::TestCallBack(CallType type)
//{
//    switch (type)
//    {
//    case NAME:
//        m_PrintName(string("name"));
//        break;
//    default:
//        break;
//    }
//}
//
//class BaseCall
//{
//public:
//    BaseCall();
//    ~BaseCall();
//
//public:
//    //静态的类成员函数
//    static void onPrintName(string strName);
//private:
//    shared_ptr<CallBack> m_CallBack;
//};
//
//BaseCall::BaseCall()
//{
//    m_CallBack = make_shared<CallBack>();
//    //和回调函数绑定
//    m_CallBack->m_PrintName = onPrintName;
//    m_CallBack->TestCallBack(NAME);
//}
//
//BaseCall::~BaseCall()
//{
//
//}
//
//void BaseCall::onPrintName(string strName)
//{
//    printf("姓名： %s\n", strName.c_str());
//}
//int main() {
//    BaseCall bs;
//    return 0;
//}


//{
//void basketball()//函数1
//{
//	printf("选择篮球");
//}
//void football()//函数2
//{
//	printf("选择足球");
//}
//void selectball(void (*ball)())//函数3
//{
//	printf("选择什么球？");
//	ball();
//}
//int main(void)
//{
//	selectball(basketball);
//	selectball(football);
//	return 0;
//}
//}
//
//{
////callbackTest.c
////1.定义函数onHeight（回调函数）
////@onHeight 函数名
////@height   参数
////@contex   上下文
//void onHeight(double height, void* contex)
//{
//	sprint("current height is %lf", height);
//}
//
////2.定义onHeight函数的原型
////@CallbackFun 指向函数的指针类型
////@height      回调参数，当有多个参数时，可以定义一个结构体
////@contex      回调上下文，在C中一般传入nullptr，在C++中可传入对象指针
//typedef void (*CallbackFun)(double height, void* contex);
//
////3.定义注册回调函数
////@registHeightCallback 注册函数名
////@callback             回调函数原型
////@contex               回调上下文
//void registHeightCallback(CallbackFun callback, void* contex)
//{
//	double h = 100;
//	callback(h, nullptr);
//}
//
////4.main函数
//void main()
//{
//	//注册onHeight函数，即通过registHeightCallback的参数将onHeight函数指针
//	//传入给registHeightCallback函数，在registHeightCallback函数中调用
//	//callback就相当于调用onHeight函数。
//	registHeightCallback(onHeight，nullptr);
//}
//}
//先定义一个类class DataPrint
//打印数据类class DataPrint


//#include<iostream>
//using namespace std;
////CallbackFun类型
////@CallbackFun 指向函数的指针类型
////@height      回调参数，当有多个参数时，可以定义一个结构体
////@contex      回调上下文，在C中一般传入nullptr，在C++中可传入对象指针
//typedef void (*CallbackFun)(double height, void* contex);
//
////注册回调函数接口
////@registHeightCallback 注册函数名
////@callback             回调函数原型
////@contex               回调上下文
//void registHeightCallback(CallbackFun callback, void* contex);
//class DataPrint {
//public:
//	DataPrint() {}
//	~DataPrint() {}
//	void printHeight(double height)
//	{
//		cout << "print height is " << height << endl;
//	}
//};
//
////要在类Sensor中增加DataPrint的指针和一个DataPrint指针赋值函数，class Sensor修改为
////接收数据类class Sensor
//class Sensor {
//public:
//	Sensor() {}
//	~Sensor() {}
//	//定义回调函数onHeight
//	static void onHeight(double height, void* contex)
//	{
//		DataPrint* dp = (DataPrint*)contex;
//		if (dp)  //注意判断dp是否有效
//			dp->printHeight(height);
//	}
//	//定义注册回调函数
//	void registCallback()
//	{
//		registHeightCallback(onHeight, m_pDataPrint);
//	}
//	//新增的成员函数
//	void getHeight(double height)
//	{
//		//cout << "current height is  " << height << endl;
//	}
//	void setDataPrint(DataPrint* dp)
//	{
//		m_pDataPrint = dp;
//	}
//private:
//	DataPrint* m_pDataPrint;
//};
//
////main主函数
//void main()
//{
//	DataPrint* dp = new DataPrint();
//	Sensor* sens = new Sensor();
//	//注意这两句的顺序不能颠倒
//	sens->setDataPrint(dp);
//	sens->registCallback();
//}
//
//void registHeightCallback(CallbackFun callback, void* contex)
//{
//	//callback();
//}

//#include <stdio.h>
//
//int add(int a, int b, int (*p)(int,int)) {
//    return (*p)(a, b);
//}
//
//int add(int a, int b) {
//    return a + b;
//}
//int main(int argc, char* args[]) {
//    int res = add(4, 2, add);
//    printf("%d\n", res);
//    return 0;
//}
#include<iostream>
#include <functional>
using namespace std;
typedef void(*PrintName)(string strName);

enum CallType
{
    NAME,
    AGE,
    GRADE,
};

class CallBack
{
public:
    CallBack();
    ~CallBack();

public:
    void TestCallBack(CallType type);
public:
    PrintName m_PrintName;
    function<void(int)> m_PrintAge;  //C11 写法1
};



CallBack::CallBack()
{
}

CallBack::~CallBack()
{
}

void CallBack::TestCallBack(CallType type)
{
    switch (type)
    {
    case NAME:
        m_PrintName(string("name"));
        break;
    case AGE:
        m_PrintAge(100);
        break;
    case GRADE:
    {
        function<void(int)> printGrade = bind(BaseCall::onPrintGrade, placeholders::_1);
        printGrade(2019);
    }
    break;
    default:
        break;
    }
}
class BaseCall
{
public:
    BaseCall();
    ~BaseCall();

public:
    static void onPrintName(string strName);
    static void onPrintAge(int nAge);
    static void onPrintGrade(int);
private:
    std::shared_ptr<CallBack> m_CallBack;
};

BaseCall::BaseCall()
{
    m_CallBack = make_shared<CallBack>();
    m_CallBack->m_PrintName = onPrintName;
        m_CallBack->m_PrintAge = bind(BaseCall::onPrintAge, placeholders::_1); //C11写法1(表示绑定函数 onPrintAge 第一个参数由m_PrintAge指定)

    m_CallBack->TestCallBack(NAME);
    m_CallBack->TestCallBack(AGE);
    m_CallBack->TestCallBack(GRADE);
}

BaseCall::~BaseCall()
{

}

void BaseCall::onPrintName(string strName)
{
    printf("姓名： %s\n", strName.c_str());
}

void BaseCall::onPrintAge(int nAge)
{
    printf("年龄： %d\n", nAge);
}

void BaseCall::onPrintGrade(int nGrade)
{
    printf("班级：%d\n", nGrade);
}