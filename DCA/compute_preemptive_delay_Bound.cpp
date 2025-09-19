#include "common.h"
#include <vector>
#include <algorithm> // Required for std::sort

int compute_preemptive_delay_Bound(
    int jobIdx, 
    const vector<int>& priorities, 
    const vector<vector<int>>& execTime, 
    const vector<int>& arrivalTimes)
{
    // Basic pipeline parameters
    int numJobs = execTime.size();
    if (numJobs == 0) return 0;
    int numStages = execTime[0].size();

    // The job whose delay we are bounding is J1
    int J1_priority = priorities[jobIdx];
    int J1_arrival = arrivalTimes[jobIdx];

    // --- Step 1: Identify the job set S_bar (S̄) ---
    // S_bar: Set of jobs with higher priority than J1, INCLUDING J1 itself.
    vector<int> setS_bar;
    setS_bar.push_back(jobIdx); // S̄ always includes J1

    for (int i = 0; i < numJobs; i++) {
        if (i == jobIdx) continue;
        if (priorities[i] < J1_priority) {
            setS_bar.push_back(i); // Higher priority jobs
        }
    }

    // --- Step 2: Calculate the two terms of the preemptive formula ---
    // Delay(J_1) <= Term 1 + Term 2

    // Term 1: Σ (C_eq_i) for all jobs J_i in S̄
    int term1 = 0;
    for (int job : setS_bar) {
        // Find C_i,max1 and C_i,max2 for the current job
        vector<int> jobExecTimes = execTime[job];
        sort(jobExecTimes.rbegin(), jobExecTimes.rend()); // Sort descending

        int C_max1 = jobExecTimes.size() > 0 ? jobExecTimes[0] : 0;
        int C_max2 = jobExecTimes.size() > 1 ? jobExecTimes[1] : 0;

        // Calculate C_eq_i based on arrival times
        int C_eq_i = 0;
        if (J1_arrival < arrivalTimes[job]) {
            // J1 arrives before Ji
            C_eq_i = C_max1 + C_max2;
        } else {
            // J1 arrives at the same time or after Ji
            C_eq_i = C_max1;
        }
        term1 += C_eq_i;
    }

    // Term 2: Σ (max(C_i,j)) over stages j=1 to N-1, for all jobs J_i in S̄
    int term2 = 0;
    for (int stage = 0; stage < numStages - 1; stage++) { // Loop from j=1 to N-1
        int max_Cij_in_S_bar = 0;
        for (int job : setS_bar) {
            max_Cij_in_S_bar = max(max_Cij_in_S_bar, execTime[job][stage]);
        }
        term2 += max_Cij_in_S_bar;
    }

    return term1 + term2;
}