#include<iostream>  
#include<thread>  
#include<cstdarg>  
using namespace std;
int show(const char* fun, ...)
{
    va_list ap;//ָ��  
    va_start(ap, fun);//��ʼ  
    vprintf(fun, ap);//����  
    va_end(ap);
    return 0;
}
int main()
{
    thread t1(show, "%s    %d    %c    %f", "hello world!", 100, 'A', 3.14159);
    t1.join();
    return 0;
}