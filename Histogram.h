#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <fstream>

template <class T>
class Histogram
{
 public:
  Histogram<T>(int nBins, T min, T max, std::string header);
  Histogram<T>(int nBins, T min, T max, std::string header, std::string filename);
  ~Histogram<T>() {}
  Histogram<T>& operator=(Histogram<T> rhs);

  //Calculation
  double getAverage();
  double getStdDev();
  double getVariance();
  T getMax();
  T getMin();
  T getMinGreaterThanZero();
  int optimisedBinNum();
  double calculateBinCost(Histogram<T> thist);
  void reBinData(int numBins);
    
  //Input
  int getLocation(T value);
  void addValue(T val);  

  //Output
  void writeToFile(std::string outputfile);
  void writeRawDataToFile(std::string outputfile);
  void readFromFile(std::string fileName);
  void print();
 private:
  void addHistValueOnly(T value);
  
  std::string header;
  int nBins;
  T min;
  T max;
  double binSize;
  long int count;
  std::vector<T> values;
  std::vector<T> rawData;
  std::vector<T> index;
  
  //moments
  T accu;
  T accusq;
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

}

template <class T>
Histogram<T>::Histogram(int nBins, T min, T max, std::string header){
  this->values.resize(nBins);
  this->index.resize(nBins);
  this->nBins = nBins;
  this->min = min;
  this->max = max;
  this->binSize = (this->max - this->min)/(T)this->nBins;
  for(int i = 0; i < nBins; i++){
    this->values[i] = 0;
    this->index[i] = (i + 1)*this->binSize;
  }
  this->header = header;
  this->count = 0;
  this->accu = 0;
  this->accusq = 0;

}

template<class T> 
int Histogram<T>::getLocation(T value){
 if(value > max || value < min){
    if(value == this->max){
      return values.size() - 1;
    }
    //    std::cout << "ERROR: value " << value << " out of range." << std::endl;
    return -1;
  }

 return (int)floor(value / this->binSize);
}

template <class T>
void Histogram<T>::addValue(T value){
  this->addHistValueOnly(value);
  this->rawData.push_back(value);
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
double Histogram<T>::calculateBinCost(Histogram<T> tHist){
  double av, avsq;
  av = 0;
  avsq = 0;
  for( int i = 0 ; i < tHist.values.size(); i++){
    av += (double)tHist.values[i];
    avsq += (double)tHist.values[i]*(double)tHist.values[i];
  }
  av /= tHist.nBins;
  avsq /= tHist.nBins;
  avsq -= av*av; 
  return (2*av - avsq)/(tHist.binSize*tHist.binSize);
  
}

template <class T>
int  Histogram<T>::optimisedBinNum(){
  int curGuess = 2;
  int binInc = (int)round(curGuess/2);
  double curCost;

  Histogram<T> hHist = *this;
  Histogram<T> lHist = *this;
  hHist.reBinData(curGuess);
  curCost = this->calculateBinCost(hHist);

  double lcost, hcost;
  


/*   while (binInc > 1){ */

/*     std::cout << curGuess << "\t" << binInc << std::endl; */
/*     hHist.reBinData(curGuess + binInc); */
/*     lHist.reBinData(curGuess - binInc); */

/*     lcost = calculateBinCost(lHist); */
/*     hcost = calculateBinCost(hHist); */

/*     if(lcost <= curCost){ */
/*       curGuess -= binInc; */
/*       curCost = lcost; */
/*     } */
/*     else if (hcost < curCost){ */
/*       curGuess += binInc; */
/*       curCost = hcost; */
/*     } */
/*     else{ */
/*       return curGuess; */
/*     } */
/*     binInc = (int)round(binInc/2); */
    
/*   } */

  double prevCost = curCost;
  int bestGuess = curGuess;
  double bestCost = curCost;
  while(curGuess < (this->max - this->min)){
    curGuess += 1;
    hHist.reBinData(curGuess);
    prevCost = curCost;
    curCost = calculateBinCost(hHist);
    if(curCost < bestCost){
      bestGuess = curGuess;
      bestCost = curCost;
    }
  }
  return bestGuess;
}

template <class T>
void Histogram<T>::reBinData(int numBins){
  values.resize(0);
  index.resize(0);
    
    
  this->nBins = numBins;
  this->binSize = (this->max - this->min)/(double)this->nBins;

  for(int i = 0; i < this->nBins; i++){
    this->values.push_back(0);
    this->index.push_back((i + 1)*this->binSize);
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
  if(binLoc < 0){
    return;
  }
  this->values[binLoc]++;
  this->count++;
  this->accu += value;
  this->accusq += value*value;
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

#endif
