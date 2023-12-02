#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;

    unsigned int result = 0;
    while (std::getline(in, line))
    {
        int d1 = -1, d2 = -1;
        for (size_t i = 0; i < line.length(); i++)
        {
            char c = line[i];
            if (std::isdigit(c) != 0)
            {
                if (d1 == -1)
                {
                    d1 = c;
                }
                else
                {
                    d2 = c;
                }
            }
        }

        if (d2 == -1)
        {
            d2 = d1;
        }

        result += 10 * (d1-'0') + (d2-'0');
    }
   
    std::cout << result << std::endl;

    return 0;
}
