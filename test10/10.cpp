#include<iostream>  
#include<thread>  
#include<cstdarg>  
using namespace std;
int show(const char* fun, ...)
{
    va_list ap;//指针  
    va_start(ap, fun);//开始  
    vprintf(fun, ap);//调用  
    va_end(ap);
    return 0;
}
int main()
{
    thread t1(show, "%s    %d    %c    %f", "hello world!", 100, 'A', 3.14159);
    t1.join();
    return 0;
}