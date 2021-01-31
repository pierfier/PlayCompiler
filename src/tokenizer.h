#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

using namespace std;

// Token definitions
enum TokenType {key, id, logic, group, sep, lit};

struct Token{
    TokenType t_type;
    string value;
};


// Operate and encapsulate
class Tokenizer{
    public:
        Tokenizer(string source_file);
        void tokenize();
    private:
        void get_text_characters(string file);
        string remove_front(string stream);

        string file_contents_;
        vector<Token> tokens_;
};

#endif
