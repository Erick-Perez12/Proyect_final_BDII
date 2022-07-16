#pragma once
#include<iostream>
#include <vector>
#include "Bucket.h"
#include <set>
using namespace std;

class Directory {
    int global_depth, bucket_size;
    std::vector<Bucket*> buckets;
    int hash(int n);
    int pairIndex(int bucket_no, int depth);
    void grow(void);
    void shrink(void);
    void split(int bucket_no);
    void merge(int bucket_no);
    string bucket_id(int n);
public:
    Directory(int depth, int bucket_size);
    void aea(int max);
    void insert(int key, string value, bool reinserted);
    void remove(int key, int mode);
    void update(int key, string value);
    void search(int key);
    void tabla();
    void display(bool duplicates);
};

Directory::Directory(int depth, int bucket_size)
{
    this->global_depth = depth;
    this->bucket_size = bucket_size;
    for (int i = 0; i < 1 << depth; i++)
    {
        buckets.push_back(new Bucket(depth, bucket_size));
    }
}

int Directory::hash(int n)
{
    return n & ((1 << global_depth) - 1);
}

int Directory::pairIndex(int bucket_no, int depth)
{
    return bucket_no ^ (1 << (depth - 1));
}

void Directory::grow(void)
{
    for (int i = 0; i < 1 << global_depth; i++) {
        buckets.push_back(buckets[i]);
    }
    global_depth++;
}

void Directory::shrink(void)
{
    int i, flag = 1;
    for (i = 0; i < buckets.size(); i++)
    {
        if (buckets[i]->getDepth() == global_depth)
        {
            flag = 0;
            return;
        }
    }
    global_depth--;
    for (i = 0; i < 1 << global_depth; i++)
        buckets.pop_back();
}

void Directory::split(int bucket_no)
{
    int local_depth, pair_index, index_diff, dir_size, i;
    map<int, string> temp;
    map<int, string>::iterator it;

    local_depth = buckets[bucket_no]->increaseDepth();
    if (local_depth > global_depth)
        grow();
    pair_index = pairIndex(bucket_no, local_depth);
    buckets[pair_index] = new Bucket(local_depth, bucket_size);
    temp = buckets[bucket_no]->copy();
    buckets[bucket_no]->clear();
    index_diff = 1 << local_depth;
    dir_size = 1 << global_depth;
    for (i = pair_index - index_diff; i >= 0; i -= index_diff)
        buckets[i] = buckets[pair_index];
    for (i = pair_index + index_diff; i < dir_size; i += index_diff)
        buckets[i] = buckets[pair_index];
    for (it = temp.begin(); it != temp.end(); it++)
        insert((*it).first, (*it).second, 1);
}

void Directory::merge(int bucket_no)
{
    int local_depth, pair_index, index_diff, dir_size, i;

    local_depth = buckets[bucket_no]->getDepth();
    pair_index = pairIndex(bucket_no, local_depth);
    index_diff = 1 << local_depth;
    dir_size = 1 << global_depth;

    if (buckets[pair_index]->getDepth() == local_depth)
    {
        buckets[pair_index]->decreaseDepth();
        delete(buckets[bucket_no]);
        buckets[bucket_no] = buckets[pair_index];
        for (i = bucket_no - index_diff; i >= 0; i -= index_diff)
            buckets[i] = buckets[pair_index];
        for (i = bucket_no + index_diff; i < dir_size; i += index_diff)
            buckets[i] = buckets[pair_index];
    }
}

string Directory::bucket_id(int n)
{
    int d;
    string s;
    d = buckets[n]->getDepth();
    s = "";
    while (n > 0 && d > 0)
    {
        s = (n % 2 == 0 ? "0" : "1") + s;
        n /= 2;
        d--;
    }
    while (d > 0)
    {
        s = "0" + s;
        d--;
    }
    return s;
}

int cont = 0;
void Directory::aea(int max) {
    if (cont <= max) {
        cont = max;
    }
}

void Directory::insert(int key, string value, bool reinserted)
{
    int bucket_no = hash(key);
    int max = key;
    int status = buckets[bucket_no]->insert(key, value);
    if (status == 1)
    {
        if (!reinserted){
            cout << "Hecho" << endl;
        }
        //cout << "Insertar key " << key << " en el bucket " << bucket_id(bucket_no) << endl;
        else {
            cout << "Hecho" << endl; 
        }
        aea(max);
    }
            //cout << "Mover key " << key << " al bucket " << bucket_id(bucket_no) << endl;
    else if (status == 0)
    {
        split(bucket_no);
        insert(key, value, reinserted);
    }
    else
    {
        cout << "Key " << key << " ya existente" << bucket_id(bucket_no) << endl;
    }
}

void Directory::remove(int key, int mode)
{
    int bucket_no = hash(key);
    if (buckets[bucket_no]->remove(key))
        cout << "Eliminado" << endl;
        //cout << "Deleted key " << key << " del bucket " << bucket_id(bucket_no) << endl;
    if (mode > 0)
    {
        if (buckets[bucket_no]->isEmpty() && buckets[bucket_no]->getDepth() > 1)
            merge(bucket_no);
    }
    if (mode > 1)
    {
        shrink();
    }
}

void Directory::update(int key, string value)
{
    int bucket_no = hash(key);
    buckets[bucket_no]->update(key, value);
}

void Directory::search(int key)
{
    int bucket_no = hash(key);
    //cout << "key de busqueda " << key << " en bucket " << bucket_id(bucket_no) << endl;
    buckets[bucket_no]->search(key);
}

void Directory::tabla() {
    int key = 0;
    cout << "  ID   |   NOMBRE   |" << endl;
    for (int i = 0 ; i < cont+1; i++) {
        int bucket_no = hash(key);
        if (buckets[bucket_no]->search_a(key) == true) {
            buckets[bucket_no]->tabla_full(key);
            key++;
        }
        else {
            key++;
        }
    }
}

void Directory::display(bool duplicates)
{
    int i, j, d;
    string s;
    std::set<string> shown;
    cout << "Profundidad global : " << global_depth << endl;
    for (i = 0; i < buckets.size(); i++)
    {
        d = buckets[i]->getDepth();
        s = bucket_id(i);
        if (duplicates || shown.find(s) == shown.end())
        {
            shown.insert(s);
            for (j = d; j <= global_depth; j++)
                cout << " ";
            cout << s << " => ";
            buckets[i]->display();
        }
    }
}

