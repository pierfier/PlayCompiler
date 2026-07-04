#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <string>

using namespace std;

// Native, C++-implemented functions exposed to PlayCompiler programs.
// TODO signatures will need to change once there is a real Value/AST-result
// type to pass in and return, instead of a placeholder string.

void print(const string & value);

#endif
