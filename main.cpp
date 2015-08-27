#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Histogram.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv){

  bool setGraphical = false;
  bool setInteger = false;
  for(int i = 0; i < argc; i++){
    if(std::string(argv[i]) == "-g"){
      setGraphical = true;
    }
    if(std::string(argv[i]) == "-i"){
      setInteger = true;
    }
    if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"){
      cout << "Command line tool for calculating histograms.\n\n";
      cout << "Finds the optimal bin width using the method\n";
      cout << "detailed by Shimazaki and Shinomoto.\n\n\n";
      cout << "Command line options:\n\n";
      cout << "-i\tEnable integer mode, calculates\n";
      cout << "\tthe correct bin width for int data";	
      cout << "-g\tEnable graphical mode, prints\n";
      cout << "\thistogram to command line graphically.\n\n";
      return 0;
    }
  }
  

  if(setInteger){
    vector<int> temp;
    int min = 0;
    int max = 0;
    int x;
    cin >> x;
    temp.push_back(x);
    min = x;
    while(cin >> x){
      temp.push_back(x);
      if(max < x){
	max = x;
      }
      if(x < min){
	min = x;
      }

    }
    Histogram<int> hist = Histogram<int>(10, min, max, "");
    for(int i = 0; i < temp.size(); i++){
      hist.addValue(temp[i]);
    }
    cout << "Values added" << endl;
    int opBinNum = hist.optimisedBinNum();
    cout << "optimised" << endl;
    hist.reBinData(opBinNum);
    cout << "rebinned" << endl;
    if(setGraphical){
      hist.printGraphical();
    }
    else{
      hist.print();
    }

  }
  else if (!setInteger) {
    vector<double> temp;
    double min = 0;
    double max = 0;
    double x;
    cin >> x;
    temp.push_back(x);
    min = x;
    while(cin >> x){
      temp.push_back(x);
      if(max < x){
	max = x;
      }
      if(x < min){
	min = x;
      }
   
    }
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

  }
    

  return 0;
}
