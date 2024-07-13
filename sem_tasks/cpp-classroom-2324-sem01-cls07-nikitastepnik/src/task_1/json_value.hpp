#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <variant>

namespace cls07 {
    class JsonValue;
    using jsonType = std::variant<bool, int, char, std::string, const char*, JsonValue>;

    class IndexOutOfRange : public std::out_of_range {
        public:
            explicit IndexOutOfRange(const std::string &message) : std::out_of_range(message)  {}
    };

    class JsonValue {
    private:
        std::vector<jsonType> data;
        long unsigned int countAppends = 0;
        mutable std::vector<const std::vector<JsonValue>*> allocatedData;

    public:
        friend constexpr auto size(const auto& obj) {
            return obj.data.size();
        }

        using StringType = std::string;
        using ListType = std::vector<JsonValue>;
        JsonValue() = default;
        JsonValue(const bool& value);
        JsonValue(const int& value);
        JsonValue(const char& value);
        JsonValue(const jsonType& value);
        JsonValue(const std::string& value);
        JsonValue(const char* value);
        JsonValue(JsonValue const &otherJson);

        ~JsonValue() {
            for (const auto& element : allocatedData) {
                delete element;
            }
        }

        bool& GetBool();
        int& GetInt();
        std::string& GetString();
        std::vector<JsonValue>& GetArray();

        bool GetBool() const;
        int GetInt() const;
        std::string GetString() const;
        const std::vector<JsonValue>&  GetArray() const;

        bool IsNull() const;
        bool IsBool() const;
        bool IsInt() const;
        bool IsString() const;
        bool IsArray() const;

        void SetNull();

        void Append(const jsonType &value);

        const JsonValue& operator[](size_t index) const;
        JsonValue& operator[](size_t index);
    };

}