#include "common.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // --- 1. SETUP ---
    srand(time(0));

    int numStages, numJobs;
    vector<int> priorities, arrivalTimes;
    vector<vector<int>> execTime;

    generateRandomInput(numStages, numJobs, priorities, execTime, arrivalTimes);


    // --- 2. DISPLAY GENERATED INPUT ---
    cout << "--- Generated Pipeline Data ---\n";
    cout << "Number of Stages: " << numStages << "\n";
    cout << "Number of Jobs:   " << numJobs << "\n\n";

    cout << "-----------------------------------------------------\n";
    cout << "Job\tArrival\tPriority\tExecution Times\n";
    cout << "-----------------------------------------------------\n";
    for (int i = 0; i < numJobs; ++i) {
        cout << i << "\t" << arrivalTimes[i] << "\t" << priorities[i] << "\t\t[ ";
        for (int time : execTime[i]) {
            cout << time << " ";
        }
        cout << "]\n";
    }
    cout << "-----------------------------------------------------\n\n";
    cout << "Enter any key to continue...  y for yes n for no \n";
    char c;
    cin>>c;
    if(c=='n'){
            return 0;
    }
    // --- 3. COMPUTE AND DISPLAY DELAYS ---
    // Change this value to test different jobs
    int targetJobIdx = 0; 

    cout << "--- Analysis for Job " << targetJobIdx 
         << " (Arrival Time: " << arrivalTimes[targetJobIdx] << ") ---\n\n";

    // --- Non-Preemptive Case ---
    cout << "## Non-Preemptive Scheduling ##\n";
    int np_bound = compute_non_preemptive_Delay_bound(targetJobIdx, priorities, execTime);
    cout << "Upper Bound Delay      : " << np_bound << "\n";

    JobSchedule np_actual = compute_Actual_non_preemptive_Time(targetJobIdx, priorities, execTime, arrivalTimes);
    cout << "Actual Simulated Delay : " << np_actual.totalDelay << "\n\n";

    // --- Preemptive Case ---
    cout << "## Preemptive Scheduling ##\n";
    // Assuming the function signature for the preemptive bound is as follows:
    int p_bound = compute_preemptive_delay_Bound(targetJobIdx, priorities, execTime, arrivalTimes);
    cout << "Upper Bound Delay      : " << p_bound << "\n";

    // Assuming the function signature for the actual preemptive time is as follows:
    JobSchedule p_actual = compute_Actual_Preemptive_Time(targetJobIdx, priorities, execTime, arrivalTimes);
    cout << "Actual Simulated Delay : " << p_actual.totalDelay << "\n";

    return 0;
}