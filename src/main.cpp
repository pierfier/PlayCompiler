#include <iostream>
#include <string>

using namespace std;

int main(int argc, char * argv[]){
    
    string[] source_files;

    // Read in files to compile
    for(int i = 0; i < argc; ++i){
        
        // If argument is not a dash, it must be a filename not a flag
        if(string(argv[i][0] != "-")){
            source_files.push_back(string(argv[i+1]));
        }
    }
}
