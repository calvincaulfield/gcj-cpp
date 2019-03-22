#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <math.h>
#include <iomanip>

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

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

double sector_area(double radius, double angle) {
    return radius * radius * angle / 2;
}

double get_other_len(double radius, double x) {
    return sqrt(radius * radius - x * x);
}

// Deal with only half of circle (first quarter)
double circular_segment_area(double radius, double x) {
    double y = get_other_len(radius, x);
    double angle = acos(x / radius);
    return sector_area(radius, angle) - x * y / 2;
}

double round_triangle_area(double radius, double x, double y) {
    double tangent_y = get_other_len(radius, x);
    return circular_segment_area(radius, y) - circular_segment_area(radius, tangent_y) - x * (tangent_y - y);
}

double intersection_area(double radius, double x, double y, double square_size) {
    double tangent_y = get_other_len(radius, x);
    double tangent_x = get_other_len(radius, y);
    double new_x = x;
    double new_y = y;
    double offset_area = 0;

    if (tangent_y > y + square_size) {
        new_x = get_other_len(radius, y + square_size);
    }
    offset_area += square_size * (new_x - x);

    if (tangent_x > x + square_size) {
        new_y = get_other_len(radius, x + square_size);
    }
    offset_area += (new_y - y) * (square_size - (new_x - x));  

    return offset_area + round_triangle_area(radius, new_x, new_y);    
}

double solve_case() {
    vector<string> ints = split(read_string(), ' ');
    double f = stod(ints[0]);
    double R = stod(ints[1]);
    double t = stod(ints[2]);
    double r = stod(ints[3]);
    double g = stod(ints[4]); 

    double inner_radius = R - t - f;
    double interval = g + 2 * r;
    double unit_square_size = g - 2*f;
     
    if (unit_square_size <= 0) {
        return 1;
    }
    
    double a = M_PI;

    double hole_area = 0;
    double total_area = sector_area(R, M_PI / 2);

    double first_position = r + f;
    for (double x = first_position; x < inner_radius; x += interval) {
        double y_max = get_other_len(inner_radius, x);
        double x_right = x + unit_square_size;
      
        // Bottom square
        int num_included = 0;
        double first_non_included_y = first_position;

        if (x_right >= inner_radius) {
            // Cannot contain any square
        } else {
            double y_right_max = get_other_len(inner_radius, x_right);
            num_included = (y_right_max + r + f) / interval;
            first_non_included_y += num_included * interval;
        }

        hole_area += num_included * (unit_square_size * unit_square_size);

        for (double y = first_non_included_y; y < y_max; y += interval) {
            hole_area += intersection_area(inner_radius, x, y, unit_square_size);
        }
    }

    return (total_area - hole_area) / total_area;
}

int main() {
    int num_cases = read_int();
    for (int i = 0; i < num_cases; i++) {
        stringstream ss;
        ss << std::fixed << std::setprecision(6) << solve_case();
        cout << "Case #" << i + 1 << ": " << ss.str() << "\n";
    }
}