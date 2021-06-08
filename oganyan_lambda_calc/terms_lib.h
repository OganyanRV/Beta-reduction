// Copyright 2021 Oganyan Robert

#ifndef OGANYAN_LAMBDA_CALC_TERMS_LIB_H
#define OGANYAN_LAMBDA_CALC_TERMS_LIB_H

#include <iostream>
#include <string>
#include <map>

using std::map;
using std::string;

class LibFuncs {
private:
    map<string, string> functions;
public:
    LibFuncs() {

        // Logical functions

        functions["True"] = "(\\t (\\f t))";
        functions["False"] = "(\\t (\\f f))";
        functions["If"] = "(\\b (\\x (\\y b x y)))";
        functions["And"] = "(\\b (\\c b c False))";
        functions["Or"] = "(\\b (\\c b True c))";
        functions["Not"] = "(\\b b False True)";
        functions["IsZero"] = "(\\index index (\\c False) True)";
//        functions["Test"] = "(\\l (\\m (\\index l m index)))";

        // Nums

        functions["Zero"] = "(\\s (\\z z))";
        functions["One"] = "(\\s (\\z s z))";
        functions["Two"] = "(\\s (\\z s (s z)))";

        // Arithmetic functions

        functions["Scc"] = "(\\index (\\s (\\z s (index s z))))";
        functions["Plus"] = "(\\index (\\m (\\s (\\z (index s (m s z))))))";
        functions["Mult"] = "(\\x (\\y (x (Plus y) z)))";
        functions["Pow"] = "(\\index (\\m (\\s (\\ z (index s z)))))";

        //  Combinators

        functions["I"] = "(\\x x)";
        functions["S"] = "(\\f (\\g (\\x f x (g x))))";
        functions["K"] = "(\\x (\\y x))";
        functions["Omega"] = "((\\x x x)(\\x x x))";
        functions["B"] = "(\\f (\\g (\\x f (g x))))";
        functions["C"] = "(\\f (\\x (\\y f y x)))";
        functions["V"] = "(\\x (\\y x y y))";


        //  Pairs
        functions["Pair"] = "(\\f (\\s (\\b b f s)))";
        functions["First"] = "(\\p p True)";
        functions["Second"] = "(\\p p False)";
    }

    bool exist(const string &str) const {
        return (functions.find(str) != functions.end());
    }

    //  Not string& to avoid changing data
    string operator[](const string &index) {
        if (exist(index)) {
            return functions[index];
        }
        else {
            return "";
        }
    }
};

#endif //OGANYAN_LAMBDA_CALC_TERMS_LIB_H
