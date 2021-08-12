#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <algorithm>
#include <sys/time.h>

int main(int argc, char* argv[])
{
    //random length
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned>length(1,100);
    std::vector<std::string> random_str;
    std::uniform_int_distribution<unsigned char>cha(0,25);

    e.seed(time(NULL));
    for (size_t i = 0; i < 1000000; i++)
    {
        std::string single_str;
        int length_str = length(e);
        for (size_t i = 0; i < length_str; i++)
        {
            single_str += cha(e) + 'a';
        }
        // std::cout << single_str << std::endl;
        random_str.emplace_back(single_str);    
    }
    
    // std::map<unsigned int, unsigned int> statistics_length;
    // std::map<char, int> statistics_char;
    // for(auto &s_str : random_str)
    // {
    //     statistics_length[s_str.length()] += 1;
    //     statistics_char[s_str.at(0)] += 1;
    // }

    std::vector<std::string> random_str_copy = random_str;

    // for (auto it = statistics_char.begin(); it != statistics_char.end(); ++it)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }
    
    // for (auto it = statistics_length.begin(); it != statistics_length.end(); ++it)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }

    struct timeval t1,t2;
    gettimeofday(&t1,NULL);
    std::sort(random_str.begin(), random_str.end());
    gettimeofday(&t2,NULL);
    std::cout << "char sort use: " << std::to_string(t2.tv_sec-t1.tv_sec) << "s"
        << std::to_string(t2.tv_usec-t1.tv_usec < 0 ? t2.tv_usec-t1.tv_usec + 1000000 : t2.tv_usec-t1.tv_usec) 
        << "us" << std::endl;
    // for (auto &tmp : random_str)
    // {
    //     std::cout << tmp << std::endl;
    // }
    
    auto length_comp = [](const std::string &a, const std::string &b){return (a.length() < b.length());};  
    gettimeofday(&t1,NULL);
    std::sort(random_str_copy.begin(), random_str_copy.end(), length_comp);
    gettimeofday(&t2,NULL);
    std::cout << "length sort use: " << std::to_string(t2.tv_sec-t1.tv_sec) << "s"
        << std::to_string(t2.tv_usec-t1.tv_usec < 0 ? t2.tv_usec-t1.tv_usec + 1000000 : t2.tv_usec-t1.tv_usec) 
        << "us" << std::endl;
    // for (auto &tmp : random_str_copy)
    // {
    //     std::cout << tmp << std::endl;
    // }
    gettimeofday(&t1,NULL);
    std::find(random_str_copy.begin(),random_str_copy.end(), "abc") == random_str_copy.end()
        ? (std::cout << "not include" << std::endl) : (std::cout << "include" << std::endl);
    gettimeofday(&t2,NULL);
    std::cout << "length find use: " << std::to_string(t2.tv_sec-t1.tv_sec) << "s"
        << std::to_string(t2.tv_usec-t1.tv_usec < 0 ? t2.tv_usec-t1.tv_usec + 1000000 : t2.tv_usec-t1.tv_usec) 
        << "us" << std::endl;

    gettimeofday(&t1,NULL);
    std::find(random_str.begin(),random_str.end(), "abc") == random_str.end()
        ? (std::cout << "not include" << std::endl) : (std::cout << "include" << std::endl);
    gettimeofday(&t2,NULL);
    std::cout << "char find use: " << std::to_string(t2.tv_sec-t1.tv_sec) << "s"
        << std::to_string(t2.tv_usec-t1.tv_usec < 0 ? t2.tv_usec-t1.tv_usec + 1000000 : t2.tv_usec-t1.tv_usec) 
        << "us" << std::endl;

    int ss = 0;    
    gettimeofday(&t1,NULL);
    for (auto &tmp : random_str_copy)
    {
        ss++;
    }
    
    gettimeofday(&t2,NULL);
    std::cout << "loop use: " << std::to_string(t2.tv_sec-t1.tv_sec) << "s"
        << std::to_string(t2.tv_usec-t1.tv_usec < 0 ? t2.tv_usec-t1.tv_usec + 1000000 : t2.tv_usec-t1.tv_usec) 
        << "us" << std::endl;    
}
