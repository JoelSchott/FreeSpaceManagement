#include "space_algorithms.h"

SearchResult BestFit::findHole(const vector<Hole> & holes, const Process & p) const {
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

SearchResult FirstFit::findHole(const vector<Hole> & holes, const Process & p) const {
  bool validHole = false;
  int holesChecked = 0;
  Hole bestHole(-1, -1);
  while(!validHole && (holesChecked < holes.size()-1))
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

SearchResult NextFit::findHole(const vector<Hole> & holes, const Process & p) const {
  bool validHole = false;
  int holesChecked = 0;
  Hole bestHole(-1, -1);
  while(!validHole && (holesChecked < holes.size()-1))
  {
    if(p.getSpaceNeeded() <= holes[(head + holesChecked) % holes.size()].getSize())
    {
      validHole = true;
      bestHole = holes[(head + holesChecked) % holes.size()];
    }
    holesChecked++;
  }
  
  return SearchResult(validHole, bestHole, holesChecked);
}