#HistogramTool
Commandline tool for histograming data. Finds the optimal bin width for the data. Histogram.h can also be used as a general histogramming header file in c++ applications.

##Usage
Assuming data is a file of values e.g.  
  
    1.0  
    2.0  
    3.0  
  
Then using command:  
  
    cat data | hist
  
Would result in the output like:  
  
    1.0   1  
    2.0   1  
    3.0   1  
  
The program finds the optimal bin width to accurately represent data with multiple peaks.

##options
-g	Turns graphical mode on, the histogram is displayed in the commandline using o as the marker e.g

    [0 - 1]	oo  
    [1 - 2] oooooo  
    [2 - 3] ooooo  
    [3 - 4] oooo  
    [4 - 5] ooo  

##Building
You should just be able to type make to build.
