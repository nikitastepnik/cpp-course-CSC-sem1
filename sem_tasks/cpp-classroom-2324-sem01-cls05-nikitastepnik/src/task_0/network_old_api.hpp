#pragma once

struct Post;

Post *create_post(
    char const *user,
    char const *text,
    Post *head = nullptr
);

void destroy_posts(const Post *head);

Post* previous(Post const* post);

char const* get_user(Post const* post); // возвращает автора поста
char const* get_text(Post const* post); // возвращает сообщение в посте

Post* remove_by_content(Post* head, char const* content);

void set_text(Post* post, char const* new_text);
