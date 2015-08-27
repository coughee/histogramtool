#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Histogram.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv){
  double x;
  bool setGraphical = false;
  for(int i = 0; i < argc; i++){
    if(std::string(argv[i]) == "-g"){
      setGraphical = true;
    }
    if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"){
      cout << "Command line tool for calculating histograms.\n\n";
      cout << "Finds the optimal bin width using the method\n";
      cout << "detailed by Shimazaki and Shinomoto.\n\n\n";
      cout << "Command line options:\n\n";
      cout << "-g\tEnable graphical mode, prints\n";
      cout << "\thistogram to command line graphically.\n\n";
      return 0;
    }
  }
  
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
  cout << min << "\t" << max << endl;
  Histogram<double> hist = Histogram<double>(10, min, max, "");
  for(int i = 0; i < temp.size(); i++){
    hist.addValue(temp[i]);
  }
  int opBinNum = hist.optimisedBinNum();
  hist.reBinData(opBinNum);
  if(setGraphical){
    hist.printGraphical();
  }
  else{
    hist.print();
  }
  return 0;
}
