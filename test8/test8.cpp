#include<iostream>  
#include<thread>  
#include<chrono>  
using namespace std;
int main()
{
    thread th1([]()
        {
            //���̵߳ȴ�3��  
            this_thread::sleep_for(chrono::seconds(3));
            //��cpuִ���������е��߳�  
            this_thread::yield();
            
            //�߳�id  
            cout << this_thread::get_id() << endl;
        });
    th1.join();
    return 0;
}