#include <iostream>
#include "View.h"
#include "Model.h"
#include <string>
using namespace std;

void View::displayData(Model &model)
{
    std::cout << "\nFile Changed : " << model.getData() << "\n" << std::endl;
}