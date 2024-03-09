/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    this->size = 0;
    this->capacity = 4;
    this->table = new LinearDictionary<K, V>[this->capacity];
    this->maxLoadFactor = 0.75;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
    this->size = 0;
    this->capacity = 4;
    this->table = new LinearDictionary<K, V>[this->capacity];
    this->maxLoadFactor = maxLoadFactor;
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
    // calls LinearDictionary destructor to delete HashTable
    delete[] this->table;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
    // returns number of elements inserted into hash table
    return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
    // returns true if hash table is empty, false otherwise
    if (this->size == 0) {
        return true;
    }
    else {
        return false;
    }
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
    // checks if key already exists in table
    if (this->contains(key)) {
        throw runtime_error("Key already in table");
    } else {
        // hashes key and inserts at specified index
        int index = hash(key, this->capacity);
        this->table[index].insert(key, value);

        // increments size of table
        this->size = this->size + 1;

        // increases capacity of table if maxLoadFactor is exceeded
        float load = float(this->size) / this->capacity;
        if (load > this->maxLoadFactor) {
            this->ensureCapacity();
        }
    }
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
    // hashes specified key to find the index it's stored at
    int index = hash(key, this->capacity);

    // changes value stored at key if key exists at that index
    if (this->table[index].contains(key)){
        this->table[index].update(key, value);
    }
    else {
        throw runtime_error("Key not found!");
    }
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
    // hashes specified key to find the index it's stored at
    int index = hash(key, this->capacity);

    // returns value stored
    return this->table[index].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
    // hashes specified key to find the index it's stored at
    int index = hash(key, this->capacity);

    // returns true if key is found at index, false otherwise
    if (this->table[index].contains(key)) {
        return true;
    }
    else {
        return false;
    }
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
    // hashes specified key to find the index its stored at
    int index = hash(key, this->capacity);

    // erases LinearDictionary index key is being stored at
    this->table[index].remove(key);

    // decrements size by 1
    this->size = this->size - 1;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
    vector<K> keyVector;     // stores all keys in hash table
    vector<K> current_keys;  // stores keys in each LinearDictionary

    // gets the keys in the LinearDictionary stored at each index
    for (int i = 0; i < this->capacity; i++) {
        current_keys = this->table[i].getKeys();
        // inserts each key in current_keys to keyVector
        for (int j = 0; j < current_keys.size(); j++) {
            keyVector.push_back(current_keys[j]);
        }
    }

    return keyVector;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
    vector<pair<K, V>> itemVector;  // stores all items in hash table
    vector<pair<K, V>> tempVector;  // stores all items in each LinearDictionary

    // gets items in the LinearDictionary stored at each index
    for (int i = 0; i < this->capacity; i++) {
        tempVector = this->table[i].getItems();
        // inserts each key-value pair in tempVector to itemVector
        for (int j = 0; j < tempVector.size(); j++) {
            itemVector.push_back(tempVector[j]);
        }
    }

    return itemVector;
}

template <typename K, typename V> void HashTable<K, V>::ensureCapacity() {
    // new LinearDictionary with double the capacity of old LinearDictionary
    LinearDictionary<K, V>* newTable = new LinearDictionary<K, V>[this->capacity*2];

    // vector with all keys and values in old hash table
    vector<pair<K, V>> items = this->getItems();

    // updates capacity to match capacity of newTable
    this->capacity = this->capacity*2;

    // hashes each item in old hash table into newTable
    for (int i = 0; i < items.size(); i++) {
        int index = hash(items[i].first, this->capacity);
        newTable[index].insert(items[i].first, items[i].second);
    }

    // deletes old table and sets table to newTable
    delete[] this->table;
    this->table = newTable;
}
