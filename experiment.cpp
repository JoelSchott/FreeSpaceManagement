#include "experiment.h"

ExperimentResult runExperiment(const ProcessCreator & pc, const SpaceAlgorithm * a, const int memorySize)
{
  int holeChecks = 0;
  int failedAllocs = 0;
  float totalWaitTime = 0;
  float averageUsage = 0;

  float currentTime = 0;
  int nextProcessIndex = 0;
  MemorySpace space(memorySize, currentTime);
  vector<Process> processes = pc.createProcesses();
  queue<Process> waitingProcesses;

  while (nextProcessIndex < processes.size() || !waitingProcesses.empty() || space.timeUntilNextFinishes() != -1)
  {
    // find which event will come next, either a process finishes or the next process starts
    bool nextProcessStarts = false;
    float nextFinishTime = space.timeUntilNextFinishes();
    if (nextFinishTime == -1)
    {
      nextProcessStarts = true;
    }
    else
    {
      if (nextProcessIndex < processes.size())
      {
        nextProcessStarts = (processes[nextProcessIndex].getStartTime() - currentTime) < nextFinishTime;
      }
      else
      {
        nextProcessStarts = false;
      }
    }
    // if a new process is starting
    if (nextProcessStarts)
    {
      float deltaTime = processes[nextProcessIndex].getStartTime() - currentTime;
      // if there are already processes waiting, then this process must wait as well
      if (waitingProcesses.size() > 0)
      {
        waitingProcesses.push(processes[nextProcessIndex]);
      }
      // no process is waiting, so see if this process can be placed
      else
      {
        SearchResult result = a->findHole(space.getHoles(), processes[nextProcessIndex]);
        holeChecks += result.getHolesSearched();
        // if the placement was successful
        if (result.didFindHole())
        {
          space.insertProcess(processes[nextProcessIndex], result.getHole().getLocation());
        }
        // if there was no location found for the process
        else
        {
          waitingProcesses.push(processes[nextProcessIndex]);
          failedAllocs++;
        }
      }
      totalWaitTime += deltaTime * waitingProcesses.size();
      averageUsage += deltaTime * space.usage();
      currentTime += deltaTime;
      space.updateTime(currentTime);
      nextProcessIndex++;
    }
    // if a process finishes next
    else
    {
      totalWaitTime += nextFinishTime * waitingProcesses.size();
      averageUsage += nextFinishTime * space.usage();
      currentTime += nextFinishTime;
      space.updateTime(currentTime);

      // see if there are waiting processes that can now run
      bool canPlaceFirst = true;
      while (waitingProcesses.size() > 0 && canPlaceFirst)
      {
        SearchResult result = a->findHole(space.getHoles(), waitingProcesses.front());
        holeChecks += result.getHolesSearched();
        if (result.didFindHole())
        {
          space.insertProcess(waitingProcesses.front(), result.getHole().getLocation());
          waitingProcesses.pop();
        }
        else
        {
          canPlaceFirst = false;
          failedAllocs++;
        }
      }
    }   
  }

  averageUsage /= currentTime;
  ExperimentResult result(holeChecks, failedAllocs, totalWaitTime, averageUsage);
  return result;
}