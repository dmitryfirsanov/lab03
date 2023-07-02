#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Input {
	vector<double> numbers;
	size_t bin_count;
};

Input read_input(istream& in);

vector<double> input_numbers(istream& in, size_t count);
pair <double, double> find_minmax(const vector<double>& numbers);
vector<size_t> make_histogram(const Input& data);
void show_histogram_text(const vector<size_t>& bins);

// SVG

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<size_t>& bins);