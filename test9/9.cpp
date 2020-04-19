#include<iostream>  
#include<thread>  
using namespace std;
class MyThread :public thread   //继承thread  
{
public:
    //子类MyThread()继承thread()的构造函数  
    MyThread() : thread()
    {
    }
    //MyThread()初始化构造函数  
    template<typename T, typename...Args>
    MyThread(T&& func, Args&&...args) : thread(forward<T>(func), forward<Args>(args)...)
    {
       
    }
    void showcmd(const char* str)  //运行system  
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
    th1.showcmd("calc"); //运行calc  
    //lambda  
    MyThread th2([](const char* str)
        {
            cout << "hello" << str << endl;
        }, " this is MyThread");
    th2.showcmd("notepad");//运行notepad  
    return 0;
}