#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Record
{
private:
    std::string name;
    int size;
    time_t timestamp;
public:
    Record()=default;
    Record(std::string &name, int &size);
    
    void write_record();

    static std::vector<Record> records_vector();
    static void print_records(std::vector<Record> &records_vector);
};


#endif