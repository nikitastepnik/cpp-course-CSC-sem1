#pragma once
#include <string>

class StringView
{
public:
    explicit(false) StringView(const char* c_str);
    explicit(false) StringView(const std::string& str);
    StringView(const char* begin, size_t size);

    StringView(const StringView& rhs) = default;
    StringView& operator=(const StringView& rhs) = default;

    StringView(StringView&& rhs) = default;
    StringView& operator=(StringView&& rhs) = default;

    ~StringView() = default;

    StringView& operator=(const char* c_str);
    StringView& operator=(const std::string& str);

    const char* data() const;
    size_t size() const;

    StringView substr(size_t begin, size_t end = npos) const;

    const char& operator[](size_t idx) const;

    size_t find(const StringView& view) const;
    size_t find(char c) const;

    bool startsWith(const StringView& view) const;
	bool startsWith(char c) const;
	bool endsWith(const StringView& view) const;
	bool endsWith(char c) const;

    size_t findFirstOf(const StringView& view, size_t begin = 0) const;
	size_t findFirstOf(char c, size_t begin = 0) const;
	size_t findFirstNotOf(const StringView& view, size_t begin = 0) const;
	size_t findFirstNotOf(char c, size_t begin = 0) const;

    void removePrefix(size_t offset);

    inline static constexpr size_t npos = std::string::npos;

private:
    const char* str_ = nullptr;
    size_t size_ = 0;
};
