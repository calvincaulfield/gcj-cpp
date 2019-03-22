#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
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

pair<string, string> split_into_two(const string &s, char delim) {
    int index = s.find(delim);
    return make_pair(s.substr(0, index), s.substr(index + 1));
}

int convert_to_min(string time) {
    int hours = stoi(time.substr(0, 2));
    int mins = stoi(time.substr(3));
    //cout << time << ": " << hours * 60 + mins << "\n";
    return hours * 60 + mins;
}

int get_maximum_debt(vector<int> ins, vector<int> outs) {
    
    // 1: in, 2: out
    // Note that numeric order of in and out matters, because of simultaneous arrival and departure
    vector<pair<int, int>> list;
    for (int in : ins) {
        list.push_back(make_pair(in, 1));
    }
    for (int out : outs) {
        list.push_back(make_pair(out, 2));
    }
    sort(list.begin(), list.end());

    int max_debt = 0;
    int current_debt = 0;

    for (auto elem : list) {
        if (elem.second == 1) {
            current_debt--;
        } else {
            current_debt++;
        }
        if (current_debt > max_debt) {
            max_debt = current_debt;
        }
    }

    return max_debt;
}

pair<int, int> solve_case() {
    int turnaround = read_int();
    auto ints = split_into_two(read_string(), ' ');
    int num_lines1 = stoi(ints.first);
    int num_lines2 = stoi(ints.second);

    vector<int> a_out;
    vector<int> a_in;
    vector<int> b_out;
    vector<int> b_in;

    for (int i = 0; i < num_lines1; i++) {
        auto two_times = split_into_two(read_string(), ' ');
        a_out.push_back(convert_to_min(two_times.first));
        b_in.push_back(convert_to_min(two_times.second) + turnaround);
    }
    for (int i = 0; i < num_lines2; i++) {
        auto two_times = split_into_two(read_string(), ' ');
        b_out.push_back(convert_to_min(two_times.first));
        a_in.push_back(convert_to_min(two_times.second) + turnaround);
    }   

    return make_pair(get_maximum_debt(a_in, a_out), get_maximum_debt(b_in, b_out));
}

int main() {
    int num_cases = read_int();
    for (int i = 0; i < num_cases; i++) {
        auto answer = solve_case();
        cout << "Case #" << i + 1 << ": " << answer.first << " " << answer.second << "\n";
    }
}