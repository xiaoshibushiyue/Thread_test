#include <iostream>
#include<thread>
#include<atomic>
#include<mutex>
#include <stdexcept> 
#include <vector>
#include <future>
using namespace std;
mutex m;
mutex mtx;
long total = 0;
int i =0;
atomic<int> foo(0);
atomic<bool> ready(false);
atomic<bool> winner(false);
std::condition_variable cv;
bool ready1 = false;
int cargo = 0;
int tag =0;
std::condition_variable produce, consume;
void show() {
    cout << "多线程执行" << endl;
}
void show_S(string s) {
    cout << s << endl;
}
void show_Y(char &a) {
    a = 'c';
}
void sum() {
    m.lock();
    for (; i < 1000000; i++)
    {
        
        total += 1;
      
    }
    m.unlock();
}
void print_thread_id(int id) {
    try {
        // using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
       lock_guard<mutex> lck(mtx);
       if (id % 2 == 0) cout << id<< " is even" << endl;
       else
       {
           char a[20];
           _itoa(id, a, 10);
           strcat_s(a, " not even");

           throw (logic_error(a));
       }
    }
    catch (logic_error&e) {
        cout << e.what()<<endl;
    }
}
void print_block(int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    unique_lock<mutex> lck(mtx);
    for (int i = 0; i < n; ++i) { cout << c; }
    cout << '\n';
}
void print_star() {
    unique_lock<mutex> lck(mtx, defer_lock);
    // print '*' if successfully locked, 'x' otherwise: 
    if (lck.try_lock())
        cout << '*';
    else
        cout << 'x';
}
void count1m(int id) {
    while (!ready) {}                  // wait for the ready signal
    for (int i = 0; i < 1000000; ++i) {}   // go!, count to 1 million
    if (!winner.exchange(true)) { cout << "thread #" << id << " won!\n"; }
};
void set_foo(int x) {
    foo.store(x, memory_order_relaxed);     // set value atomically
}
void print_foo() {
    int x;
    do {
        x = foo.load(memory_order_relaxed);  // get value atomically
        cout << "foo: " << x << '\n';
    } while (x == 0);
   
}
bool is_prime(int x)
{
    for (int  j= 2; j < x; j++)
    {
        if (x % j == 0)
            return false;
    }
    return true;
}
void print_int(std::future<int>& fut) {
    chrono::milliseconds span(100);
    while (fut.wait_for(span) != future_status::ready)
    {
        cout << ".";
    }
    cout << endl;
    int x = fut.get();
   
    std::cout << "value: " << x << '\n';
}
void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);
    // ...
    std::cout << "thread " << id << '\n';
}
void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready1= true;
    cv.notify_all();
}
void consumer() {
    while (true)
    {
        std::unique_lock<std::mutex> lck(mtx);
       
        while (cargo == 0&&tag<=20) {
            consume.wait(lck);
        }
        cargo--;
        tag++;
        std::cout <<"消费："<< cargo << '\n';
        
        lck.unlock();
        if (tag > 20)
        {
            break;
        }
        produce.notify_one();//一通知就切换线程了
    }
}

void producer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lck(mtx);
        while (cargo != 0) {
            chrono::milliseconds span(5000);         
            if (produce.wait_for(lck, span) == cv_status::timeout)
            {
                break;
            } 
            else {
                cargo = id;
                std::cout << "生产：" << cargo << '\n';
            }
        }
      
        lck.unlock();
        consume.notify_one();

        
    }
}
int main()
{
    char a='g';
    //基础用法
    {
        thread t1(show);
        if (t1.joinable()) {
            t1.join();
        }
        thread t2(show_S, "xiaoshi");
        t2.join();
        thread t3(show_Y, ref(a));
        t3.join();
    }
    //几种锁
    {
        //用两个线程来计算sum
        thread t4(sum);
        t4.join();
        thread t5(sum);
        t5.join();
        //lock_guard<mutex>
        thread threads[10];
        for (int i = 0; i < 10; ++i)
            threads[i] = thread(print_thread_id, i + 1);
        for (auto& th : threads) 
            th.join();
        //unique_lock
        thread th1(print_block, 50, '*');
        thread th2(print_block, 50, '$');

        th1.join();
        th2.join();
        vector<thread> threads1;
        for (int i = 0; i < 500; ++i)
            threads1.emplace_back(print_star);
        for (auto& x : threads1) x.join();
    }
    //原子操作
    {
        thread first(print_foo);
        thread second(set_foo, 10);
        first.join();
        second.join();

       vector<thread> threads;
        cout << "spawning 10 threads that count to 1 million...\n";
        for (int i = 1; i <= 10; ++i) threads.push_back(thread(count1m, i));
        ready = true;
        for (auto& th : threads) th.join();
    }
    //future
    {
        std::future<bool> fut = std::async(is_prime, 700020007);
        std::cout << "please wait";
        std::chrono::milliseconds span(100);
        while (fut.wait_for(span) != std::future_status::ready)
            std::cout << ".";
        std::cout << std::endl;

        bool ret = fut.get();
        std::cout << "final result: " << ret << std::endl;
    }
    //promise
    {
        //有点线程之间通信的意思
        std::promise<int> prom;                      // create promise
        std::future<int> fut = prom.get_future();    // engagement with future
        std::thread th1(print_int, std::ref(fut));  // send future to new thread
        chrono::milliseconds span(1000);
        this_thread::sleep_for(span);
        prom.set_value(10);                         // fulfill promise
                                       // (synchronizes with getting the future)
        th1.join();
    }

    //condition_variable
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i = 0; i < 10; ++i)
            threads[i] = std::thread(print_id, i);
        std::cout << "10 threads ready to race...\n";
        go();                       // go! 启动函数
        for (auto& th : threads) th.join();

        std::thread consumers;
            thread producers[1];           
            consumers = std::thread(consumer);
            for (int i = 0; i < 1; i++)
            {
                producers[i] = std::thread(producer, 10);
            }
            for (int i = 0; i < 1; i++)
            {
                producers[i].join();
            }
            consumers.join();

    }

    cout << "结束" << endl;
    return 0;
}