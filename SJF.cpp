#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<vector<int>> at_bt = {{6,24},{0,3},{3,3}};
    vector<int> ct(at_bt.size());
    vector<int> tat(at_bt.size());
    vector<int> wt(at_bt.size());
    double avg_tat = 0;
    double avg_wt = 0;
    int n = at_bt.size();
    vector<bool> completed(n, false);
    int time = 0;
    int count = 0;

    while(count < n)
    {
        int index = -1;
        int mn = INT_MAX;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && at_bt[i][0] <= time)
            {
                if(at_bt[i][1] < mn)
                {
                    mn = at_bt[i][1];
                    index = i;
                }
            }
        }
        if(index == -1)
        {
            time++;
            continue;
        }
        time += at_bt[index][1];
        ct[index] = time;
        tat[index] = ct[index] - at_bt[index][0];
        wt[index] = tat[index] - at_bt[index][1];

        avg_tat += tat[index];
        avg_wt += wt[index];

        completed[index] = true;
        count++;
    }
    avg_tat /= n;
    avg_wt /= n;
    cout << "Avg. TAT = " << avg_tat << endl;
    cout << "Avg WT = " << avg_wt << endl;
    return 0;
}
