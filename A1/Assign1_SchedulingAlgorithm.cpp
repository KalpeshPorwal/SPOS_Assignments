#include <bits/stdc++.h>
using namespace std;

class Process
{
    int id;
    int at;      // arrival time
    int bt, btc; // burst time and burst time copy
    int pr;
    int wt;
    int tat;

public:
    Process()
    {
        cout << "New Process entry:\n";
        cout << "Enter Process id: ";
        cin >> id;
        cout << "Enter arrival time: ";
        cin >> at;
        cout << "Enter burst time: ";
        cin >> bt;
        cout << "Enter priority of process: ";
        cin >> pr;
    }
    friend class SchedulingAlgo;
};

class SchedulingAlgo
{
    int n;
    Process *proc;

    void FCFS_WT(int wt[]);
    void SJF_WT(int wt[]);
    void PR_WT(int wt[]);
    void RR_WT(int wt[], int tat[], int comp_time[]);

public:
    // Constructor
    SchedulingAlgo(int n)
    {
        this->n = n;
        proc = new Process[n];
    }

    void FCFS_avg();
    void SJF_avg();
    void PR_avg();
    void RR_avg();
};

// void SchedulingAlgo ::FCFS_WT(int wt[])
// {
//     sort(proc, proc + n, [](Process &a, Process &b){return a.at < b.at;} );
//     wt[0] = 0;
//     for (int i = 1; i < n; i++)
//     {
//         wt[i] = (proc[i - 1].at + proc[i - 1].bt + wt[i - 1]) - proc[i].at;
//     }
// }

void SchedulingAlgo ::FCFS_WT(int wt[]){
    sort(proc, proc + n, [](Process &a, Process &b)
         { return a.at < b.at; });
    wt[0] = 0;
    int time = proc[0].bt + proc[0].at;
    int nopc = 1;
    while (nopc != n)
    {
        if(proc[nopc].at <= time ){
            time += proc[nopc].bt;
            wt[nopc] = time - proc[nopc].at - proc[nopc].bt;
            nopc++;
        }else{
            time = proc[nopc].at;
        }
    }
    
}

void SchedulingAlgo ::FCFS_avg()
{
    int wt[n];
    int tat[n];
    int sum_wt = 0;
    int sum_tat = 0;

    FCFS_WT(wt);
    // calculating TAT
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + proc[i].bt;
    }

    // AVG
    for (int i = 0; i < n; i++)
    {
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "Average wating time of FCFS scheduling algorithm is: " << sum_wt / (float)n << endl;
    cout << "Average turnaround time of FCFS scheduling algorithm is: " << sum_tat / (float)n << endl;
}

void SchedulingAlgo ::SJF_WT(int wt[])
{
    int complete = 0;
    int shortest = 0;
    bool check = false;
    int time = 0;
    int minm = INT_MAX;
    int rem_bt[n];
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = proc[i].bt;
    }

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if (proc[j].at <= time && rem_bt[j] < minm && rem_bt[j] > 0)
            {
                minm = rem_bt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false)
        {
            time++;
            continue;
        }

        time++;
        rem_bt[shortest]--;
        minm = rem_bt[shortest];

        if (minm == 0)
        {
            minm = INT_MAX;
        }

        if (rem_bt[shortest] == 0)
        {
            complete++;
            check = false;
            tat[shortest] = time - proc[shortest].at;
            wt[shortest] = tat[shortest] - proc[shortest].bt;
        }
    }
}

void SchedulingAlgo ::SJF_avg()
{
    int wt[n];
    int tat[n];
    int sum_wt = 0;
    int sum_tat = 0;

    SJF_WT(wt);
    // calculating TAT
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + proc[i].bt;
    }

    // AVG
    for (int i = 0; i < n; i++)
    {
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "Average wating time of SJF scheduling algorithm is: " << sum_wt /(float)n << endl;
    cout << "Average turnaround time of SJF scheduling algorithm is: " << sum_tat / (float)n << endl;
}

// non - premptive
void SchedulingAlgo ::PR_WT(int wt[])
{
    sort(proc, proc + n, [](Process &a, Process &b)
         { return a.at < b.at; });
    int nopc = 1;
    int time = proc[0].at + proc[0].bt;

    wt[proc[0].id - 1] = 0;
    tat[proc[0].id - 1] = proc[0].bt;
    bool flag = true;
    while (nopc != n)
    {
        if (flag)
        {
            int index = nopc;
            while (true)
            {
                if (proc[index].at <= time)
                {
                    index++;
                    if (index == n)
                    {
                        flag = false;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            sort(proc + nopc, proc + index, [](Process &a, Process &b)
                 { return a.pr < b.pr; });
        }
        if (time < proc[nopc].at)
        {
            time = proc[nopc].at;
        }
        time += proc[nopc].bt;
        wt[proc[nopc].id - 1] = time - proc[nopc].at - proc[nopc].bt;
        tat[proc[nopc].id - 1] = wt[proc[nopc].id - 1] + proc[nopc].bt;
        nopc++;
    }
}

void SchedulingAlgo ::PR_avg()
{
    int wt[n];
    int tat[n];
    int sum_wt = 0;
    int sum_tat = 0;

    PR_WT(wt);
    // calculating TAT
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + proc[i].bt;
    }

    // AVG
    for (int i = 0; i < n; i++)
    {
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "Average wating time of Priority scheduling algorithm is: " << sum_wt / (float)n << endl;
    cout << "Average turnaround time of Priority scheduling algorithm is: " <<  sum_tat / (float)n << endl;
}
/* 
Program No.     Arrival Time    Burst Time
3               0               5               
2               1               4               
4               2               2               
1               3               1               
 */
/* 
Program No.     Arrival Time    Burst Time
1               3               1               
2               1               4               
3               0               5               
4               2               2               
 */



void SchedulingAlgo ::RR_WT(int wt[], int tat[], int comp_time[])
{
    int complete = 0;
    int p = 0;
    int time = 0;
    int rem_bt[n];
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = proc[i].bt;
    }
    int quantam;
    cout << "Enter the quantam: ";
    cin >> quantam;

    sort(proc, proc + n, [](Process &a, Process &b)
         { return a.at < b.at; });

    queue<Process> q;

    time = proc[0].at;
    q.push(proc[0]);
    while (complete != n)
    {
        Process temp = q.front();
        int index = temp.id - 1;
        if (rem_bt[index] <= quantam && rem_bt[index] > 0)
        {
            time += rem_bt[index];
            rem_bt[index] = 0;
            complete++;
            q.pop();
            tat[index] = time - temp.at;
            wt[index] = tat[index] - temp.bt;
        }
        else
        {
            time += quantam;
            rem_bt[index] -= quantam;
        }

        for (int i = p + 1; i < n; i++)
        {
            if (proc[i].at <= time)
            {
                q.push(proc[i]);
                p++;
            }
            else
            {
                break;
            }
        }

        if (rem_bt[index] != 0)
        {
            q.push(temp);
            q.pop();
        }
    }
}

void SchedulingAlgo ::RR_avg()
{
    int wt[n];
    int tat[n];
    int sum_wt = 0;
    int sum_tat = 0;
    int comp_time[n];
    RR_WT(wt, tat, comp_time);
    // AVG
    for (int i = 0; i < n; i++)
    {
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "Average wating time of Roundrobin scheduling algorithm is: " << sum_wt / (float)n << endl;
    cout << "Average turnaround time of Roundrobin scheduling algorithm is: " << sum_tat / (float)n << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    SchedulingAlgo obj(n);
    obj.FCFS_avg();
    obj.SJF_avg();
    obj.PR_avg();
    obj.RR_avg();
    return 0;
}