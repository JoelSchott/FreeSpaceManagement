#include <iostream>
#include <string>
#include <vector>

#include "space_algorithms.h"

using namespace std;

int main(){
  vector<Hole> holes = {Hole(0, 4), Hole(3, 7), Hole(10, 5)};
  Process p(0, 4, 9);
  BestFit bestFitAlg;
  SearchResult result = bestFitAlg.findHole(holes, p);
  cout << "Found Hole?: " << result.didFindHole() << endl;
  cout << "Hole Location: " << result.getHole().getLocation() << endl;
  cout << "Holes searched: " << result.getHolesSearched() << endl;
  return 0;
}