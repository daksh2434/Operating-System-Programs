#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 50
int diff(int a, int b) {
    return abs(a-b);
}
void fcfs(int req[], int n, int head) {
    int total=0, cur=head;

    for(int i=0; i<n; i++) {
        total+=diff(cur,req[i]);
        cur=req[i];
    }
    cout<<"FCFS Total head movement = "<<total<<endl;
}
void sstf(int req[], int n, int head) {
    int visited[MAX]={0}, total=0, cur=head;
    for(int c=0; c<n; c++) {
        int idx=-1, best=999999;
        for(int i=0; i<n; i++) {
            if(!visited[i] && diff(cur,req[i])<best) {
                best=diff(cur,req[i]);
                idx=i;
            }
        }
        visited[idx]=1;
        total+=best;
        cur=req[idx];
    }
    cout<<"SSTF Total head movement = "<<total<<endl;
}
void scan(int req[], int n, int head, int diskSize) {
    int arr[MAX+1];
    for(int i=0; i<n; i++) arr[i]=req[i];
    arr[n]=head;
    sort(arr,arr+n+1);
    int idx=0;
    for(int i=0; i<=n; i++)
        if(arr[i]==head) { idx=i; break; }
    int total=0, cur=head;
    for(int i=idx+1; i<=n; i++) {
        total+=diff(cur,arr[i]);
        cur=arr[i];
    }
    total+=diff(cur,diskSize-1);
    cur=diskSize-1;
    for(int i=idx-1; i>=0; i--) {
        total+=diff(cur,arr[i]);
        cur=arr[i];
    }
    total += cur;
    cout<<"SCAN Total head movement = "<<total<<endl;
}
void cscan(int req[], int n, int head, int diskSize) {
    int arr[MAX+1];
    for(int i=0; i<n; i++) arr[i]=req[i];
    arr[n]=head;
    sort(arr,arr+n+1);
    int idx=0;
    for(int i=0; i<=n; i++)
        if(arr[i]==head) { idx=i; break; }
    int total=0, cur=head;
    for(int i=idx+1; i<=n; i++) {
        total+=diff(cur,arr[i]);
        cur=arr[i];
    }
    total+=diff(cur,diskSize-1);
    total+=diskSize-1;
    cur=0;
    for(int i=0; i<idx; i++) {
        total+=diff(cur,arr[i]);
        cur=arr[i];
    }
    cout<<"C-SCAN Total head movement = "<<total<<endl;
}
int main() {
    int n, head, diskSize, req[MAX];
    cout<<"Enter number of requests: ";
    cin>>n;
    if(n<1 || n>MAX) {
        cout<<"Invalid number of requests";
        return 0;
    }
    cout<<"Enter the requests: ";
    for(int i=0; i<n; i++) cin>>req[i];
    cout<<"Enter initial head position: ";
    cin>>head;
    cout<<"Enter disk size (max cylinder + 1): ";
    cin>>diskSize;
    if(diskSize<=0 || head<0 || head>=diskSize) {
        cout<<"Invalid disk size or head position";
        return 0;
    }
    for(int i=0; i<n; i++) {
        if(req[i]<0 || req[i]>=diskSize) {
            cout<<"Invalid request position";
            return 0;
        }
    }
    fcfs(req,n,head);
    sstf(req,n,head);
    scan(req,n,head,diskSize);
    cscan(req,n,head,diskSize);
    return 0;
}
