

class Post {
    char const *user_;
    char *text_;
    Post *tail_;
};

class PostsList {
    Post *node_;
};
