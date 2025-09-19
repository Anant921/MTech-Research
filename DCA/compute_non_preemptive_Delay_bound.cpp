#include "common.h"
#include <numeric> // Required for std::accumulate if used, but max_element is in <algorithm>

int compute_non_preemptive_Delay_bound(
    int jobIdx,
    const vector<int>& priorities,
    const vector<vector<int>>& execTime)
{
    // Basic pipeline parameters
    int numJobs = execTime.size();
    if (numJobs == 0) return 0;
    int numStages = execTime[0].size();

    // The job whose delay we are bounding is J1
    int J1_priority = priorities[jobIdx];

    // --- Step 1: Identify the job sets based on the paper's definitions ---
    // S_bar (S̄): Set of jobs with higher priority than J1, INCLUDING J1 itself.
    // S_lower (S̲): Set of jobs with lower priority than J1.
    vector<int> setS_bar;
    vector<int> setS_lower;

    setS_bar.push_back(jobIdx); // S̄ always includes J1

    for (int i = 0; i < numJobs; i++) {
        if (i == jobIdx) continue;

        if (priorities[i] < J1_priority) {
            setS_bar.push_back(i); // Higher priority jobs
        } else if (priorities[i] > J1_priority) {
            setS_lower.push_back(i); // Lower priority jobs
        }
        // Note: Jobs with equal priority are not explicitly defined, but typically
        // a tie-breaker (like FIFO) would place them in S̄. Assuming no equal priorities for simplicity.
    }

    // --- Step 2: Calculate the three terms of the formula ---
    // Delay(J_1) <= Term 1 + Term 2 + Term 3

    // Term 1: Σ (C_i,max1) for all jobs J_i in S̄
    int term1 = 0;
    for (int job : setS_bar) {
        int C_imax1 = 0;
        for (int stage = 0; stage < numStages; ++stage) {
            C_imax1 = max(C_imax1, execTime[job][stage]);
        }
        term1 += C_imax1;
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

    // Term 3: Σ (max(C_i,j)) over stages j=1 to N, for all jobs J_i in S̲
    int term3 = 0;
    for (int stage = 0; stage < numStages; stage++) { // Loop from j=1 to N
        int max_Cij_in_S_lower = 0;
        for (int job : setS_lower) {
            max_Cij_in_S_lower = max(max_Cij_in_S_lower, execTime[job][stage]);
        }
        term3 += max_Cij_in_S_lower;
    }

    return term1 + term2 + term3;
}



// this correctly calculates the delay bound for a given job in a non-preemptive scheduling scenario.