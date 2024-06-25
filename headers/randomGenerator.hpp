#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <cinttypes>
#include <random>
#include <cassert>

template <class T, size_t _tsize>
class randomGenerator
{
    std::uniform_int_distribution<T> dis;
    std::mt19937_64 gen;
    size_t index;
    T nums[_tsize];

    void reset();
    static constexpr T getMin();
    static constexpr T getMax();
    static int64_t baseRand();

public:
    randomGenerator();
    randomGenerator(const int64_t seed);
    randomGenerator(const T minInclusive, const T maxInclusive);
    randomGenerator(const int64_t seed, const T minInclusive, const T maxInclusive);

    T next();

    std::vector<T> genVec(const size_t size);
    std::vector<T> genVec(const size_t size, const size_t capacity);

    void fill(T* block, const size_t size);
    void fill(T* startInclusive, T* endInclusive);

    T* genChunk(const size_t size);
};

template <class T, size_t _tsize>
void randomGenerator<T, _tsize>::reset()
{
    this->index = 0;
    for (size_t i = 0; i < _tsize; i++) nums[i] = dis(gen);
}

template <class T, size_t _tsize>
constexpr T randomGenerator<T, _tsize>::getMin()
{
    return std::numeric_limits<T>::min();
}

template <class T, size_t _tsize>
constexpr T randomGenerator<T, _tsize>::getMax()
{
    return std::numeric_limits<T>::max();
}

template <class T, size_t _tsize>
int64_t randomGenerator<T, _tsize>::baseRand()
{
    std::random_device randDevice;
    const int64_t r1 = rand();
    const int64_t r2 = rand();
    const int64_t r3 = rand();
    return r1*r2*r3;
}

template <class T, size_t _tsize>
randomGenerator<T, _tsize>::randomGenerator() : randomGenerator<T, _tsize>(baseRand(), getMin(), getMax()) {}

template <class T, size_t _tsize>
randomGenerator<T, _tsize>::randomGenerator(const int64_t seed) : randomGenerator<T, _tsize>(seed, getMin(), getMax()) {}

template <class T, size_t _tsize>
randomGenerator<T, _tsize>::randomGenerator(const T minInclusive, const T maxInclusive) : randomGenerator<T, _tsize>(baseRand(), minInclusive, maxInclusive) {}

template <class T, size_t _tsize>
randomGenerator<T, _tsize>::randomGenerator(const int64_t seed, const T minInclusive, const T maxInclusive)
{
    gen = std::mt19937_64(seed);
    dis = std::uniform_int_distribution<T>(minInclusive, maxInclusive);
    this->reset();
}

template <class T, size_t _tsize>
T randomGenerator<T, _tsize>::next()
{
    if (this->index == _tsize) this->reset();
    return this->nums[this->index++];
}

template <class T, size_t _tsize>
std::vector<T> randomGenerator<T, _tsize>::genVec(const size_t size)
{
    return genVec(size, size);
}

template <class T, size_t _tsize>
std::vector<T> randomGenerator<T, _tsize>::genVec(const size_t size, const size_t capacity)
{
    assert(capacity >= size);
    std::vector<T> v;
    v.resize(size);
    v.reserve(capacity);
    this->fill(&v[0], capacity);
    return v;
}

template <class T, size_t _tsize>
void randomGenerator<T, _tsize>::fill(T* block, const size_t size)
{
    for (size_t i = 0; i < size; i++) block[i] = next();
}

template <class T, size_t _tsize>
void randomGenerator<T, _tsize>::fill(T* startInclusive, T* endInclusive)
{
    const int64_t delta = endInclusive - startInclusive + 1;
    assert(delta > 0);
    this->fill(startInclusive, delta);
}

template <class T, size_t _tsize>
T* randomGenerator<T, _tsize>::genChunk(const size_t size)
{
    T* ptr = malloc(size*sizeof(T));
    this->fill(ptr, size);
    return ptr;
}

#endif // RANDOMGENERATOR_H