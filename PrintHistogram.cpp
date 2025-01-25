#include "DictionaryOnSequence.h"
#include <string>
#include <iostream>


void PrintHistogram(const DictionaryOnSequence<std::string, int>& histogram)
{
    for (int i = 0; i < histogram.GetCount(); i++)
    {
        auto pair = histogram.GetByIndex(i);
        std::cout << pair.key << ": " << pair.value << std::endl;
    }
}