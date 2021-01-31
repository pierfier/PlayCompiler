#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

using namespace std;

// Token definitions

enum TokenType {key, id, logic, group, sep, lit};
// Token structure:
//  -- The type
//  -- the value
//  -- its source file and line number
struct Token{
    TokenType t_type;
    string value;
    string source_loc;
};

// Correspond enum values to their string literal
extern string enum_map[];

// Help for checking identifiers
extern char indi_chars[]; 

// Operate and encapsulate
class Tokenizer{
    public:
        Tokenizer(string source_file);
        void tokenize();
        void print_tokens();
    private:
        // Internal functions
        void get_text_characters(string file);
        string remove_front(string stream);
        string get_string_literal(string & stream, int line_num);
        string read_num(string & stream, int line_num);

        // Variables
        string source_filename;
        string file_contents_;
        vector<Token> tokens_;
};

#endif
