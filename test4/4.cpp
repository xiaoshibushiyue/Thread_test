#include<iostream>  
#include<thread>  
#include<array>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    array<thread, 3>  threads = { thread(show), thread(show), thread(show) };
    for (int i = 0; i < 3; i++)
    {
        cout << threads[i].joinable() << endl;//判断线程是否可以join  
        threads[i].join();//主线程等待当前线程执行完成再退出  
    }
    return 0;
}

