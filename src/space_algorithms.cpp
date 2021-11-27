#include "space_algorithms.h"

SearchResult BestFit::findHole(const vector<Hole> & holes, const Process & p) {
  Hole bestHole(-1, -1);
  int bestWastedSpace = -1;
  int holesChecked = 0;
  // look through each hole for the best-fitting hole
  for (const Hole h : holes)
  {
    holesChecked++;
    int wastedSpace = h.getSize() - p.getSpaceNeeded();
    // if the process fits in this hole
    if (wastedSpace >= 0)
    {
      // if it is a better fit than the previous best
      if (bestWastedSpace == -1 || wastedSpace < bestWastedSpace)
      {
        bestHole = h;
        bestWastedSpace = wastedSpace;
        // if it is a perfect fit, no other hole could be better
        if (bestWastedSpace == 0)
        {
          break;
        }
      }
    } 
  }
  bool holeFound = (bestWastedSpace != -1);

  return SearchResult(holeFound, bestHole, holesChecked);
}

SearchResult WorstFit::findHole(const vector<Hole> & holes, const Process & p) {
  Hole worstHole(-1, -1);
  int mostWastedSpace = -1;
  int holesChecked = 0;
  // look through each hole for the best-fitting hole
  for (const Hole h : holes)
  {
    holesChecked++;
    int wastedSpace = h.getSize() - p.getSpaceNeeded();
    // if the process fits in this hole
    if (wastedSpace >= 0)
    {
      // if it is a better fit than the previous best
      if (mostWastedSpace == -1 || wastedSpace > mostWastedSpace)
      {
        worstHole = h;
        mostWastedSpace = wastedSpace;    
      }
    } 
  }
  bool holeFound = (mostWastedSpace != -1);

  return SearchResult(holeFound, worstHole, holesChecked);
}

SearchResult FirstFit::findHole(const vector<Hole> & holes, const Process & p) {
  bool validHole = false;
  int holesChecked = 0;
  Hole bestHole(-1, -1);
  while(!validHole && (holesChecked < holes.size()))
  {
    if(p.getSpaceNeeded() <= holes[holesChecked].getSize())
    {
      validHole = true;
      bestHole = holes[holesChecked];
    }
    holesChecked++;
  }

  return SearchResult(validHole, bestHole, holesChecked);
}

SearchResult NextFit::findHole(const vector<Hole> & holes, const Process & p) {
  bool validHole = false;
  int holesChecked = 0;
  Hole bestHole(-1, -1);
  int currHead = head % holes.size();
  while(!validHole && (holesChecked < holes.size()))
  {
    if(p.getSpaceNeeded() <= holes[currHead].getSize())
    {
      validHole = true;
      bestHole = holes[currHead];
    }
    holesChecked++;
    currHead = (head + holesChecked) % holes.size();
  }
  head = currHead;
  return SearchResult(validHole, bestHole, holesChecked);
}