#include <iostream>
#include "../common/TnStatistic.h"
#include "../common/Auxiliary.h"
#include "optionparser.h"
using namespace std;

string version = "1.0";

/****************************
*                           *
*      Argument parser      *
*                           *
****************************/

struct Arg: public option::Arg
{
    static void PrintError(const char* msg1, const option::Option& opt, const char* msg2)
    {
        fprintf(stderr, "%s", msg1);
        fwrite(opt.name, opt.namelen, 1, stderr);
        fprintf(stderr, "%s", msg2);
    }

    static option::ArgStatus Required(const option::Option& option, bool msg)
    {
        if (option.arg != 0)
            return option::ARG_OK;

        if (msg) PrintError("Option '", option, "' requieres an argument.\n");
        return option::ARG_ILLEGAL;
    }
};

enum  OptionIndex { UNKNOWN, DATA_FILE, DATA_LIST, C, ALPHA, CALC_INTERVAL, CMIN, CMAX, DELTAC, OUT_FILE, ABOUT, HELP};

const option::Descriptor usage[] =
{
    {UNKNOWN, 0, "", "",Arg::None, "INSTRUCTIONS: TnStatistic [options]\n"},
    {DATA_FILE,  0,"", "data_file", Arg::Required, "  \t--data_file=<arg>  \tPath to file with data." },
    {DATA_LIST,  0,"", "data", Arg::Required, "  \t--data=<arg>  \tData as a list. E.g: -3,-2,-1,0,1,2." },
    {C,  0,"", "c", Arg::Required, "  \t--c=<arg>  \tPoint of symmetry." },
    {ALPHA,  0,"", "alpha", Arg::Required, "  \t--alpha=<arg>  \tAlpha value for upper percentage point calculation. By default is 0.01, 0.05 and 0.1." },
    {CALC_INTERVAL,  0,"", "calc_interval", Arg::None, 
    "  \t--calc_interval  \tCalculate Tn for an interval of c. Requires to specify cmin, cmax and deltac." },
    {CMIN,  0,"", "cmin", Arg::Required, "  \t--cmin=<arg>  \tMinimum value of c. Default value is -1." },
    {CMAX,  0,"", "cmax", Arg::Required, "  \t--cmax=<arg>  \tMaximum value of c. Default value is 1." },
    {DELTAC,  0,"", "deltac", Arg::Required, "  \t--deltac=<arg>  \tStep interval of c. Default value is 0.01." },
    {OUT_FILE,  0,"", "out_file", Arg::Required, "  \t--out_file=<arg>  \tPath to the output file." },
    {ABOUT,    0,"", "about", Arg::None,    "  \t--about  \tInformation about the program." },
    {HELP,    0,"", "help", Arg::None,    "  \t--help  \tShow instructions." },
    {0,0,0,0,0,0}
};

int main(int argc, char** argv)
{
    // Default values.
    bool calc_interval = false;
    string data_file = "", data_list = "", out_file = "";
    double c = 0, cmin = -1.0, cmax = 1.0, deltac = 0.01, alpha = -1.0;
    
    // Execute argument parser.
    argc -= (argc>0); argv += (argc>0);
    option::Stats  stats(usage, argc, argv);
    option::Option *options = new option::Option[stats.options_max];
    option::Option *buffer = new option::Option[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);
    
    if (parse.error())
    {
        option::printUsage(cout, usage);
        return 1;
    }

    if (options[HELP] || argc == 0)
    {
        option::printUsage(cout, usage);
        return 0;
    }

    if (options[ABOUT])
    {
        cout << "Version: " << version << endl;
        cout << "If you use this program for academic purposes, please cite as: \n"
            "C.M. Rodriguez-Martinez, H.F. Coronel-Brizio (2016) Tn Symmetry "
            "Statistic [Computer program]. Available at: http://github.com/CarlosManuelRodr/TnSymmetryStatistic" << endl;
        return 0;
    }

    for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next())
        cout << "Unknown option: " << opt->name << "\n";
    
    for (int i = 0; i < parse.optionsCount(); ++i)
    {
        option::Option& opt = buffer[i];
        switch (opt.index())
        {
            case DATA_FILE:
                data_file = opt.arg;
                break;

            case DATA_LIST:
                data_list = opt.arg;
                break;
            
            case C:
                c = aux_string_to_num<double>(opt.arg);
                break;

            case ALPHA:
                alpha = aux_string_to_num<double>(opt.arg);
                break;
            
            case CALC_INTERVAL:
                calc_interval = true;
                break;
                
            case CMIN:
                cmin = aux_string_to_num<double>(opt.arg);
                break;
                
            case CMAX:
                cmax = aux_string_to_num<double>(opt.arg);
                break;
                
            case DELTAC:
                deltac = aux_string_to_num<double>(opt.arg);
                break;
                
            case OUT_FILE:
                out_file = opt.arg;
                break;
        }
    }

    delete[] options;
    delete[] buffer;
    
    
    // Check conflicting options and errors.
    if (data_file.empty() && data_list.empty())
    {
        cout << "Error: No input." << endl;
        return 1;
    }
    if (!data_file.empty() && !data_list.empty())
    {
        cout << "Error: Two inputs given, must be only one." << endl;
        return 1;
    }
    
    // Load the data from file or given list.
    vector <double> data;
    if (!data_file.empty())
    {
        if (!aux_file_exist(data_file.c_str()))
        {
            cout << "Error: File doesn't exist." << endl;
            return 1;
        }
        
        string ext = aux_get_file_extension(data_file);
        if (ext == "csv")
            data = aux_csv_file_to_vector(data_file);
        else if (ext == "dat")
            data = aux_dat_file_to_vector(data_file);
        else
        {
            cout << "Warning: Unknown file extension. File will be loaded as a .dat file." << endl;
            data = aux_dat_file_to_vector(data_file);
        }
    }
    if (!data_list.empty())
        data = aux_csv_to_vector<double>(data_list);
    
    if (data.empty())
    {
        cout << "Error: Invalid data." << endl;
        return 1;
    }

    // Information about the mean.
    double sample_mean = mean(data);
    double sample_std_error = standard_error(data);
    cout << "The mean of the data is: " << sample_mean << endl;
    cout << "The lower 95% confidence limit of the mean is: " << sample_mean - sample_std_error << endl;
    cout << "The upper 95% confidence limit of the mean is: " << sample_mean + sample_std_error << endl;

    // Information about upper percentage points.
    if (alpha != -1.0)
        cout << "Upper percentage point at alpha value " << alpha << " is " << upper_percentage_point(alpha) << endl;
    else
    {
        cout << "Upper percentage point at alpha value 0.01 is: " << upper_percentage_point(0.01) << endl;
        cout << "Upper percentage point at alpha value 0.05 is: " << upper_percentage_point(0.05) << endl;
        cout << "Upper percentage point at alpha value 0.1 is: " << upper_percentage_point(0.1) << endl;
    }

    
    // Calculate Tn.
    if (calc_interval)
    {
        vector< Coord<double> > result = ranged_tn(data, cmin, cmax, deltac);
        aux_print_coordvector(result);
        
        if (!out_file.empty())
            aux_coordvector_to_file(out_file, result);
    }
    else
    {
        double result;
        if (c == 0)
            result = tn(data);
        else
            result = tn(data, c);
        
        cout << "Tn = " << result << endl;
        
        if (!out_file.empty())
            aux_number_to_file(out_file, result);
    }
    
    return 0;
}