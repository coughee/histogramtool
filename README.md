#HistogramTool
Commandline tool for histograming data. Finds the optimal bin width for the data.

##Usage
Assuming data is a file of values:
cat data | histogramtool
Would find the optimal bin width for the data and bin it accordingly, outputting the histogram as tab delimited data with column 1 being the maximum bin value and column 2 being the frequency.

##options
-g	Turns graphical mode on, the histogramis displayed in the commandline using o as the marker e.g

[0 - 1]	oo
[1 - 2] oooooo
[2 - 3] ooooo
[3 - 4] oooo
[4 - 5] ooo