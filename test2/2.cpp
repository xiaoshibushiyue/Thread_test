#include<iostream>  
#include<thread>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    //ջ��  
    thread t1(show);   //���ݺ�����ʼ��ִ��  
    thread t2(show);
    thread t3(show);
    //�߳�����  
    thread th[3]{ thread(show), thread(show), thread(show) };
    //����  
    thread* pt1(new thread(show));
    
    thread* pt2(new thread(show));
    thread* pt3(new thread(show));
    //�߳�ָ������  
    thread* pth(new thread[3]{ thread(show), thread(show), thread(show) });
    return 0;
}