#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct Value
{
    string key;
    int gridx;
    int gridy;
    string color;
    int val1;
    float val2;
};

class Data
{
    public:
        Data();
        Data(int sizeIn);
        void Add(Value record);
        void Delete(string key);
        Value LookUp(string key);
        void printValue(Value record);
    private:
        int size;
        vector<Value> seqData;
        int hashFunction(int key);
        void seqAdd(Value record);
        void hashAdd(Value record);
        void seqDelete(string key);
        void hashDelete(string key);
        Value seqLookUp(string key);
        Value hashLookUp(string key);
};

Data::Data() { size = 100; }

Data::Data(int sizeIn) { size = sizeIn; }

// public
void Data::Add(Value record)
{
    seqAdd(record);
}

/*
void Data::Delete(string key)
{
    seqDelete(key);
}

*/
Value Data::LookUp(string key)
{
    return seqLookUp(key);
}

void Data::printValue(Value record)
{
    cout << "Key: " << record.key << endl <<
    "    X: " << record.gridx << endl <<
    "    Y: " << record.gridy << endl <<
    "Color: " << record.color << endl <<
    "Val 1: " << record.val1 << endl <<
    "Val 2: " << record.val2 << endl;
}

// private

/*
int Data::hashFunction(int key)
{
}
*/

void Data::seqAdd(Value record)
{
    seqData.push_back(record);
}

/*
void Data::hashAdd(Value record)
{
}

void Data::seqDelete(string key)
{
}

void Data::hashDelete(string key)
{
}

*/
Value Data::seqLookUp(string key)
{
    for (int i=0;i<seqData.size();i++){
        if (seqData[i].key == key){
            return seqData[i];
        }
    }
    cout << "Key not found in list" << endl;
    exit(1);
}

/*
Value Data::hashLookUp(string key)
{
}
*/

int main(int argc, char *argv[])
{
    ifstream file;

    if (argc != 3)
    {
        cout << "Error: file not provided!" << endl;
        return 1;
    }
    file.open(argv[1]);

    Data dataObject;
    Value value;
    string data;
    while(getline(file, value.key, ','))
    {
        getline(file, data, ',');
        value.gridx = stoi(data);

        getline(file, data, ',');
        value.gridy = stoi(data);

        getline(file, value.color, ',');

        getline(file, data, ',');
        value.val1 = stoi(data);

        getline(file, data);
        value.val2 = stof(data);
        dataObject.Add(value);
    }
    file.close();

    file.open(argv[2]);
    string action;
    while(getline(file, action, ','))
    {
        if (action == "add")
        {
            getline(file, data, ',');
            value.key = data;

            getline(file, data, ',');
            value.gridx = stoi(data);

            getline(file, data, ',');
            value.gridy = stoi(data);

            getline(file, value.color, ',');

            getline(file, data, ',');
            value.val1 = stoi(data);

            getline(file, data);
            value.val2 = stof(data);

            dataObject.Add(value);
        }
        else if (action == "search")
        {
            getline(file, data);
            dataObject.printValue(dataObject.LookUp(data));
        }
        else if (action == "remove")
        {
            // getline(file, data);
            // dataObject.Delete(data);
        }
    }
    file.close();

    return  0;
}
