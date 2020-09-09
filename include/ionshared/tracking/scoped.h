#pragma once

#include <memory>
#include <queue>
#include <functional>
#include <ionshared/construct/base_construct.h>
#include <ionshared/tracking/symbol_table.h>
#include <ionshared/misc/util.h>

namespace ionshared {
    template<typename T>
    using TraversalCallback = std::function<bool(T)>;

    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename T>
    class Scoped {
    private:
        PtrSymbolTable<T> symbolTable;

        OptPtr<Scoped<T>> parent;

    public:
        explicit Scoped(
            PtrSymbolTable<T> symbolTable = util::makePtrSymbolTable<T>(),
            OptPtr<Scoped<T>> parent = std::nullopt
        ) :
            symbolTable(symbolTable),
            parent(parent) {
            //
        }

        virtual PtrSymbolTable<T> getSymbolTable() const {
            return this->symbolTable;
        }

        virtual void setSymbolTable(PtrSymbolTable<T> symbolTable) {
            this->symbolTable = symbolTable;
        }

        [[nodiscard]] OptPtr<Scoped<T>> getParentScope() const noexcept {
            return this->parent;
        }

        [[nodiscard]] bool hasParentScope() const noexcept {
            return util::hasValue(this->parent);
        }

        void traverseScopes(TraversalCallback<Scoped<T>> callback) {
            std::queue<Scoped<T>> queue = std::queue<Scoped<T>>(*this);

            while (!queue.empty()) {
                Scoped<T> scope = queue.front();

                queue.pop();

                // TODO: CRITICAL! Since it's being  passed as
                if (!callback(scope)) {
                    break;
                }
                else if (scope->hasParentScope()) {
                    queue.push(*scope->getParentScope());
                }
            }
        }

        [[nodiscard]] std::optional<T> findNearestSymbol(std::string key) {
            std::optional<T> result = std::nullopt;

            this->traverseScopes([&, this](Scoped<T> scope) -> bool {
                    ionshared::OptPtr<T> symbol = scope.getSymbolTable()->lookup(key);

                    if (util::hasValue(symbol)) {
                        result = symbol;

                        return false;
                    }

                    return true;
                }
            );

            return result;
        }
    };
}
