#include<iostream>  
#include<thread>  
using namespace std;
class MyThread :public thread   //�̳�thread  
{
public:
    //����MyThread()�̳�thread()�Ĺ��캯��  
    MyThread() : thread()
    {
    }
    //MyThread()��ʼ�����캯��  
    template<typename T, typename...Args>
    MyThread(T&& func, Args&&...args) : thread(forward<T>(func), forward<Args>(args)...)
    {
       
    }
    void showcmd(const char* str)  //����system  
    {
        system(str);
    }
};
int main()
{
    MyThread th1([]()
        {
            cout << "hello" << endl;
        });
    th1.showcmd("calc"); //����calc  
    //lambda  
    MyThread th2([](const char* str)
        {
            cout << "hello" << str << endl;
        }, " this is MyThread");
    th2.showcmd("notepad");//����notepad  
    return 0;
}