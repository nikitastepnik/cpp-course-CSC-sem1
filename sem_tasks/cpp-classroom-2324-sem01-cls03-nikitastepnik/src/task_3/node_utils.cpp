#include "node_utils.hpp"


void cleanup(Node * head) {
    Node* tmpNode;
    if (!head) {
        return;
    }
    while (head) {
        tmpNode=head->next;
        delete head;
        head=tmpNode;
    }
}

void revert(Node **headAddr) {
    Node *curNode = *headAddr;
    Node *nextNode;
    Node *tmp;

    if (!curNode) {
        return;
    }

    nextNode = curNode->next;
    while (nextNode) {
        tmp = nextNode->next;
        nextNode->next = curNode;
        curNode = nextNode;
        nextNode = tmp;
    }

    (*headAddr)->next = nullptr;
    *(headAddr)=curNode;
}
