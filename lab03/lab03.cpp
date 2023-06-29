#include <iostream>
#include <vector>
#include <string>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers(size_t count) {
	cerr << "Input numbers:" << '\n';
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}

pair <double, double> find_minmax(const vector<double> &numbers) {
	double min = numbers[0];
	double max = numbers[0];
	for (double number : numbers) {
		if (number < min) {
			min = number;
		}
		else if (number > max) {
			max = number;
		}
	}
	return pair<double, double>(min, max);
}

vector<size_t> make_histogram(const vector<double> &numbers, size_t bin_count) {
	vector<size_t> result(bin_count);

	auto [min, max] = find_minmax(numbers);

	double bin_size = (max - min) / bin_count;

	for (size_t i = 0; i < numbers.size(); i++) {
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;
			if ((lo <= numbers[i]) && (numbers[i] < hi)) {
				result[j]++;
				found = true;
			}
		}

		if (!found) {
			result[bin_count - 1]++;
		}
	}

	return result;
}

void show_histogram_text(const vector<size_t> &bins) {

	size_t max_count = 0;
	for (size_t bin : bins) {
		if (bin > max_count) {
			max_count = bin;
		}
	}

	for (size_t i = 0; i < bins.size(); i++) {
		if (bins[i] < 100) {
			cout << ' ';
		}

		if (bins[i] < 10) {
			cout << ' ';
		}

		cout << bins[i] << "|";

		size_t height;
		if (max_count > MAX_ASTERISK) {
			if (bins[i] > MAX_ASTERISK) {
				height = MAX_ASTERISK * 1.0;
			}
			else {
				height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
			}
		}
		else {
			height = bins[i];
		}

		for (size_t j = 0; j < height; j++) {
			cout << '*';
		}
		cout << '\n';
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

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
	cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void show_histogram_svg(const vector<size_t>& bins) {
	const auto IMAGE_WIDTH = 400;
	const auto IMAGE_HEIGHT = 300;
	const auto TEXT_LEFT = 20;
	const auto TEXT_BASELINE = 20;
	const auto TEXT_WIDTH = 50;
	const auto BIN_HEIGHT = 30;
	const auto BLOCK_WIDTH = 10;

	svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
	double top = 0;

	size_t max_count = 0;
	for (size_t bin : bins) {
		if (bin > max_count) {
			max_count = bin;
		}
	}

	double bin_width;
	for (size_t bin : bins) {
		if (max_count > MAX_ASTERISK) {
			if (bin > MAX_ASTERISK) {
				bin_width = MAX_ASTERISK * 1.0 * BLOCK_WIDTH;
			}
			else {
				bin_width = MAX_ASTERISK * (static_cast<double>(bin) / max_count) * BLOCK_WIDTH;
			}
		}
		else {
			bin_width = BLOCK_WIDTH * bin;
		}

		svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
		svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
		top += BIN_HEIGHT;
	}
	svg_end();	
}

void building_histogram(const vector <double>& numbers) {
	size_t bin_count;
	cerr << "Input the count of bins: ";
	cin >> bin_count;

	const auto bins = make_histogram(numbers, bin_count);

	show_histogram_svg(bins);

	cerr << "Are you satisfied with the result?\n" << "0 - no; 1 - yes\n";
	size_t answer;
	cin >> answer;

	switch (answer)
	{
	case 0:
		cerr << "OK, let's rebuild the histogram\n";
		building_histogram(numbers);
		break;
	case 1:
		cerr << "OK, goodbye";
		break;
	default:
		cerr << "Wrong answer";
		break;
	}
}

int main() {
	size_t number_count;

	cerr << "Input the count of numbers: ";
	cin >> number_count;

	const auto numbers = input_numbers(number_count);

	building_histogram(numbers);
}