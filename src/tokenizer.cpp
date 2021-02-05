#include <iostream>
#include <fstream>
#include<ctype.h>
#include <string>
#include "tokenizer.h"

using namespace std;

//-- Start of global variable definitions

// Intialize the individual characters
char indi_chars[] = {'[', ']', '(', ')', '{', '}', ',', '"'};

string enum_map[] = {"key", "identifier", "operator", "logic", "group", "separator", "literal"};
//-- End of global variable definitions


Tokenizer::Tokenizer(string filename){
    get_text_characters(filename);
    source_filename = filename;
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
//return the popped value and chop the string as a side effect
string Tokenizer::pop_front(string & stream){
    string f_char;
    f_char = stream[0];

    if(stream.length() >= 2){
        stream = stream.substr(1, stream.length() - 1);
        
    }else{
        stream = "";
    }

    return f_char;
}


// Read in a word that is only consisted of numbers or characters
// Assumes that user already checked that the first character is a letter
// Kills the program if there is a symbolage that is not recognized
string Tokenizer::read_word(string & stream, int line_num){
    string word;
    
    // Concatenate all digits and decimal points
    while(isalpha(stream[0]) || isdigit(stream[0])){
        word += pop_front(stream);
    }

    return word;
}

// Read in a number literal and remove all of the 
string Tokenizer::read_num(string & stream, int line_num){
    string num;

    // Decimal should only be found once
    // TODO need to implement this ^
    bool pointFound = false;


    // Concatenate all digits and decimal points
    while(isdigit(stream[0]) || stream[0] == '.'){
        num += pop_front(stream);
    }

    return num;
}

//Read in until another unescaped '\' character appears in the string
//It will trim the stream variable that is passed to function
string Tokenizer::get_string_literal(string & stream, int line_num){
    string literal("");
    string f_char;

    while(stream[0] != '"'){
        f_char = pop_front(stream);
        
        //Escape character, ignore next character
        if(f_char == string("\\") && stream.length() > 0){
            literal += pop_front(stream);
        
        // Reached end of file and no string literal enclosure
        }else if(f_char == string("\\") && stream.length() == 0){
            cout << "ERROR [Lexer]: string not completed after \\ escape character at" << source_filename << ": " << line_num << "\n";
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
        
        int line_count = 1;
        
        // Keep reading word until a separator, grouping, or space is encountered
        string word; 
        while(!file_stream.empty()){

            Token token;
            switch(file_stream[0]){
                
                case '(':
                    token.t_type = group;
                    token.value = string("LParam");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;

                case ')':
                    token.t_type = group;
                    token.value = string("RParam");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                
                case '[':
                    token.t_type = group;    
                    token.value = string("RBracket");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;

                case ']':
                    token.t_type = group;    
                    token.value = string("LBracket");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '{':
                    token.t_type = group;    
                    token.value = string("LCurl");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '}':
                    token.t_type = group;    
                    token.value = string("RCurl");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case ',':
                    token.t_type = sep;    
                    token.value = string("Comma");
                    cout << "asdfdaf " << enum_map[token.t_type] << "\n";
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '=':
                    token.t_type = op;    
                    token.value = string("Assign");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '+':
                    token.t_type = op;    
                    token.value = string("Add");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '-':
                    token.t_type = op;    
                    token.value = string("Subtract");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '*':
                    token.t_type = op;    
                    token.value = string("Multiply");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;
                case '/':
                    token.t_type = op;    
                    token.value = string("Divide");
                    tokens_.push_back(token);
                    pop_front(file_stream);
                    break;

                    //This made need some debugging. I will do a string literal 
                case '"':
                    pop_front(file_stream);
                    token.t_type = lit;
                    token.value = get_string_literal(file_stream, line_count);
                    tokens_.push_back(token);
                    break;

                // Ignore newlines and update the line count
                case '\n':
                    pop_front(file_stream);
                    ++line_count;
                    break;
                case ' ':
                    pop_front(file_stream);
                    ++line_count;
                    break;

                // Check for words, i.e. keywords and identifiers, and numbrs
                default:
                    string word;
                    
                    // word is a number sequence, throw error if it is not
                    if(isdigit(file_stream[0])){
                        word = read_num(file_stream, line_count);
                        
                        //TODO add number token types

                    }else{
                        //Read characters until a separator or grouping is found
                        //Preserve that separator, grouping, or space character
                        word = read_word(file_stream, line_count);
                        
                        // Word is empty meaning symbolage is not recognized
                        if(word.empty()){
                            cout << "Unknown character -" << file_stream[0] << "-\n";
                            
                            // Completely kill the compiler
                            exit(0);
                            
                        // Word is complete, so check if its a keyword
                        }else{
                            
                            // Word is a keyword
                            if(word == string("Func") || word == string("if") || word == string("let") || word == string("in") || word == string("main") || word == string("do")){
                                token.t_type = key;
                                token.value = word;
                                tokens_.push_back(token);
                            
                            // Word is an identifier
                            }else{
                                token.t_type = id;
                                token.value = word;
                                tokens_.push_back(token);
                            }
                        }

                    }
            }
        }
    }else{
        cout << "Read in file contents" << endl;
    }
}

// Barebone printing of all the tokens that are collected so far
void Tokenizer::print_tokens(){
    int num_padding = 0;
    
    cout << "--Printing tokens--" << "\n";

    for(int i = 0; i < tokens_.size(); ++i){
        cout << enum_map[tokens_[i].t_type] << ": " << tokens_[i].value << "\n";
    }
}
