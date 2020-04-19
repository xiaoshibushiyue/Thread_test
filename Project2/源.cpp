//#include<iostream>
//#include<vector>
//#include<thread>
//#include<queue>
//#include<mutex>
//#include<Windows.h>
//#include <future>
//using namespace std;
//class demo {
//private:
//	condition_variable is_full;
//	condition_variable is_empty;
//	mutex mtx;
//	vector<std::thread> tpool;
//private:
//	queue<int> item_buff;
//	const int buffsize;
//	static int item_id;
//	int c_no, p_no;
//private:
//	void producItem() {
//		while (true) {
//			std::unique_lock<mutex> lck(mtx);
//			while (item_buff.size() == buffsize) {
//				is_full.wait(lck);
//			}
//			item_id = item_id++ % buffsize;
//			item_buff.push(item_id);
//			cout << "product item id: " << item_id << endl;
//			lck.unlock();
//			is_empty.notify_all();
//			Sleep(2000);
//		}
//	}
//	void consumeItem() {
//		while (true) {
//			std::unique_lock<mutex> lck(mtx);
//			while (item_buff.empty()) {
//				cout << "wait product" << endl;
//				is_full.notify_one();
//				is_empty.wait(lck);
//			}
//			cout << "customer id : " << this_thread::get_id() << endl;
//			cout << "consume Item id: " << item_buff.front() << endl;
//			item_buff.pop();
//		lck.unlock();
//		}
//	}
//public:
//	demo(int size = 10, int pno = 10, int cno = 1) :buffsize(size), p_no(pno), c_no(cno) {};
//	void run() {
//		productTask();
//		customerTask();
//		for (auto& i : tpool) {
//			i.join();
//		}
//	}
//	void productTask() {
//		for (int i = 0; i < p_no; i++) {
//			tpool.emplace_back(thread(&demo::producItem, this));
//		}
//	}
//	void customerTask() {
//		for (int i = 0; i < c_no; i++) {
//			tpool.emplace_back(thread(&demo::consumeItem, this));
//		}
//	}
//};
//
//int demo::item_id = 0;
//
//int main()
//{
//	demo t;
//	t.run();
//
//	return 0;
//}
//#include <iostream>           
//#include <queue>
//#include <thread>             
//#include <mutex> 
//#include<Windows.h>
//#include <condition_variable> 
//using namespace std;
//
//mutex mtx;
//condition_variable produce, consume;  // 条件变量是一种同步机制，要和mutex以及lock一起使用
//
//queue<int> q;     // shared value by producers and consumers, which is the critical section
//int maxSize = 200;
//
//void consumer()
//{
//    while (true)
//    {
//        this_thread::sleep_for(chrono::milliseconds(1000));
//       // sleep(1);//包含在unistd.h头文件中,Sleep包含在windows.h中
//        unique_lock<mutex> lck(mtx);
//        while (q.size() == 0)
//        {
//            consume.wait(lck);             //condition_variable.wait()锁至满足while条件不满足 
//        }
//        //consume.wait(lck, [] {return q.size() != 0; });     // wait(block) consumer until q.size() != 0 is true
//
//        cout << "consumer " << this_thread::get_id() << ": ";
//        q.pop();
//        cout << q.size() << '\n';
//
//        produce.notify_all();                               // nodity(wake up) producer when q.size() != maxSize is true
//        lck.unlock();
//    }
//}
//
//void producer(int id)
//{
//    while (true)
//    {
//        this_thread::sleep_for(chrono::milliseconds(900));      // producer is a little faster than consumer  
//        //sleep(1);//  
//        unique_lock<mutex> lck(mtx);
//        while (q.size() == maxSize)
//        {
//            produce.wait(lck);
//        }
//        // produce.wait(lck, [] {return q.size() != maxSize; });   // wait(block) producer until q.size() != maxSize is true
//
//        cout << "-> producer " << this_thread::get_id() << ": ";
//        q.push(id);
//        cout << q.size() << '\n';
//
//        consume.notify_all();                                   // notify(wake up) consumer when q.size() != 0 is true
//        lck.unlock();
//    }
//}
//
//int main()
//{
//    thread consumers[20], producers[20];
//
//    // spawn 2 consumers and 2 producers:
//    for (int i = 0; i < 20; ++i)
//    {
//        consumers[i] = thread(consumer);
//        producers[i] = thread(producer, i + 1);  //thread：第一个参数是task任务，第二个参数是task函数的参数 
//    }
//
//    // join them back: (in this program, never join...)
//    for (int i = 0; i < 20; ++i)
//    {
//        producers[i].join();
//        consumers[i].join();
//    }
//    
//    system("pause");
//    return 0;
//}
#include <iostream>
#include <mutex>
#include <thread>

#ifdef _MSC_VER
#include <windows.h>	// windows
#else
#include <unistd.h>		// linux
#endif

// 跨平台的延时函数:毫秒
void mySleep(int milliseconds) {
#ifdef _MSC_VER
	Sleep(milliseconds);
#else
	sleep(milliseconds);
#endif
}


const int kProduceItems = 20;	// 计划生产的产品个数
const int kRepositorySize = 5;	// 仓库大小

// 仓库类
template<class T>
class Repository {
public:
	T items_buff[kRepositorySize];			// 数组实现环形队列

	std::mutex mtx;							// 生产者消费者互斥量
	std::mutex produce_mutex;				// 生产计数互斥量
	std::mutex consume_mutex;				// 消费计数互斥量
	std::condition_variable repo_not_full;	// 仓库不满条件变量
	std::condition_variable repo_not_empty;	// 仓库不空条件变量

	size_t produce_item_count;				// 生产数量计数
	size_t consume_item_count;				// 消费数量计数
	size_t produce_position;				// 下一个生产的位置
	size_t consume_position;				// 下一个消费的位置

	Repository() {
		produce_item_count = 0;
		consume_item_count = 0;
		produce_position = 0;
		consume_position = 0;
	};
};

// 工厂类
template<class T>
class Factory {
private:
	Repository<T> repo;

	// 将生产好的产品放入仓库
	void ProduceItem(Repository<T>& repo, T item) {
		std::unique_lock<std::mutex> lock(repo.mtx);
		// +1 后判断，因为在初始时，两者位于同一位置（因此仓库中最大存在 kRepositorySize-1 个产品）
		while ((repo.produce_position + 1) % kRepositorySize == repo.consume_position) {
			std::cout << "Repository is full, waiting..." << std::endl;
			repo.repo_not_full.wait(lock);			// 阻塞时释放锁，被唤醒时获得锁
		}
		repo.items_buff[repo.produce_position++] = item;
		if (repo.produce_position == kRepositorySize)
			repo.produce_position = 0;
		repo.repo_not_empty.notify_all();			// 唤醒所有因空阻塞的进程
		lock.unlock();
	}

	// 从仓库中拿取一个产品
	T ConsumeItem(Repository<T>& repo) {
		std::unique_lock<std::mutex> lock(repo.mtx);
		while (repo.consume_position == repo.produce_position) {
			std::cout << "Repository is empty, waiting ..." << std::endl;
			repo.repo_not_empty.wait(lock);			// 阻塞时释放锁，被唤醒时获得锁
		}
		T data = repo.items_buff[repo.consume_position++];
		if (repo.consume_position == kRepositorySize)
			repo.consume_position = 0;
		repo.repo_not_full.notify_all();			// 唤醒所有因满阻塞的进程
		lock.unlock();
		return data;
	}

public:
	void ProduceTask() {
		bool ready_to_exit = false;
		while (true) {

			std::unique_lock<std::mutex> lock(repo.produce_mutex);

			if (repo.produce_item_count < kProduceItems) {		// 结束线程条件
				repo.produce_item_count++;

				// 生产产品代码块
				//----------------------------------------------------
				mySleep(1000);		// 模仿消费产品需要的时间，实际运用中不需要
				T item = repo.produce_item_count;
				std::cout << "producer id: " << std::this_thread::get_id()
					<< " is producing item:\t[" << item << "]" << std::endl;
				//----------------------------------------------------

				ProduceItem(repo, item);
			}
			else {
				ready_to_exit = true;
			}

			lock.unlock();
			if (ready_to_exit)
				break;
		}
	}

	void ConsumeTask() {
		bool ready_to_exit = false;
		while (true) {
			std::unique_lock<std::mutex> lock(repo.consume_mutex);

			if (repo.consume_item_count < kProduceItems) {		// 结束线程条件
				T item = ConsumeItem(repo);

				// 消费产品代码块
				//----------------------------------------------------
				mySleep(1000);		// 模仿消费产品需要的时间，实际运用中不需要
				std::cout << "consumer id: " << std::this_thread::get_id()
					<< " is consuming item:\t[" << item << "]" << std::endl;
				//----------------------------------------------------

				repo.consume_item_count++;
			}
			else {
				ready_to_exit = true;
			}

			lock.unlock();
			if (ready_to_exit)
				break;
		}
	}
};

int main() {
	std::cout << "Main thread id :" << std::this_thread::get_id() << std::endl;
	class Factory<int> myfactory;
	std::thread producer1(&Factory<int>::ProduceTask, &myfactory);
	std::thread producer2(&Factory<int>::ProduceTask, &myfactory);

	std::thread consumer1(&Factory<int>::ConsumeTask, &myfactory);
	std::thread consumer2(&Factory<int>::ConsumeTask, &myfactory);
	std::thread consumer3(&Factory<int>::ConsumeTask, &myfactory);

	producer1.join();
	producer2.join();
	consumer1.join();
	consumer2.join();
	consumer3.join();
}

