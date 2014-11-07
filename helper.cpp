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

        for(int i=0; i<(int)tempVec.size(); i++)
            resultVec.push_back(std::stoi(tempVec[i]));

        return resultVec;
    }

    std::vector<std::vector<int> > strToMatrix(std::string inputStr)
    {
        std::vector<int> tempVec = Helper::inputParser(inputStr);
        std::vector<int> firstRow(tempVec.begin(), tempVec.begin()+2);
        std::vector<int> secondRow(tempVec.begin()+2, tempVec.end());
        std::vector<std::vector<int> > m;
        m.push_back(firstRow);
        m.push_back(secondRow);
        return m;
    }
}
