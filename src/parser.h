#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

using namespace std;


// Operate and encapsulate
class Parser{
    public:
        Tokenizer(string source_file);
    private:
        // Internal functions

        // Variables
        vector<Token> tokens_;
};

#endif
