#include "network.hpp"
#include <iostream>

Post* create_post(
        char const* user,
        char const* text,
        Post* head
) {
    Post* newPost = new Post;

    newPost->user=new char[strlen(user)+1];
    newPost->text=new char[strlen(text)+1];

    memcpy((char*)newPost->user, user, strlen(user)+1);
    memcpy((char*)newPost->text, text, strlen(text)+1);

    newPost->ptrToPrevPost=head;

    return newPost;
}

const Post* previous(Post const* post) {
    return post->ptrToPrevPost;
}

char const* get_text(Post const* post) {
    return post->text;
}

char const* get_user(Post const* post) {
    return post->user;
}

void destroy_posts(Post const* head) {
    if (head) {
        Post const* copyPtr;
        while (head->ptrToPrevPost!= nullptr) {
            copyPtr = head;
            head = head->ptrToPrevPost;
            delete[] copyPtr->text;
            delete[] copyPtr->user;
            delete copyPtr;
        }
    }
}

// task2
Post* remove_by_content(Post* head, char const* content) {
    Post* copyPtr;
    Post* newHead = nullptr;
    Post* currHead = nullptr;
    while (head) {
        if (std::strstr(head->text, content)) {
            copyPtr=head->ptrToPrevPost;
            delete head;
            head=copyPtr;
            if (currHead) {
                currHead->ptrToPrevPost= nullptr;
            }
        } else {
            if (newHead == nullptr) {
                newHead=head;
                currHead=head;
            } else {
                copyPtr=currHead;
                currHead=head;
                copyPtr->ptrToPrevPost=currHead;
            }
            head=head->ptrToPrevPost;
        }
    }
    if (newHead!= nullptr) {
        return newHead;
    } else {
        return nullptr;
    }
}


//const char* str = "Try not. Do, or do not. There is no try.";
//const char* target = "not";
//const char* result = str;
//
//while ((result = std::strstr(result, target)


//// for TASK_3
//static std::uint64_t get_current_time() {
//    static std::uint64_t current_time = 0;
//    return current_time++;
//}
