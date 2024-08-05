#pragma once

#include "c_with_classes.h"

struct PPM
{
    arr<arr<str>> image_data{};
    arr<str> image_header{};
    int image_size{};

    PPM(const int size):
        image_data{arr<arr<str>> (size,arr<str> (size))},
        image_header{3},
        image_size{size}
    {
        const str image_size_name{std::to_string(image_size)};
        image_header[0] = "P3";
        image_header[1] = image_size_name + " " + image_size_name;
        image_header[2] = "255";
        for (int row{0}; row < image_size; ++row)
        {
            for (int col{0}; col < image_size; ++col)
            {
                image_data[row][col] = "255 255 255";
            }
        }
    }

    str& operator ()(const int row, const int col)
    {
        return image_data[image_size - 1 - col][row];
    }

    void save(const str& filename)
    {
        file f{};
        f.open(filename + ".ppm", write);
        for (auto& header_line: image_header)
        {
            f << header_line << "\n";
        }
        for (auto& row: image_data)
        {
            for (auto& pixel: row)
            {
                f << pixel << "\n";
            }
        }
    }
};

