#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

std::vector<std::string> digits = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

unsigned int digit(std::string line, unsigned int i)
{
    for (unsigned int j = 0; j < digits.size(); j++)
    {
        std::string digit = digits[j];
        // check if written digits exceeds length of line
        if (i + digit.length() > line.length())
        {
            continue;
        }

        std::string line_rest = line.substr(i, digit.length());
        if (line_rest == digit)
        {
            return j;
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;

    unsigned int result = 0;
    while (std::getline(in, line))
    {
        int d1 = -1, d2 = -1;
        for (unsigned int i = 0; i < line.length(); i++)
        {
            char c = line[i];
            if (std::isdigit(c) != 0)
            {
                if (d1 == -1)
                {
                    d1 = c - '0';
                }
                else
                {
                    d2 = c - '0';
                }
            }
            else
            {
                int d = digit(line, i);
                if (d >= 0)
                {
                    if (d1 == -1)
                    {
                        d1 = d;
                    }
                    else
                    {
                        d2 = d;
                    }
                }
            }
        }

        if (d2 == -1)
        {
            d2 = d1;
        }

        if (d1 > -1)
        {
            result += 10 * d1 + d2;
        }
    }
   
    std::cout << result << std::endl;

    return 0;
}
