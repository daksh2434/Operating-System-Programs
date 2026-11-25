#include<bits\stdc++.h>
#include<vector>
using namespace std;
int main(){
    vector<vector<int>> at_bt = {{6,24},{0,3},{3,3}};
    vector<int> ct(at_bt.size());
    vector<int> tat(at_bt.size());
    vector<int> wt(at_bt.size());
    double avg_tat = 0;
    double avg_wt = 0;
    sort(at_bt.begin(),at_bt.end());
    int time = at_bt[0][0];
    for(int i=0;i<at_bt.size();i++)
    {
        if(time < at_bt[i][0])
            time = at_bt[i][0];
        time += at_bt[i][1];
        ct[i] = time;
        tat[i] = ct[i] - at_bt[i][0];
        wt[i] = tat[i] - at_bt[i][1];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= tat.size();
    avg_wt /= wt.size();
    cout << "Avg. TAT = " << avg_tat << endl;
    cout << "Avg WT = " << avg_wt << endl;
return 0;
}
