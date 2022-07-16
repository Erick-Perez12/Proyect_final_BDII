#pragma once

#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class Bucket {
    int depth, size;
    std::map<int, string> values;
public:
    Bucket(int depth, int size);
    int insert(int key, string value);
    int remove(int key);
    int update(int key, string value);
    void search(int key);
    bool search_a(int key);
    void tabla_full(int key);
    int isFull(void);
    int isEmpty(void);
    int getDepth(void);
    int increaseDepth(void);
    int decreaseDepth(void);
    std::map<int, string> copy(void);
    void clear(void);
    void display(void);
};

Bucket::Bucket(int depth, int size)
{
    this->depth = depth;
    this->size = size;
}

int Bucket::insert(int key, string value)
{
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
        return -1;
    if (isFull())
        return 0;
    values[key] = value;

    return 1;
}

int Bucket::remove(int key)
{
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
    {
        values.erase(it);
        return 1;
    }
    else
    {
        cout << "No se puede eliminar: clave no existente" << endl;
        return 0;
    }
}

int Bucket::update(int key, string value)
{
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
    {
        values[key] = value;
        cout << "Valor actualizado" << endl;
        return 1;
    }
    else
    {
        cout << "No se puede actualizar: clave no existente" << endl;
        return 0;
    }
}

void Bucket::search(int key)
{
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
    {
        cout << "  ID   |   NOMBRE   |" << endl;
        cout << "  "<<key << "        " << it->second;
        cout << endl;
    }
    else
    {
        cout << "Esta clave no existe" << endl;
    }
}

bool Bucket::search_a(int key)
{
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bucket::tabla_full(int key)
{
    ofstream archivo;
    archivo.open("1.txt", ios::app);
    std::map<int, string>::iterator it;
    it = values.find(key);
    if (it != values.end())
    {
        cout << "  " << key << "        " << it->second << endl;
        archivo << "  " << key << "        " << it->second<<endl;
    }

}

int Bucket::isFull(void)
{
    if (values.size() == size)
        return 1;
    else
        return 0;
}

int Bucket::isEmpty(void)
{
    if (values.size() == 0)
        return 1;
    else
        return 0;
}

int Bucket::getDepth(void)
{
    return depth;
}

int Bucket::increaseDepth(void)
{
    depth++;
    return depth;
}

int Bucket::decreaseDepth(void)
{
    depth--;
    return depth;
}

std::map<int, string> Bucket::copy(void)
{
    std::map<int, string> temp(values.begin(), values.end());
    return temp;
}

void Bucket::clear(void)
{
    values.clear();
}

void Bucket::display()
{
    std::map<int, string>::iterator it;
    for (it = values.begin(); it != values.end(); it++)
        cout << it->first << " ";
    cout << endl;
}