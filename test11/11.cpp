#include<iostream>  
#include<thread>  
using namespace std;
int main()
{
    thread t1([]()
        {
            cout << "thread1" << endl;
        });
    thread t2([]()
        {
            cout << "thread2" << endl;
        });
    cout << "thread1' id is " << t1.get_id() << endl;
    cout << "thread2' id is " << t2.get_id() << endl;

    cout << "swap after:" << endl;
    swap(t1, t2);//Ïß³Ì½»»»  
    cout << "thread1' id is " << t1.get_id() << endl;
    cout << "thread2' id is " << t2.get_id() << endl;
    return 0;
}