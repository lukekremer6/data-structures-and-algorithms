/*
 * Implements a key-value pair for a 2-3-4 tree node.
*/

#ifndef ELEMENT_H
#define ELEMENT_H

template <typename keytype, typename valuetype>
struct Element {
    keytype key;
    valuetype value;
};

#endif
