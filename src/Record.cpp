#include "../include/Record.h"

Record::Record(std::string &name_, int &size_): name(name_), size(size_), timestamp(time(nullptr)) {};

// в рекорды
void Record::write_record()
{
    std::ofstream file("records.txt", std::ios::app);
    file<<name<<" "<<size<<" "<<timestamp<<std::endl;
    file.close();
}

std::vector<Record> Record::records_vector()
{
    std::vector<Record> records;
    std::ifstream file("records.txt");
    if (!file) {
        std::cout << "Файл рекордов не найден, создаём новый" << std::endl;
        return records;
    }

    Record temp;
    while(file>>temp.name>>temp.size>>temp.timestamp)
    {
        records.push_back(temp);
    }
    file.close();
    return records;
}

void Record::print_records(std::vector<Record> &records_vector)
{
    std::sort(records_vector.begin(), records_vector.end(), [](const Record &a, const Record &b) {
        if (a.size!=b.size) return a.size>b.size;
        return a.timestamp>b.timestamp;
    });

    int top_count=std::min(10, (int)records_vector.size());
    tm *local_time;
    char buffer[80];
    std::cout<<"=======RECORDS======="<<std::endl;
    std::cout<<"name    count    date"<<std::endl;
    for (int i =0; i<top_count; ++i)
    {
        local_time = localtime(&records_vector[i].timestamp);
        strftime(buffer, 80, "%d.%m.%Y %H:%M", local_time);
        std::cout<<records_vector[i].name<<'\t'<<records_vector[i].size<<'\t'<<buffer<<std::endl;
    }
}