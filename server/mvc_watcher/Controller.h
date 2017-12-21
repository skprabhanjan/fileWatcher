#ifndef CONTROLLER
#define CONTROLLER
#include "Model.h"
#include "View.h"
#include <iostream>
class Controller{
    public:
    int traverseFS(char *foler,int first_time,Model &model,View &view);
    string send_notification(char *cmd);
    long getFileCreationTime(char *path,int first);
};

#endif