#include "processes.h"

vector<Process> createProcesses(const int nProcesses, const float avgProcessSize, const float stdProcessSize,
                                const float avgDuration, const float stdDuration,
                                const float earliestTime, const float latestTime, const int randomSeed)
{
  srand(randomSeed);
  default_random_engine generator;
  normal_distribution<float> processDistribution(avgProcessSize, stdProcessSize);
  normal_distribution<float> durationDistribution(avgDuration, stdDuration);

  vector<Process> processes;
  for (int i = 0; i < nProcesses; i++)
  {
    int size = static_cast<int>(processDistribution(generator) + 0.5);
    float duration = durationDistribution(generator);

    float timeProportion = rand() / static_cast<float>(RAND_MAX);
    float time = timeProportion * (latestTime - earliestTime) + earliestTime;

    processes.push_back(Process(time, duration, size));
  }

  return processes;
}