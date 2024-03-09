/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if(!current) {
        throw runtime_error("Key not found in tree.");
    } else if(current->getKey() > key) {
        return this->findInSubtree(current->getLeft(), key);
    } else if(current->getKey() < key) {
        return this->findInSubtree(current->getRight(), key);
    } else {
        return current->getValue();
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
    try {
        this->findInSubtree(current, key);
    } catch(runtime_error e) {
        return false;
    }
    return true;
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key,
                                      V value) {
    // Recursively finds key in tree to update value.
    if(!current) {
        throw runtime_error("Key not found in tree.");
    } else if(current->getKey() > key) {
        this->updateInSubtree(current->getLeft(), key, value);
    } else if(current->getKey() < key) {
        this->updateInSubtree(current->getRight(), key, value);
    } else {
        current->setValue(value);
    }
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
    // Go down all branches to find the tallest subtree and get height.
    if(current->getLeft() && current->getRight()) {
        int leftHeight = this->getHeightInSubtree(current->getLeft());
        int rightHeight = this->getHeightInSubtree(current->getRight());
        if(leftHeight > rightHeight) {
            return ++leftHeight;
        } else {
            return ++rightHeight;
        }
    } else if(current->getLeft()) {
        int temp = this->getHeightInSubtree(current->getLeft());
        return ++temp;
    } else if(current->getRight()) {
        int temp = this->getHeightInSubtree(current->getRight());
        return ++temp;
    } else {
        return 0;
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
    if(current->getLeft()) {
        return getMinInSubtree(current->getLeft());
    } else {
        return pair<K, V> (current->getKey(), current->getValue());
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {
    if(current->getRight()) {
        return getMaxInSubtree(current->getRight());
    } else {
        return pair<K, V> (current->getKey(), current->getValue());
    }
}

template <typename K, typename V>
LinkedBSTNode<K, V>* LinkedBST<K, V>::insertInSubtree(
    LinkedBSTNode<K, V>* current, K key, V value) {
    if(!current) {
        current = new LinkedBSTNode<K, V>(key, value);
        this->size++;
    } else if(current->getKey() == key) {
        throw runtime_error("No duplicate keys allowed.");
    } else if(current->getKey() > key) {
        current->setLeft(
            this->insertInSubtree(current->getLeft(), key, value));
    } else if(current->getKey() < key) {
        current->setRight(
            this->insertInSubtree(current->getRight(), key, value));
    }
    return current;
}

template <typename K, typename V>
LinkedBSTNode<K, V>* LinkedBST<K, V>::removeFromSubtree(
    LinkedBSTNode<K, V>* current, K key) {
    if(!current) {
        throw runtime_error("Key not found in tree.");
    } else if(current->getKey() > key) {
        current->setLeft(this->removeFromSubtree(current->getLeft(), key));
        return current;
    } else if(current->getKey() < key) {
        current->setRight(this->removeFromSubtree(current->getRight(), key));
        return current;
    } else {
        if(current->getLeft() && current->getRight()) {
            pair<K, V> predecessor = this->getMaxInSubtree(current->getLeft());
            current->setKey(predecessor.first);
            current->setValue(predecessor.second);
            current->setLeft(this->removeFromSubtree(
                current->getLeft(), predecessor.first));
            return current;
        } else if(current->getLeft()) {
            LinkedBSTNode<K, V> *temp = current->getLeft();
            delete current;
            this->size--;
            return temp;
        } else if(current->getRight()) {
            LinkedBSTNode<K, V> *temp = current->getRight();
            delete current;
            this->size--;
            return temp;
        } else {
            delete current;
            this->size--;
            return nullptr;
        }
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
    if(!current) {
        return;
    }
    this->deleteSubtree(current->getLeft());
    this->deleteSubtree(current->getRight());
    delete current;
    this->size--;
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {
    if(!current) {
        return;
    }
    list->insertLast(pair<K, V> (current->getKey(), current->getValue()));
    this->buildPreOrderTraversal(current->getLeft(), list);
    this->buildPreOrderTraversal(current->getRight(), list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {
    if(!current) {
        return;
    }
    this->buildInOrderTraversal(current->getLeft(), list);
    list->insertLast(pair<K, V> (current->getKey(), current->getValue()));
    this->buildInOrderTraversal(current->getRight(), list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
    if(!current) {
        return;
    }
    this->buildPostOrderTraversal(current->getLeft(), list);
    this->buildPostOrderTraversal(current->getRight(), list);
    list->insertLast(pair<K, V> (current->getKey(), current->getValue()));
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (!current) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
