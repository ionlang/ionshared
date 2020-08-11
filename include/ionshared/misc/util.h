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

        static bool withinRange(long value, long from, long to);

        static std::string joinStringVector(std::vector<std::string> vector);

        template<typename T>
        static std::vector<T> sliceVector(std::vector<T> subject, uint32_t start, uint32_t length) {
            uint32_t end = start + length;

            if (subject->size() < end) {
                throw std::out_of_range("Not enough items in vector");
            }

            return std::vector<T>(subject->begin() + start, subject->begin() + end);
        }

        /**
         * Returns the number of binary digits, called bits, necessary
         * to represent an integer as a binary number. See more information
         * at: https://en.wikipedia.org/wiki/Bit-length.
         */
        static uint32_t calculateBitLength(int64_t number);

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
