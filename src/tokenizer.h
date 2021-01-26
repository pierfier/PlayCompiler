#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>

using namespace std;

// Token definitions
enum TokenType = {key, id, logic, group, sep, lit};

struct Token{
    TokenType t_type;
    string value;
};


// Operate and encapsulate
class Tokenizer{
    public:


    private:
        string file_contents_;
        vector<token> tokens_;
}:

#endif
