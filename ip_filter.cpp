#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <array>


template<typename C, typename P>
void print(C container, P predicate) {
    typedef typename C::value_type element_type;
    std::vector<element_type> ip_pool_filter;

    std::copy_if(container.begin(), container.end(),  std::back_inserter(ip_pool_filter), predicate);
    for(std::vector<std::array<size_t, 4>>::const_iterator ip = ip_pool_filter.cbegin(); ip != ip_pool_filter.cend(); ++ip)
    {
        for(std::array<size_t, 4>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    try
    {        
        std::vector<std::array<size_t, 4>> ip_pool;
        std::ifstream file("ip_filter.tsv");

        for(std::string line; std::getline(file, line);)
        {
            std::string s_addr = line.substr(0, line.find('\t'));
            std::vector<std::string> v = split(s_addr, '.');
            std::array<size_t, 4> addr = {std::stoi(v.at(0)), std::stoi(v.at(1)), std::stoi(v.at(2)), std::stoi(v.at(3))};            
            ip_pool.push_back(addr);
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>());        
        auto all_ip = [](const std::array<size_t, 4>& octetsA) { return true; };
        print(ip_pool, all_ip);

        // ip = filter(1),  1.*.*.*       
        auto starts_from_1 = [](const std::array<size_t, 4>& octetsA) { return octetsA[0] == 1; };
        print(ip_pool, starts_from_1);

        // ip = filter(46, 70), 46.70.*.*        
        auto starts_from_4670 = [](const std::array<size_t, 4>& octetsA) { return octetsA[0] == 46 && octetsA[1] == 70; };
        print(ip_pool, starts_from_4670);

        // ip = filter_any(46), 46.*.*.* || *.46.*.* || *.*.46.* || *.*.*.46        
        auto has_any_46 = [](const std::array<size_t, 4>& octetsA) { return octetsA[0] == 46 || octetsA[1] == 46 || octetsA[2] == 46 || octetsA[3] == 46; };
        print(ip_pool, has_any_46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
