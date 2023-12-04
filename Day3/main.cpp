#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

inline bool isgear(char& c)
{
    return c == '*';
}

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(in, line))
    {
        lines.push_back(line);
    }
    in.close();

    std::map<std::pair<size_t, size_t>, std::vector<unsigned int>> gears;
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::stringstream buf;
        bool is_relevant = false;
        std::pair<size_t, size_t> gear_pos;
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            char& c = lines[i][j];
            if (std::isdigit(c))
            {
                buf << c;
                if (i > 0 && j > 0 && isgear(lines[i - 1][j - 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i - 1, j - 1);
                    is_relevant = true;
                }
                if (i > 0 && isgear(lines[i - 1][j]))
                {
                    gear_pos = std::pair<size_t, size_t>(i - 1, j);
                    is_relevant = true;
                }
                if (i > 0 && (j + 1) < lines[i].size() && isgear(lines[i - 1][j + 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i - 1, j + 1);
                    is_relevant = true;
                }
                if (j > 0 && isgear(lines[i][j - 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i, j - 1);
                    is_relevant = true;
                }
                if ((j + 1) < lines[i].size() && isgear(lines[i][j + 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i, j + 1);
                    is_relevant = true;
                }
                if ((i + 1) < lines.size() && j > 0 && isgear(lines[i + 1][j - 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i + 1, j - 1);
                    is_relevant = true;
                }
                if ((i + 1) < lines.size() && isgear(lines[i + 1][j]))
                {
                    gear_pos = std::pair<size_t, size_t>(i + 1, j);
                    is_relevant = true;
                }
                if ((i + 1) < lines.size() && (j + 1) < lines[i + 1].size() && isgear(lines[i + 1][j + 1]))
                {
                    gear_pos = std::pair<size_t, size_t>(i + 1, j + 1);
                    is_relevant = true;
                }
            }
            else
            {
                if (is_relevant)
                {
                    unsigned int num = std::stoi(buf.str());
                    if (gears.find(gear_pos) != gears.end())
                    {
                        gears[gear_pos].push_back(num);
                    }
                    else
                    {
                        auto numbers = std::vector<unsigned int>();
                        numbers.push_back(num);
                        gears[gear_pos] = numbers;
                    }
                    is_relevant = false;
                }
                buf = std::stringstream();
            }
        }

        // end of line
        if (is_relevant)
        {
            unsigned int num = std::stoi(buf.str());
            if (gears.find(gear_pos) != gears.end())
            {
                gears[gear_pos].push_back(num);
            }
            else
            {
                auto numbers = std::vector<unsigned int>();
                numbers.push_back(num);
                gears[gear_pos] = numbers;
            }
            is_relevant = false;
        }
    }

    unsigned long long int sum = 0;
    for (auto& entry : gears)
    {
        if (entry.second.size() == 2)
        {
            unsigned long long int ratio = entry.second[0] * entry.second[1];
            std::cout << "* at " << entry.first.first << "," << entry.first.second << ", ratio:" << ratio << std::endl;
            sum += ratio;
        }
    }
    std::cout << "sum: " << sum << std::endl;

    return 0;
}