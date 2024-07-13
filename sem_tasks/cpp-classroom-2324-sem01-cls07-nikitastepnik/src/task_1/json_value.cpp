#include "json_value.hpp"

cls07::JsonValue::JsonValue(const bool &value) {
    data.emplace_back(value);
}

cls07::JsonValue::JsonValue(const int &value) {
    data.emplace_back(value);
}

cls07::JsonValue::JsonValue(const char &value) {
    data.emplace_back(std::string(1, value));
}

cls07::JsonValue::JsonValue(const std::string &value) {
    data.emplace_back(value);
}

cls07::JsonValue::JsonValue(const char *value) {
    data.emplace_back(std::string(value));
}

cls07::JsonValue::JsonValue(const jsonType &value) {
    data.emplace_back(value);
}

cls07::JsonValue::JsonValue(JsonValue const &otherJson) {
    countAppends = otherJson.countAppends;
    data = otherJson.data;
}


bool cls07::JsonValue::GetBool() const {
    if (data.empty()) {
        throw cls07::IndexOutOfRange("");
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (std::holds_alternative<bool>(val[0])) {
        return std::get<bool>(val[0]);
    }

    throw std::bad_variant_access();
}

bool &cls07::JsonValue::GetBool() {
    if (data.empty()) {
        data.emplace_back(false);
        return std::get<bool>(data[0]);
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (!std::holds_alternative<bool>(val[0])) {
        val.pop_back();
        val.emplace_back(false);
    }
    data = val;
    return std::get<bool>(data[0]);
}

int cls07::JsonValue::GetInt() const {
    if (data.empty()) {
        throw cls07::IndexOutOfRange("");
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (std::holds_alternative<int>(val[0])) {
        return std::get<int>(val[0]);
    }
    throw std::bad_variant_access();
}

int &cls07::JsonValue::GetInt() {
    if (data.empty()) {
        data.emplace_back(0);
        return std::get<int>(data[0]);
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (!std::holds_alternative<int>(val[0])) {
        val.pop_back();
        val.emplace_back(0);
    }
    data = val;
    return std::get<int>(data[0]);
}

std::string cls07::JsonValue::GetString() const {
    if (data.empty()) {
        throw cls07::IndexOutOfRange("");
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (std::holds_alternative<const char *>(val[0])) {
        return {std::get<const char *>(val[0])};
    } else if (std::holds_alternative<char>(val[0])) {
        return {std::get<char>(val[0])};
    } else if (std::holds_alternative<std::string>(val[0])) {
        return std::get<std::string>(val[0]);
    }
    throw std::bad_variant_access();
}


std::string &cls07::JsonValue::GetString() {
    if (data.empty()) {
        data.emplace_back(std::string(""));
        return std::get<std::string>(data[0]);
    }
    auto val = data;
    if (std::holds_alternative<JsonValue>(val[0])) {
        JsonValue copiedVal = std::get<JsonValue>(val[0]);
        val = copiedVal.data;
    }
    if (!(std::holds_alternative<std::string>(val[0]) or std::holds_alternative<const char*>(val[0]))) {
        val.pop_back();
        val.emplace_back(std::string(""));
    }
    data = val;

    if (std::holds_alternative<const char*>(val[0])) {
        const char* constCharValue =  std::get<const char*>(data[0]);
        data[0] = std::string(constCharValue);
    }
    return std::get<std::string>(data[0]);
}


const std::vector<cls07::JsonValue>& cls07::JsonValue::GetArray() const {
    auto* arrayData = new std::vector<JsonValue>();
    // Copy the elements from this->data into arrayData
    for (const auto& element : data) {
        if (std::holds_alternative<JsonValue>(element)) {
            arrayData->push_back(std::get<JsonValue>(element));
        }
    }
    allocatedData.emplace_back(arrayData);
    return *arrayData;
}

std::vector<cls07::JsonValue>& cls07::JsonValue::GetArray() {
    auto* arrayData = new std::vector<JsonValue>();
    // Copy the elements from this->data into arrayData
    for (const auto& element : data) {
        if (std::holds_alternative<JsonValue>(element)) {
            arrayData->push_back(std::get<JsonValue>(element));
        }
    }
    allocatedData.emplace_back(arrayData);
    return *arrayData;
}

bool cls07::JsonValue::IsNull() const {
    if (data.empty()) {
        return true;
    }

    if (!std::holds_alternative<JsonValue>(data[0])) {
        if (data.empty()) {
            return true;
        }
    } else {
        JsonValue val = std::get<JsonValue>(data[0]);
        if (val.data.empty()) {
            return true;
        }
    }
    return false;
}

bool cls07::JsonValue::IsBool() const {
    try {
        GetBool();
    } catch (const std::bad_variant_access &exc) {
        return false;
    } catch (const IndexOutOfRange &exc) {
        return false;
    }
    return true;
}

bool cls07::JsonValue::IsInt() const {
    try {
        GetInt();
    } catch (const std::bad_variant_access &exc) {
        return false;
    } catch (const IndexOutOfRange &exc) {
        return false;
    }
    return true;
}

bool cls07::JsonValue::IsString() const {
    try {
        GetString();
        return true;
    } catch (const std::bad_variant_access &exc) {
        return false;
    } catch (const IndexOutOfRange &exc) {
        return false;
    }
}


bool cls07::JsonValue::IsArray() const {
    if (countAppends >= 1) {
        return true;
    }
    return false;
}


void cls07::JsonValue::SetNull() {
    data.clear();
}


void cls07::JsonValue::Append(const cls07::jsonType &value) {
    if (data.size() > countAppends) {
        data.resize(countAppends);
    }
    if (std::holds_alternative<JsonValue>(value)) {
        data.emplace_back(value);
    }
    else {
        data.emplace_back(cls07::JsonValue(value));
    }
    ++countAppends;
}


const cls07::JsonValue& cls07::JsonValue::operator[](size_t index) const {
    return std::get<JsonValue>(data[index]);
}

cls07::JsonValue& cls07::JsonValue::operator[](size_t index) {
    return std::get<JsonValue>(data[index]);
}