#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "histogram.h"
using namespace std;
int main()
{
    const auto input = read_input(cin, true);
    
    vector<size_t> bins = make_histogram(input);
    //svg_text();
    show_histogram_svg(bins);
}