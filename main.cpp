#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "pixel.h"

Pixel make_pixel(std::string&line){

    Pixel p;
    int pos;
    pos = line.find(",");
    p.x = std::stoi(line.substr(0,pos));
    line = line.substr(pos+1);

    pos = line.find(",");
    p.y = std::stoi(line.substr(0,pos));
    line = line.substr(pos+1);

    pos = line.find(",");
    p.r = std::stof(line.substr(0,pos));
    line = line.substr(pos+1);

    pos = line.find(",");
    p.g = std::stof(line.substr(0,pos));
    line = line.substr(pos+1);

    p.b = std::stof(line);
    return p;
}

std::vector<std::string> split_string(const std::string &str, char comma) {
    std::vector<std::string> pixel;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find(comma, start)) != std::string::npos) {
        pixel.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    pixel.push_back(str.substr(start));

    return pixel;
}

void flip_vertically(std::vector<Pixel> &pixel_list) {
    const int max_y = 256;

    for (size_t i = 0; i < pixel_list.size(); ++i) {
        pixel_list[i].y = max_y - 1 - pixel_list[i].y;
    }
}

void average_colors(std::vector<Pixel> &pixel_list) {
    float total_r = 0, total_g = 0, total_b = 0;
    int count = pixel_list.size();

    for (const auto &pixel : pixel_list) {
        total_r += pixel.r;
        total_g += pixel.g;
        total_b += pixel.b;
    }
    std::cout << "Average R: " << total_r / count << "\n";
}



int main(int argc, char *argv[]) {

std::vector<Pixel>pixel_list;

std::ifstream file("pixels.dat");
std::string line;
    if (!file){
        std::cerr << "Error: Could not open file " << std::endl;
        return 1;
        }
    if (file.is_open()){
    
        while (std::getline(file, line)) {
            pixel_list.push_back(make_pixel(line));
        }
        file.close();
        average_colors(pixel_list);
        flip_vertically(pixel_list);

    
    std::ofstream outfile("flipped.dat");
    if (outfile.is_open()){
        for (int i = 0; i < pixel_list.size(); ++i) {
            outfile << pixel_list[i].x << "," << pixel_list[i].y << ","
            << pixel_list[i].r << "," << pixel_list[i].g << "," << pixel_list[i].b << "\n";
        }
    }

    else{
    std::cerr << "Error: Could not open file " << std::endl;
    return 1;
    }
}
    return 0;
}