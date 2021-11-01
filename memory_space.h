#ifndef MEMORY_SPACE_H
#define MEMORY_SPACE_H

#include "processes.h"
#include <vector>

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

    int getLocation() {return location;}
    int getSize() {return size;}
};

/**
 * Represents a contiguous section of memory where processes can be added and removed
 */
class MemorySpace
{
  private:
    int space;
    int time;
  
  public:
    MemorySpace(const int size, const int t=0): space(size), time(t) {}

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
    void updateTime(const int newTime);

    /**
     * Finds all of the holes in the memory space at the current time
     * 
     * @return holes in the memory space, sorted in ascending order by location
     */
    vector<Hole> getHoles();

    /**
     * Finds how long it will be until a process finishes. At least one process must be running
     * in the memory space when this is called.
     * 
     * @return the time until the next process finishes
     */
    int timeUntilNextFinishes();
};

#endif