#pragma once

struct Node {
    int value=0;
    Node* next=nullptr;
};

void cleanup(Node* head);
void revert(Node** headAddr);

