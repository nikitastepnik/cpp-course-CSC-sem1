#pragma once
#include <cstring>

struct Post {
    char const* user;
    char const* text;
    Post* ptrToPrevPost;
};

// task1
Post* create_post(
        char const* user,
        char const* text,
        Post* head = nullptr
);
void destroy_posts(Post const* head);

const Post* previous(Post const* post);

char const* get_user(Post const* post); // возвращает автора поста
char const* get_text(Post const* post); // возвращает сообщение в посте


Post* remove_by_content(Post* head, char const* content);


