#include <iostream>
#include <fstream>
#include <string>
#include "tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(string filename){
    get_text_characters(filename);
}

// Put everything into file_contents variable
void Tokenizer::get_text_characters(string f){
    ifstream in(f.c_str(), ifstream::in);
    string line;
    
    while(getline(in, line)){
        file_contents_ += line;
    }

    in.close();
}

// Take file contents string and start to tokenize
void Tokenizer::tokenize(){
    if(!file_contents_.empty()){
        string file_stream = file_contents_;
        
        while(!file_stream.empty()){
            Token token;
            switch(file_stream[0]){
                
                //NOTE this is a Bad way of doing, this. The switch cases should actually be used for individual characters.
                //
                //For the keywords, I should just keep reading until a space or separator is found.

                case '(':
                    token.t_type = sep;
                    token.value = string("LParam");
                    tokens_.push_back(token);
                    
                    //TODO remove front character
                    file_stream = file_stream.substr(1, file_stream.length() - 1); // Is this the best way to remove the first character and keep the string
                    break;

                case ')':
                    token.t_type = sep;
                    token.value = string("RParam");
                    break;
                
                case '[':
                    token.t_type = sep;    
                    break;

                

                //Func keyword
                
                case 'F':
                    if(file_stream.substr(0, 5) == string("Func ")){
                        Token token;
                        token.t_type = key;
                        token.value = string("Func");
                        tokens_.push_back(token);
                        
                    }else{
                        //TODO read in indentifier
                    }

                    break;

                //if keyword
                case 'i':

                    break;

            }
        }

    }else{
        cout << "Read in file contents" << endl;
    }
}
