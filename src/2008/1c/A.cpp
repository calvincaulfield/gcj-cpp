#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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

vector<int> split_to_int(const string &s, char delim) {
    vector<int> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(stoi(item));
        }
    }
    return elems;
}

long long solve_case() {
    auto tokens = split_to_int(read_string(), ' ');
    int num_buttons = tokens[1];

    auto frequencies = split_to_int(read_string(), ' ');

    sort(frequencies.begin(), frequencies.end());
    reverse(frequencies.begin(), frequencies.end());

    int press_count = 1;
    int current_button = 0;
    long long result = 0;

    for (int frequency : frequencies) {
        result += frequency * press_count;
        current_button++;
        if (current_button == num_buttons) {
            press_count++;
            current_button = 0;
        }
    }
    return result;
}

int main() {
    int num_cases = read_int();
    for (int i = 0; i < num_cases; i++) {
        cout << "Case #" << i + 1 << ": " << solve_case() << "\n";
    }
}