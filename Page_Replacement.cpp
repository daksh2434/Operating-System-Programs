#include <iostream>
using namespace std;
#define MAXFRAMES 10
#define MAXPAGES 50
int isPresent(int frames[], int nf, int page) {
    for(int i=0; i<nf; i++)
        if(frames[i]==page) return 1;
    return 0;
}
void fifo(int ref[], int n, int nf) {
    int frames[MAXFRAMES], front=0, faults=0;
    for(int i=0; i<nf; i++) frames[i]=-1;
    for(int i=0; i<n; i++) {
        if(!isPresent(frames,nf,ref[i])) {
            frames[front]=ref[i];
            front=(front+1)%nf;
            faults++;
        }
    }
    cout<<"FIFO Page Faults = "<<faults<<endl;
}
void lru(int ref[], int n, int nf) {
    int frames[MAXFRAMES], lastUsed[MAXFRAMES];
    int filled=0, faults=0;
    for(int i=0; i<nf; i++) frames[i]=-1;
    for(int i=0; i<n; i++) {
        int pos=-1;
        for(int j=0; j<nf; j++)
            if(frames[j]==ref[i]) {
                pos=j;
                break;
            }
        if(pos==-1) {
            faults++;
            if(filled<nf) {
                frames[filled]=ref[i];
                lastUsed[filled++]=i;
            } else {
                int idx=0;
                for(int j=1; j<nf; j++)
                    if(lastUsed[j]<lastUsed[idx]) idx=j;

                frames[idx]=ref[i];
                lastUsed[idx]=i;
            }
        } else {
            lastUsed[pos]=i;
        }
    }
    cout<<"LRU Page Faults = "<<faults<<endl;
}
void optimal(int ref[], int n, int nf) {
    int frames[MAXFRAMES], filled=0, faults=0;
    for(int i=0; i<nf; i++) frames[i]=-1;
    for(int i=0; i<n; i++) {
        if(isPresent(frames,filled,ref[i])) continue;
        faults++;
        if(filled<nf) {
            frames[filled++]=ref[i];
            continue;
        }
        int idx=-1, farthest=-1;
        for(int j=0; j<nf; j++) {
            int k;
            for(k=i+1; k<n; k++)
                if(frames[j]==ref[k]) break;
            if(k==n) {
                idx=j;
                break;
            }
            if(k>farthest) {
                farthest=k;
                idx=j;
            }
        }
        frames[idx]=ref[i];
    }
    cout<<"Optimal Page Faults = "<<faults<<endl;
}
int main() {
    int ref[MAXPAGES], n, nf;
    cout<<"Enter number of pages in reference string: ";
    cin>>n;
    cout<<"Enter the reference string: ";
    for(int i=0; i<n; i++) cin>>ref[i];
    cout<<"Enter number of frames: ";
    cin>>nf;
    if(n<1 || n>MAXPAGES || nf<1 || nf>MAXFRAMES) {
        cout<<"Invalid input";
        return 0;
    }
    fifo(ref,n,nf);
    lru(ref,n,nf);
    optimal(ref,n,nf);
    return 0;
}
