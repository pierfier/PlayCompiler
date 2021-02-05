#include <iostream>
#include <string>
#include "tokenizer.h"
#include <vector>

using namespace std;

int main(int argc, char * argv[]){
    // Store all of the source file filenames   
    vector<string> source_files;

    // Read in files to compile
    for(int i = 1; i < argc; ++i){
        
        // If argument is not a dash, it must be a filename not a flag
        if(argv[i][0] != '-'){
            source_files.push_back(string(argv[i]));
        }else{
            //TODO use option flags
        }
        
    }

    // Front End stuff
    vector<Tokenizer> tokens;
    
    for(int i = 0; i < source_files.size(); ++i){
        tokens.push_back(Tokenizer(source_files[i]));
    }

    //Tokenize all of the source files
    //
    //TODO may need to do a glob where we store all of the tokens in one spot across all files, and then just have a single main file that starts everything
    for(int i = 0; i < tokens.size(); ++i){
        tokens[i].tokenize();
    }

    //DEBUG show all of the read tokens
    tokens[0].print_tokens();

    return 0;
}
