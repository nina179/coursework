/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    // returns size of dictionary vector
    return this->dictionary.size();
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    // returns true if dictionary vector is empty, false otherwise
    if (this->dictionary.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

template <typename K, typename V> 
void LinearDictionary<K, V>::insert(K key, V value) {
    // iterates over length of dictionary to see if key already exists 
    for (int i = 0; i < this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            throw std::runtime_error("Key is already in dictionary!");
        }
    }

    // creates new key-value pair
    pair<K, V> newPair;
    newPair.first = key;
    newPair.second = value;

    // adds newPair to dictionary
    this->dictionary.push_back(newPair);
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    // assumes key is not in dictionary
    bool found = false;

    // iterates over length of dictionary to see if key is in dictionary
    for (int i = 0; i < this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            // updates value stored at key if key is found
            found = true;
            this->dictionary[i].second = value;
        }
    }

    // throws error if key is not found 
    if (found == false) {
        throw std::runtime_error("Key not found!");
    }
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {
    // iterates over length of dictionary to find specified key
    for (int i = 0; i < this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            // returns value stored at key if key is found
            return this->dictionary[i].second;
        }
    }

    // throws error if key not found
    throw std::runtime_error("Key not found!");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
    // iterates over length of dictionary to find key
    for (int i = 0; i < this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            return true;
        }
    }

    // returns false if key not found
    return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
    // assumes key is not in dictionary
    bool found = false;

    // iterates over length of dictionary to see if key is in dictionary
    for (int i = 0; i < this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            // erases key from dictionary when key is found
            found = true;
            this->dictionary.erase(this->dictionary.begin() + i, 
                this->dictionary.begin() + i + 1);
        }
    }

    // throws error if key not found
    if (found == false) {
        throw std::runtime_error("Key was not found in dictionary");
    }
    
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
    // vector accumulating all keys in dictionary
    vector<K> keyVector;

    // iterates over length of dictionary and appends each key to keyVector
    for (int i = 0; i < this->dictionary.size(); i++) {
        keyVector.push_back(this->dictionary[i].first);
    }

    return keyVector;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
    // returns entire dictionary of key-value pairs
    return this->dictionary;
}
