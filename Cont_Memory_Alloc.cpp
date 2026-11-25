#include <iostream>
using namespace std;
#define MAX 20
void display(int allocation[], int psize[], int pn, string name)
{
    cout << "\n--- " << name << " ---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < pn; i++) {
        cout << "P" << i + 1 << "\t" << psize[i] << "\t";
        if (allocation[i] != -1)
            cout << "B" << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}
void allocate(int bsize[], int bn, int psize[], int pn, int type) {
    int block[MAX], allocation[MAX];
    for (int i = 0; i < bn; i++)
        block[i] = bsize[i];
    for (int i = 0; i < pn; i++) {
        allocation[i] = -1;
        int idx = -1;
        for (int j = 0; j < bn; j++) {
            if (block[j] >= psize[i]) {
                if (type == 1) {
                    idx = j;
                    break;
                }
                if (idx == -1 ||
                    (type == 2 && block[j] < block[idx]) ||
                    (type == 3 && block[j] > block[idx]))
                    idx = j;
            }
        }
        if (idx != -1) {
            allocation[i] = idx;
            block[idx] -= psize[i];
        }
    }
    if (type == 1) display(allocation, psize, pn, "First Fit");
    if (type == 2) display(allocation, psize, pn, "Best Fit");
    if (type == 3) display(allocation, psize, pn, "Worst Fit");
}
int main() {
    int bn, pn, bsize[MAX], psize[MAX];
    cout << "Enter number of memory blocks: ";
    cin >> bn;
    cout << "Enter block sizes: ";
    for (int i = 0; i < bn; i++)
        cin >> bsize[i];
    cout << "Enter number of processes: ";
    cin >> pn;
    cout << "Enter process sizes: ";
    for (int i = 0; i < pn; i++)
        cin >> psize[i];
    allocate(bsize, bn, psize, pn, 1);
    allocate(bsize, bn, psize, pn, 2);
    allocate(bsize, bn, psize, pn, 3);
    return 0;
}
