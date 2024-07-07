#include <string>
#include <map>
#include <vector>
#include <iostream>



std::map<std::string,std::string> POST;

std::vector<std::string> split(const std::string& str,const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
std::map<std::string,std::string> get_post(const std::vector<std::string>& ps,const std::string& delim)
{
    std::map<std::string,std::string> pars;
    std::string key,value;
    size_t prev = 0, pos = 0;
    for(const std::string& str : ps)
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        key = str.substr(0, pos);

        if(pos < str.length())
        {
            pos++;
            value = str.substr(pos, str.length() - 1);
        }
        else
        {
            value = "";
        }

        pars.insert(std::pair(key,value));
    }
    return pars;
}

int main(int argc, char *argv[])
{

    std::string strpost;
    std::cin >> strpost;
    auto params = split(strpost,"&");
    POST = get_post(params,"=");

    /*for (auto const& x : POST)
    {
        std::cout << x.first  // string (key)
              << ':'
              << x.second // string's value
              << std::endl;
    }
    */


    printf("Content-type: text/html\n\n");
    std::map<std::string,std::string>::iterator result = POST.find(std::string("counter"));
    int number;
    if(result != POST.end())
    {
        number = std::stoi(result->second);
        number++;
        printf("%i",number);
    }

	return 0;
}
