#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Histogram.h"
#include <vector>

using namespace std;

int main(int argc, char **argv){
  double x;
  
  
  vector<double> temp;

  double min = 0;
  double max = 0;
  cin >> x;
  temp.push_back(x);
  min = x;
    
  while(cin >> x){
    temp.push_back(x);
    if(max < x){
      max = x;
    }
    if(x < min && x >= 0){
      min = x;
    }
  }
  if( min < 0){
    min = 0;
  }
  
  Histogram<double> hist = Histogram<double>(10, min, max, "");
  for(int i = 0; i < temp.size(); i++){
    hist.addValue(temp[i]);
  }
  int opBinNum = hist.optimisedBinNum();
  hist.reBinData(opBinNum);
  hist.print();

  return 0;
}
