#include "common.h"
#include <cstdlib>  // for rand()

void generateRandomInput(int& numStages, int& numJobs,
                         vector<int>& priorities,
                         vector<vector<int>>& execTime,
                         vector<int>& arrivalTimes)
{
    // 1. Generate random numbers for stages and jobs
    numStages = rand() % 4 + 2; // Random stages between 2 and 5
    numJobs = rand() % 6 + 5;   // Random jobs between 5 and 10

    // 2. Resize and populate the vectors based on the new numJobs
    priorities.assign(numJobs, 0);
    arrivalTimes.assign(numJobs, 0);
    execTime.assign(numJobs, vector<int>(numStages));

    // 3. Fill vectors with random data
    for (int i = 0; i < numJobs; i++) {
        priorities[i] = rand() % 10 + 1;      // Priority between 1 and 10
        arrivalTimes[i] = rand() % 15;        // Arrival time between 0 and 14

        for (int j = 0; j < numStages; j++) {
            execTime[i][j] = rand() % 10 + 1; // Execution time between 1 and 10
        }
    }
}

