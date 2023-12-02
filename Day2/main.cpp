#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;
    unsigned int sum = 0;
    while (std::getline(in, line))
    {
        size_t pos = line.find_first_of(":");
        if (pos != std::string::npos)
        {
            // extract game number
            unsigned int game_num = std::stoi(line.substr(5, pos)); // 5 = "Game ".length()

            // parse subsets
            bool success = true;
            std::stringstream ss(line.substr(pos + 1)); // Remove "Game N:"
            std::string token;
            unsigned int max_red = 0, max_green = 0, max_blue = 0;
            while (std::getline(ss, token, ';'))
            {
                std::stringstream ss2(token);
                std::string token2;
                while (std::getline(ss2, token2, ','))
                {
                    token2 = token2.substr(1); // remove space at the beginning
                    pos = token2.find_first_of(' ');
                    if (pos != std::string::npos)
                    {
                        unsigned int count = std::stoi(token2.substr(0, pos));
                        std::string color = token2.substr(pos + 1); // +1 to remove space before color

                        if (color == "red" && count > max_red)
                        {
                            max_red = count;
                        }
                        if (color == "green" && count > max_green)
                        {
                            max_green = count;
                        }
                        if (color == "blue" && count > max_blue)
                        {
                            max_blue = count;
                        }
                    }
                }
            }
            sum += max_red * max_green * max_blue;
        }
    }
    std::cout << "sum: " << sum << std::endl;

    return 0;
}