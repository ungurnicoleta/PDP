//
// Created by Nicoleta Ungur on 04/11/2019.
//

#ifndef LAB4_QUEUE_H
#define LAB4_QUEUE_H

#include <condition_variable>
#include <vector>
#include "Task.h"

class Queue {
private:
    std::condition_variable cond;
    std::mutex m_mutex;
    bool closed;
    std::vector<Task> queue;

public:
    void enqueue(Task task){
        std::unique_lock<std::mutex> lock(m_mutex);
        queue.push_back(task);
        cond.notify_one();
    }

    bool dequeue(Task& task){
        while(true){
            std::unique_lock<std::mutex> lock(m_mutex);
            if(!queue.empty())
            {
                task = queue.front();
                queue.erase(queue.begin());
                return true;
            }
            if(closed){
                return false;
            }
            else
                cond.wait(lock);
        }
    }

    void close(){
        std::unique_lock<std::mutex> lock(m_mutex);
        closed = true;
        cond.notify_all();
    }

    bool is_closed(){
        std::unique_lock<std::mutex> lock(m_mutex);
        return closed;
    }
};


#endif //LAB4_QUEUE_H
