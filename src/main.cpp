#include <iostream>
#include <string>
#include "tokenizer.h"
#include <vector>

using namespace std;

int main(int argc, char * argv[]){
    // Store all of the source file filenames   
    vector<string> source_files;

    // Read in files to compile
    for(int i = 0; i < argc; ++i){
        
        // If argument is not a dash, it must be a filename not a flag
        if(argv[i][0] != '-'){
            source_files.push_back(string(argv[i+1]));
        }
    }

    // Front End stuff
    vector<Tokenizer> tokens;
    
    for(int i = 0; i < source_files.size(); ++i){
        tokens.push_back(Tokenizer(source_files[i]));
    }

    return 0;
}
