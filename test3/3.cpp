#include<iostream>  
#include<thread>  
using namespace std;
void show(const char* str, const int id)
{
    cout << "Ïß³Ì " << id + 1 << " £º" << str << endl;
}
int main()
{
    thread t1(show, "hello cplusplus!", 0);
    thread t2(show, "ÄãºÃ£¬C++£¡", 1);      
    thread t3(show, "hello!", 2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}