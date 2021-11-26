#ifndef SPACE_ALGORITHMS_H
#define SPACE_ALGORITHMS_H

#include "memory_space.h"
#include <vector>

using namespace std;

/**
 * Represents the result of a space algorithm trying to find space for a process
 */
class SearchResult
{
  private:
    bool foundHole;
    Hole hole;
    int holesSearched;
  
  public:
    SearchResult(bool found, Hole h, int searched): foundHole(found), hole(h), holesSearched(searched) {}

    bool didFindHole() {return foundHole;}
    Hole getHole() {return hole;}
    int getHolesSearched() {return holesSearched;}
};

/**
 * This abstract class represents all space management algorithms
 */
class SpaceAlgorithm
{
  public:
    /**
     * Examines the given holes and returns the result of the search
     * 
     * @param holes the holes to examine
     * @param p the process to allocate in one of the holes
     * @return the outcome of the search
     */ 
    virtual SearchResult findHole(const vector<Hole> & holes, const Process & p) const = 0;
};

class BestFit : SpaceAlgorithm
{
  public:
    /**
     * Looks through all of the holes and finds the smallest hole that has sufficient size
     */
    SearchResult findHole(const vector<Hole> & holes, const Process & p) const;
};

class WorstFit : SpaceAlgorithm
{
  public:
    /**
     * Looks through all of the holes and finds the largest hole if the largest hole is large enough
     */ 
    SearchResult findHole(const vector<Hole> & holes, const Process & p) const;
};

class NextFit : SpaceAlgorithm
{
  public:
    /**
     * Keeps track of the current hole and examines the holes starting with the hole after
     * the current hole, stopping when a hole of sufficient size is found
     */
    SearchResult findHole(const vector<Hole> & holes, const Process & p);

  private:
    int head = 0;
};

class FirstFit : SpaceAlgorithm
{
  public:
    /**
     * Starting from the beginning, finds the first hole that is of sufficient size
     */
    SearchResult findHole(const vector<Hole> & holes, const Process & p) const;
};

#endif