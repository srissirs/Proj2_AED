#ifndef PROJ2AED_MINHEAP_H
#define PROJ2AED_MINHEAP_H
#include <vector>
#include <unordered_map>
using namespace std;

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

///> Binary min-heap to represent integer keys of type K with values (priorities) of type V
template <class K, class V>
class MinHeap {
    struct Node { ///> An element of the heap: a pair (key, value)
        K key;
        V value;
    };

    int size;                  ///> Number of elements in heap
    int maxSize;               ///> Maximum number of elements in heap
    vector<Node> a;            ///> The heap array
    unordered_map<K, int> pos; ///> maps a key into its position on the array a
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MinHeap(int n, const K& notFound); ///> Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
    int getSize();              ///> Return number of elements in the heap
    bool hasKey(const K& key);  ///> Heap has key?
    void insert(const K& key, const V& value);      ///> Insert (key, value) on the heap
    void decreaseKey(const K& key, const V& value); ///> Decrease value of key
    K removeMin(); ///> remove and return key with smaller value
};


/**
 * @brief Make a value go "up the tree" until it reaches its position
 * @tparam K
 * @tparam V
 * @param i
 */
template <class K, class V>
void MinHeap<K,V>::upHeap(int i) {
    while (i>1 && a[i].value < a[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}


/**
 * @brief Make a value go "down the tree" until it reaches its position
 * @tparam K
 * @tparam V
 * @param i
 */
template <class K, class V>
void MinHeap<K,V>::downHeap(int i) {
    ///> while within heap limits
    while (LEFT(i) <= size) {
        int j = LEFT(i);
        ///> choose smaller child
        if (RIGHT(i)<=size && a[RIGHT(i)].value < a[j].value) j = RIGHT(i);
        ///> node already smaller than children, stop
        if (a[i].value < a[j].value) break;
        ///> otherwise, swap with smaller child
        swap(i, j);
        i = j;
    }
}

/**
 * @brief Swap two positions of the heap (update their positions)
 * @tparam K
 * @tparam V
 * @param i1
 * @param i2
 */
template <class K, class V>
void MinHeap<K,V>::swap(int i1, int i2) {
    Node tmp = a[i1]; a[i1] = a[i2]; a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}


/**
 * @brief Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
 * @tparam K
 * @tparam V
 * @param n
 * @param notFound
 */
template <class K, class V>
MinHeap<K,V>::MinHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n+1) {
}

/**
 * @brief Return number of elements in the heap
 * @tparam K
 * @tparam V
 * @return
 */
template <class K, class V>
int MinHeap<K,V>::getSize() {
    return size;
}

/**
 * @brief Heap has key?
 * @tparam K
 * @tparam V
 * @param key
 * @return
 */
template <class K, class V>
bool MinHeap<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}

/**
 * @brief Insert (key, value) on the heap
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 */
template <class K, class V>
void MinHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

/**
 * @brief Decrease value of key to the indicated value
 * @tparam K
 * @tparam V
 * @param key
 * @param value
 */
template <class K, class V>
void MinHeap<K,V>::decreaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value > a[i].value) return; // value would increase, do nothing
    a[i].value = value;
    upHeap(i);
}

/**
 * @brief remove and return key with smaller value
 * @tparam K
 * @tparam V
 * @return
 */
template <class K, class V>
K MinHeap<K,V>::removeMin() {
    if (size == 0) return KEY_NOT_FOUND;
    K min = a[1].key;
    pos.erase(min);
    a[1] = a[size--];
    downHeap(1);
    return min;
};


#endif //PROJ2AED_MINHEAP_H
