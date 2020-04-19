#include<iostream>  
#include<thread> 
#include<future>
using namespace std;
int factorial(int n) {
    int res = 1;
    return res;
}
int main()
{
    thread t1([]()
        {
            cout << "thread1" << endl;
        });
    cout << "thread1' id is " << t1.get_id() << endl;
    thread t2 = move(t1);;
    cout << "thread2' id is " << t2.get_id() << endl;
    cout << "thread1' id is " << t1.get_id() << endl;

    future<int> fu = async(factorial, 5);
    fu.get();
    return 0;
}