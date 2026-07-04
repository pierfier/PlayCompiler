#include <iostream>
#include <string>
#include "parser.h"
#include "tokenizer.h"

using namespace std;

//TODO implement constructor: needs to initialize tokens_ and pos_
Parser::Parser(vector<Token> tokens){
    tokens_ = tokens;
    pos_ = 0;
}

//TODO implement: true when pos_ has run past the end of tokens_
bool Parser::atEnd(){
    return pos_ >= tokens_.size();
}

//TODO implement: return the current token without consuming it
Token Parser::peek(){
    return tokens_[pos_];
}

Token Parser::advance(){
    Token t = tokens_[pos_];
    pos_ += 1;
    return t;
}

void Parser::parse_id_expr(){
    // Save the identifier
    Token var_t = advance();
    Token next_t = peek();
    
    // If the next token is a closed grouping then return the final variable reference as is
    if(next_t.t_type == TokenType::group && 
        (next_t.value == "RParen" || next_t.value == "RCurl")){
        //TODO return variable reference     
    }else{
        parse_expr();
    }
}

//TODO implement: parse a `let x = e1 in e2` expression
void Parser::parse_let_expr(){
}

void Parser::parse_do_expr(){
    Token t = advance();

    if(t.t_type != TokenType::group && t.value != "LCurl"){
        cout << "Missing LCurl" << endl;
        //TODO error
    }

    t = advance();
    while(t.t_type != TokenType::group && t.value != "RCurl"){
        parse_expr();
    }
}

void Parser::parse_expr(){
    Token cur_t = peek();

    switch(cur_t.t_type){
        case TokenType::id:
            parse_id_expr();
            break;
        case TokenType::key:
            // "let" statement then evaluate assignment expression
            if(cur_t.value == "let"){
                parse_let_expr();
            }else if(cur_t.value == "do"){
                parse_do_expr();
            }
            // if statements, then just evaluate the ifs

            //TODO may need to remove this at some point
            advance();

            break;
        default:
            // I am not sure what to do here actually
            advance();
            break;
    };
}

void Parser::parse_func(){
    //Consume the Func key term
    advance();

    //Grab the identifier token
    Token t = advance();
    
    string func_name;
    vector<string> args; // TODO figure out how to keep scope here?

    if(t.t_type == TokenType::id){
        //TODO I believe I need to start adding some AST nodes here

        func_name = t.value;

        // Read in and check for arguments
        t = advance();

        if(t.t_type == TokenType::group && t.value == "LParen"){

            // Repeatedly read in arguments
            t = advance();
            while(t.t_type != TokenType::group && t.value != "RParen"){
                
                //TODO if its a separator, continue onward, otherwise parse expression
                if(t.t_type == TokenType::id){
                    args.push_back(t.value);   
                    
                }else if(t.t_type == TokenType::sep && t.value == "Comma"){
                    t = advance();

                    if(t.t_type == TokenType::id){
                        args.push_back(t.value);   
                    
                    }else{
                        cout << "Missing identifier at " << t.source_loc << endl;
                    }
                }else{
                    cout << "Unknown Symbol " << t.value << " at " << t.source_loc << endl;
                }

                t = advance();                
            }
            
            t = advance();

            //TODO start parsing the functions main body
            if(t.t_type == TokenType::group && t.value == "LCurl"){
                // Keep parsing functions
                while(t.t_type != TokenType::group && t.value != "RCurl"){
                    parse_expr(); //TODO would I need to return nodes here? Most likely!
                }
                //TODO eat the rightCurl
            }

        }else{
            cout << "Missing '(' in function declaration" << endl;
        }

    }else{
        cout << "Missing function identifier: " << t.source_loc << endl;
    }
}

void Parser::parse_main(){
    // Eat the 'main' keyword
    advance();
    // Eat the = symbol
    Token t = advance();
    if(t.value != "Assign"){
        cout << "Missing =" << endl;
        //TODO return Null Error
    }

    // Parse the expression
    parse_expr();
}

// Entry point to parse the whole program
void Parser::parse_program(){
    while(!atEnd()){

        Token t = peek();

        // Determine which grammar rule handles this token
        switch(t.t_type){
            case TokenType::key:
                if(t.value == "Func"){
                    parse_func(); // Found a function and need to parse it
                }else if(t.value == "main"){
                    parse_main(); // Found the main function to start the program
                }
            break;

            default:
                advance(); // Skip anything we don't handle yet
            break;
        }


        //DEBUG
        //cout << "Still looping whole program";
    }
}
