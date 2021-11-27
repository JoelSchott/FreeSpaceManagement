#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "space_algorithms.h"
#include "memory_space.h"
#include "experiment.h"
#include "processes.h"

using namespace std;

int main(){
  const int NUM_SIZE_TRIALS = 3;
  const int NUM_TIME_TRIALS = 2;
  const int NUM_PROCESS_TRIALS = 3;
  const int NUM_RAND_SEED_TRIALS = 5;
  const int MEMORY_SPACE_SIZE = 100;
  const string OUT_FILE = "experiment_results.csv";
  
  int processSizeAvg [NUM_SIZE_TRIALS] = {10, 15, 15};
  int processSizeStd [NUM_SIZE_TRIALS] = {2, 2, 10};
  
  int processTimeAvg [NUM_TIME_TRIALS] = {10 , 15};
  int processTimeStd [NUM_TIME_TRIALS] = {2, 10};
  
  int numProcesses [NUM_PROCESS_TRIALS] = {50, 50, 50};
  int arrivalEndingTime [NUM_PROCESS_TRIALS] = {20, 40, 60};

  ofstream writer(OUT_FILE);
  // write the header
  writer << "Algorithm,Average Process Size,Standard Deviation Process Size,Average Process Time,"
         << "Standard Deviation Process Time,Number of Processes,Size of Process Arrival Window,"
         << "Random Seed,Total Hole Checks,Number of Failed Allocations,Total Wait Time,Average Usage\n";
  for (int sizeTrial = 0; sizeTrial < NUM_SIZE_TRIALS; sizeTrial++)
  {
    for (int timeTrial = 0; timeTrial < NUM_TIME_TRIALS; timeTrial++)
    {
      for (int processTrial = 0; processTrial < NUM_PROCESS_TRIALS; processTrial++)
      {
        for (int seedTrial = 0; seedTrial < NUM_RAND_SEED_TRIALS; seedTrial++)
        {
          vector<Process> processes = createProcesses(numProcesses[processTrial],
                                                      processSizeAvg[sizeTrial],
                                                      processSizeStd[sizeTrial],
                                                      processTimeAvg[timeTrial],
                                                      processTimeStd[timeTrial],
                                                      0, arrivalEndingTime[processTrial],
                                                      seedTrial);
          BestFit bf;
          WorstFit wf;
          NextFit nf;
          FirstFit ff;
          vector<SpaceAlgorithm> algs = {bf, wf, nf, ff};
          string alg_names [4] = {"Best Fit", "Worst Fit", "Next Fit", "First fit"};
          for (int a = 0; a < 4; a++)
          {
            SpaceAlgorithm * spaceAlg = &algs[a];
            ExperimentResult result = runExperiment(processes, spaceAlg, MEMORY_SPACE_SIZE);
            writer << alg_names[a] << "," << processSizeAvg[sizeTrial] << "," << processSizeStd[sizeTrial] << ","
                   << processTimeAvg[timeTrial] << "," << processTimeStd[timeTrial] << "," << numProcesses[processTrial] << ","
                   << arrivalEndingTime[processTrial] << "," << seedTrial << "," << result.getTotalHoleChecks() << ","
                   << result.getNumFailedAllocations() << "," << result.getTotalWaitTime() << "," << result.getAverageUsage() << "\n";
          }
        }
      }
    }
  }
  writer.close();
  return 0;
}
