#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <queue>
#include "processes.h"
#include "space_algorithms.h"
#include "memory_space.h"
#include <iostream>

using namespace std;

class ExperimentResult
{
  private:
    int totalHoleChecks;
    int numFailedAllocations;
    float totalWaitTime;
    float averageUsage;

  public:
    ExperimentResult(int holeChecks, int failedAllocs, float waitTime, float avgUsage): 
      totalHoleChecks(holeChecks), numFailedAllocations(failedAllocs), totalWaitTime(waitTime), averageUsage(avgUsage) {}

    int getTotalHoleChecks() {return totalHoleChecks;}
    int getNumFailedAllocations() {return numFailedAllocations;}
    float getTotalWaitTime() {return totalWaitTime;}
    float getAverageUsage() {return averageUsage;}
};

ExperimentResult runExperiment(vector<Process> & processes, SpaceAlgorithm * a, const int memorySize);

#endif