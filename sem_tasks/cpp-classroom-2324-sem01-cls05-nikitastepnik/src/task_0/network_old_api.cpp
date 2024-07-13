#include <cstdint>
#include <cstring>
#include "network_old_api.hpp"

// TASK 1

struct Post {
    char const *user;
    char *text;
    Post *tail;
};

void deletePost(const Post *head);

char *copyText(char const* text) {
    size_t text_size = std::strlen(text) + 1;
    char *new_text = new char [text_size];
    std::memcpy(new_text, text, text_size);
    return new_text;
}

Post *create_post(
        char const *user,
        char const *text,
        Post *head
) {
    Post *new_post = new Post{};
    new_post->user = copyText(user);
    new_post->text = copyText(text);
    new_post->tail = head;
    new_post->ts = get_current_time();
    return new_post;
}

void destroy_posts(const Post *head) {
    while (head != nullptr) {
        const Post *temp = head->tail;
        deletePost(head);
        head = temp;
    }
}

void deletePost(const Post *head) {
    delete[] head->user;
    delete[] head->text;
    delete head;
}

Post* previous(Post const* post) {
    return post->tail;
}

char const* get_user(Post const* post) {
    return post->user;
}

char const* get_text(Post const* post) {
    return post->text;
}


Post* remove_by_content(Post* head, char const* content)
{
    // prev <- curr <- next
    Post* curr = head;
    Post* next = nullptr;

    while (curr != nullptr) {
        auto prev = curr->tail;

        if (std::strstr(get_text(curr), content)) {
            deletePost(curr);

            if (next) // prev <- curr <- next
                next->tail = prev;
            else      // prev <- [curr/head]
                head = prev;
        }
        else {
            next = curr;
        }

        curr = prev;
    }

    return head;
}

void set_text(Post* post, char const* new_text) {
    delete[] post->text;
    post->text = copyText(new_text);
}
