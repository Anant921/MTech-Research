#include "common.h"

JobSchedule compute_Actual_non_preemptive_Time(
    int jobIdx,
    const vector<int>& priorities,
    const vector<vector<int>>& execTime,
    const vector<int>& arrivalTimes)
{
    int numJobs = execTime.size();
    int numStages = execTime[0].size();

    // Create order of jobs based on priority (lower = higher priority)
    vector<int> jobOrder(numJobs);
    iota(jobOrder.begin(), jobOrder.end(), 0);

    sort(jobOrder.begin(), jobOrder.end(),
         [&](int a, int b) {
             return priorities[a] < priorities[b];
         });


    // Track stage availability
    vector<int> stageFreeTime(numStages, 0);

    // Track start/finish times for all jobs
    vector<vector<int>> start(numJobs, vector<int>(numStages, 0));
    vector<vector<int>> finish(numJobs, vector<int>(numStages, 0));

    // Process jobs in priority order
    for (int job : jobOrder) {
        for (int stage = 0; stage < numStages; stage++) {
            int prevStageFinish = (stage > 0) ? finish[job][stage - 1] : arrivalTimes[job];

            // Start when job has arrived, previous stage done, and stage is free
            start[job][stage] = max({arrivalTimes[job], prevStageFinish, stageFreeTime[stage]});
            finish[job][stage] = start[job][stage] + execTime[job][stage];

            // Update when stage will be free
            stageFreeTime[stage] = finish[job][stage];
        }
    }

    JobSchedule schedule;
    schedule.startTimes = start[jobIdx];
    schedule.finishTimes = finish[jobIdx];
    schedule.totalDelay = finish[jobIdx][numStages - 1] - arrivalTimes[jobIdx];
    return schedule;
}
