# Tn Statistic

This code implements the Tn Statistic symmetry test described in *Coronel-Brizio, H.F.; Hernandez-Montoya, A.R.; Rodriguez-Achach, M.E. and R. Huerta-Quintanilla
(2007): Assesing Symmetry of Financial Return Series. Physica A. 383, 5-9.*

If you use this program for academic purposes, please cite as:

	C. M. Rodriguez-Martinez, H.F. Coronel-Brizio (2016) Tn Symmetry Statistic [Computer program]. Available at: http://github.com/CarlosManuelRodr/TnSymmetryStatistic

# Instructions
Tn Statistic comes with three backends. The command line interface (CLI), a graphical user interface (GUI) and a Mathematica implementation and a separate MathLink for faster performance.

The instructions for the CLI are the following.

	INSTRUCTIONS: TnStatistic [options]
	
	  --data_file=<arg>  Path to file with data.
	  --data=<arg>       Data as a list. E.g: -3,-2,-1,0,1,2.
	  --c=<arg>          Point of symmetry.
	  --alpha=<arg>      Alpha value for upper percentage point calculation. By
	                     default is 0.01, 0.05 and 0.1.
	  --calc_interval    Calculate Tn for an interval of c. Requires to specify
	                     cmin, cmax and deltac.
	  --cmin=<arg>       Minimum value of c. Default value is -1.
	  --cmax=<arg>       Maximum value of c. Default value is 1.
	  --deltac=<arg>     Step interval of c. Default value is 0.01.
	  --out_file=<arg>   Path to the output file.
	  --help             Show instructions.

For example, to calculate the symmetry for the points (-4, -3, -2, -1, 0, 1, 2 ,3) around zero, the command is:

	TnStatisticCLI --data=-4,-3,-2,-1,0,1,2,3 --c=0

And to calculate the symmetry from c=-1 to c=1 using steps of size 0.1 the command is:

	TnStatisticCLI --data=-4,-3,-2,-1,0,1,2,3 --calc_interval --cmin=-1 --cmax=1, --deltac=0.1

Both the CLI and the GUI accept data from .dat files in which data is structured in columns, for example:

	-4
	-3
	-2
	-1
	0
	1
	2
	3

or .csv files, in which data is separated by commas

	-4,-3,-2,-1,0,1,2,3 



# Compiling

### CLI
For the command line interface you can compile using

```
make
```

It requires a C++11 compatible compiler.

On Windows you can use the Visual Studio project file.

### GUI
The graphical user interface uses the QT toolkit, and you can compile directly from QTCreator.


### Mathematica
There are two Mathematica compatible implementations. The first is implemented directly in the Wolfram Language on the file *SymmetryTest.nb*. A much faster implementation is made using the MathLink binding.

To compile the Mathlink version you can use the makefile on Linux or the project file on Windows.

Since the neccesary MathLink file may be installed elsewhere on your system, you may need to change the line

```
MLINKDIR = /opt/Mathematica/SystemFiles/Links/MathLink/DeveloperKit/Linux-x86-64
```

on the makefile to your Mathematica installation path. On Windows you may need to do the equivalent step but changing the paths on the VS project file.