#pragma once
#include <cstddef> // size_t
#include <stdlib.h> 
#include <time.h> 
#include <stdexcept>

#define STEP_OF_CAPACITY 15

template<typename T> class TVector;

template<typename T>
int find_first(const TVector<T>& vec, const T& value);

template<typename T>
int find_last(const TVector<T>& vec, const T& value);

template<typename T>
int* find_elems(const TVector<T>& vec, const T& value);

template<typename T>
void swap(T* a, T* b);

template<typename T>
void randomize(const TVector<T>& vec);

template<typename T>
void hoara_sort_rec(const TVector<T>& vec, int left, int right);

template<typename T>
void hoara_sort(const TVector<T>& vec);

enum State { empty, busy, deleted };

template<class T>
class TVector {
    T* _data; 
    size_t _capacity; 
    size_t _size; 
    size_t _deleted; 
    State* _states; 
public:
    TVector();
    TVector(size_t); 
    TVector(const T*, size_t);
    TVector(const TVector<T>&);

    ~TVector();

    size_t capacity() const noexcept;
    size_t size() const noexcept;

    inline bool is_empty() const noexcept;

    inline T& front();
    inline T& back();

    inline T* begin() noexcept;
    inline T* end() noexcept;

    inline const T* data() const noexcept; 
    inline const State* states() const noexcept;

    void push_front_elem(const T&);
    void push_back_elem(const T&);
    void insert_elem(const T&, size_t); 
    void push_front_elems(T* values, size_t count);
    void push_back_elems(T* values, size_t count);
    void insert_elems(size_t pos, T* values, size_t count);

    void pop_front_elem();
    void pop_back_elem();
    void erase_elem(size_t);
    void pop_front_elems(size_t count);
    void pop_back_elems(size_t count);
    void erase_elems(size_t pos, size_t count);

    void emplace(size_t pos, T value); 

    void clear() noexcept;
    void reserve(size_t new_capacity);
    void assign(size_t count, const T& value);
    T& at(size_t pos);
    void shrink_to_fit();
    void resize(size_t new_size, const T& value);
    void resize(size_t new_size);

    TVector<T>& operator=(const TVector<T>& other);
    bool operator==(const TVector<T>& other) const noexcept;
    bool operator!=(const TVector<T>& other) const noexcept;
    T& operator[](size_t pos); 

    void print_elems();
    void print_states();

    friend int find_first<T>(const TVector<T>&, const T&);
    friend int find_last<T>(const TVector<T>&, const T&);
    friend int* find_elems<T>(const TVector<T>&, const T&);

    friend void swap<T>(T* a, T* b);
    friend void randomize<T>(const TVector<T>& vec);

    friend void hoara_sort_rec<T>(const TVector<T>& vec, int left, int right);
    friend void hoara_sort<T>(const TVector<T>& vec);

private:
    inline bool is_full() const noexcept;
    void allocate_memory(size_t);
    void reallocate_memory(size_t);
    void reallocate_memory_for_delete();
    void free_memory() noexcept;
};

template<class T>
TVector<T>::TVector() {
    _data = nullptr;
    _capacity = 0;
    _size = 0;
    _deleted = 0;
    _states = nullptr;
}

template<class T>
TVector<T>::TVector(size_t size) {
    _data = nullptr;
    _size = size;
    _capacity = 0; 
    _deleted = 0;
    _states = nullptr;


    if (_size > 0) { 
        _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY; 
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}

template<class T>
TVector<T>::TVector(const T* arr, size_t size) {
    _capacity = 0; 
    _data = nullptr; 
    _size = size;
    _deleted = 0;
    _states = nullptr;

    if (_size > 0) {
        _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; ++i) {
            _data[i] = arr[i];
        }
        for (size_t i = 0; i < _size; i++) {
            _states[i] = busy;
        }
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}

template<class T>
TVector<T>::TVector(const TVector<T>& other) {
    _capacity = 0;
    _data = nullptr;
    _size = other._size;
    _deleted = other._deleted;
    _states = nullptr;

    if (_size > 0) {
        _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
    }
}

template<class T>
TVector<T>::~TVector() {
    delete[] _data;
    delete[] _states;
}

template<class T>
inline const T* TVector<T>::data() const noexcept { return _data; }

template<class T>
inline const State* TVector<T>::states() const noexcept { return _states; }

template<class T>
size_t TVector<T>::capacity() const noexcept { return _capacity; }

template<class T>
size_t TVector<T>::size() const noexcept { return _size - _deleted; }
 
template<class T>
inline T& TVector<T>::front() {
    if (_size == 0) {
        throw std::logic_error("There are no busy elements");
    }
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            return _data[i];
        }
    }
}

template<class T>
inline T& TVector<T>::back() {
    if (_size == 0) {
        throw std::logic_error("There are no busy elements");
    }
    for (size_t i = _size; i > 0; --i) {
        if (_states[i - 1] == busy) {
            return _data[i - 1];
        }
    }
}

template<class T>
inline T* TVector<T>::begin() noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            return _data[i];
        }
    }
}

template<class T>
inline T* TVector<T>::end() noexcept { 
    return _data + _size;
}

template<class T>
inline bool TVector<T>::is_empty() const noexcept {
    if (_size == 0) return true;

    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == busy) {
            return false;
        }
    }
    return true;
}


template<class T>
void TVector<T>::push_front_elem(const T& value) {
    size_t i = 0;
    while (i < _capacity && _states[i] == deleted) {
        i++;
    }
    if (i > 0 && i < _capacity) {
        _data[i - 1] = value;
        _states[i - 1] = busy;
        _size++;
        _deleted--;
        return;
    }
    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    for (size_t j = _size; j > 0; j--) {
        _data[j] = _data[j - 1];
        _states[j] = _states[j - 1];
    }
    _data[0] = value;
    _states[0] = busy;
    _size++;
}

template<class T>
void TVector<T>::push_back_elem(const T& value) {
    for (size_t i = _size; i > 0; i--) {
        if (_states[i] == deleted) {
            _data[i] = value;
            _states[i] = busy;
            _deleted--;
            return; 
        }
        if (_states[i] == busy) break; 
    }

    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    _data[_size] = value;
    _states[_size] = busy;
    _size++;
}

template<class T>
void TVector<T>::insert_elem(const T& value, size_t pos) {
    pos--;
    if (pos > _size) {
        throw std::out_of_range("Insert position out of range");
    }

    if (_size > 0 && _states[pos] == deleted) {
        _data[pos] = value;
        _states[pos] = busy;
        return;
    }

    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }

    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }

    _data[pos] = value;
    _states[pos] = busy;
    _size++;
}

template<class T>
void TVector<T>::push_front_elems(T* values, size_t count) {
    if (!values || count == 0) return;

    size_t reused = 0; //  сколько элементов поместили в deleted
    for (size_t i = 0; i < _capacity && reused < count; ++i) {
        if (_states[i] == deleted) {
            _data[i] = values[reused++];
            _states[i] = busy;
            _deleted--;
        }
    }

    const size_t remaining = count - reused; // сколько осталось добавить
    if (remaining > 0) {
        if (_size + remaining > _capacity) {
            size_t new_capacity = _capacity;
            while (_size + remaining > new_capacity) {
                new_capacity += STEP_OF_CAPACITY;
            }
            reallocate_memory(new_capacity);
        }

        for (size_t i = _size; i-- > 0; ) {
            _data[i + remaining] = _data[i];
            _states[i + remaining] = _states[i];
        }

        for (size_t i = 0; i < remaining; ++i) {
            _data[i] = values[reused + i];
            _states[i] = busy;
        }

        _size += remaining;
    }
}

template<class T>
void TVector<T>::push_back_elems(T* values, size_t count) {
    if (values == nullptr || count == 0) {
        return;
    }
    if (_size + count > _capacity) {
        size_t new_capacity = _capacity;
        while (_size + count > new_capacity) {
            new_capacity += STEP_OF_CAPACITY;
        }
        reallocate_memory(new_capacity);
    }
    for (size_t i = 0; i < count; i++) {
        if (_states[_size + i] == deleted) {
            _data[_size + i] = values[i];
            _states[_size + i] = busy;
            _deleted--;
        }
        else {
            _data[_size + i] = values[i];
            _states[_size + i] = busy;
        }
    }

    _size += count;
}

template<class T>
void TVector<T>::insert_elems(size_t pos, T* values, size_t count) { 
    pos--;
    if (pos > _size) {
        throw std::out_of_range("Insert position out of range");
    }
    if (values == nullptr || count == 0) {
        return;
    }
    size_t reused = 0;
    for (size_t i = pos; i < _capacity && reused < count; i++) {
        if (_states[i] == deleted) {
            _data[i] = values[reused++];
            _states[i] = busy;
            _deleted--;
        }
    }
    const size_t remaining = count - reused;
    if (remaining > 0) {
        if (_size + remaining > _capacity) {
            size_t new_capacity = _capacity;
            while (_size + remaining > new_capacity) {
                new_capacity += STEP_OF_CAPACITY;
            }
            reallocate_memory(new_capacity);
        }
        
        for (size_t i = _size; i > pos; i--) {
            _data[i + remaining - 1] = _data[i - 1];
            _states[i + remaining - 1] = _states[i - 1];
        }

        for (size_t i = 0; i < remaining; i++) {
            _data[pos + i] = values[i];
            _states[pos + i] = busy;
        }
    }

    _size += remaining;
}


template<class T>
void TVector<T>::pop_front_elem() {
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            break;
        }
    }
    _deleted += 1;

    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_back_elem() {
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }
    size_t i = _size;
    while (i > 0 && _states[i - 1] == deleted) {
        i--;
        _states[i] = empty;
        _size--;
        _deleted--;
    }
    for (size_t i = _size - 1; i > 0; i--) {
        if (_states[i] == busy) {
            _states[i] = empty;
            break;
        }
    }

    _size--;

    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::erase_elem(size_t pos) { 
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (pos == 0 || pos > _size) { 
        throw std::out_of_range("Insert position out of range");
    }

    for (int i = pos - 1; i < _size; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            break;
        }
    }

    _deleted += 1;
    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_front_elems(size_t count) {
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (count > _size - _deleted) {
        throw std::invalid_argument("Count cannot be bigger than size");
    }

    size_t removed = 0;
    for (size_t i = 0; removed < count; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            removed++;
        }
    }
    _deleted += count;

    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_back_elems(size_t count) { 
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (count > _size - _deleted) {
        throw std::invalid_argument("Count cannot be bigger than size");
    }

    size_t i = _size;
    while (i > 0 && _states[i - 1] == deleted) {
        i--;
        _states[i] = empty;
        _size--;
        _deleted--;
    }

    for (int i = _size - 1; i > _size - count - 1; i--) {
        if (_states[i] == busy) {
            _states[i] = empty;
        }
    }

    _size -= count;

    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::erase_elems(size_t pos, size_t count) {  
    if (_size == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (count > _size) {
        throw std::invalid_argument("Count cannot be bigger than size");
    }

    if (pos > _size || pos < 0 ) {
        throw std::out_of_range("Insert position out of range");
    }

    while (pos < _size && _states[pos] != busy) {
        pos++;
    }

    for (int i = pos - 1; i < pos + count - 1; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
        }
    }
    _deleted += count;

    if (_deleted * 100 > _capacity * 15) {
        reallocate_memory_for_delete();
    }
}


template <typename T>
void TVector<T>::emplace(size_t pos, T value) {
    if (pos >= _size - _deleted) {
        throw std::out_of_range("Position out of range");
    }

    int busy_count = 0;
    int new_index = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            busy_count++;
            if (busy_count == pos) {
                _data[new_index] = value;
                _states[new_index] = busy;
                break;
            }
            new_index++;
        }
    }
}

template <typename T>
void TVector<T>::clear() noexcept {
    for (size_t i = 0; i < _capacity; ++i) {  
        if (_states[i] == busy) {
            _states[i] = empty;  
        }
    }
    _size = 0;
    _deleted = 0;

    /*delete[] _data;
    delete[] _states;
    _data = nullptr;
    _states = nullptr;
    _capacity = 0; */
}

template<class T>
void TVector<T>::reserve(size_t new_capacity) { 
    if (new_capacity <= _capacity) {
        return;
    }

    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity]();

    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[i] = _data[i];
            new_states[i] = busy;
        }
    }

    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _size -= _deleted;
    _capacity = new_capacity;
    _deleted = 0;
}

template <typename T>
void TVector<T>::assign(size_t count, const T& value) {
    clear();
    if (count > 0) {
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            _data[i] = value;
            _states[i] = busy;
        }
        _size = count;
    }
}

template <typename T>
T& TVector<T>::at(size_t pos) {
    if (pos >= _size - _deleted) {
        throw std::out_of_range("Index out of range");
    }
    while (pos < _size && _states[pos] != busy) {
        pos++;
    }
    return _data[pos]; 
}

template <typename T>
void TVector<T>::shrink_to_fit() {
    if (_size == 0) {
        delete[] _data;
        delete[] _states;
        _data = nullptr;
        _states = nullptr;
        _capacity = 0;
        return;
    }

    T* new_data = new T[_size - _deleted];
    State* new_states = new State[_size -_deleted];

    size_t new_index = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[new_index] = _data[i];
            new_states[new_index] = busy;
            new_index++;
        }
    }

    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _size -= _deleted;
    _capacity = _size;
    _deleted = 0;
}


template <typename T>
void TVector<T>::resize(size_t new_size) {
    if (new_size < _size - _deleted) {
        for (size_t i = new_size; i < _size - _deleted; i++) {
            if (_states[i] == busy) {
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size - _deleted) {
        reserve(new_size);
        for (size_t i = _size - _deleted; i < new_size; i++) {
            _data[i] = T();
            _states[i] = busy;
        }
        _size = new_size;
    }
}

template <typename T>
void TVector<T>::resize(size_t new_size, const T& value) {
    if (new_size < _size - _deleted) {
        for (size_t i = new_size; i < _size - _deleted; i++) {
            if (_states[i] == busy) {
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size - _deleted) {
        reserve(new_size);
        for (size_t i = _size - _deleted; i < new_size; i++) {
            _data[i] = value;
            _states[i] = busy;
        }
        _size = new_size;
    }
}

//template <typename T>
//TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
//    if (this != &other) {
//        if (_capacity != other._capacity) {
//            free_memory();
//            reserve(other._capacity);
//        }
//        for (size_t i = 0; i < other._size; ++i) {
//            if (other._states[i] == busy) {
//                _data[i] = other._data[i];
//                _states[i] = busy;
//            }
//        }
//        _size = other._size;
//        //_deleted = other._deleted;
//    }
//    return *this;
//}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        if (_capacity != other._capacity) {
            free_memory(); 
            reserve(other._capacity); 
        }
        for (size_t i = 0; i < other._size; ++i) {
            if (other._states[i] == busy) {
                _data[i] = other._data[i];
                _states[i] = busy; 
            }
            else if (other._states[i] == deleted) {
                _states[i] = deleted;
            }
        }

        _size = other._size;
        _deleted = other._deleted; 
    }
    return *this;
}

template <typename T>
bool TVector<T>::operator==(const TVector<T>& other) const noexcept { 
    if (this == &other) return true;
    if (_size != other._size) return false;

    int this_count = 0, other_count = -1;

    for (int i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            for (int j = 0; j < other._size; j++) {
                other_count += 1;
                if (other._states[other_count] == busy) {
                    if (_data[i] != other._data[other_count]) {
                        return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}

template <typename T>
bool TVector<T>::operator!=(const TVector<T>& other) const noexcept {
    return !(*this == other);
}

template <typename T>
T& TVector<T>::operator[](size_t pos) { 
    while (pos < _size && _states[pos] != busy) {
        pos++;
    }
    return _data[pos];
}

template<class T>
void TVector<T>::print_elems() {
    int entrance = 0;
    for (size_t i = 0; entrance < _size; i++) {
        if (_states[i] == busy) {
            std::cout << _data[i] << " ";
            entrance++;
        }
    }
    std::cout << std::endl;
    /*for (size_t i = 0; i < _capacity; i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;*/
}

template<class T>
void TVector<T>::print_states() {
    for (size_t i = 0; i < _capacity; i++) {
        std::cout << _states[i] << " ";
    }
    std::cout << std::endl;
}

template<class T>
inline bool TVector<T>::is_full() const noexcept { return _capacity > 0 && (_size - _deleted) == _capacity; } 

template<class T>
void TVector<T>::allocate_memory(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < new_capacity; ++i) {
        new_states[i] = empty;
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _deleted = 0;
}

template<class T>
void TVector<T>::reallocate_memory_for_delete() {
    size_t busy_count = _size - _deleted;
    size_t new_capacity = ((busy_count / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;

    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    size_t new_index = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == busy) {
            new_data[new_index] = _data[i];
            new_states[new_index] = busy;
            new_index++;

        }
    }

    delete[] _data;
    delete[] _states;

    _size = busy_count;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _deleted = 0;

    for (size_t i = _size; i < _capacity; ++i) {
        _states[i] = empty;
    }
}

template<class T>
void TVector<T>::reallocate_memory(size_t new_capacity) {
    if (_capacity == 0) {
        allocate_memory(STEP_OF_CAPACITY);
    }

    T* new_data =  new T[new_capacity];
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < new_capacity; ++i) {
        new_states[i] = empty;
    }

    size_t new_index = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == busy) {
            new_data[new_index] = _data[i];
            new_states[new_index] = busy;
            new_index++;

        }
    }
    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _deleted = 0;  
}

template<class T>
void TVector<T>::free_memory() noexcept {
    delete[] _data;
    delete[] _states;

    _data = nullptr;
    _states = nullptr;
    _size = 0;
    _capacity = 0;
    _deleted = 0;
}

template <typename T>
int find_first(const TVector<T>& vec, const T& value) {
    int visible_idx = -1;

    if (vec.size() == 0) {
        throw std::invalid_argument("Cannot find from empty vector");
    }
    for (size_t i = 0; i < vec._size; i++) {
        if (vec._states[i] == busy) {
            visible_idx++;
            if (vec._data[i] == value) {
                return visible_idx;
            }
        }
    }
    return -1;
}

template <typename T>
int find_last(const TVector<T>& vec, const T& value) {
    int last_found = -1;
    int visible_idx = vec.size();

    if (vec.size() == 0) {
        throw std::invalid_argument("Cannot find from empty vector");
    }

    for (size_t i = vec.size() - 1; i > 0; i--) {
        if (vec._states[i] == busy) {
            visible_idx--;
            if (vec._data[i] == value) {
                last_found = visible_idx;
                break;
            }
        }
    }

    return last_found;
}

template<typename T>
int* find_elems(const TVector<T>& vec, const T& value) {
    if (vec.size() == 0) {
        throw std::invalid_argument("Cannot find from empty vector");
    }

    int size = 0;

    for (int i = 0; i < vec.size(); i++) { 
        if (vec._states[i] == busy && vec._data[i] == value) {
            size++;
        }
    }

    if (size == 0) {
        int* result = new int[1];
        result[0] = -1;
        return result;
    }

    int* result = new int[size];
    int index = 0;

    for (int i = 0; i < vec.size(); i++) { 
        if (vec._states[i] == busy && vec._data[i] == value) {
            result[index] = i; 
            index++;
        }
    }

    return result; 
}

template <typename T>
void randomize(const TVector<T>& vec) {
    srand(time(NULL));

    for (int i = vec._size; i > 0; i--) {
        if (vec._states[i] == busy) {
            int j = rand() % (i + 1);
            swap(&vec._data[i], &vec._data[j]);
            swap(&vec._states[i], &vec._states[j]);
        }
    }
}

template <typename T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void hoara_sort_rec(const TVector<T>& vec, int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int base_pos = (left + right) / 2;  
        T base_value = vec._data[base_pos];

        while (l <= r) {
            while (vec._data[l] < base_value) {
                l++;
            }
            while (vec._data[r] > base_value) {
                r--;
            }
            if (l <= r) {                   
                if (l < r) {  
                    swap(&vec._data[l], &vec._data[r]);
                    swap(&vec._states[l], &vec._states[r]);
                }
                l++;
                r--;
            }
        }
        hoara_sort_rec(vec, left, r);
        hoara_sort_rec(vec, l, right);  
    }
}

template <typename T>
void hoara_sort(const TVector<T>& vec) {
    hoara_sort_rec(vec, 0, vec._size);
}