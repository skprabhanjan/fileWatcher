#include <iostream>
#include "Model.h"
#include <string>
using namespace std;

void Model::receiveInput(string input)
{
    data = input;
}

string Model::getData()
{
    return data;
}
