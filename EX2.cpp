#include <bits/stdc++.h>
using namespace std;

#define BUF_SIZE 3

typedef struct PCB
{
    /* data */
    int name; // 进程名称,使用数字表示名称
    int type; // 进程类型/生产者、消费者,1表示生产者，0表示消费者
} PCB;

// 函数声明
void Creat_Process();

int num = -1;         // 记录缓冲区中的数据数量
int buffer[BUF_SIZE]; // 缓冲区

queue<PCB> PCB_P;    // 生产者等待队列
queue<PCB> PCB_C;    // 消费者等待队列
queue<PCB> PCB_R;    // 就绪队列
queue<PCB> PCB_OVER; // OVER队列


void Print_Queue_OVER(queue<PCB> P)
{
    //输出就绪队列中数据，方便区分进程类型
    queue<PCB> Q;
    Q = P;
    if (!Q.empty())
    {
        while (!Q.empty())
        {
            // 输出并删除队列中元素
            PCB T;
            T = Q.front();
            if(T.type==1)
            cout<<"P";
            else if(T.type==0)
            cout<<"C";
            cout << T.name << " ";
            Q.pop();
        }
        cout << endl;
    }
    else
    {
        cout << "NULL" << endl;
    }
}

void Print_Queue(queue<PCB> P)
{
    queue<PCB> Q;
    Q = P;
    if (!Q.empty())
    {
        while (!Q.empty())
        {
            // 输出并删除队列中元素
            PCB T;
            T = Q.front();
            cout << T.name << " ";
            Q.pop();
        }
        cout << endl;
    }
    else
    {
        cout << "NULL" << endl;
    }
}

void Wakeup_C()
{
    PCB T;
    // 取出等待队列中的元素并且将其pop
    T = PCB_C.front();
    PCB_C.pop();
    // 将取出的PCB插入到就绪队列队尾
    PCB_R.push(T);
    cout << "唤醒消费者成功" << endl;
}

void Wakeup_P()
{
    PCB T;
    // 取出等待队列中的元素并将其从等待队列中删除
    T = PCB_P.front();
    PCB_P.pop();
    PCB_R.push(T);
    cout << "唤醒生产者成功" << endl;
}

int main()
{
    Creat_Process();
    // 输出各队列的信息
    cout << "创建完队列之后所有队列的信息" << endl;
    cout << "就绪队列: ";
    Print_Queue(PCB_R);
    cout << "生产者等待队列: ";
    Print_Queue(PCB_P);
    cout << "消费者等待队列： ";
    Print_Queue(PCB_C);
    cout << "OVER队列: ";
    Print_Queue_OVER(PCB_OVER);
    cout << "_________________________________" << endl;

    while (1)
    {
        // 就绪队列不为空
        while (!PCB_R.empty())
        {

            // 从就绪队列中选取其中的进程
            PCB temp;
            temp = PCB_R.front();
            PCB_R.pop();
            if (temp.type == 1)
            {
                // 生产者
                if (num < BUF_SIZE - 1)
                {
                    // 缓冲区为空,将ID号放入缓冲区中
                    num++;
                    buffer[num] = temp.name;
                    // 将该进程放到OVER队列中
                    PCB_OVER.push(temp);
                    if (!PCB_C.empty())
                    {
                        // 若消费者等待队列不为空则唤醒消费者等待队列中的进程
                        Wakeup_C();
                    }
                }
                else
                {
                    cout << "缓冲区已满！" << endl;
                    // 将当前进程放入生产者等待队列中
                    PCB_P.push(temp);
                }
            }
            else if (temp.type == 0)
            {
                // 消费者
                if (num == -1)
                {
                    // 缓冲区中没有结果
                    cout << "缓冲区为空！" << endl;
                    // 将其挂到消费者等待队列中
                    PCB_C.push(temp);
                }
                else
                {
                    num--;
                    // 将当前进程挂到OVER队列中
                    PCB_OVER.push(temp);
                    // 唤醒生产者
                    if (!PCB_P.empty())
                    {
                        Wakeup_P();
                    }
                }
            }
            // 输出各队列的信息
            cout << "就绪队列: ";
            Print_Queue(PCB_R);
            cout << "生产者等待队列: ";
            Print_Queue(PCB_P);
            cout << "消费者等待队列： ";
            Print_Queue(PCB_C);
            cout << "OVER队列: ";
            Print_Queue_OVER(PCB_OVER);
            cout << "_________________________________" << endl;
        }
    }
}

void Creat_Process()
{
    // 产生10个进程及其类别，存入就绪队列
    PCB pcb[10];
    for (int i = 0; i < 10; i++)
    {
        // 创建进程实体以及进程类型
        pcb[i].name = i;
        pcb[i].type = rand() % 2;
    }
    // 将进程分别放入进程就绪队列中
    for (int i = 0; i < 10; i++)
    {
        PCB_R.push(pcb[i]);
    }
}
