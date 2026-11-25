#include <iostream>
using namespace std;
#define MAX 20
struct Process {
    int pid, at, bt, pr, ct, tat, wt, rem;
};
void display(Process p[], int n) {
    float twt = 0, ttat = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t"
             << p[i].bt << "\t" << p[i].ct << "\t"
             << p[i].tat << "\t" << p[i].wt << endl;
        twt += p[i].wt;
        ttat += p[i].tat;
    }
    cout << "Average Waiting Time = " << twt / n << endl;
    cout << "Average Turnaround Time = " << ttat / n << endl;
}
void calculate(Process &p, int time) {
    p.ct = time;
    p.tat = p.ct - p.at;
    p.wt = p.tat - p.bt;
}
void fcfs(Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        calculate(p[i], time);
    }
    display(p, n);
}
void sjf(Process p[], int n) {
    int time = 0, done[MAX] = {0};
    for (int c = 0; c < n; c++) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= time &&
                (idx == -1 || p[i].bt < p[idx].bt))
                idx = i;
        if (idx == -1) { time++; c--; continue; }
        time += p[idx].bt;
        calculate(p[idx], time);
        done[idx] = 1;
    }
    display(p, n);
}
void priority(Process p[], int n) {
    int time = 0, done[MAX] = {0};
    for (int c = 0; c < n; c++) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= time &&
                (idx == -1 || p[i].pr < p[idx].pr))
                idx = i;

        if (idx == -1) { time++; c--; continue; }
        time += p[idx].bt;
        calculate(p[idx], time);
        done[idx] = 1;
    }
    display(p, n);
}
void roundRobin(Process p[], int n, int q) {
    int time = 0, completed = 0, queue[1000];
    int front = 0, rear = 0, added[MAX] = {0};
    for (int i = 0; i < n; i++) p[i].rem = p[i].bt;
    while (completed < n) {
        for (int i = 0; i < n; i++)
            if (!added[i] && p[i].at <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        if (front == rear) { time++; continue; }
        int i = queue[front++];
        int t = min(q, p[i].rem);
        time += t;
        p[i].rem -= t;
        for (int j = 0; j < n; j++)
            if (!added[j] && p[j].at <= time) {
                queue[rear++] = j;
                added[j] = 1;
            }
        if (p[i].rem > 0)
            queue[rear++] = i;
        else {
            calculate(p[i], time);
            completed++;
        }
    }
    display(p, n);
}

int main() {
    Process p[MAX];
    int n, choice, q;
    cout << "Enter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "Enter AT, BT, Priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }
    cout << "\n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin";
    cout << "\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: fcfs(p, n); break;
        case 2: sjf(p, n); break;
        case 3: priority(p, n); break;
        case 4:
            cout << "Enter time quantum: ";
            cin >> q;
            if (q > 0) roundRobin(p, n, q);
            else cout << "Invalid quantum";
            break;
        default: cout << "Invalid choice";
    }
    return 0;
}
