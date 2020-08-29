#pragma once

#include <optional>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <string_view>
#include <cmath>
#include <ionshared/tracking/symbol_table.h>
#include "helpers.h"

namespace ionshared::util {
    constexpr std::string_view specialChars{"{}$^.?\\[]()*+|<>-&"};

    bool stringStartsWith(std::string subject, std::string value);

    std::string escapeRegex(std::string subject);

    /**
     * Create a Regex instance containing a string literal as its value.
     * Escapes any special characters that may be present in the value.
     */
    std::regex createPureRegex(std::string value);

    bool withinRange(long value, long from, long to);

    std::string joinStringVector(std::vector<std::string> vector);

    /**
     * Returns the number of binary digits, called bits, necessary
     * to represent an integer as a binary number. See more information
     * at: https://en.wikipedia.org/wiki/Bit-length.
     */
    uint32_t calculateBitLength(int64_t number);

    /**
     * Trim a string from the end (right).
     */
    [[nodiscard]] std::string rightTrim(std::string subject);

    /**
     * Trim a string from the beginning (left).
     */
    [[nodiscard]] std::string leftTrim(std::string subject);

    /**
     * Trim a string from both ends (right then left).
     */
    [[nodiscard]] std::string trim(std::string subject);

    template<typename T, typename U>
    bool instanceOf(T *value) {
        return dynamic_cast<U *>(value) != nullptr;
    }

    template<typename T>
    std::optional<uint32_t> locateInVector(std::vector<T> vector, T item) {
        auto iterator = std::find(vector.begin(), vector.end(), item);

        if (iterator != vector.cend()) {
            return std::distance(vector.begin(), iterator);
        }

        return std::nullopt;
    }

    template<typename T>
    bool vectorContains(std::vector<T> vector, T item) {
        return util::locateInVector(vector, item) != std::nullopt;
    }

    template<typename ... Args>
    std::optional<std::string> formatString(const std::string &format, Args ... args) {
        // Extra space for '\0'.
        size_t size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;

        if (size <= 0) {
            return std::nullopt;
        }

        std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(new char[size]);

        std::snprintf(buffer.get(), size, format.c_str(), args ...);

        return std::string(buffer.get(), buffer.get() + size - 1);
    }

    /**
     * Convert all std::strings to const char* using constexpr if (C++17).
     */
    template<typename T>
    auto convertString(T&& t) {
        if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value) {
            return std::forward<T>(t).c_str();
        }
        else {
            return std::forward<T>(t);
        }
    }

    template<typename ... Args>
    std::optional<std::string> formatStringA(std::string format, Args &&...args) {
        return util::formatString(format, util::convertString(std::forward<Args>(args))...);
    }

    template<typename ... Args>
    std::runtime_error quickError(std::string format, Args &&...args) {
        auto formattedString = util::formatStringA(format, args...);

        if (!formattedString.has_value()) {
            throw std::runtime_error("Could not format string");
        }

        return std::runtime_error(*formattedString);
    }

    template<typename T>
    std::vector<T> sliceVector(std::vector<T> subject, uint32_t start, uint32_t length) {
        uint32_t end = start + length;

        if (subject->size() < end) {
            throw std::out_of_range("Not enough items in vector");
        }

        return std::vector<T>(subject->begin() + start, subject->begin() + end);
    }

    template<typename TKey, typename TValue>
    bool mapContains(std::map<TKey, TValue> map, TKey key) {
        return map.find(key) != map.end();
    }

    template<typename T>
    std::vector<T> mergeVectors(std::vector<T> a, std::vector<T> b) {
        for (const auto item : b) {
            a.push_back(item);
        }

        return a;
    }

    template<typename TKey, typename TValue>
    std::map<TValue, TKey> flipMap(std::map<TKey, TValue> map) {
        // TODO: What about if different keys contain the same value? Maybe report an error.
        std::map<TValue, TKey> flippedMap = {};

        for (const auto &[key, value] : map) {
            flippedMap[value] = key;
        }

        return flippedMap;
    }

    template<typename T>
    bool hasValue(OptPtr<T> pointer) noexcept {
        return pointer.has_value() && pointer != nullptr;
    }

    template<typename T>
    bool hasValue(std::optional<T *> pointer) noexcept {
        return pointer.has_value() && *pointer != nullptr;
    }

    template<typename T>
    ionshared::PtrSymbolTable<T> makePtrSymbolTable(ionshared::SymbolTable<ionshared::Ptr<T>> symbolTable) {
        return std::make_shared<ionshared::SymbolTable<ionshared::Ptr<T>>>(symbolTable);
    }

    template<typename T>
    ionshared::PtrSymbolTable<T> makePtrSymbolTable() {
        return std::make_shared<ionshared::SymbolTable<ionshared::Ptr<T>>>();
    }

    template<typename T>
    std::string getPointerAddressString(T *pointer) {
        std::ostringstream stream;

        stream << pointer;

        return stream.str();
    }
}
