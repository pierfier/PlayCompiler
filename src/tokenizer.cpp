#include <iostream>
#include <string>

using namespace std;

Tokenizer::Tokenizer(string filename){
    get_text_characters(filename);
}

// Put everything into file_contents variable
void Tokenizer::get_text_characters(string file){
    ifstream in(file);
    string line;
    
    while(getline(in, line)){
        file_contents += line;
    }

    in.close();
}

// Take file contents string and start to tokenize
void Tokenizer::tokenize(){
    if(!file_contents.empty()){
        string file_stream = file_contents;
        
        while(!file_stream.empty()){
            Token token;
            switch(file_stream[0]){
                
                //NOTE this is a Bad way of doing, this. The switch cases should actually be used for individual characters.
                //
                //For the keywords, I should just keep reading until a space or separator is found.

                case '(':
                    token.type = sep;
                    token.value = string("LParam");
                    tokens_.push_back();
                    
                    //TODO remove front character
                    //file_stream = 
                    break;

                case ')':
                    token.type = sep;
                    token.value = string("RParam");
                    break;
                
                case '[':
                    token,    
                    break;

                

                //Func keyword
                
                case 'F':
                    if(file_stream.substr(0, 5) == string("Func ")){
                        Token token;
                        token.type = key;
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
