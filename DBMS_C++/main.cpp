#include <iostream>
#include "Directory.h"
using namespace std;


void menu()
{
    cout << "--------------------" << endl;
    cout << "Ingrese las consultas en el siguiente formato :" << endl;
    cout << "insert <key> <valor>     (key: entero, value: string)" << endl;
    cout << "delete <key> <modo>      (modo: 0-Perezoso / 1-combinar buckets vacios / 2-combinar buckets y reducirlo )" << endl;
    cout << "update <key> <nuevo valor>" << endl;
    cout << "search <key>" << endl;
    cout << "tabla" << endl;
    cout << "display" << endl;
    cout << "exit" << endl;
    cout << "--------------------" << endl;
}

int main()
{
    bool show_messages, show_duplicate_buckets;
    int bucket_size, initial_global_depth;
    int key, mode;
    string choice, value;

    show_messages = 1;

    show_duplicate_buckets = 0;

    if (show_messages) { cout << "Tamaño del Bucket  : "; }
    cin >> bucket_size;
    if (show_messages) { cout << "Profundidad global inicial : "; }
    cin >> initial_global_depth;

    Directory d(initial_global_depth, bucket_size);
    cout << endl << "Estructura de directorio inicializada" << endl;

    if (show_messages)
        menu();

    do
    {
        cout << endl;
        if (show_messages) { cout << ">>> "; }
        cin >> choice;
        if (choice == "insert")
        {
            cin >> key >> value;
            if (show_messages) { cout << endl; }
            d.insert(key, value, 0);
        }
        else if (choice == "delete")
        {
            cin >> key >> mode;
            if (show_messages) { cout << endl; }
            d.remove(key, mode);
        }
        else if (choice == "update")
        {
            cin >> key >> value;
            if (show_messages) { cout << endl; }
            d.update(key, value);
        }
        else if (choice == "search")
        {
            cin >> key;
            if (show_messages) { cout << endl; }
            d.search(key);
        }
        else if (choice == "tabla") {
            if (show_messages) { cout << endl; }
            d.tabla();
        }
        else if (choice == "display")
        {
            if (show_messages) { cout << endl; }
            d.display(show_duplicate_buckets);
        }
    } while (choice != "exit");

    return 0;
}


