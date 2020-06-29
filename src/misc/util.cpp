#include <sstream>
#include <ionshared/misc/util.h>

namespace ionshared {
    bool Util::stringStartsWith(std::string subject, std::string value) {
        return subject.rfind(value, 0) == 0;
    }

    std::string Util::escapeRegex(std::string subject) {
        std::string result;

        for (char &character : subject) {
            // Determine if the character is denoted special.
            if (Util::specialChars.find(character) != Util::specialChars.npos) {
                // If so, escape the character and append it to the result.
                result += "\\" + std::string(1, character);

                continue;
            }

            // Otherwise, append it to the result directly.
            result += character;
        }

        return result;
    }

    std::regex Util::createPureRegex(std::string value) {
        return std::regex(Util::escapeRegex(value));
    }

    bool Util::withinRange(long value, long from, long to) {
        return value >= from && value <= to;
    }

    std::string Util::joinStringVector(std::vector<std::string> vector) {
        if (vector.empty()) {
            return "";
        }

        std::stringstream result;

        for (auto iterator = std::begin(vector); iterator != std::end(vector); ++iterator) {
            result << *iterator;

            if (std::next(iterator) != vector.end()) {
                result << " ";
            }
        }

        return result.str();
    }

    uint32_t Util::calculateBitLength(int64_t number) {
        if (number < 0) {
            throw std::runtime_error("Number cannot be less than zero");
        }
        else if (number == 0) {
            return 1;
        }

        /**
         * Formula has been taken from Wikipedia.
         */
        return floor(log2(number + 1));
    }
}
