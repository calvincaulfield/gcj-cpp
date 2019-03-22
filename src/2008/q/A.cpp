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

int solve_case() {
    int num_servers = read_int();
    for (int i = 0; i < num_servers; i++) {
        // Server name is meaningless
        read_string();
    }

    int num_seaches = read_int();
    //cout << "Num searches " << num_seaches << "\n";
    set<string> used_keyword;
    int server_change_count = 0;

    for (int i = 0; i < num_seaches; i++) {
        string keyword = read_string();
        used_keyword.insert(keyword);

        if (used_keyword.size() == num_servers) {
            server_change_count++;
            used_keyword.clear();
            used_keyword.insert(keyword);
        }
    }
    return server_change_count;
}

int main() {
    int num_cases = read_int();
    for (int i = 0; i < num_cases; i++) {
        cout << "Case #" << i + 1 << ": " << solve_case() << "\n";
    }
}