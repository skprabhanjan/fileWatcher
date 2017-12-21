#include <iostream>
#include <string>
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <unistd.h>
using namespace std;
int main(){
    // Model *m = new Model();
    // m->receiveInput("hi");
    // cout << m->getData() << endl;
    Model model;
    View view;
    Controller controller;
    // controller.getAndSendUserInput(model,view);
    char* path = (char *)"/Users/prabhanjansk/uspPrograms";
    int first_time = 1;
    cout << "Watching For Any Changes in " << path  << endl;
     while(true){
        sleep(2);
        controller.traverseFS(path,first_time,model,view);
        first_time = 0;
    }
    return 1;
}