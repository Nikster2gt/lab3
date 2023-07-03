#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "histogram.h"
using namespace std;
int main()
{
    int result;
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers = input_numbers(number_count);
    do {
        int bin_count;
        cerr << "Enter bin count: ";
        cin >> bin_count;
        vector<size_t> bins = make_histogram(numbers, bin_count);
        //svg_text();
        show_histogram_svg(bins);
        cerr << "Are you satisfied with the result? 1-YES, 0-NO" << endl;
        cin >> result;
    } while (result == 0);
}