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

template <class T>
class Histogram
{
 public:
  Histogram<T>(int nBins, T min, T max, std::string header);
  Histogram<T>(int nBins, T min, T max, std::string header, std::string filename);
  ~Histogram<T>() {}
  Histogram<T>& operator=(Histogram<T> rhs);
  Histogram<T>(const Histogram<T> &other);
  //Calculation
  double getAverage();
  double getStdDev();
  double getVariance();
  T getMax();
  T getMin();
  T getMinGreaterThanZero();
  int optimisedBinNum();
  double calculateBinCost();
  void reBinData(int numBins);
    
  //Input
  int getLocation(T value);
  void addValue(T val);  

  //Output
  void writeToFile(std::string outputfile);
  void writeRawDataToFile(std::string outputfile);
  void readFromFile(std::string fileName);
  void print();
  void printGraphical();
 private:
  void addHistValueOnly(T value);
  std::string header;
  int nBins;
  T min;
  T max;

  double binSize;
  int count;
  std::vector<T> values;
  std::vector<T> rawData;
  std::vector<double> index;

  bool areIntegers;
  
  //moments
  double accu;
  double accusq;
};


//Implementation.
template <class T>
Histogram<T>::Histogram(int nBins, T min, T max, 
			std::string header,
			std::string filename){
  this->values.resize(nBins);
  this->index.resize(nBins);
  this->nBins = nBins;
  this->min = min;
  this->max = max;
  this->binSize = (double)(this->max - this->min)/(double)this->nBins;
  for(int i = 0; i < nBins; i++){
    this->values[i] = 0;
    this->index[i] = (i + 1)*this->binSize;
  }
  this->header = header;
  this->count = 0;
  this->accu = 0;
  this->accusq = 0;
  this->readFromFile(filename);
  this->areIntegers = true;
}

template <class T>
Histogram<T>::Histogram(int nBins, T min, T max, std::string header){
  this->values.resize(nBins);
  this->index.resize(nBins);
  this->nBins = nBins;
  this->min = min;
  this->max = max;
  this->binSize = (double)(this->max - this->min)/(double)this->nBins;
  for(int i = 0; i < nBins; i++){
    this->values[i] = 0;
    this->index[i] = (double)(i + 1)*this->binSize + this->min;
  }
  this->header = header;
  this->count = 0;
  this->accu = 0;
  this->accusq = 0;
  this->areIntegers = true;
}

template<class T> 
int Histogram<T>::getLocation(T value){
 if(value > max || value < min){
    if(value == this->max){
      return values.size() - 1;
    }
    std::cout << "ERROR: value " << value << " out of range." << std::endl;
    return -1;
  }
 int rval = (int)floor((value - this->min) / this->binSize);
 return rval;

}

template <class T>
void Histogram<T>::addValue(T value){
  this->addHistValueOnly(value);
  this->rawData.push_back(value);
  double integerpart;
  if (!(std::modf(value,&integerpart) == 0)){
    this->areIntegers = false;
  }
}
template <class T>
void Histogram<T>::print(){
  for(int i = 0; i < this->nBins; i++){
    std::cout << this->index[i] << "\t" 
	      << this->values[i] << std::endl;
  }
}

template <class T>
void Histogram<T>::writeToFile(std::string outputfile){
  std::ofstream file;
  file.open(("hist_" + outputfile).c_str());
  file << this->header.c_str() << "\n";
  for(int i = 0; i < nBins; i++){
    file << index[i] << "\t" << values[i] << "\n";
  }
  file.close();
}

template <class T>
void Histogram<T>::writeRawDataToFile(std::string outputfile){
  std::ofstream file;
  file.open(("rawdata_" + outputfile).c_str());

  for(int i = 0; i < rawData.size(); i++){
    file << rawData[i] << "\n";
  }
  file.close();
}


template <class T>
double Histogram<T>::getAverage(){
  return (double)accu / ((double)count);
}

template <class T>
double Histogram<T>::getStdDev(){
  double av = getAverage();
  av = av*av;
  return sqrt((double)accusq/((double)count) - (double)av);
}

template <class T>
double Histogram<T>::getVariance(){
  double av = getAverage();
  av = av*av;
  return (double)accusq/((double)count) - (double)av;
}

template <class T>
void Histogram<T>::readFromFile(std::string filename){
  std::fstream myfile(filename.c_str(), std::ios_base::in);
  T temp;
  while (myfile >> temp){
    this->addValue(temp);
  }
  myfile.close();
}

template <class T> 
T Histogram<T>::getMax(){
  T maxV = this->rawData[0];
  for(int i = 1; i < this->rawData.size(); i++){
    if (this->rawData[i] > maxV){
      maxV = this->rawData[i];
    }
  }
  return maxV;
}

template <class T> 
T Histogram<T>::getMin(){
  T minV = this->rawData[0];
  for(int i = 1; i < this->rawData.size(); i++){
    if (this->rawData[i] < minV){
      minV = this->rawData[i];
    }
  }
  return minV;
}

template <class T>
T Histogram<T>::getMinGreaterThanZero(){
  T minV = 0;
  int j = 0;
  while (minV == 0){
    minV = this->rawData[j];
    j++;
  }
  for(int i = 1; i < this->rawData.size(); i++){
    if (abs(this->rawData[i]) < minV && this->rawData[i] != 0){
      minV = abs(this->rawData[i]);
    }
  }
  return minV;

}
template <class T> 
double Histogram<T>::calculateBinCost(){
  double av, avsq;
  av = 0;
  avsq = 0;
  for( int i = 0 ; i < this->values.size(); i++){
    av += (double)this->values[i];
    avsq += (double)this->values[i]*(double)this->values[i];
  }
  av /= this->nBins;
  avsq /= this->nBins;
  avsq -= av*av; 
  return (2*av - avsq)/((double)this->binSize*(double)this->binSize);
  
}

template <class T>
int  Histogram<T>::optimisedBinNum(){
  int curGuess = 2;
  int binInc = (int)round(curGuess/2);
  double curCost;
  Histogram<T>* hHist = new Histogram<T>(curGuess,this->min, this->max, "");
  for(int i = 0; i < this->rawData.size(); i++){
    hHist->addValue(rawData[i]);
  }
  
  curCost = hHist->calculateBinCost();



  int bestGuess = curGuess;
  double bestCost = curCost;

  while(curGuess < (this->max - this->min)/2){
    curGuess += 1;
    hHist->reBinData(curGuess);
    if((int)(this->max - this->min) % curGuess == 0 && hHist->areIntegers){
      curCost = hHist->calculateBinCost();
    }
    else if (!hHist->areIntegers){
      curCost = hHist->calculateBinCost();
    }

    if(curCost < bestCost){
      bestGuess = curGuess;
      bestCost = curCost;
    }

   }
   return bestGuess;
}

template <class T>
void Histogram<T>::reBinData(int numBins){
  values.clear();
  index.clear();


  this->nBins = numBins;
  this->binSize = (this->max - this->min)/(double)(this->nBins);


  for(int i = 0; i < this->nBins; i++){
    this->values.push_back(0);
    this->index.push_back((double)((i + 1)*this->binSize) + (double)this->min);
  }



  this->count = 0;
  this->accu = 0;
  this->accusq = 0;

  for(int i = 0; i < this->rawData.size(); i++){
    this->addHistValueOnly(this->rawData[i]);
  }


  
}

template <class T>
void Histogram<T>::addHistValueOnly(T value){
  int binLoc = getLocation(value);
  this->values[binLoc]++;
  this->count++;
  this->accu += value;
  this->accusq += value*value;
}

template <class T>
Histogram<T>::Histogram(const Histogram<T> &other){
  this->values = other.values;
  this->rawData = other.rawData;
  this->index = index;
  this->nBins = other.nBins;
  this->accu = other.accu;
  this->accusq = other.accusq;
  this->min = other.min;
  this->max = other.max;
  this->binSize = other.binSize;
  this->header = other.header;
  this->count = other.count;

}
template <class T>
Histogram<T>& Histogram<T>::operator=(const Histogram<T> rhs){
  this->values = rhs.values;
  this->rawData = rhs.rawData;
  this->index = index;

  this->nBins = rhs.nBins;
  this->accu = rhs.accu;
  this->accusq = rhs.accusq;
  this->min = rhs.min;
  this->max = rhs.max;
  this->binSize = rhs.binSize;
  this->header = rhs.header;
  this->count = rhs.count;

  return *this;
}

template <class T>
void Histogram<T>::printGraphical(){
  for(int i = 0; i < values.size(); i++){
    if(i == 0){
      std::cout << "[0 - " << index[i] << "]\t";
    }
    else {
      std::cout << "[" << index[i - 1] << " - " << index[i] << "]\t";
    }
    for(int j = 0; j < values[i]; j++){
      std::cout << "o";
    }
    std::cout << std::endl;
  }
}
#endif
