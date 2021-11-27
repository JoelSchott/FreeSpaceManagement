#include "memory_space.h"

void MemorySpace::insertProcess(const Process p, const int location)
{
  // First we need to check if there is room for
  // the process at the given location
  bool validLocation = true;
  for (int i = 0; i < p.getSpaceNeeded(); i++)
  {
    if (location + i >= memory.size())
    {
      validLocation = false;
      break;
    }
    if (memory[location + i])
    {
      validLocation = false;
      break;
    }
  }
  if (!validLocation)
  {
    throw runtime_error("Tried to insert a process at an invalid location");
  }
  // Now that we know the space if free, we can insert it into the memory
  for (int i = 0; i < p.getSpaceNeeded(); i++)
    memory[location + i] = true; // true represents an unavailable piece of memory
  activeProcesses.push_back(p);
  activeProcessLocations.push_back(location);
}

void MemorySpace::updateTime(const float newTime)
{
  for (int i = activeProcesses.size() - 1; i >= 0; i--)
  {
    // if the process should be removed
    if (newTime + 0.001 >= activeProcesses[i].getAllocTime() + activeProcesses[i].getDuration())
    {
      // deallocate the memory
      for (int j = 0; j < activeProcesses[i].getSpaceNeeded(); j++)
      {
        memory[activeProcessLocations[i] + j] = false;
      }
      // remove the process and the location
      activeProcesses.erase(activeProcesses.begin() + i);
      activeProcessLocations.erase(activeProcessLocations.begin() + i);
    }
  }
  time = newTime;
}

vector<Hole> MemorySpace::getHoles()
{
  vector<Hole> Holes;
  int holeLocation, holeSize;
  for (int i = 0; i < space; i++)
  {
    if (memory[i] == 0)
    {
      holeLocation = i;
      holeSize = 0;
      // continue iterating until we reach a 1 to find size
      while (memory[i] != 1 && i < space)
      {
        i++;
        holeSize++;
      }
      Holes.push_back(Hole(holeLocation, holeSize));
    }
  }
  return Holes;
}

float MemorySpace::timeUntilNextFinishes()
{
  // preliminarily check to make sure there are processes running
  if (activeProcesses.size() == 0)
    return -1;

  float minTimeLeft = 99999; // a number theoretically bigger than any input duration
  for (Process p : activeProcesses)
  {
    float timeLeft = p.getAllocTime() + p.getDuration() - time;
    if (timeLeft < minTimeLeft)
      minTimeLeft = timeLeft;
  }
  return minTimeLeft;
}

int MemorySpace::usage()
{
  int used = 0;
  for (int i = 0; i < space; i++)
    if (memory[i] == 1)
      used++;
  return used;
}
