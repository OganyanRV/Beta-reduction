// Copyright 2021 Oganyan Robert

#ifndef OGANYAN_LAMBDA_CALC_BETA_REDUCTION_H
#define OGANYAN_LAMBDA_CALC_BETA_REDUCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "correct_syntax_check.h"

using std::cout;
using std::set;
using std::map;
using std::vector;
using std::string;
using std::stack;

const int lambda = -1;
const int opening_bracket = -2;
const int closing_bracket = -3;
const int unprocessed = -4;

class Term {
public:
    int index;
    string term;
    int alpha_conversion_count;

    Term() {
        index = unprocessed;
        term = "";
        alpha_conversion_count = 0;
    }

    Term(int index_, string term_, int alpha_conversion_count_) :
            index(index_), term(std::move(term_)), alpha_conversion_count(alpha_conversion_count_) {}

    Term(int index_, string term_) :
            index(index_), term(std::move(term_)), alpha_conversion_count(0) {}

};

string GetOutPutString(const vector<Term> &term_vec_original) {
    auto term_vec = term_vec_original;
    string result_string_term;
    // Remove the most left and the most right brackets if they are useless
    while (true) {
        bool cycle_is_done = true;
        if ((term_vec[0].term == "(") && (term_vec[term_vec.size() - 1].term == ")")) {
            int brackets_count = 0;
            bool need_to_remove_brackets = true;
            for (size_t elem = 1; elem < term_vec.size() - 1; ++elem) {
                if (term_vec[elem].term == "(") {
                    brackets_count++;
                } else if (term_vec[elem].term == ")") {
                    brackets_count--;
                }
                if (brackets_count == -1) {
                    need_to_remove_brackets = false;
                    break;
                }
            }
            if (need_to_remove_brackets) {
                term_vec.pop_back();
                term_vec.erase(term_vec.begin());
                cycle_is_done = false;
            }
        }
        if (cycle_is_done) {
            break;
        }
    }

    // Need to rename back unnecessary renamed variables
    map<string, set<int>> alpha_conversion_map;

    alpha_conversion_map["("].insert(0);
    alpha_conversion_map[")"].insert(0);

    // pre-processing
    for (const auto &term : term_vec) {
        if (term.term == "(" || term.term == ")") {
            continue;
        }
        if (term.term[0] == '\\') {
            alpha_conversion_map[term.term.substr(1)].insert(term.alpha_conversion_count);
        } else {
            alpha_conversion_map[term.term].insert(term.alpha_conversion_count);
        }
    }

    // making the result string considering correct amount of "'"
    for (size_t elem = 0; elem < term_vec.size(); ++elem) {
        auto cur_term = term_vec[elem];
        result_string_term += cur_term.term;
        string name_of_term;
        auto alpha_conversion_count = alpha_conversion_map["("].begin();
        if (cur_term.term[0] == '\\') {
            name_of_term = cur_term.term.substr(1);
            alpha_conversion_count = alpha_conversion_map[name_of_term].find(cur_term.alpha_conversion_count);
        } else {
            name_of_term = cur_term.term;
            alpha_conversion_count = alpha_conversion_map[name_of_term].find(cur_term.alpha_conversion_count);
        }

        while (true) {
            if (alpha_conversion_count == alpha_conversion_map[name_of_term].begin()) {
                break;
            }
            result_string_term += "'";
            --alpha_conversion_count;
        }

        if (elem + 1 < term_vec.size()) {
            auto next_term = term_vec[elem + 1];
            if ((cur_term.term != "(") && (next_term.term != ")")) {
                result_string_term += " ";
            }
        }

    }
    return result_string_term;
}


string MakeCorrectForm(const string &term) {
    string return_term = term;
    while (true) {
        string new_term;
        bool is_correct = true;
        for (size_t pos_for_opening_bracket = 0;
             pos_for_opening_bracket < return_term.size(); ++pos_for_opening_bracket) {
            if (return_term[pos_for_opening_bracket] == '\\' && return_term[pos_for_opening_bracket - 1] != '(') {
                int brackets_count = 0;
                int pos_for_ending_bracket = return_term.size();
                for (size_t j = pos_for_opening_bracket + 1; j < return_term.size(); ++j) {
                    if (return_term[j] == '(') {
                        brackets_count++;
                    } else if (return_term[j] == ')') {
                        brackets_count--;
                    }
                    if (brackets_count < 0) {
                        pos_for_ending_bracket = j;
                        break;
                    }
                }
                new_term = return_term.substr(0, pos_for_opening_bracket) + '('
                           +
                           return_term.substr(pos_for_opening_bracket, pos_for_ending_bracket - pos_for_opening_bracket)
                           + ')' +
                           return_term.substr(pos_for_ending_bracket, return_term.size() - pos_for_ending_bracket);
                is_correct = false;
            }
        }
        if (is_correct) {
            break;
        }
        return_term = new_term;
    }
    return return_term;
}


vector<Term> ConvertToDeBruijnNotation(const vector<string> &term_vec) {

    vector<Term> term_de_bruijn(term_vec.size(), Term());
    map<string, int> usage_counter;

    // Main part of processing indexes and making alpha-conversion for NOT FREE (bounded) terms
    for (size_t cur_elem = 0; cur_elem < term_vec.size(); ++cur_elem) {
        if (term_de_bruijn[cur_elem].index != unprocessed) {
            continue;
        }
        string cur_term = term_vec[cur_elem];
        if (cur_term == "(") {
            term_de_bruijn[cur_elem] = Term(opening_bracket, cur_term);
            continue;
        }
        if (cur_term == ")") {
            term_de_bruijn[cur_elem] = Term(closing_bracket, cur_term);
            continue;
        }
        if (cur_term[0] == '\\') {
            term_de_bruijn[cur_elem] = Term(lambda, cur_term, usage_counter[cur_term.substr(1)]++);
            int brackets_in_lambda_count = 0;
            int end_lambda = -1;
            // true if opening bracket is for the following lambda ((\n n)); false if opening bracket is for application ((a b))
            stack<bool> brackets_type;
            for (size_t j = cur_elem + 1; j < term_vec.size(); ++j) {
                string cur_sub_term = term_vec[j];
                if (cur_sub_term == "(") {
                    if (term_vec[j + 1][0] == '\\') {
                        brackets_type.push(true);
                        brackets_in_lambda_count++;
                    } else {
                        brackets_type.push(false);
                    }
                    continue;
                } else if (cur_sub_term == ")") {
                    if (brackets_type.empty()) {
                        break;
                    }
                    if (brackets_type.top()) {
                        brackets_in_lambda_count--;
                    }
                    brackets_type.pop();
                    if (brackets_in_lambda_count == end_lambda - 1) {
                        cout << "ebal" << "\n";
                        end_lambda = -1;
                    }
                    continue;
                }
                if (end_lambda == -1 && cur_sub_term == cur_term.substr(1)) {
                    term_de_bruijn[j] = Term(brackets_in_lambda_count, cur_sub_term,
                                             term_de_bruijn[cur_elem].alpha_conversion_count);
                    continue;
                }
                if (cur_sub_term == cur_term) {
                    end_lambda = brackets_in_lambda_count; // ?
                }
            }
        }
    }

    //  Processing for FREE terms
    map<string, int> free_terms;
    for (int elem = static_cast<int>(term_vec.size()) - 1; elem >= 0; --elem) {
        if (term_de_bruijn[elem].index != unprocessed) {
            continue;
        }
        free_terms[term_vec[elem]] = free_terms.size() - 1;
    }

    int count_of_bound_terms = 0;
    // Similarly as previous one
    stack<bool> brackets_type;

    for (size_t elem = 0; elem < (int) term_vec.size(); ++elem) {
        if (term_vec[elem] == "(") {
            if (term_vec[elem + 1][0] == '\\') {
                count_of_bound_terms++;
                brackets_type.push(true);
            } else {
                brackets_type.push(false);
            }
        }
        if (term_vec[elem] == ")") {
            if (brackets_type.top()) {
                count_of_bound_terms--;
            }
            brackets_type.pop();
        }
        if (term_de_bruijn[elem].index == unprocessed) {
            term_de_bruijn[elem] = Term(free_terms[term_vec[elem]] + count_of_bound_terms, term_vec[elem],
                                        usage_counter[term_vec[elem]]);
        }
    }

    return term_de_bruijn;
}

vector<Term> RemoveUnnecessaryBrackets(const vector<Term> &term_vec) {
    auto return_vec = term_vec;

    //  Remove (), (\x) (x)

    while (true) {
        bool found_useless_brackets = false;
        for (size_t elem = 0; elem < return_vec.size(); ++elem) {
            if (return_vec[elem].term != "(") {
                continue;
            }
            if (return_vec[elem + 1].term == ")") {
                found_useless_brackets = true;
                return_vec.erase(return_vec.begin() + elem, return_vec.begin() + elem + 2);
                break;
            }
            if (return_vec[elem + 2].term == ")") {
                found_useless_brackets = true;
                return_vec.erase(return_vec.begin() + elem + 2);
                return_vec.erase(return_vec.begin() + elem);
                break;
            }
        }
        if (!found_useless_brackets) {
            break;
        }
    }


    // Remove ((*))
    while (true) {
        bool found_useless_brackets = false;
        for (size_t elem = 1; elem < return_vec.size(); ++elem) {
            if (return_vec[elem].term != "(" ||
                return_vec[elem - 1].term != "(") {
                continue;
            }
            int brackets_count = 0;
            for (size_t j = elem + 1; j < return_vec.size(); ++j) {
                if (return_vec[j].term == "(") {
                    brackets_count++;
                } else if (return_vec[j].term == ")") {
                    brackets_count--;
                    if (brackets_count == -1) {
                        if (return_vec[j + 1].term == ")") {
                            return_vec.erase(return_vec.begin() + j + 1);
                            return_vec.erase(return_vec.begin() + elem);
                            found_useless_brackets = true;
                        }
                        break;
                    }
                }
            }
        }
        if (!found_useless_brackets) {
            break;
        }
    }
    return return_vec;
}

// Normal strategy. The outermost left redex
vector<string> ReduceNormalStrat(const vector<Term>& term_vec_original) {
    auto term_vec = term_vec_original;
    vector<string> result_reduce;
    while (true) {
        vector<Term> current_reduce_step; // Массив подставляемых значений
        //  Удаляем ненужные скобки
        term_vec = RemoveUnnecessaryBrackets(term_vec);
        result_reduce.push_back(GetOutPutString(term_vec));
        // Если Бета-редукция бесконечна (нет нормальной формы)
        if (result_reduce.size() >= 2) {
            if (result_reduce[result_reduce.size() - 1] == result_reduce[result_reduce.size() - 2]) {
                result_reduce.clear();
                result_reduce.emplace_back("Term can't be reduced");
                return result_reduce;
            }
        }


        bool term_changed = false;

        for (size_t elem = 0; elem < term_vec.size(); ++elem) {
            if (term_vec[elem].index != lambda) {
                continue;
            }
            int brackets_count = 0;
            // Получаем выражение, к которой применяем аппликацию
            int lambda_end_bracket = static_cast<int>(term_vec.size()) - 1;
            for (size_t j = elem + 1; j < term_vec.size(); ++j) {
                if (term_vec[j].index == opening_bracket) {
                    brackets_count++;
                } else if (term_vec[j].index == closing_bracket) {
                    brackets_count--;
                    if (brackets_count == -1) {
                        lambda_end_bracket = j;
                        break;
                    }
                }
            }

            // Если правая скобка - последний элемент, то не к чему применять аппликацию - скип
            if (lambda_end_bracket == term_vec.size() - 1) {
                continue;
            }

            // Массив для подставляемого выражения
            vector<Term> substituted_term;
            if (term_vec[lambda_end_bracket + 1].index >= 0) {
                substituted_term.push_back(term_vec[lambda_end_bracket + 1]);
            } else if (term_vec[lambda_end_bracket + 1].index == opening_bracket) {
                brackets_count = 0;
                substituted_term.push_back(term_vec[lambda_end_bracket + 1]);
                for (int j = lambda_end_bracket + 2; j < (int) term_vec.size(); j++) {
                    if (term_vec[j].index == opening_bracket) {
                        brackets_count++;
                    } else if (term_vec[j].index == closing_bracket) {
                        brackets_count--;
                    }
                    substituted_term.push_back(term_vec[j]);
                    if (brackets_count == lambda) {
                        break;
                    }
                }
            }
            //  Если у терма нет аппликации
            if (substituted_term.empty()) {
                continue;
            }

            // Формируем новую строку. Сначала записываем то что было до лямбды
            for (size_t elem_before_application = 0; elem_before_application < elem - 1; ++elem_before_application) {
                current_reduce_step.push_back(term_vec[elem_before_application]);
            }

            // Говорит о том, находится ли лямбда после открывающей скобки
            stack<bool> bracket_type;
            brackets_count = 0; // подсчитывает количество действующих лямбд. НУжно для де брейна

            for (size_t j = elem + 1; j < lambda_end_bracket; j++) {
                if (term_vec[j].index == opening_bracket) {
                    if (term_vec[j + 1].index == lambda) {
                        bracket_type.push(true);
                        brackets_count++;
                    } else {
                        bracket_type.push(false);
                    }
                }
                if (term_vec[j].index == closing_bracket) {
                    if (bracket_type.top()) {
                        brackets_count--;
                    }
                    bracket_type.pop();
                }
                if (term_vec[j].index < brackets_count) {
                    // лямбда или скобка
                    current_reduce_step.push_back(term_vec[j]);
                } else if (term_vec[j].index > brackets_count) {
                    // тело относится к внешней лямбде
                    current_reduce_step.emplace_back(term_vec[j].index - 1, term_vec[j].term,
                                 term_vec[j].alpha_conversion_count);
                } else {
                    // тело относится к лямбде, к которой применяется аппликация
                    stack<bool> item_bracket_type;
                    int item_cnt = 0;
                    for (size_t k = 0; k < substituted_term.size(); ++k) {
                        if (substituted_term[k].index == opening_bracket) {
                            if (substituted_term[k + 1].index == lambda) {
                                item_bracket_type.push(true);
                                item_cnt++;
                            } else {
                                item_bracket_type.push(false);
                            }
                        }
                        if (substituted_term[k].index == closing_bracket) {
                            if (item_bracket_type.top()) {
                                item_cnt--;
                            }
                            item_bracket_type.pop();
                        }
                        if (item_cnt <= substituted_term[k].index) {
                            current_reduce_step.emplace_back(substituted_term[k].index + brackets_count,
                                            substituted_term[k].term,
                                            substituted_term[k].alpha_conversion_count);
                        } else {
                            current_reduce_step.push_back(substituted_term[k]);
                        }
                    }
                }
            }
            for (size_t elem_after_application = lambda_end_bracket + substituted_term.size() + 1;
                 elem_after_application < term_vec.size(); elem_after_application++) {
                current_reduce_step.push_back(term_vec[elem_after_application]);
            }
            term_changed = true;
            break;
        }
        if (!term_changed) {
            break;
        }
        term_vec = current_reduce_step;
    }
    return result_reduce;
}

vector<string> BetaReduction(const string &term) {
    if (!IsSyntaxCorrect(term)) {
        return vector<string>();
    }
    auto good_form_term = MakeCorrectForm(term);
    if (!IsSyntaxCorrect(good_form_term)) {
        return vector<string>();
    }
    vector<string> term_vec = ParseToVec(good_form_term);
    if (!ChangeLibFuncsToTerms(term_vec)) {
        return vector<string>();
    }
    vector<Term> term_de_bruijn = ConvertToDeBruijnNotation(term_vec);

//    for (auto x: term_de_bruijn) {
//        cout << x.term << " ";
//    }
//    cout << "\n";
//
//    for (auto x: term_de_bruijn) {
//        cout << x.index << " ";
//    }
//    cout << "\n";
//
//    for (auto x: term_de_bruijn) {
//        cout << x.alpha_conversion_count << " ";
//    }
//    cout << "\n";
    vector<string> reduction_result = ReduceNormalStrat(term_de_bruijn);
    return reduction_result;
}

#endif //OGANYAN_LAMBDA_CALC_BETA_REDUCTION_H
