//#pragma once//��ӡ�����൱�����������е�δ��ɵĹ���<br>#include <stdio.h>
//#include <string>
//#include<memory>
//using namespace std;//����һ������ָ��
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
//    //��̬�����Ա����
//    static void onPrintName(string strName);
//private:
//    shared_ptr<CallBack> m_CallBack;
//};
//
//BaseCall::BaseCall()
//{
//    m_CallBack = make_shared<CallBack>();
//    //�ͻص�������
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
//    printf("������ %s\n", strName.c_str());
//}
//int main() {
//    BaseCall bs;
//    return 0;
//}


//{
//void basketball()//����1
//{
//	printf("ѡ������");
//}
//void football()//����2
//{
//	printf("ѡ������");
//}
//void selectball(void (*ball)())//����3
//{
//	printf("ѡ��ʲô��");
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
////1.���庯��onHeight���ص�������
////@onHeight ������
////@height   ����
////@contex   ������
//void onHeight(double height, void* contex)
//{
//	sprint("current height is %lf", height);
//}
//
////2.����onHeight������ԭ��
////@CallbackFun ָ������ָ������
////@height      �ص����������ж������ʱ�����Զ���һ���ṹ��
////@contex      �ص������ģ���C��һ�㴫��nullptr����C++�пɴ������ָ��
//typedef void (*CallbackFun)(double height, void* contex);
//
////3.����ע��ص�����
////@registHeightCallback ע�ắ����
////@callback             �ص�����ԭ��
////@contex               �ص�������
//void registHeightCallback(CallbackFun callback, void* contex)
//{
//	double h = 100;
//	callback(h, nullptr);
//}
//
////4.main����
//void main()
//{
//	//ע��onHeight��������ͨ��registHeightCallback�Ĳ�����onHeight����ָ��
//	//�����registHeightCallback��������registHeightCallback�����е���
//	//callback���൱�ڵ���onHeight������
//	registHeightCallback(onHeight��nullptr);
//}
//}
//�ȶ���һ����class DataPrint
//��ӡ������class DataPrint


//#include<iostream>
//using namespace std;
////CallbackFun����
////@CallbackFun ָ������ָ������
////@height      �ص����������ж������ʱ�����Զ���һ���ṹ��
////@contex      �ص������ģ���C��һ�㴫��nullptr����C++�пɴ������ָ��
//typedef void (*CallbackFun)(double height, void* contex);
//
////ע��ص������ӿ�
////@registHeightCallback ע�ắ����
////@callback             �ص�����ԭ��
////@contex               �ص�������
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
////Ҫ����Sensor������DataPrint��ָ���һ��DataPrintָ�븳ֵ������class Sensor�޸�Ϊ
////����������class Sensor
//class Sensor {
//public:
//	Sensor() {}
//	~Sensor() {}
//	//����ص�����onHeight
//	static void onHeight(double height, void* contex)
//	{
//		DataPrint* dp = (DataPrint*)contex;
//		if (dp)  //ע���ж�dp�Ƿ���Ч
//			dp->printHeight(height);
//	}
//	//����ע��ص�����
//	void registCallback()
//	{
//		registHeightCallback(onHeight, m_pDataPrint);
//	}
//	//�����ĳ�Ա����
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
////main������
//void main()
//{
//	DataPrint* dp = new DataPrint();
//	Sensor* sens = new Sensor();
//	//ע���������˳���ܵߵ�
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
    function<void(int)> m_PrintAge;  //C11 д��1
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
        m_CallBack->m_PrintAge = bind(BaseCall::onPrintAge, placeholders::_1); //C11д��1(��ʾ�󶨺��� onPrintAge ��һ��������m_PrintAgeָ��)

    m_CallBack->TestCallBack(NAME);
    m_CallBack->TestCallBack(AGE);
    m_CallBack->TestCallBack(GRADE);
}

BaseCall::~BaseCall()
{

}

void BaseCall::onPrintName(string strName)
{
    printf("������ %s\n", strName.c_str());
}

void BaseCall::onPrintAge(int nAge)
{
    printf("���䣺 %d\n", nAge);
}

void BaseCall::onPrintGrade(int nGrade)
{
    printf("�༶��%d\n", nGrade);
}