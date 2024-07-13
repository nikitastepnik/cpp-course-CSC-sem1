#include "string_view.hpp"

#include <cstring>

StringView::StringView(const char* c_str) :
    str_{c_str},
    size_{strlen(c_str)}
{}

StringView::StringView(const std::string& str) :
    str_{str.c_str()},
    size_{str.size()}
{}

StringView::StringView(const char* begin, const size_t size) :
    str_{begin},
    size_{size}
{}

StringView& StringView::operator=(const char* c_str)
{
    str_ = c_str;
    size_ = strlen(c_str);
    return *this;
}

StringView& StringView::operator=(const std::string& str)
{
    str_ = str.c_str();
    size_ = str.size();
    return *this;
}

const char* StringView::data() const
{
    return str_;
}

size_t StringView::size() const
{
    return size_;
}

StringView StringView::substr(const size_t begin, size_t end) const
{
    if (begin > size_)
    {
        return { str_ + size_, 0 };
    }

    if (end < begin)
    {
        end = begin;
    }

	const size_t len = std::min(end - begin, size_ - begin);
	return { str_ + begin, len };
}

const char& StringView::operator[](const size_t idx) const
{
    return str_[idx];
}

size_t StringView::find(const StringView& view) const
{
    if (view.size_ > size_)
    {
        return npos;
    }

    if (const auto result = static_cast<char*>(memmem(str_, size_, view.str_, view.size_)))
    {
        return result - str_;
    }

    return npos;
}

size_t StringView::find(const char c) const
{
    const char str[2] = { c, '\0' };
    return find({ str, 1 });
}

bool StringView::startsWith(const StringView& view) const
{
    if (view.size_ > size_)
    {
        return false;
    }

    return strncmp(str_, view.str_, view.size_) == 0;
}

bool StringView::startsWith(const char c) const
{
    const char str[2] = { c, '\0' };
    return startsWith({ str, 1 });
}

bool StringView::endsWith(const StringView& view) const
{
    if (view.size_ > size_)
    {
        return false;
    }

    return strncmp(str_ + size_ - view.size_, view.str_, view.size_) == 0;
}

bool StringView::endsWith(const char c) const
{
    const char str[2] = { c, '\0' };
    return endsWith({ str, 1 });
}

size_t StringView::findFirstOf(const StringView& view, size_t begin) const
{
    for (; view.size_ > 0 && begin < size_; ++begin)
    {
        if (const auto off = view.find(str_[begin]); off != npos)
        {
            return begin;
        }
    }

    return npos;
}

size_t StringView::findFirstOf(const char c, const size_t begin) const
{
    const char str[2] = { c, '\0' };
    return findFirstOf({ str, 1 }, begin);
}

size_t StringView::findFirstNotOf(const StringView& view, size_t begin) const
{
    for (; begin < size_; ++begin)
    {
        if (const auto off = view.find(str_[begin]); off == npos)
        {
            return begin;
        }
    }

    return npos;
}

size_t StringView::findFirstNotOf(const char c, const size_t begin) const
{
    const char str[2] = { c, '\0' };
    return findFirstNotOf({ str, 1 }, begin);
}

void StringView::removePrefix(size_t offset)
{
    if (offset >= size_)
    {
        offset = size_ - 1;
    }

    str_ = &str_[offset];
	size_ -= offset;
}
