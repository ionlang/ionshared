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

namespace ionshared {
    class Util {
    private:
        static constexpr std::string_view specialChars{"{}$^.?\\[]()*+|<>-&"};

    public:
        static bool stringStartsWith(std::string subject, std::string value);

        static std::string escapeRegex(std::string subject);

        /**
         * Create a Regex instance containing a string literal as its value.
         * Escapes any special characters that may be present in the value.
         */
        static std::regex createPureRegex(std::string value);

        static bool withinRange(long value, long from, long to);

        static std::string joinStringVector(std::vector<std::string> vector);

        /**
         * Returns the number of binary digits, called bits, necessary
         * to represent an integer as a binary number. See more information
         * at: https://en.wikipedia.org/wiki/Bit-length.
         */
        static uint32_t calculateBitLength(int64_t number);

        template<typename T, typename U>
        static bool instanceOf(T *value) {
            return dynamic_cast<U *>(value) != nullptr;
        }

        template<typename T>
        static std::optional<uint32_t> locateInVector(std::vector<T> vector, T item) {
            auto iterator = std::find(vector.begin(), vector.end(), item);

            if (iterator != vector.cend()) {
                return std::distance(vector.begin(), iterator);
            }

            return std::nullopt;
        }

        template<typename ... Args>
        static std::optional<std::string> formatString(const std::string &format, Args ... args) {
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
        static auto convertString(T&& t) {
            if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value) {
                return std::forward<T>(t).c_str();
            }
            else {
                return std::forward<T>(t);
            }
        }

        template<typename ... Args>
        static std::optional<std::string> formatStringA(std::string format, Args &&...args) {
            return Util::formatString(format, Util::convertString(std::forward<Args>(args))...);
        }

        template<typename ... Args>
        static std::runtime_error quickError(std::string format, Args &&...args) {
            auto formattedString = Util::formatStringA(format, args...);

            if (!formattedString.has_value()) {
                throw std::runtime_error("Could not format string");
            }

            return std::runtime_error(*formattedString);
        }

        template<typename T>
        static std::vector<T> sliceVector(std::vector<T> subject, uint32_t start, uint32_t length) {
            uint32_t end = start + length;

            if (subject->size() < end) {
                throw std::out_of_range("Not enough items in vector");
            }

            return std::vector<T>(subject->begin() + start, subject->begin() + end);
        }

        template<typename TKey, typename TValue>
        static bool mapContains(std::map<TKey, TValue> map, TKey key) {
            return map.find(key) != map.end();
        }

        template<typename T>
        static std::vector<T> mergeVectors(std::vector<T> a, std::vector<T> b) {
            for (const auto item : b) {
                a.push_back(item);
            }

            return a;
        }

        template<typename TKey, typename TValue>
        static std::map<TValue, TKey> flipMap(std::map<TKey, TValue> map) {
            // TODO: What about if different keys contain the same value? Maybe report an error.
            std::map<TValue, TKey> flippedMap = {};

            for (const auto &[key, value] : map) {
                flippedMap[value] = key;
            }

            return flippedMap;
        }

        template<typename T>
        static bool hasValue(OptPtr<T> pointer) noexcept {
            return pointer.has_value() && pointer != nullptr;
        }

        template<typename T>
        static bool hasValue(std::optional<T *> pointer) noexcept {
            return pointer.has_value() && *pointer != nullptr;
        }

        template<typename T>
        static ionshared::PtrSymbolTable<T> makePtrSymbolTable(ionshared::SymbolTable<ionshared::Ptr<T>> symbolTable) {
            return std::make_shared<ionshared::SymbolTable<ionshared::Ptr<T>>>(symbolTable);
        }

        template<typename T>
        static ionshared::PtrSymbolTable<T> makePtrSymbolTable() {
            return std::make_shared<ionshared::SymbolTable<ionshared::Ptr<T>>>();
        }
    };
}
