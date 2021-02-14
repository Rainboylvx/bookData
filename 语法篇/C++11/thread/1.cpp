#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx; //全局互斥锁
condition_variable condi; //全局条件变量
bool ready = false; //全局标志

void do_print_id(int id){
    unique_lock<mutex> lck(mtx);
    while ( !ready ) {
        condi.wait(lck);
    }
    cout << " thread " << id << endl;
}

void go(){
    unique_lock<mutex> lck(mtx);
    ready = true;
    condi.notify_all();
}

int main(){
    thread threads[10];
    for(int i=1;i<=10;++i){
        threads[i-1] = thread(do_print_id,i);
    }
    std::cout << " 10 threads ready to race ..\n" ;
    go();
    for (auto & th : threads) {
        th.join();
    }
    return 0;
}
