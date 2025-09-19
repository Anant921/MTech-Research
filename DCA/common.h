#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>

using namespace std;

struct JobSchedule {
  vector<int> startTimes;
  vector<int> finishTimes;
  int totalDelay;
};

JobSchedule compute_Actual_Preemptive_Time(int jobIdx,
                                           const vector<int> &priorities,
                                           const vector<vector<int>> &execTime,
                                           const vector<int> &arrivalTimes);

int compute_preemptive_delay_Bound(
    int jobIdx, 
    const vector<int>& priorities, 
    const vector<vector<int>>& execTime, 
    const vector<int>& arrivalTimes
);

JobSchedule compute_Actual_non_preemptive_Time(int jobIdx, const vector<int> &priorities,
                                   const vector<vector<int>> &execTime,
                                   const vector<int> &arrivalTimes);

int compute_non_preemptive_Delay_bound(int jobIdx,
                                       const vector<int> &priorities,
                                       const vector<vector<int>> &execTime);

void generateRandomInput(int &numStages, int &numJobs, vector<int> &priorities,
                         vector<vector<int>> &execTime,
                         vector<int> &arrivalTimes);

#endif
