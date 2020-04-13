#ifndef FM_SAMPLE_H_
#define FM_SAMPLE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


class fm_sample
{
public:
    int y;
    double weight;
    vector<pair<string, double> > x;
    fm_sample(const string& line);
private:
    static const string spliter;
    static const string featureSpliter;
    static const string innerSpliter;
};

const string fm_sample::spliter = "\t";
const string fm_sample::featureSpliter = " ";
const string fm_sample::innerSpliter = ":";


fm_sample::fm_sample(const string& line)
{
    this->x.clear();
    size_t posb = line.find_first_not_of(spliter, 0);
    size_t pose = line.find_first_of(spliter, posb);
    this->weight = atof(line.substr(posb, pose-posb).c_str());
    posb = pose + 1;
    pose = line.find_first_of(spliter, posb);
    double label = atof(line.substr(posb, pose-posb).c_str());
    this->y = label > 0 ? 1 : -1;
    string key;
    double value;
    pose += 1;
    while(pose < line.size())
    {
        posb = line.find_first_not_of(featureSpliter, pose);
        if(posb == string::npos)
        {
            break;
        }
        pose = line.find_first_of(innerSpliter, posb);
        if(pose == string::npos)
        {
            cerr << "wrong line of sample input\n" << line << endl;
            exit(1);
        }
        key = line.substr(posb, pose-posb);
        posb = pose + 1;
        if(posb >= line.size())
        {
            cerr << "wrong line of sample input\n" << line << endl;
            exit(1);
        }
        pose = line.find_first_of(featureSpliter, posb);
        value = stod(line.substr(posb, pose-posb));
        if(value != 0)
        {
            this->x.push_back(make_pair(key, value));
        }
    }
}


#endif /*FM_SAMPLE_H_*/
