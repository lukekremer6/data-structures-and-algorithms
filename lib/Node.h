/*
 * Implements a node for a 2-3-4 tree.
*/

#ifndef NODE_H
#define NODE_H

#include "Element.h"
#include <array>
#include <string>
#include <iostream>
#include <utility>

template <typename keytype, typename valuetype>
class Node {
    private:
        std::array<Element<keytype, valuetype>, 3> elements;
        std::array<Node*, 4> children;
        Node* parent;
        int numElements;
        int numChildren;
        int size;

    public:
        Node();
        Node(keytype k, valuetype v);
        ~Node();
        Node(const Node & oldNode);
        Node & operator=(const Node & oldTree);
        void insert(keytype k, valuetype v);
        void insert(Element<keytype, valuetype> element);
        void insert(Node* child);
        void remove(keytype k);
        void remove(Element<keytype, valuetype> element);
        void remove(Node* child);
        Element<keytype, valuetype> & getElement(int index);
        Element<keytype, valuetype> & getMaximumElement();
        Element<keytype, valuetype> & getMinimumElement();
        Node* getChild(int index) const;
        Node* getLeftmostChild() const;
        Node* getRightmostChild() const;
        Node* getLeftChildOf(keytype k) const;
        Node* getRightChildOf(keytype k) const;
        Node* getLeftSibling() const;
        Node* getRightSibling() const;
        bool isLeftmostChild() const;
        bool isRightmostChild() const;
        Node* getParent() const;
        Element<keytype, valuetype> & getLeftParentElement() const;
        Element<keytype, valuetype> & getRightParentElement() const;
        int getNumElements() const;
        int getNumChildren() const;
        int getSize() const;
        void updateSize();
        void updateSizeRecursive();
        int indexOf(keytype k) const;
        int indexOf(const Node* child) const;
        void setParent(Node* newParent);
};

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node() {
    for (int i = 0; i < 4; ++i) {
        children.at(i) = nullptr;
    }

    parent = nullptr;

    numElements = 0;
    numChildren = 0;

    size = 0;
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node(keytype k, valuetype v) {
    elements.at(0).key = k;
    elements.at(0).value = v;

    for (int i = 0; i < 4; ++i) {
        children.at(i) = nullptr;
    }

    parent = nullptr;

    numElements = 1;
    numChildren = 0;
    size = 1;
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::~Node() {
    for (int i = 0; i < numChildren; ++i) {
        delete children.at(i);
    }
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node(const Node<keytype, valuetype> & oldNode) {
    for (int i = 0; i < oldNode.numElements; ++i) {
        elements.at(i) = oldNode.elements.at(i);
    }

    for (int i = 0; i < 4; ++i) {
        children.at(i) = nullptr;
    }

    for (int i = 0; i < oldNode.numChildren; ++i) {
        children.at(i) = new Node<keytype, valuetype>;
        *(children.at(i)) = *(oldNode.children.at(i));
        children.at(i)->parent = this;
    }

    parent = nullptr;

    numElements = oldNode.numElements;
    numChildren = oldNode.numChildren;

    size = oldNode.size;
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype> & Node<keytype, valuetype>::operator=(const Node<keytype, valuetype> & oldNode) {
    if (this != &oldNode) {
        for (int i = 0; i < oldNode.numElements; ++i) {
            elements.at(i) = oldNode.elements.at(i);
        }

        for (int i = 0; i < 4; ++i) {
            children.at(i) = nullptr;
        }

        for (int i = 0; i < oldNode.numChildren; ++i) {
            children.at(i) = new Node<keytype, valuetype>;
            *(children.at(i)) = *(oldNode.children.at(i));
            children.at(i)->parent = this;
        }

        parent = nullptr;

        numElements = oldNode.numElements;
        numChildren = oldNode.numChildren;

        size = oldNode.size;
    }

    return *this;
}


template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::insert(keytype k, valuetype v) {
    if (numElements == 3) {
        throw (std::string) "NI1";
    }

    else {
        Element<keytype, valuetype> newElement;
        newElement.key = k;
        newElement.value = v;

        for (int i = 0; i <= numElements; ++i) {
            if (newElement.key < elements.at(i).key || i == numElements) {
                std::swap(elements.at(i), newElement);
            }
        }

        ++numElements;
    }
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::insert(Element<keytype, valuetype> element) {
    keytype k = element.key;
    valuetype v = element.value;
    this->insert(k, v);
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::remove(Element<keytype, valuetype> element) {
    keytype k = element.key;
    this->remove(k);
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::remove(keytype k) {
    if (numElements == 0) {
        throw (std::string) "NRE2";
    }

    else if (this->indexOf(k) == -1) {
        throw (std::string) "NRE3";
    }

    else {
        for (int i = this->indexOf(k); i < numElements - 1; ++i) {
            elements.at(i) = elements.at(i + 1);
        }

        --numElements;
    }
}

// Note: never insert another node's child. Always insert a copy.
template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::insert(Node<keytype, valuetype>* child) {
    if (child == nullptr) {
        throw (std::string) "NIC1";
    }

    else if (child->getNumElements() == 0) {
        children.at(numChildren) = child;
    }

    else {
        Node<keytype, valuetype>* childToMove = child;
        for (int i = 0; i <= numChildren; ++i) {
            if (i == numChildren) {
                children.at(i) = childToMove;
            }

            else if (children.at(i)->getNumElements() == 0 ||
                childToMove->getElement(0).key < children.at(i)->getElement(0).key) {
                std::swap(children.at(i), childToMove);
            }
        }
    }

    ++numChildren;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::remove(Node<keytype, valuetype>* child) {
    if (numChildren == 0) {
        throw (std::string) "NRC1";
    }

    else if (this->indexOf(child) == -1) {
        throw (std::string) "NRC2";
    }

    else {
        int childIndex = indexOf(child);
        delete children.at(childIndex);

        for (int i = childIndex; i < numChildren - 1; ++i) {
            children.at(i) = children.at(i + 1);
        }

        --numChildren;

        children.at(numChildren) = nullptr;
    }

}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Node<keytype, valuetype>::getElement(int n) {
    if (n >= numElements) {
        throw (std::string) "NGE1";
    }

    return elements.at(n);
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Node<keytype, valuetype>::getMaximumElement() {
    return elements.at(numElements - 1);
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Node<keytype, valuetype>::getMinimumElement() {
    return elements.at(0);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getChild(int n) const {
    return children.at(n);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getLeftmostChild() const {
    return children.at(0);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getRightmostChild() const {
    return children.at(numChildren - 1);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getLeftChildOf(keytype k) const {
    return children.at(this->indexOf(k));
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getRightChildOf(keytype k) const {
    return children.at(this->indexOf(k) + 1);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getLeftSibling() const {
    if (parent->indexOf(this) == 0) {
        return nullptr;
    }

    else {
        return parent->getChild(parent->indexOf(this) - 1);
    }
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getRightSibling() const {
    if (parent->indexOf(this) == parent->getNumChildren() - 1) {
        return nullptr;
    }

    else {
        return parent->getChild(parent->indexOf(this) + 1);
    }
}

template <typename keytype, typename valuetype>
bool Node<keytype, valuetype>::isLeftmostChild() const {
    return (parent->indexOf(this) == 0);
}

template <typename keytype, typename valuetype>
bool Node<keytype, valuetype>::isRightmostChild() const {
    return (parent->indexOf(this) == parent->getNumChildren() - 1);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::getParent() const {
    return parent;
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Node<keytype, valuetype>::getLeftParentElement() const {
    int x = parent->indexOf(this) - 1;
    return parent->getElement(x);
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Node<keytype, valuetype>::getRightParentElement() const {
    return parent->getElement(parent->indexOf(this));
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::getNumElements() const {
    return numElements;
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::getNumChildren() const {
    return numChildren;
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::getSize() const {
    return size;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::updateSize() {
    size = numElements;

    for (int i = 0; i < numChildren; ++i) {
        size += children.at(i)->getSize();
    }
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::updateSizeRecursive() {
    this->updateSize();

    if (parent != nullptr) {
        parent->updateSizeRecursive();
    }
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::indexOf(keytype k) const {
    for (int i = 0; i < numElements; ++i) {
        if (k == elements.at(i).key) {
            return i;
        }
    }

    return -1;
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::indexOf(const Node<keytype, valuetype>* child) const {
    for (int i = 0; i < numChildren; ++i) {
        if (child == children.at(i)) {
            return i;
        }
    }

    return -1;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::setParent(Node<keytype, valuetype>* newParent) {
    parent = newParent;
}

#endif
