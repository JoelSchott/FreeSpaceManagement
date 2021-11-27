#ifndef PROCESSES_H
#define PROCESSES_H

#include <vector>
#include <random>

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
    float allocTime;
    int space;

  public:
    Process(const float startTime, const float duration, const int spaceNeeded): start(startTime), time(duration), space(spaceNeeded) {}

    float getStartTime() const {return start;}
    float getAllocTime() const {return allocTime;}
    float getDuration() const {return time;}
    int getSpaceNeeded() const {return space;}

    void setAllocTime(const float t){allocTime = t;}
};


/**
 * Creates the array of processes with the given parameters. The size of the processes 
 * and the duration of the processes will follow normal distributions.
 * The start time of the processes will follow a uniform distribution. 
 * The random seed can be used to make the exact same processes given the same parameters.
 * 
 * @return the processes generated using the parameters
 */
vector<Process> createProcesses(const int nProcesses, const float avgProcessSize, const float stdProcessSize,
                                const float avgDuration, const float stdDuration,
                                const float earliestTime, const float latestTime, const int randomSeed);

#endif