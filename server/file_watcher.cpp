#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  
#include <sstream>
#include <map>
#include <iterator>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

 using namespace std;

// void filePutContents(const std::string& name, const std::string& content, bool append = false) {
//     std::ofstream outfile;
//     if (append)
//         outfile.open(name, std::ios_base::app);
//     else
//         outfile.open(name);
//     outfile << content;
// }

std::string send_notification(char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

long getFileCreationTime( char* path,int first) {
    struct stat attr;
    stat(path, &attr);
    ifstream filestr;

    filestr.open("data.txt", ios::binary); // open your file
    filestr.seekg(0, ios::end);                         // put the "cursor" at the end of the file
    int length = filestr.tellg();                           // find the position of the cursor
    filestr.close();                                    // close your file

    if (length == 0 || first)
    {
        std::ofstream ofs;
        ofs.open("data.txt", std::ofstream::out | std::ofstream::app);
        string data = string(path) + " " + to_string(attr.st_mtime);
        ofs << data << endl;
        ofs.close();
    }

    //printf("Last modified time: %s", ctime(&attr.st_mtime));
    // freopen("data.txt","a+",stdout);
    // cout << path << " " << attr.st_mtime <<  "\n";
    //std::time_t mod_time = std::chrono::system_clock::to_time_t(&attr.st_mtime);
    // cout << mod_time << endl;
    //fclose (stdout);
    return attr.st_mtime;
}


int traverseFS(char* folder,int first_time){
	DIR *dir;
	struct dirent *ent;
	const char* path = folder; // folder to be traversed
     map<string,int> changed_times;
     std::ifstream file("data.txt");
        std::string str;
        while (std::getline(file, str))
        {
            istringstream iss(str);
            vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
            if(results.size() != 0 ){
                stringstream convert(results[1]);
                int time_stamp = 0;
                convert >> time_stamp;
                changed_times.insert(pair<string,int>(results[0],time_stamp));
            }
        }
        // map<string, int>::iterator itr;
        // for (itr = changed_times.begin(); itr != changed_times.end(); ++itr)
        // {
        //     cout << '\t' << itr->first
        //          << '\t' << itr->second << '\n';
        // }
        // cout << endl;
	if ((dir = opendir (path)) != NULL) {

	  while ((ent = readdir (dir)) != NULL) {
		//printf ("%s\n", ent->d_name);
		char* ffpath = new char[256];
		// if(*path != '.'){
		// 	strcpy(ffpath , "./");
		// }
		//cout << "ffpath : " << ffpath << endl;
		strcat(ffpath , path);
		//cout << "FIRST ffpath : " << ffpath << endl;
		strcat(ffpath , "/");
		//cout << "ffpath : " << ffpath << endl;
		strcat(ffpath , ent->d_name);
        //puts(ffpath);
		//printf("/n");
        long lastModified = getFileCreationTime(ffpath,first_time);
        std::map<string,int>::iterator it;
        it = changed_times.find(ffpath);
        if( it != changed_times.end()){
            if(it->second < lastModified){
                if( it->first.substr(it->first.length() - 2) != ".." && it->first.substr(it->first.length() - 2) != "/."){
                    cout << "\n" << it->first << " File Has Changed" << endl;
                    //char *url = "curl -s localhost:8080/file_changed?filename=hi > /dev/null";
                    char *url = new char[256];
                    ifstream inFile;
                    inFile.open("client.txt");
                    char *x;                    
                    //strcpy(url,"curl -s localhost:8080/file_changed?filename=");
                    strcpy(url,"curl -s ");
                    while(inFile >> x){
                        strcat(url,x);
                    }
                    strcat(url,"file_changed?filename=");
                    string filename = it->first;
                    int l = filename.length();
                    char filename_char[l+1];
                    strcpy(filename_char,filename.c_str());
                    strcat(url,filename_char);
                    strcat(url," > /dev/null");
                    send_notification(url);
                    //send_notification("curl localhost:8080/file_changed?filename="+ (it->first));
                    std::fstream fs("data.txt", std::fstream::out | std::fstream::trunc);
                    traverseFS(folder,1);
                }
            }
            else{
                //cout <<  it->first << " File Not Changed" << endl;
            }
        }
        else{
            //cout << "not found" << endl;
        }
	  }
	  closedir (dir);
	}
    else{
        return -1;
    }
return -1;
}

int main(){

	char* path = (char *)"/Users/prabhanjansk/uspPrograms";
    int first_time = 1;
    cout << "Watching For Any Changes in " << path  << endl;
    while(true){
        sleep(2);
        traverseFS(path,first_time);
        first_time = 0;
    }
	

}
