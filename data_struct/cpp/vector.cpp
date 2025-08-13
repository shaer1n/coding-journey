#include <iostream>
#include <memory>

template<class T>
class Vector{
public:
    Vector()
        :_start(nullptr),_finish(nullptr),_endofstorage(nullptr)
    {}

    ~Vector(){
        clear();
        if(_start){
            _alloc.deallocate(_start, capacity());
        }
    }

    void push_back(const T &val){
        if(size() == capacity()){
            reallocate();
        }
        // 插入元素，调用元素的构造函数
        _alloc.construct(_finish++, val);
    }

    int size() const {return _finish - _start;}
    int capacity() const {return _endofstorage - _start;}

    T& operator[](size_t i){
        if(i < size()) return _start[i];
        throw std::out_of_range("Index out range");
    }

    const T& operator[](size_t i) const {
        if(i < size()) return _start[i];
        throw std::out_of_range("Index out range");
    }

    void clear(){
        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
    }
private:
    void reallocate(){
        size_t oldSize = size();
        size_t oldCapacity = capacity();
        size_t newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

        T *temp = _alloc.allocate(newCapacity);
        // 使用移动构造
        std::uninitialized_move(_start, _finish, temp);

        // 清空原来开辟的空间资源
        clear();
        if(_start){
            _alloc.deallocate(_start, oldCapacity);
        }

        _start = temp;
        _finish = temp + oldSize;
        _endofstorage = temp + newCapacity;

    }
    T *_start;
    T *_finish;
    T *_endofstorage;
    static std::allocator<T> _alloc;
};

template<class T>
std::allocator<T> Vector<T>::_alloc;

int main(){
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::cout << v.size() << " " << v.capacity() << std::endl;
    for(size_t i = 0; i < v.size(); ++i){
        std::cout << v[i] << std::endl;
    }
    return 0;
}