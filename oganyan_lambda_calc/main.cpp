// Copyright 2021 Oganyan Robert

#include <iostream>
#include <string>
#include <vector>
#include "./beta-reduction.h"

//vector<string> BetaReduction(string formula);
//bool IsSyntaxCorrect(string input);
using std::cout;
using std::string;
using std::vector;
using std::cin;

void create_test(const string& test, const string& ans) {
    auto res = BetaReduction(test);
    if (*(--res.end()) == ans) {
        cout << "Correct! " << test << " reduced correctly to " << ans;
    } else {
        cout << " Oopsie. " << test << " reduced wrong to " << *(--res.end());
    }
    cout << "\n";
//    cout << "\n" << "Showing steps: " << "\n";
//    for (auto &element : res) {
//        cout << " -> " << element << "\n";
//    }
}

void test() {
    create_test("(\\x x x)(\\y \\z y z)","\\z (\\z' z z')");
    create_test("\\x \\y (\\z (\\x z x) (\\y z y))(xy)", "\\x \\y (x y \\y' x y y')");
    create_test("Omega a", "Term can't be reduced");
    create_test("(\\x x (x (y z)) x) (\\u u v)","((y z) v) v (\\u u v)");
    create_test("First (Pair a b)","a");
    create_test("(\\x \\y x y y)(\\u u y x)", "\\y y y' x y");
    create_test("(\\f \\x f (f x)) (\\x x)", "\\x x");
    create_test("(\\x \\y \\z x z (y z))((\\x \\y y x) u) ((\\x \\y y x) v) w", "w u (w v)");
    create_test("(\\x \\y \\z x z y)(\\x \\y x)", "\\y (\\z z)");
    create_test("(\\b \\x \\y b x y) False t e", "e");

//    create_test("\\x", "")


}

int main() {
    test();
    return 0;
}
/*
int main() {
    cout << "type 'exit' to close the program" << "\index";
    while (true) {
        cout << "> ";
        string input;
        getline(cin, input);

        if (input == "exit") {
            return 0;
        }

        if (!IsSyntaxCorrect(input)) {
            continue;
        }

        auto output = BetaReduction(input);

        for (auto &element : output) {
            cout << " -> " << element << "\index";
        }
    }
}
 */