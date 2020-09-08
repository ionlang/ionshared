#pragma once

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
    class Scoped : public std::enable_shared_from_this<Scoped<T>> {
    private:
        PtrSymbolTable<T> symbolTable;

        OptPtr<Scoped<T>> parent;

    public:
        explicit Scoped(
            PtrSymbolTable<T> symbolTable = util::makePtrSymbolTable<T>(),
            OptPtr<Scoped<T>> parent = std::nullopt
        ) :
            symbolTable(symbolTable) {
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

        void traverseScopes(TraversalCallback<Ptr<Scoped<T>>> callback) {
            std::queue<Ptr<Scoped<T>>> queue =
                std::queue<Ptr<Scoped<T>>>(this->shared_from_this());

            while (!queue.empty()) {
                Ptr<Scoped<T>> scope = queue.front();

                queue.pop();

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

            this->traverseScopes([&, this](Ptr<Scoped<T>> scope) -> bool {
                    ionshared::OptPtr<T> symbol = scope->getSymbolTable()->lookup(key);

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
