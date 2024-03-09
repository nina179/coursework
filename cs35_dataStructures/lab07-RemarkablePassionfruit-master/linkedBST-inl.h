/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"
#include "helpers.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
	this->size = 0;
	this->root = nullptr;
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    this->deleteSubtree(this->root);
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
	return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    if(this->size) {
		return false;
	} else {
		return true;
	}
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
	if(!this->root) {
        this->root = this->insertInSubtree(this->root, key, value);
    } else {
        this->insertInSubtree(this->root, key, value);
    }
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    this->updateInSubtree(this->root, key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
    return this->findInSubtree(this->root, key);
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
	return this->containsInSubtree(this->root, key);
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    this->root = this->removeFromSubtree(this->root, key);
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
    vector<pair<K, V>> allNodes = this->traverseInOrder();
    vector<K> allKeys;
    for(int i = 0; i < allNodes.size(); i++) {
        allKeys.push_back(allNodes[i].first);
    }
    return allKeys;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    return this->traverseInOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
    return this->getHeightInSubtree(this->root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
    return this->getMaxInSubtree(this->root).first;
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
    return this->getMinInSubtree(this->root).first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
    List<pair<K, V>> *traversal = new STLList<pair<K, V>>;
    this->buildPreOrderTraversal(this->root, traversal);
    return dynamicListToStaticVector(traversal);
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
    List<pair<K, V>> *traversal = new STLList<pair<K, V>>;
    this->buildInOrderTraversal(this->root, traversal);
    return dynamicListToStaticVector(traversal);
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
    List<pair<K, V>> *traversal = new STLList<pair<K, V>>;
    this->buildPostOrderTraversal(this->root, traversal);
    return dynamicListToStaticVector(traversal);
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
    OrderedCollection<LinkedBSTNode<K, V>*> *processingQueue = 
        new STLQueue<LinkedBSTNode<K, V>*>;
    processingQueue->insert(this->root);

    vector<pair<K, V>> traversal;
    LinkedBSTNode<K, V> *tempNode;
    while(!processingQueue->isEmpty()) {
        tempNode = processingQueue->remove();
        if(tempNode) {
            processingQueue->insert(tempNode->getLeft());
            processingQueue->insert(tempNode->getRight());
            traversal.push_back(
                pair<K, V> (tempNode->getKey(), tempNode->getValue()));
        }
    }
    delete processingQueue;
    return traversal;
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false
        // arguments indicate that they do not apply.  But we need a
        // value of type K to fill this parameter since we don't have
        // globally min/max K values generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
