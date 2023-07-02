#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
void find_minmax(const vector<double> &numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
}
vector<size_t> make_histogram(vector<double> numbers, int bin_count) {
    vector<size_t> bins(bin_count);
    double max, min;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return(bins);
}
void show_histogram_text(vector<size_t> bins) {
    double max_b = *max_element(bins.begin(), bins.end());
    for (size_t i = 0; i < bins.size(); i++) {
        if (bins[i] < 10)
            cout << "  ";
        else
            if (bins[i] < 100)
                cout << ' ';
        cout << bins[i] << '|';
        if (max_b > 76) {
            bins[i] = 76 * (static_cast<double>(bins[i]) / max_b);
        }
        for (size_t j = 0; j < bins[i]; j++)
            cout << '*';
        cout << endl;
    }
}
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
        show_histogram_text(bins);
        cerr << "Are you satisfied with the result? 1-YES, 0-NO" << endl;
        cin >> result;
    } while (result == 0);
}