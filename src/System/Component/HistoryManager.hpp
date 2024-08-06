#pragma once
#include <iostream> 
#include <vector>

class HistoryManager
{
private:
    std::vector<std::string> history;
    int currentHistoryIndex;
};