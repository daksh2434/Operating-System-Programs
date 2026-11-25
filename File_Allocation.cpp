#include <iostream>
using namespace std;
#define MAXBLOCKS 30
int disk[MAXBLOCKS];
void resetDisk() {
    for(int i=0;i<MAXBLOCKS;i++) disk[i]=0;
}
void contiguousAllocation() {
    int nf;
    resetDisk();
    cout<<"\n--- Contiguous Allocation ---\n";
    cout<<"Enter number of files: ";
    cin>>nf;
    for(int f=0;f<nf;f++) {
        int start,len,ok=1;
        cout<<"File "<<f+1<<" - starting block, length: ";
        cin>>start>>len;
        for(int i=start;i<start+len;i++)
            if(i<0||i>=MAXBLOCKS||disk[i]) {ok=0;break;}
        if(!ok) {
            cout<<"Allocation failed\n";
            continue;
        }
        for(int i=start;i<start+len;i++) disk[i]=1;
        cout<<"File "<<f+1<<" allocated blocks "<<start<<" to "<<start+len-1<<endl;
    }
}
void linkedAllocation() {
    int nf;
    resetDisk();
    cout<<"\n--- Linked Allocation ---\n";
    cout<<"Enter number of files: ";
    cin>>nf;
    for(int f=0;f<nf;f++) {
        int len,count=0;
        cout<<"File "<<f+1<<" - number of blocks: ";
        cin>>len;
        cout<<"File "<<f+1<<" allocated blocks: ";
        for(int i=0;i<MAXBLOCKS&&count<len;i++) {
            if(!disk[i]) {
                disk[i]=1;
                cout<<i<<" -> ";
                count++;
            }
        }
        cout<<"NULL\n";
        if(count<len) cout<<"Warning: Disk full\n";
    }
}
void indexedAllocation() {
    int nf;
    resetDisk();
    cout<<"\n--- Indexed Allocation ---\n";
    cout<<"Enter number of files: ";
    cin>>nf;
    for(int f=0;f<nf;f++) {
        int len,count=0,indexBlock=-1;
        cout<<"File "<<f+1<<" - number of data blocks needed: ";
        cin>>len;
        for(int i=0;i<MAXBLOCKS;i++) {
            if(!disk[i]) {
                indexBlock=i;
                disk[i]=1;
                break;
            }
        }
        cout<<"File "<<f+1<<" - Index block: "<<indexBlock<<", Data blocks: ";
        for(int i=0;i<MAXBLOCKS&&count<len;i++) {
            if(!disk[i]) {
                disk[i]=1;
                cout<<i<<" ";
                count++;
            }
        }
        cout<<endl;
        if(indexBlock==-1||count<len) cout<<"Warning: Allocation incomplete\n";
    }
}
int main() {
    int choice;
    cout<<"Menu:\n1. Contiguous Allocation\n2. Linked Allocation\n3. Indexed Allocation\nEnter choice: ";
    cin>>choice;
    switch(choice) {
        case 1: contiguousAllocation(); break;
        case 2: linkedAllocation(); break;
        case 3: indexedAllocation(); break;
        default: cout<<"Invalid choice\n";
    }
    return 0;
}
