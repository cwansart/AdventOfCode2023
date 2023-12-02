#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;
    unsigned int succeeded = 0;
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

                        if (color == "red" && count > 12)
                        {
                            success = false;
                        }
                        if (color == "green" && count > 13)
                        {
                            success = false;
                        }
                        if (color == "blue" && count > 14)
                        {
                            success = false;
                        }
                    }
                }
            }

            if (success)
            {
                succeeded += game_num;
            }
        }
    }

    std::cout << "success count: " << succeeded << std::endl;

    return 0;
}