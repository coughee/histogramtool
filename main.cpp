#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Histogram.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv){

  bool setGraphical = false;
  int maxBins = 10;
  for(int i = 0; i < argc; i++){
    if(std::string(argv[i]) == "-g"){
      setGraphical = true;
    }
    if(std::string(argv[i]) == "-mb"){
      maxBins = atoi(argv[i + 1]);
    }
    if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"){
      cout << "Command line tool for calculating histograms.\n\n";
      cout << "Finds the optimal bin width using the method\n";
      cout << "detailed by Shimazaki and Shinomoto.\n\n\n";
      cout << "Command line options:\n\n";
      cout << "-mb\tSet the maximum number of bins\n";
      cout << "possible\n";
      cout << "-g\tEnable graphical mode, prints\n";
      cout << "\thistogram to command line graphically.\n\n";
      return 0;
    }
  }
  


  vector<double> temp;
  double min = 0;
  double max = 0;
  double x;
  cin >> x;
  temp.push_back(x);
  min = x;
  max = x;
  while(cin >> x){
    temp.push_back(x);
    if(max < x){
      max = x;
    }
    if(x < min){
      min = x;
    }
   
  }
  Histogram hist = Histogram(10, min, max, "");
  hist.setMaxBins(maxBins);
  for(int i = 0; i < temp.size(); i++){
    hist.addValue(temp[i]);
  }
  int opBinNum = hist.optimisedBinNum();
  Histogram histnew = Histogram(opBinNum, min, max, "");
  for(int i = 0; i < temp.size(); i++){
    histnew.addValue(temp[i]);
  }
  if(setGraphical){
    histnew.printGraphical();
  }
  else{
    histnew.print();
  }


    

  return 0;
}
