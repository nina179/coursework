#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/dictionary.h"

/**
 * An implementation of a dictionary using a linked list.
 */
template <typename K, typename V>
class LinearDictionary : public Dictionary<K, V> {
  public:
    /**
     * Creates a new, empty LinearDictionary.
     */
    LinearDictionary();

    /**
     * Cleans up this LinearDictionary.
     */
    ~LinearDictionary();

    /* Dictionary ADT Methods.  You must implement these acording to ADT
       specification.  All of these methods are expected to run in O(n) time.
     */

    /**
     * Checks size of this LinearDictionary
     * @return Integer representing number of items in linear dictionary
     */
    int getSize();

     /**
     * Checks if this LinearDictionary is empty
     * @return Boolean value indicating that the size of this LinearDicionary
     *         is either zero (true) or greater than zero (false)
     */
    bool isEmpty();

     /**
     * Creates new key-value pair and adds it to this LinearDictionary
     * @param key Element of type K being keyed into this LinearDictionary
     * @param value Element of type V stored at key
     */
    void insert(K key, V value);

     /**
     * Changes value stored at given key if key is in this LinearDictionary
     * @param key Element of type K whose stored value is being updated
     * @param value Element of type V that is now being stored at key
     */
    void update(K key, V value);

     /**
     * Finds value stored at given key
     * @param key Element of type K whose stored value is being accessed
     * @return Element of type V being stored at key
     */
    V get(K key);

     /**
     * Checks to see if given key exists in this LinearDictionary
     * @param key Element of type K assumed to be in this LinearDictionary
     * @return Boolean value indicating if key is in this LinearDictionary
     *         (true) or not (false)
     */
    bool contains(K key);

     /**
     * Removes given key and its stored value from this LinearDictionary
     * @param key Element of type K being erased from this LinearDictionary
     */
    void remove(K key);

     /**
     * Grabs all keys that exist in this LinearDictionary
     * @return Vector containing keys in this LinearDictionary
     */
    vector<K> getKeys();

     /**
     * Grabs all keys in this LinearDictionary and the values stored there
     * @return Vector containing key-value pairs of all items in this 
     *         LinearDictionary
     */
    vector<pair<K, V>> getItems();

  private:
    vector<pair<K, V>> dictionary;
};

#include "linearDictionary-inl.h"
