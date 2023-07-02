#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
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