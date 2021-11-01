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
    int start;
    int time;
    int space;

  public:
    Process(const int startTime, const int duration, const int spaceNeeded): start(startTime), time(duration), space(spaceNeeded) {}

    int getStartTime() {return start;}
    int getDuration() {return time;}
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
    // store all the parameters needed to describe the creation here
    int seed;

  public:
    // add additional parameters to constructor
    ProcessCreator(const int s): seed(s) {}

    vector<Process> createProcesses();
};

#endif