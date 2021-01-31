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

//Pop front of the string
string Tokenizer::remove_front(string stream){
    if(stream.length() >= 2){
        return stream.substr(1, stream.length() - 1);
    }else{
        return string("");
    }
}

//Read in until another unescaped '\' character appears in the string
string Tokenizer::get_string_literal(string stream){
    string literal("");
    string f_char;

    while(stream[0] != '"'){
        f_char = remove_front(stream);
        
        if(f_char == string("\\")){
            literal += remove_front(stream);
        }else{
            literal += f_char;
        }
    }

    return literal;
}

// Take file contents string and start to tokenize
void Tokenizer::tokenize(){
    if(!file_contents_.empty()){
        string file_stream = file_contents_;
        
        while(!file_stream.empty()){
            Token token;
            switch(file_stream[0]){
                
                case '(':
                    token.t_type = group;
                    token.value = string("LParam");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;

                case ')':
                    token.t_type = group;
                    token.value = string("RParam");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;
                
                case '[':
                    token.t_type = group;    
                    token.value = string("RBracket");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;

                case ']':
                    token.t_type = group;    
                    token.value = string("LBracket");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;
                case '{':
                    token.t_type = group;    
                    token.value = string("LCurl");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;
                case '}':
                    token.t_type = group;    
                    token.value = string("RCurl");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;
                case ',':
                    token.t_type = sep;    
                    token.value = string("Comma");
                    tokens_.push_back(token);
                    file_stream = remove_front(file_stream);
                    break;
                
                    //This made need some debugging. I will do a string literal 
                case '"':
                    file_stream = remove_front(file_stream);
                    token.t_type = lit;
                    token.value = get_string_literal(file_stream);
                    tokens_.push_back(token);
                    break;


                // Check full words
                default:
                    

                //Func keyword
                //TODO should probably do this after switch statement
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
