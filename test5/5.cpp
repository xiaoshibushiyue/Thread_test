#include<iostream>  
#include<thread>  
using namespace std;
void show()
{
    cout << "hello cplusplus!" << endl;
}
int main()
{
    thread th(show);
    //th.join();   
    th.detach();//�������̵߳İ󶨣����̹߳��ˣ����̲߳��������߳�ִ�����Զ��˳���  
    //detach�Ժ����̻߳��Ϊ�¶��̣߳��߳�֮�佫�޷�ͨ�š�  
    cout << th.joinable() << endl;
    auto n = thread::hardware_concurrency();//��ȡcpu���ĸ���  
    cout << n << endl;
    return 0;
}

