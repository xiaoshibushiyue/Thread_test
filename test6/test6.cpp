#include<iostream>  
#include<thread>  
#include<mutex>
#include<stack>
using namespace std;
const int N = 100000000;
int num(0);
mutex m;
void run()
{
    for (int i = 0; i < N; i++)
    {
        m.lock();
        num++;
        m.unlock();
        
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
    cout << "num=" << num << ",ÓÃÊ± " << end - start << " ms" << endl;
   
    return 0;
}