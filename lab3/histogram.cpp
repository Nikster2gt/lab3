#include "histogram.h"
#include <algorithm>
using namespace std;
Input read_input(istream& in,bool prompt) {
    
    Input data;
    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if (prompt)
        cerr << "Enter bin count: ";
    in >>data.bin_count;
    return data;
}
void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() == 0)
        return;
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            if (number > 0)
                min = number;
            else
                min = 0;
        }
        if (number > 0) {
            if (number > max)
                max = number;
        }
        else
            max = 0;
        
    }
}
vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}
vector<size_t> make_histogram(Input m) {
    vector<size_t> bins(m.bin_count);
    double max, min;
    find_minmax(m.numbers, min, max);
    double bin_size = (max - min) / m.bin_count;
    for (size_t i = 0; i < m.numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < m.bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= m.numbers[i]) && (m.numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[m.bin_count - 1]++;
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
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end() {
    cout << "</svg>\n";
}
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x = '" << x << "' y = '" << y << "' width = '" << width << "' height = '" << height << "' stroke = '" << stroke << "' fill = '" << fill << "'/>";
}
void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    auto TEXT_LEFT = 35;
    auto DIAGR_LEFT = 20;
    const auto TEXT_BASELINE = 270;
    const auto BIN_BASELINE = 250;
    const auto BIN_WIDTH = 40;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    size_t max_count = 0;
    for (size_t bin : bins) {
        if (bin > max_count) {
            max_count = bin;
        }
    }

    double BIN_HEIGHT;
    for (size_t bin : bins) {
        BIN_HEIGHT = BIN_BASELINE * (static_cast<double>(bin) / max_count);

        svg_rect(DIAGR_LEFT, BIN_BASELINE - BIN_HEIGHT, BIN_WIDTH, BIN_HEIGHT, "black", "red");
        svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bin));
        TEXT_LEFT += BIN_WIDTH + 10;
        DIAGR_LEFT += BIN_WIDTH + 10;
    }
    svg_end();
}