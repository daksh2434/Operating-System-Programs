#include <iostream>
using namespace std;
#define P 5
#define R 3
int available[R];
int maximum[P][R];
int allocation[P][R];
int need[P][R];
void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}
int isSafe(int safeSeq[]) {
    int work[R], finish[P] = {0};
    for (int j = 0; j < R; j++)
        work[j] = available[j];
    int count = 0;
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j]) break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }
    return 1;
}
int requestResources(int pid, int request[]) {
    for (int j = 0; j < R; j++) {
        if (request[j] > need[pid][j]) {
            cout << "Error: Maximum claim exceeded." << endl;
            return 0;
        }
        if (request[j] > available[j]) {
            cout << "Request denied: Not enough resources." << endl;
            return 0;
        }
    }
    for (int j = 0; j < R; j++) {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }
    int safeSeq[P];
    if (isSafe(safeSeq)) {
        cout << "Request can be granted safely." << endl;
        return 1;
    }
    else {
        for (int j = 0; j < R; j++) {
            available[j] += request[j];
            allocation[pid][j] -= request[j];
            need[pid][j] += request[j];
        }
        cout << "Request denied: Unsafe state." << endl;
        return 0;
    }
}
int main() {
    cout << "Enter available resources: ";
    for (int j = 0; j < R; j++)
        cin >> available[j];
    cout << "Enter Maximum matrix:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> maximum[i][j];
    cout << "Enter Allocation matrix:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    calculateNeed();
    int safeSeq[P];
    if (isSafe(safeSeq)) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < P; i++)
            cout << "P" << safeSeq[i] << " ";
        cout << endl;
    }
    else {
        cout << "System is in an UNSAFE state." << endl;
    }
    int pid, request[R];
    cout << "\nEnter process number: ";
    cin >> pid;
    printf("\n");
    if (pid < 0 || pid >= P) {
        cout << "Invalid process number." << endl;
        return 0;
    }
    cout << "Enter request vector: ";
    for (int j = 0; j < R; j++)
        cin >> request[j];
    requestResources(pid, request);
    return 0;
}
