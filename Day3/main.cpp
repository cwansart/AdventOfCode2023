#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

inline bool issymbol(char& c)
{
    return c != '.' && !std::isdigit(c);
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

    unsigned int sum = 0;
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::stringstream buf;
        bool is_relevant = false;
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            char& c = lines[i][j];
            if (std::isdigit(c))
            {
                buf << c;
                if (!is_relevant &&
                    (i > 0 && j > 0 && issymbol(lines[i - 1][j - 1])) || // above left
                    (i > 0 && issymbol(lines[i - 1][j])) || // above
                    (i > 0 && (j + 1) < lines[i].size() && issymbol(lines[i - 1][j + 1])) || // above right
                    (j > 0 && issymbol(lines[i][j - 1])) || // left
                    ((j + 1) < lines[i].size() && issymbol(lines[i][j + 1])) || // right
                    ((i + 1) < lines.size() && j > 0 && issymbol(lines[i + 1][j - 1])) || // below left
                    ((i + 1) < lines.size() && issymbol(lines[i + 1][j])) || // below
                    ((i + 1) < lines.size() && (j + 1) < lines[i + 1].size() && issymbol(lines[i + 1][j + 1]))) // below right
                {
                    is_relevant = true;
                }
                
            }
            else
            {
                if (is_relevant)
                {
                    sum += std::stoi(buf.str());
                    is_relevant = false;
                }
                buf = std::stringstream();
            }
        }

        // end of line
        if (is_relevant)
        {
            sum += std::stoi(buf.str());
            is_relevant = false;
        }
    }
    
    std::cout << "sum: " << sum << std::endl;

    return 0;
}