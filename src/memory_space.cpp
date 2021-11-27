#include "memory_space.h"

void MemorySpace::insertProcess(const Process p, const int location)
{
  // First we need to check if there is room for 
  // the process at the given location
  bool validLocation;
  if(memory[location] == -1)
  {
    validLocation = true;
    for(int i = 1; i < p.getSpaceNeeded(); i++)
      if(memory[location+i] != -1)
        validLocation = false;
  }
  else
    //TODO: throw error
  // Now that we know the space if free, we can insert it into the memory
  if (validLocation)
  {
    for(int i = 0; i < p.getSpaceNeeded(); i++)
      memory[location+i] = 1; // 1 represents an unavailable piece of memory
    activeProcesses.push_back({p,p.getDuration(),location});
  }
  return;
}

void MemorySpace::updateTime(const float newTime)
{
  for (auto& [p, duration, location] : activeProcesses) {
    duration--;
    // if the process is done, remove it from memory
    if(duration == 0)
    {
      for(int i = 0; i < p.getSpaceNeeded(); i++)
        memory[location+i] = 0;
    }
  }
  return;
}

vector<Hole> MemorySpace::getHoles()
{
  vector<Hole> Holes;
  int holeLocation, holeSize;
  for (int i = 0; i < space; i++)
  {
    if(memory[i] == 0)
    {
      holeLocation = i;
      holeSize = 1;
      // continue iterating until we reach a 1 to find size
      while(memory[i] != 1 && i < space)
      {
        i++;
        holeSize++;
      }
      Holes.push_back(Hole(holeLocation,holeSize));
    }
  }
  return Holes;
}

float MemorySpace::timeUntilNextFinishes()
{
  // preliminarily check to make sure there are processes running
  if(activeProcesses.size() == 0)
    return -1;

  float minTimeLeft = 99999; // a number theoretically bigger than any input duration
  for(auto& [p, duration, location] : activeProcesses)
  {
    if(duration < minTimeLeft)
      minTimeLeft = duration;
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

