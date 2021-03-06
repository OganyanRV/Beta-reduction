// Copyright 2021 Oganyan Robert

#include <iostream>
#include <string>
#include "./beta-reduction.h"

//#define Show_Steps_At_Tests
#define Show_Steps_At_Interpreter
using std::cout;
using std::string;
using std::cin;

bool CreateTest(const string &test, const string &ans) {
    bool result;

    auto res = BetaReduction(test);
    if (*(--res.end()) == ans) {
        cout << "Correct! " << test << " reduced correctly to " << ans;
        result = true;
    } else {
        cout << " Oopsie. " << test << " reduced wrong to " << *(--res.end());
        result = false;
    }
    cout << "\n";

#ifdef Show_Steps_At_Tests
    cout << "Showing steps: " << "\n";
    for (auto &element : res) {
        cout << " -> " << element << "\n";
    }
#endif

    return result;
}

bool RunTests() {
    bool is_passed = true;

    is_passed &= CreateTest("(\\x \\y x y y)(\\u u y x)", "\\y y y' x y");
    is_passed &= CreateTest("(\\x x x)(\\y \\z y z)", "\\z (\\z' z z')");
    is_passed &= CreateTest("\\x \\y (\\z (\\x z x) (\\y z y)) (x y)", "\\x (\\y (x y) (\\y' (x y) y'))");
    is_passed &= CreateTest("Omega a", "Term can't be reduced");
    is_passed &= CreateTest("(\\x x (x (y z)) x) (\\u u v)", "((y z) v) v (\\u u v)");
    is_passed &= CreateTest("First (Pair a b)", "a");
    is_passed &= CreateTest("(\\f \\x f (f x)) (\\x x)", "\\x x");
    is_passed &= CreateTest("(\\x \\y \\z x z (y z))((\\x \\y y x) u) ((\\x \\y y x) v) w", "w u (w v)");
    is_passed &= CreateTest("(\\x \\y \\z x z y)(\\x \\y x)", "\\y (\\z z)");
    is_passed &= CreateTest("(\\b \\x \\y b x y) False t e", "e");

    return is_passed;
}

void DoRequest(const string &request) {
    if (request == "rules") {
        cout << "-+-+-+-+-+-+-+-+-+-+  Rules  -+-+-+-+-+-+-+-+-+-+-+-+-+" << "\n";
        cout << "1. Capital letters are only used for Library Functions such as True, False, Not ..." << "\n";
        cout << "2. Variables can be named only with cursive letters or words fully consisting of cursive letters" << "\n";
        cout << "3. Do not mess up with brackets" << "\n";
        cout << "4. Lambda is '\\x'; Expression splits with spaces, for example '(\\x x y) a -> a y' " << "\n";
        cout << "5. There are some checks for correct syntax, but not for every possible mistake. Do your best to not make any mistakes" << "\n";

        return;
    }

    if (request == "test") {
        cout << "-+-+-+-+-+-+-+-+-+-+  Running tests  -+-+-+-+-+-+-+-+-+-+-+-+-+-+" << "\n";
        if (RunTests()) {
            cout << "Tests passed successfully!" << "\n";
        } else {
            cout << "Some of tests did not pass" << "\n";
        }
        return;
    }

    if (!IsSyntaxCorrect(request)) {
        return;
    }

    auto output = BetaReduction(request);

#ifdef Show_Steps_At_Interpreter
    for (auto &element : output) {
        cout << " -> " << element << "\n";
    }

#endif

#ifndef Show_Steps_At_Interpreter
    cout << " -> " << *(--output.end()) << "\n";
#endif


}

int main() {
    cout << "Welcome to beta-reduction calculator. Choose the option:" << "\n"
         << "1. Type 'rules' to read rules for syntax " << "\n"
         << "2. Type 'test' to run implemented tests" << "\n"
         << "3. Type the lambda term to reduce it" << "\n"
         << "4. Type 'exit' to quit the program" << "\n";
    while (true) {
        cout << ">" << " ";
        string input;
        getline(cin, input);

        if (input == "exit") {
            return 0;
        }

        DoRequest(input);
    }
    return 0;
}
