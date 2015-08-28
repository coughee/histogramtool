#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <fstream>
#include <typeinfo>
#include <stdexcept>
#include <algorithm>


class Histogram
{
 public:
  Histogram(){}
  Histogram(int nBins, double min, double max, std::string header);
  Histogram(int nBins, double min, double max, std::string header, std::string filename);
  ~Histogram() {}
  Histogram& operator=(Histogram rhs);
  Histogram(const Histogram &other);
  //Calculation
  double getAverage();
  double getStdDev();
  double getVariance();
  double getMax();
  double getMin();
  double getMinGreaterThanZero();
  int optimisedBinNum();
  double calculateBinCost();
  void reBinData(int numBins);
    
  //Input
  int getLocation(double value);
  void addValue(double val);  

  //Output
  void writeToFile(std::string outputfile);
  void writeRawDataToFile(std::string outputfile);
  void readFromFile(std::string fileName);
  void print();
  void printGraphical();
  void addHistValueOnly(double value);
  void setMaxBins(int mbins);
 private:
  std::string header;
  int nBins;
  int maxBins;
  double min;
  double max;

  double binSize;
  int count;
  std::vector<double> values;
  std::vector<double> rawData;
  std::vector<double> index;

  bool areIntegers;
  
  //moments
  double accu;
  double accusq;
};

#endif
