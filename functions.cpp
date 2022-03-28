#include "functions.h"
#include <iostream>
bool compareFile(istreambuf_iterator<char> file1B, istreambuf_iterator<char> file2B, istreambuf_iterator<char> file1E, istreambuf_iterator<char> file2E)
{
    //Until each file iterator gets to the end, compare the entries of the files, if they are different, return false
    while (file1B != file1E && file2B != file2E)
    {
        if (*file1B != *file2B)
        { return false; }
        ++file1B;
        ++file2B;
    }
    return (file1B == file1E) && (file2B == file2E);
}
