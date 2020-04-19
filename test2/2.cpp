#include<iostream>  
#include<thread>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    //栈上  
    thread t1(show);   //根据函数初始化执行  
    thread t2(show);
    thread t3(show);
    //线程数组  
    thread th[3]{ thread(show), thread(show), thread(show) };
    //堆上  
    thread* pt1(new thread(show));
    
    thread* pt2(new thread(show));
    thread* pt3(new thread(show));
    //线程指针数组  
    thread* pth(new thread[3]{ thread(show), thread(show), thread(show) });
    return 0;
}