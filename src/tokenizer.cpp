#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include "tokenizer.h"

using namespace std;

char indi_chars[] = {'[', ']', '(', ')', '{', '}', ',', '"'};

string enum_map[] = {"key", "identifier", "operator", "logic", "group", "separator", "literal"};


Tokenizer::Tokenizer(string filename){
    get_text_characters(filename);
    source_filename = filename;
}

// Put each line into file_contents_, restoring the newline getline strips
void Tokenizer::get_text_characters(string f){
    ifstream in(f.c_str(), ifstream::in);
    string line;

    while(getline(in, line)){
        file_contents_ += line;
        file_contents_ += '\n';
    }

    in.close();
}

// Pop front of the string; return the popped character as a string
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

// Read an alphanumeric word (identifiers and keywords); underscores allowed
string Tokenizer::read_word(string & stream, int line_num){
    string word;

    while(!stream.empty() && (isalpha(stream[0]) || isdigit(stream[0]) || stream[0] == '_')){
        word += pop_front(stream);
    }

    return word;
}

// Read a numeric literal; enforces at most one decimal point
string Tokenizer::read_num(string & stream, int line_num){
    string num;
    bool pointFound = false;

    while(!stream.empty() && (isdigit(stream[0]) || stream[0] == '.')){
        if(stream[0] == '.'){
            if(pointFound){
                cout << "ERROR [Lexer]: Numbers cannot have more than one decimal point at "
                     << source_filename << ":" << line_num << "\n";
                exit(0);
            }
            pointFound = true;
        }
        num += pop_front(stream);
    }

    return num;
}

// Read characters until an unescaped closing '"'; consumes the closing '"'
string Tokenizer::get_string_literal(string & stream, int line_num){
    string literal;
    string f_char;

    while(!stream.empty() && stream[0] != '"'){
        f_char = pop_front(stream);

        if(f_char == string("\\") && !stream.empty()){
            literal += pop_front(stream);
        }else if(f_char == string("\\") && stream.empty()){
            cout << "ERROR [Lexer]: Unterminated string after \\ at "
                 << source_filename << ":" << line_num << "\n";
            exit(0);
        }else{
            literal += f_char;
        }
    }

    if(stream.empty()){
        cout << "ERROR [Lexer]: Unterminated string literal at "
             << source_filename << ":" << line_num << "\n";
        exit(0);
    }
    pop_front(stream);  // consume closing "

    return literal;
}

// Tokenize file_contents_ into tokens_
void Tokenizer::tokenize(){
    if(file_contents_.empty()){
        cout << "ERROR [Lexer]: Empty file contents\n";
        return;
    }

    string file_stream = file_contents_;
    int line_count = 1;

    while(!file_stream.empty()){
        Token token;
        token.source_loc = source_filename + ":" + to_string(line_count);

        switch(file_stream[0]){

            case '(':
                token.t_type = TokenType::group;
                token.value = "LParen";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case ')':
                token.t_type = TokenType::group;
                token.value = "RParen";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '[':
                token.t_type = TokenType::group;
                token.value = "LBracket";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case ']':
                token.t_type = TokenType::group;
                token.value = "RBracket";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '{':
                token.t_type = TokenType::group;
                token.value = "LCurl";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '}':
                token.t_type = TokenType::group;
                token.value = "RCurl";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case ',':
                token.t_type = TokenType::sep;
                token.value = "Comma";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '=':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '='){
                    pop_front(file_stream);
                    token.t_type = TokenType::logic;
                    token.value = "Eq";
                }else{
                    token.t_type = TokenType::op;
                    token.value = "Assign";
                }
                tokens_.push_back(token);
                break;

            case '+':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '+'){
                    pop_front(file_stream);
                    token.t_type = TokenType::op;
                    token.value = "Concat";
                }else{
                    token.t_type = TokenType::op;
                    token.value = "Add";
                }
                tokens_.push_back(token);
                break;

            case '-':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '>'){
                    pop_front(file_stream);
                    token.t_type = TokenType::op;
                    token.value = "Arrow";
                }else{
                    token.t_type = TokenType::op;
                    token.value = "Subtract";
                }
                tokens_.push_back(token);
                break;

            case '*':
                token.t_type = TokenType::op;
                token.value = "Multiply";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '/':
                token.t_type = TokenType::op;
                token.value = "Divide";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '<':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '='){
                    pop_front(file_stream);
                    token.t_type = TokenType::logic;
                    token.value = "LtEq";
                }else{
                    token.t_type = TokenType::logic;
                    token.value = "Lt";
                }
                tokens_.push_back(token);
                break;

            case '>':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '='){
                    pop_front(file_stream);
                    token.t_type = TokenType::logic;
                    token.value = "GtEq";
                }else{
                    token.t_type = TokenType::logic;
                    token.value = "Gt";
                }
                tokens_.push_back(token);
                break;

            case '!':
                pop_front(file_stream);
                if(!file_stream.empty() && file_stream[0] == '='){
                    pop_front(file_stream);
                    token.t_type = TokenType::logic;
                    token.value = "NEq";
                }else{
                    cout << "ERROR [Lexer]: Unexpected '!' at "
                         << source_filename << ":" << line_count << "\n";
                    exit(0);
                }
                tokens_.push_back(token);
                break;

            case '&':
                token.t_type = TokenType::op;
                token.value = "And";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            // Lambda backslash: \x -> x*x
            case '\\':
                token.t_type = TokenType::op;
                token.value = "Lambda";
                tokens_.push_back(token);
                pop_front(file_stream);
                break;

            case '"':
                pop_front(file_stream);
                token.t_type = TokenType::lit;
                token.value = get_string_literal(file_stream, line_count);
                tokens_.push_back(token);
                break;

            case '\n':
                pop_front(file_stream);
                ++line_count;
                break;

            case ' ':
            case '\t':
                pop_front(file_stream);
                break;

            default:
                if(isdigit(file_stream[0])){
                    string num = read_num(file_stream, line_count);
                    token.t_type = TokenType::lit;
                    token.value = num;
                    tokens_.push_back(token);
                }else{
                    string word = read_word(file_stream, line_count);

                    if(word.empty()){
                        cout << "ERROR [Lexer]: Unknown character '"
                             << file_stream[0] << "' at "
                             << source_filename << ":" << line_count << "\n";
                        exit(0);
                    }

                    if(word == "Func" || word == "if"   || word == "then" ||
                       word == "else" || word == "let"  || word == "in"   ||
                       word == "main" || word == "do"){
                        token.t_type = TokenType::key;
                    }else{
                        token.t_type = TokenType::id;
                    }
                    token.value = word;
                    tokens_.push_back(token);
                }
        }
    }
}

// Print all collected tokens
void Tokenizer::print_tokens(){
    cout << "--Printing tokens--\n";

    for(int i = 0; i < (int)tokens_.size(); ++i){
        cout << enum_map[static_cast<int>(tokens_[i].t_type)] << ": " << tokens_[i].value
             << " [" << tokens_[i].source_loc << "]\n";
    }
}

const vector<Token> & Tokenizer::get_tokens() const{
    return tokens_;
}
