#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

std::vector<int>::iterator findInSorted(std::vector<int>::iterator first, std::vector<int>::iterator last, int el)
{
    if (first == last)
        return last;

    std::vector<int>::iterator middle = first + (last - first) / 2;

    if (el == *middle)
        return middle;

    if (*middle < el && middle + 1 != last)
        return findInSorted(middle, last, el);
    if (*middle > el)
        return findInSorted(first, middle, el);

    return last;
}

int main() {
    int n = 10;
    std::vector<int> d = {-2, 3, 5, 6,7,9,13};
    std::vector<int>::iterator l  = findInSorted(d.begin(), d.end(), 3);
    std::cout<<(*l)<<std::endl;
    std::cout<<(*(l+1));

    return 0;
}


