#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

namespace Helper
{
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim))
            elems.push_back(item);
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    std::vector<int> inputParser(std::string inputStr)
    {
        std::vector<std::string> tempVec = split(inputStr, ' ');
        std::vector<int> resultVec;

        for(int i=0; i<tempVec.size(); i++)
            resultVec.push_back(std::stoi(tempVec[i]));

        return resultVec;
    }
}
