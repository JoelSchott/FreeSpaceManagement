#ifndef PROCESSES_H
#define PROCESSES_H

#include <vector>

using namespace std;

/**
 * Represents a process that arrives at a certain time, lasts a certain time, and requires
 * a set amount of memory for the entire time that it exists
 */
class Process
{
  private:
    float start;
    float time;
    int space;

  public:
    Process(const float startTime, const float duration, const int spaceNeeded): start(startTime), time(duration), space(spaceNeeded) {}

    float getStartTime() {return start;}
    float getDuration() {return time;}
    int getSpaceNeeded() {return space;}
};

/**
 * Can create an array of processes given parameters about the qualities of the processes to create.
 * This creation can be seeded such that it creates the same array of processes given the same seed
 * and the same parameters.
 */
class ProcessCreator
{
  private:
    int n;
    float avgSize;
    float stdSize;
    float startTime;
    float endTime;
    int seed;

  public:
    ProcessCreator(const int nProcesses, const float avgProcessSize, const float stdProcessSize,
                   const float earliestTime, const float latestTime, const int random_seed):
      n(nProcesses), avgSize(avgProcessSize), stdSize(stdProcessSize), 
      startTime(earliestTime), endTime(latestTime), seed(random_seed) {}

    /**
     * Creates the array of processes with the given parameters. The size of the processes 
     * will follow a normal distribution and the start time of the processes will follow
     * a uniform distribution
     * 
     * @return the processes generated using the parameters
     */
    vector<Process> createProcesses() const;
};

#endif