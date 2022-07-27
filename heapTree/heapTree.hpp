#ifndef __HEAPTREE__HPP__
#define __HEAPTREE__HPP__

#include <iostream>
#include <initializer_list>
#include <vector>

template <typename T, bool Compare = true>
class HeapTree
{
public:
    HeapTree();
    HeapTree(const std::initializer_list<T>&);
    HeapTree(const HeapTree<T, Compare>&);
    HeapTree(HeapTree<T, Compare>&&);
    ~HeapTree();

public:
    HeapTree<T, Compare>& operator = (const HeapTree<T, Compare>&);
    HeapTree<T, Compare>& operator = (HeapTree<T, Compare>&&);
    bool operator == (const HeapTree<T, Compare>&) const;
    bool operator != (const HeapTree<T, Compare>&) const;
    HeapTree<T, Compare>& operator += (const HeapTree<T, Compare>&);

public:
    template <typename T1, bool Compare1>
    friend std::ostream& operator <<(std::ostream& os, const HeapTree<T1, Compare1>& obj);

    template <typename T1, bool Compare1>
    friend HeapTree<T1, Compare1> operator + (const HeapTree<T1, Compare1>&, const HeapTree<T1, Compare1>&);

public:
    std::size_t height();
    std::size_t insert(T);
    std::size_t linear_search(T) const ;
    bool extract_max_element();

private:
    bool compare(T, T);
    void max_heapify(std::size_t);
    std::size_t left(std::size_t);
    std::size_t right(std::size_t);
    std::size_t parent(std::size_t);

private:
    std::vector<T> arr;
};

template <typename T, bool Compare>
bool HeapTree<T, Compare>::compare(T first, T second) {
    if(Compare) return first < second;
    return first > second;
};


template <typename T, bool Compare>
HeapTree<T, Compare>::HeapTree() { }

template <typename T, bool Compare>
HeapTree<T, Compare>::HeapTree(const std::initializer_list<T>& init_list) {
    for(const auto el : init_list) {
        this->insert(el);
    }
}

template <typename T, bool Compare>
HeapTree<T, Compare>::HeapTree(const HeapTree<T, Compare>& other) {
    for(int i{}; i < other.arr.size(); ++i) {
        this->arr.push_back(other.arr[i]);
    }
}

template <typename T, bool Compare>
HeapTree<T, Compare>::HeapTree(HeapTree<T, Compare>&& other) {
    for(int i{}; i < other.arr.size(); ++i) {
        this->arr.push_back(other.arr[i]);
    }
    other.arr.clear();
}

template <typename T, bool Compare>
HeapTree<T, Compare>::~HeapTree() { }

template <typename T1, bool Compare1>
std::ostream& operator <<(std::ostream& os, const HeapTree<T1, Compare1>& obj) {
    for(std::size_t i{}; i < obj.arr.size(); ++i) {
        os << obj.arr[i] << " ";
    }
    return os;
};

template <typename T, bool Compare>
HeapTree<T, Compare> operator + (const HeapTree<T, Compare>& first, const HeapTree<T, Compare>& second) {
    HeapTree<T, Compare> res{};
    std::size_t size = std::min(first.arr.size(), second.arr.size());
    for(int i{}; i < size; ++i){
        res.arr.push_back(first.arr[i] + second.arr[i]);
    }
    if(size == first.arr.size()) {
        while(size != second.arr.size()) {
            res.arr.push_back(second.arr[size]);
            size++;
        }
    }else {
       while(size != first.arr.size()) {
            res.arr.push_back(first.arr[size]);
            size++;
        } 
    }
    return res;
};

template <typename T, bool Compare>
HeapTree<T, Compare>& HeapTree<T, Compare>::operator += (const HeapTree<T, Compare>& other) {
    std::size_t size = std::min(this->arr.size(), other.arr.size());
    for(int i{}; i < size; ++i) {
        this->arr[i] += other.arr[i];
    }
    return *this;
};

template <typename T, bool Compare>
HeapTree<T, Compare>& HeapTree<T, Compare>::operator = (const HeapTree<T, Compare>& other) {
    if(this != &other) {
        this->arr.clear();
        for(int i{}; i < other.arr.size(); ++i) {
            this->arr.push_back(other.arr[i]);
        }
    }
    return *this;
};

template <typename T, bool Compare>
HeapTree<T, Compare>& HeapTree<T, Compare>::operator = (HeapTree<T, Compare>&& other) {
    if(this != &other) {
        this->arr.clear();
        for(int i{}; i < other.arr.size(); ++i) {
            this->arr.push_back(other.arr[i]);
        }
        other.arr.clear();
    }
    return *this;
};

template <typename T, bool Compare>
bool HeapTree<T, Compare>::operator == (const HeapTree<T, Compare>& other) const {
    if(this->arr.size() != other.arr.size()) return false;
    for(std::size_t i{}; i < other.arr.size(); i++) {
        if(this->arr[i] != other.arr[i]) return false;
    }
    return true;
};

template <typename T, bool Compare>
bool HeapTree<T, Compare>::operator != (const HeapTree<T, Compare>& other) const {
    return !(*this == other);
};

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::left(std::size_t index) {
    return  2 * index + 1;
}

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::right(std::size_t index) {
    return 2 * index + 2;
}

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::parent(std::size_t index) {
    if(index > 0) return (index - 1) / 2;
};

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::insert(T elem) {
    this->arr.push_back(elem);
    std::size_t index = this->arr.size() - 1;
    std::size_t par = this->parent(index);
    while(index > 0 && this->compare(this->arr[par], this->arr[index])) {
        std::swap(this->arr[par], this->arr[index]);
        index = par;
        par = this->parent(index);
    }
    return index;
}

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::height() {
    std::size_t size = this->arr.size();
    std::size_t height = -1;
    while(size) {
        height++;
        size >>= 1;
    }
    return height;
};


template <typename T, bool Compare>
void HeapTree<T, Compare>::max_heapify(std::size_t index) {
    std::size_t max_index = index;
    std::size_t left_index = this->left(index);
    std::size_t right_index = this->right(index);
    std::size_t last_index = this->arr.size() - 1;
    if(left_index <= last_index  && this->compare(this->arr[left_index], this->arr[max_index])) {
        max_index = left_index;
    }
    if(right_index <= last_index  && this->compare(this->arr[right_index], this->arr[max_index])) {
        max_index = right_index;
    }
    if(max_index != index) {
        std::swap(this->arr[max_index], this->arr[index]);
        max_heapify(max_index);
    }
};

template <typename T, bool Compare>
bool HeapTree<T, Compare>::extract_max_element() {
    if(this->height() > -1) {
        std::swap(this->arr[0], this->arr[this->arr.size() - 1]);
        this->arr.pop_back();
        max_heapify(0);
        return true;
    }
    return false;
}

template <typename T, bool Compare>
std::size_t HeapTree<T, Compare>::linear_search(T elem) const {
    for(std::size_t i{}; i < arr.size(); ++i) {
        if(arr[i] == elem) return i;
    }
    return -1;
}

#endif