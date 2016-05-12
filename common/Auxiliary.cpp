#include "Auxiliary.h"
using namespace std;


string aux_get_file_extension(const string filepath)
{
    string m_filepath = filepath;
    return m_filepath.substr(m_filepath.find_last_of('.')+1);
}
bool aux_file_exist(const char *fileName)
{
    ifstream infile(fileName);
    bool res = infile.is_open();
    if (res)
        infile.close();
    return res;
}
string aux_get_file_contents(const char *filename)
{
  ifstream in(filename, ios::in | ios::binary);
  if (in)
  {
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return(contents.str());
  }
  throw(errno);
}
vector<double> aux_dat_file_to_vector(const string filepath)
{
    vector<double> out;
    string line;
    ifstream file(filepath);

    if (file.is_open())
    {
        while (getline(file, line))
            out.push_back(aux_string_to_num<double>(line));

        file.close();
    }

    return out;
}
vector<double> aux_csv_file_to_vector(const string filepath)
{
    string filecontent = aux_get_file_contents(filepath.c_str());
    return aux_csv_to_vector<double>(filecontent);
}
void aux_number_to_file(const string filepath, const double number)
{
    ofstream file(filepath);
    if (file.is_open())
    {
        file << number;
        file.close();
    }
}
void aux_coordvector_to_file(const string filepath, vector< Coord<double> > v)
{
    ofstream file(filepath);
    if (file.is_open())
    {
        for (unsigned i=0; i<v.size(); ++i)
            file << v[i].GetX() << ", " << v[i].GetY() << endl;

        file.close();
    }
}
void aux_print_coordvector(vector< Coord<double> > v)
{
    cout << "   c   |   f(c)   " << endl;
    cout << "------------------" << endl;
    for (unsigned i=0; i<v.size(); ++i)
        cout << v[i].GetX() << ", " << v[i].GetY() << endl;
}

