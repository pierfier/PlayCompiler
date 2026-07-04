#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include "tokenizer.h"

using namespace std;


// Operate and encapsulate
class Parser{
    public:
        Parser(vector<Token> tokens);

        // Entry point
        void parse_program();

    private:
        // Grammar rules
        void parse_func();
        void parse_main();
        void parse_expr();
        void parse_id_expr();
        void parse_let_expr(); //TODO implement body in parser.cpp
        void parse_do_expr();

        // Cursor helpers
        bool atEnd();
        Token peek();
        Token advance();

        // Variables
        vector<Token> tokens_;
        int pos_;
};

#endif
