#include<iostream>  
#include<thread>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    thread th(show);
    //th.join();   
    th.detach();//脱离主线程的绑定，主线程挂了，子线程不报错，子线程执行完自动退出。  
    //detach以后，子线程会成为孤儿线程，线程之间将无法通信。  
    cout << th.joinable() << endl;
    auto n = thread::hardware_concurrency();//获取cpu核心个数  
    cout << n << endl;
    return 0;
}

