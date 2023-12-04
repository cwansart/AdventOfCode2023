#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef enum
{
    CARDNO = 0,
    WINNINGNO = 1,
    USERNO = 2
} state_t;

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ifstream in(filename);
    std::string line;
    unsigned int total_points = 0;
    while (std::getline(in, line))
    {
        std::stringstream buf;
        state_t state = CARDNO;
        unsigned int card_no = 0;
        std::vector<unsigned int> win_nums;
        std::vector<unsigned int> user_nums;
        // start at 5 to skip "Card "
        for (size_t i = 5; i < line.size(); i++)
        {
            char& c = line[i];
            buf << c;

            switch (state)
            {
            case CARDNO:
                if (c == ':')
                {
                    buf >> card_no;
                    buf = std::stringstream();
                    state = WINNINGNO;
                }
                break;
            case WINNINGNO:
                if (c == ' ' && buf.str().find_first_not_of(' ') != std::string::npos)
                {
                    win_nums.push_back(std::stoi(buf.str()));
                    buf = std::stringstream();
                }
                else if (c == '|')
                {
                    buf = std::stringstream();
                    state = USERNO;
                }
                break;
            case USERNO:
                if (c == ' ' && buf.str().find_first_not_of(' ') != std::string::npos)
                {
                    user_nums.push_back(std::stoi(buf.str()));
                    buf = std::stringstream();
                }
                else if ((i + 1) >= line.size()) // end of line
                {
                    user_nums.push_back(std::stoi(buf.str()));
                    int win_count = 0;
                    for (unsigned int num: user_nums)
                    {
                        if (std::find(win_nums.begin(), win_nums.end(), num) != win_nums.end())
                        {
                            win_count++;
                        }
                    }
                    total_points += std::pow(2, win_count - 1);
                }
                break;
            }
        }
    }
    in.close();

    std::cout << "total points: " << total_points << std::endl;

    return 0;
}