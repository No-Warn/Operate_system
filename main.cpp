#include <bits/stdc++.h>
using namespace std;

#define BUF_SIZE 3

typedef struct PCB
{
    /* data */
    int name; // ��������,ʹ�����ֱ�ʾ����
    int type; // ��������/�����ߡ�������,1��ʾ�����ߣ�0��ʾ������
} PCB;

// ��������
void Creat_Process();

int num = -1;         // ��¼�������е���������
int buffer[BUF_SIZE]; // ������

queue<PCB> PCB_P;    // �����ߵȴ�����
queue<PCB> PCB_C;    // �����ߵȴ�����
queue<PCB> PCB_R;    // ��������
queue<PCB> PCB_OVER; // OVER����


void Print_Queue_OVER(queue<PCB> P)
{
    //����������������ݣ��������ֽ�������
    queue<PCB> Q;
    Q = P;
    if (!Q.empty())
    {
        while (!Q.empty())
        {
            // �����ɾ��������Ԫ��
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
            // �����ɾ��������Ԫ��
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
    // ȡ���ȴ������е�Ԫ�ز��ҽ���pop
    T = PCB_C.front();
    PCB_C.pop();
    // ��ȡ����PCB���뵽�������ж�β
    PCB_R.push(T);
    cout << "���������߳ɹ�" << endl;
}

void Wakeup_P()
{
    PCB T;
    // ȡ���ȴ������е�Ԫ�ز�����ӵȴ�������ɾ��
    T = PCB_P.front();
    PCB_P.pop();
    PCB_R.push(T);
    cout << "���������߳ɹ�" << endl;
}

int main()
{
    Creat_Process();
    // ��������е���Ϣ
    cout << "���������֮�����ж��е���Ϣ" << endl;
    cout << "��������: ";
    Print_Queue(PCB_R);
    cout << "�����ߵȴ�����: ";
    Print_Queue(PCB_P);
    cout << "�����ߵȴ����У� ";
    Print_Queue(PCB_C);
    cout << "OVER����: ";
    Print_Queue_OVER(PCB_OVER);
    cout << "_________________________________" << endl;

    while (1)
    {
        // �������в�Ϊ��
        while (!PCB_R.empty())
        {

            // �Ӿ���������ѡȡ���еĽ���
            PCB temp;
            temp = PCB_R.front();
            PCB_R.pop();
            if (temp.type == 1)
            {
                // ������
                if (num < BUF_SIZE - 1)
                {
                    // ������Ϊ��,��ID�ŷ��뻺������
                    num++;
                    buffer[num] = temp.name;
                    // ���ý��̷ŵ�OVER������
                    PCB_OVER.push(temp);
                    if (!PCB_C.empty())
                    {
                        // �������ߵȴ����в�Ϊ�����������ߵȴ������еĽ���
                        Wakeup_C();
                    }
                }
                else
                {
                    cout << "������������" << endl;
                    // ����ǰ���̷��������ߵȴ�������
                    PCB_P.push(temp);
                }
            }
            else if (temp.type == 0)
            {
                // ������
                if (num == -1)
                {
                    // ��������û�н��
                    cout << "������Ϊ�գ�" << endl;
                    // ����ҵ������ߵȴ�������
                    PCB_C.push(temp);
                }
                else
                {
                    num--;
                    // ����ǰ���̹ҵ�OVER������
                    PCB_OVER.push(temp);
                    // ����������
                    if (!PCB_P.empty())
                    {
                        Wakeup_P();
                    }
                }
            }
            // ��������е���Ϣ
            cout << "��������: ";
            Print_Queue(PCB_R);
            cout << "�����ߵȴ�����: ";
            Print_Queue(PCB_P);
            cout << "�����ߵȴ����У� ";
            Print_Queue(PCB_C);
            cout << "OVER����: ";
            Print_Queue_OVER(PCB_OVER);
            cout << "_________________________________" << endl;
        }
    }
}

void Creat_Process()
{
    // ����10�����̼�����𣬴����������
    PCB pcb[10];
    for (int i = 0; i < 10; i++)
    {
        // ��������ʵ���Լ���������
        pcb[i].name = i;
        pcb[i].type = rand() % 2;
    }
    // �����̷ֱ������̾���������
    for (int i = 0; i < 10; i++)
    {
        PCB_R.push(pcb[i]);
    }
}
