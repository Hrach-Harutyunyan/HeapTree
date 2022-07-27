#include "heapTree.hpp"

int main() {
    HeapTree<int> a {5, 1, 9 ,8, 2};
    std::cout << a << std::endl;

    HeapTree<int, false> b {5, 1, 9 ,8, 2, 10, 4, 55, 23};
    std::cout << b << std::endl;


    

}