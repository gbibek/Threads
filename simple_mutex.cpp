#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <mutex>

using namespace std;

mutex my_mutex;

void adder(int &i)
{
    this_thread::sleep_until(chrono::system_clock::now()
        + chrono::milliseconds(100));
    lock_guard<mutex> guard(my_mutex);    
    ++i;
   // cout<<"From thread id "<<this_thread::get_id()<<endl;
}

int main()
{
    vector<thread> threads;
    int value = 0;
    cout<<"Initial value = "<<value<<endl;
    for(int i = 0; i < 200; ++i)
    {   
        threads.push_back(thread(adder,ref(value)));
    }
    for_each(threads.begin(),threads.end(), mem_fn(&thread::join));   
    cout<<"After Threads add, the result is "<<value<<endl;
return 0;
}
