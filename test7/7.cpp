#include<iostream>  
#include<thread>  
#include<atomic>  
using namespace std;
const int N = 100000000;
atomic_int num{ 0 };//���ᷢ���̳߳�ͻ���̰߳�ȫ  
void run()
{
    for (int i = 0; i < N; i++)
    {
        num++;
    }
}
int main()
{
    clock_t start = clock();
    thread t1(run);
   
    thread t2(run);
    
    t1.join();
    t2.join();
    clock_t end = clock();
    cout << "num=" << num << ",��ʱ " << end - start << " ms" << endl;

    auto fun = [](const char* str) {cout << str << endl; };
    thread t3(fun, "hello world!");
    thread t4(fun, "hello beijing!");
    return 0;
}