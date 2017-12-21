#ifndef MODEL
#define MODEL
#include <iostream>
#include <string>
using namespace std;
class Model {

public:
    void receiveInput(string input);
    string getData();

private:
  string data;
};

#endif