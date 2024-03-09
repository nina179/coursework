#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <utility> // for the "pair" STL class
#include <vector>

#include "adts/dictionary.h"
#include "linearDictionary.h"

template <typename K, typename V> class HashTable : public Dictionary<K, V> {
  public:
    /**
     * Creates a new HashTable with a maximum load factor of 0.75.
     */
    HashTable();

    /**
     * Creates a new HashTable.
     * @param maxLoadFactor The maximum load factor which will be permitted
     *                      before this hash table changes its capacity.
     */
    HashTable(float maxLoadFactor);
    /**
     * Cleans up this HashTable.
     */
    ~HashTable();

    /* Dictionary ADT Methods.
       You must implement these acording to ADT specification
     */

    /**
     * Tells total number of items in the hash table
     * @return The number of items in the hash table
     */
    int getSize();

     /**
     * Checks if anything has been inserted into the hash table
     * @return Boolean indicating if the size of the hash table is zero (true) 
     *         or greater than zero (false)
     */
    bool isEmpty();

     /**
     * Hashes key and stores value into the hash table if that key doesn't 
     * already exist in the hash table 
     * @param key Element of type K used to index into the hash table
     * @param value Element of type V being stored in the hash table
     */
    void insert(K key, V value);

     /**
     * Replaces the value currently stored at the given key with the new value
     * being passed in if the given key exists in the hash table
     * @param key Element of type K whose stored value is being changed
     * @param value New element of type V now being stored at key
     */
    void update(K key, V value);

     /**
     * Finds value stored at given key
     * @param key Element of type K being searched for
     * @return Element of type V stored at key
     */
    V get(K key);

     /**
     * Checks to see if hash table contains the given key
     * @param key Element of type K being searched for in the hash table
     * @return Boolean value indicating if key exists in the hash table
     */
    bool contains(K key);

     /**
     * Removes key and the value stored there from the hash table
     * @param key Element of type K being removed from hash table
     */
    void remove(K key);

     /**
     * Generates a vector containing all the keys stored in the hash table
     * @return Vector containing all keys in the hash table
     */
    vector<K> getKeys();

     /**
     * Generates a vector containing pairs of all keys in the hash table and 
     * the value stored at them
     * @return Vector of key-value pairs for all keys and values in hash table
     */
    vector<pair<K, V>> getItems();

  private:
    int size;                           
    int capacity;                       
    LinearDictionary<K, V>* table;      
    float maxLoadFactor;                

    // doubles capacity of hash table when hash table starts getting full
    void ensureCapacity();
};

#include "hashTable-inl.h"
