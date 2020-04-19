#include<iostream>  
#include<thread>  
#include<chrono>  
using namespace std;
int main()
{
    thread th1([]()
        {
            //让线程等待3秒  
            this_thread::sleep_for(chrono::seconds(3));
            //让cpu执行其他空闲的线程  
            this_thread::yield();
            
            //线程id  
            cout << this_thread::get_id() << endl;
        });
    th1.join();
    return 0;
}