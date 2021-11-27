#ifndef MEMORY_SPACE_H
#define MEMORY_SPACE_H

#include "processes.h"
#include <vector>
#include <stdexcept>

using namespace std;

/**
 * Represents a section of contiguous memory
 */
class Hole
{
  private:
    int location;
    int size;
  
  public:
    Hole(const int l, const int s): location(l), size(s) {}

    int getLocation() const {return location;}
    int getSize() const {return size;}
};

/**
 * Represents a contiguous section of memory where processes can be added and removed
 */
class MemorySpace
{
  private:
    int space;
    float time;
    vector<bool> memory;
    vector<Process> activeProcesses;
    vector<int> activeProcessLocations;
  
  public:
    MemorySpace(const int size, const float t=0): space(size), time(t)
    {
      for (int i = 0; i < size; i++)
      {
        memory.push_back(false);
      }
    }

    /**
     * Inserts the given process at the given location in the memory space. The memory space 
     * must have enough room at the given location to hold the process
     * 
     * @param p the process to be inserted
     * @param location the starting position of the location where the process will be stored
     */
    void insertProcess(const Process p, const int location);

    /**
     * Updates the current time of the memory space, meaning that any processes that have finished
     * will be removed and the space that those processes were using will be freed
     * 
     * @param newTime the time that the memory space should be updated to reflect
     */
    void updateTime(const float newTime);

    /**
     * Finds all of the holes in the memory space at the current time
     * 
     * @return holes in the memory space, sorted in ascending order by location
     */
    vector<Hole> getHoles();

    /**
     * Finds how long it will be until the next process finishes. If no processes
     * are currently running, -1 is returned
     * 
     * @return the time until the next process finishes
     */
    float timeUntilNextFinishes();

    /**
     * Finds how much of the memory space is currently being used by processes
     * 
     * @return the number of memory spaces that are being used by processes
     */
    int usage();
};

#endif