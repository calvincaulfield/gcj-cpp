#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int read_int() {
    string buffer;
    getline(cin, buffer);
    return stoi(buffer);
}

string read_string() {
    string buffer;
    getline(cin, buffer);
    return buffer;
}

int mode = 210; // 2 * 3 * 5 * 7

vector<int> get_minus(vector<int> const &original) {
    vector<int> result(mode, 0);
    for (int i = 0; i < mode; i++) {
        result[-i % mode] = original[i];
    }
    return result;
}

vector<int> single_number(int number) {
    vector<int> result(mode, 0);
    result[number % mode] = 1;
    return result;
}

void add(vector<int> &total, vector<int> const &to_be_added) {
    for (int i = 0; i < mode; i++) {
        total[i] += to_be_added[i];
    }  
}

int solve_case() {
    string line = read_string();
    // answer[i] stores answer for suffix of length i
    // answer[0] is meaningless
    vector<vector<int>> answer(line.size() + 1);
    for (int i = 1; i <= line.size(); i++) {
        int suffix_start_index = line.size() - i;

        vector<int> total;

        // j means # chars included in the leftmost number
        for (int j = 1; j <= i; j++) {
            int leftmost_number = stoi(line.substr(suffix_start_index, suffix_start_index + j));
            add(total, single_number(leftmost_number));

            if (j < i) {
                auto temp = single_number(leftmost_number);
                add(temp, answer[i - j]);
                add(total, temp);

                temp = single_number(leftmost_number);
                add(temp, get_minus(answer[i - j]));
                add(total, temp);
            }
            
        }

        answer[i] = total;
    }

    long long result = 0;
    for ()
}

int main() {
    int num_cases = read_int();
    for (int i = 0; i < num_cases; i++) {
        cout << "Case #" << i + 1 << ": " << solve_case() << "\n";
    }
}