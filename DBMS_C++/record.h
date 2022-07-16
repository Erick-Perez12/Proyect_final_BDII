#pragma once

#include <iostream>
#include <string.h>
using namespace std;

class Record
{
private:
    int RecordID;
    string data1;
    string data2;
public:
    Record(int);
    Record(int, string);
    void display();
    void insert(string);
    void remove(string);
    ~Record();
};

Record::Record(int id)
{
    RecordID = id;
}

Record::Record(int id, string data_1)
{
    RecordID = id;
    data1 = data_1;
}

void Record::insert(string data_1)
{
    data1 = data_1;
}

void Record::remove(string data_1)
{
    if (data1 = data_1)
        data1 = " ";
}

void Record::display()
{
    cout << RecordID << " " << data1;
}

Record::~Record()
{}