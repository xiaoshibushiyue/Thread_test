#include<iostream>  
#include<thread>  
#include<array>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    array<thread, 3>  threads = { thread(show), thread(show), thread(show) };
    for (int i = 0; i < 3; i++)
    {
        cout << threads[i].joinable() << endl;//�ж��߳��Ƿ����join  
        threads[i].join();//���̵߳ȴ���ǰ�߳�ִ��������˳�  
    }
    return 0;
}

