# include <bits/stdc++.h>
using namespace std;

enum ProcessState { READY, WAITING, FINISHED };

struct PCB {
    string name; 
    ProcessState state;
    int priority;
    int remaining_time; // 剩余需要执行的时间
};

 vector<PCB> processes;
 vector<int> readyQueue;
 vector<int> waitingQueue;

// 将PCB加入队列
void enqueue( vector<int>& queue, int index) {
    queue.push_back(index);
}

// 从队列中取出一个PCB
int dequeue( vector<int>& queue) {
    if (queue.empty())
        return -1; // 队列为空
    int front = queue.front();
    queue.erase(queue.begin());
    return front;
}

// 进程调度模拟
void simulate() {
    srand(time(nullptr));

    for (int i = 0; i < 10; ++i) {
        PCB process;
        process.name = "P" +  to_string(i); 
        process.state = static_cast<ProcessState>(rand() % 2); // 0或1
        process.priority = rand() % 10 + 1; // 1到10
        process.remaining_time = rand() % 100 + 1; // 假设执行时间在1到100ms之间
        processes.push_back(process);
    }

    for (int i = 0; i < (int)processes.size(); ++i) {
        if (processes[i].state == READY) {
            enqueue(readyQueue, i);
        } else {
            enqueue(waitingQueue, i);
        }
    }

    while (!readyQueue.empty()) { // 当就绪队列不为空时
        int maxPriorityIndex = -1;
        int maxPriority = 0;
        for (int i = 0; i < (int)readyQueue.size(); ++i) { // 遍历寻找最高优先级
            int index = readyQueue[i];
            if (processes[index].priority > maxPriority) {
                maxPriority = processes[index].priority;
                maxPriorityIndex = index;
            }
        }

        int executingIndex = maxPriorityIndex;
        int executedTime = rand() % 100 + 1; // 执行时间
        processes[executingIndex].remaining_time -= executedTime;

        // 打印执行进程、就绪队列和等待队列
         cout << "当前执行进程： " << processes[executingIndex].name <<  endl;
         cout << "当前就绪队列： ";
        for (int j = 0; j < (int)readyQueue.size(); j++) {
             cout << readyQueue[j] << " ";
        }
         cout <<  endl;

         cout << "当前等待队列： ";
        for (int k = 0; k < (int)waitingQueue.size(); k++) {
             cout << waitingQueue[k] << " ";
        }
         cout <<  endl;

        if (processes[executingIndex].remaining_time <= 0) {
            // 执行完成
            processes[executingIndex].state = FINISHED;
             cout << "Process " << processes[executingIndex].name << " finished." <<  endl;
        } else {
            // 没有执行完成
            int nextAction = rand() % 2;
            if (nextAction == 0) {
                // 加入就绪队列
                enqueue(readyQueue, executingIndex);
            } else {
                // 加入等待队列
                enqueue(waitingQueue, executingIndex);
            }

            // 可能将等待队列的进程加入就绪队列
            if (rand() % 2 == 1 && !waitingQueue.empty()) {
                int waitingIndex = dequeue(waitingQueue);
                enqueue(readyQueue, waitingIndex);
            }
        }

        // 从就绪队列中移除已执行的进程
        readyQueue.erase( remove(readyQueue.begin(), readyQueue.end(), executingIndex), readyQueue.end());
    }

     cout << "All processes have been scheduled." <<  endl;
}

int main() {
    srand(time(nullptr));
    simulate();
    return 0;
}
