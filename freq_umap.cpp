#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>

void search (std::unordered_map<std::string, int> *inp, std::unordered_map<std::string, int> &out)
{
    int j = 0;
    std::string test;
    for (const auto& i : *inp)
    {
        if (i.second > j) {j = i.second; test = i.first;}
        if (i.second == j) {
            for (size_t v = 0; v < test.size(); v++)
            {
                if (i.first[v] == '\0')
                {
                    test = i.first;
                    break;
                }
                if (test[v] == '\0')
                    break;
                if (i.first[v] < test[v])
                {
                    test = i.first;
                    v = test.size();
                    break;
                }
            }
        }
    }
    for (const auto& i : *inp)
    {
        if (i.second == j && !test.compare(i.first)) {
            out.insert(i); inp->erase(i.first); return;
            }
    }
}

int main (int argc, char *argv[])
{
    std::ifstream *f_str(NULL);
    if (argc == 2)
    {
        f_str = new std::ifstream(argv[1]);
        if (!f_str)
        {
            std::cerr << "Error: File not existed or can't be opened";
            return 1;
        }
    }
    else
    {
        std::string inp;
        std::cout << "input file name: ";
        std::cin >> inp;
        f_str = new std::ifstream(inp);
        if (!f_str)
        {
            std::cerr << "Error: File not existed or can't be opened";
            return 1;
        }
    }
    std::unordered_map<std::string, int> freq_unordered_map;
    std::string buf;
    const auto start = std::chrono::steady_clock::now();
    while (f_str->peek() != EOF)
    {
        char c;
        f_str->get(c);
        for (;!std::isalpha(c) && !f_str->eof();)
        {
            f_str->get(c);
        }
        for (;std::isalpha(c) && !f_str->eof();)
        {
            buf.push_back(c);
            f_str->get(c);
        }
        auto tmp = freq_unordered_map.find(buf);
        if (tmp == freq_unordered_map.end())
        {
            freq_unordered_map.insert({buf, 1});
            buf.clear();
        }
        else
        {
            tmp->second++;
            buf.clear();
        }
    }
    const auto build = std::chrono::steady_clock::now();
    const auto build_time = std::chrono::duration_cast<std::chrono::microseconds>((build - start));
    std::unordered_map <std::string, int> used;
    for (int x = 0; x < 10; x++)
    {
        search (&freq_unordered_map, used);
        for (const auto& s : used)
            {std::cout << s.first << " " << s.second << '\n';}
        used.clear();
    }
    const auto finish = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>((finish - build));
    std::cout << "build: " << build_time << '\n';
    std::cout << "sort: " << duration << '\n';
    return 0;
}