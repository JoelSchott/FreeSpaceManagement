#include <iostream>
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
  

  int processSizeAvg [NUM_SIZE_TRIALS] = {10, 15, 15};
  int processSizeStd [NUM_SIZE_TRIALS] = {2, 2, 10};
  
  int processTimeAvg [NUM_TIME_TRIALS] = {10 , 15};
  int processTimeStd [NUM_TIME_TRIALS] = {2, 10};
  
  int numProcesses [NUM_PROCESS_TRIALS] = {50, 50, 50};
  int arrivalEndingTime [NUM_PROCESS_TRIALS] = {20, 40, 60};


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
          BestFit bestFit;
          SpaceAlgorithm * bf = &bestFit;
          ExperimentResult bestFitResult = runExperiment(processes, bf, MEMORY_SPACE_SIZE);
          NextFit nextFit;
          SpaceAlgorithm * nf = &nextFit;
          ExperimentResult nextFitResult = runExperiment(processes, nf, MEMORY_SPACE_SIZE);
          WorstFit worstFit;
          SpaceAlgorithm * wf = &worstFit;
          ExperimentResult worstFitResult = runExperiment(processes, wf, MEMORY_SPACE_SIZE);
          FirstFit firstFit;
          SpaceAlgorithm * ff = &firstFit;
          ExperimentResult firtFitResult = runExperiment(processes, ff, MEMORY_SPACE_SIZE);

          // write these results to a csv file with columns for parameters and results
        }
      }
    }
  }
  return 0;
}
