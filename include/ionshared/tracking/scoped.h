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
    template<typename TConstruct, typename TConstructKind>
        // TODO: Used partially in projects (incomplete type).
//        requires std::derived_from<TConstruct, BaseConstruct<TConstruct, TConstructKind>>
    struct Scoped {
        typedef Scoped<TConstruct, TConstructKind> Self;

        PtrSymbolTable<TConstruct> symbolTable;

        OptRef<Self> parentScope;

        explicit Scoped(
            PtrSymbolTable<TConstruct> symbolTable =
                util::makePtrSymbolTable<TConstruct>(),

            OptRef<Self> parent = std::nullopt
        ) :
            symbolTable(symbolTable),
            parentScope(parent) {
            //
        }

        [[nodiscard]] bool hasParentScope() const noexcept {
            return this->parentScope.has_value();
        }

        /**
         * Traverses parent scopes starting from the nearest one, and
         * including itself.
         */
        void traverseScopes(TraversalCallback<Self&> callback) {
            std::queue<Ref<Self>> queue = {};

            queue.push(*this);

            while (!queue.empty()) {
                Self& scope = queue.front();

                queue.pop();

                // TODO: CRITICAL! Since it's being  passed as
                if (!callback(scope)) {
                    break;
                }
                else if (scope.hasParentScope()) {
                    queue.push(scope.parentScope.value());
                }
            }
        }

        [[nodiscard]] std::optional<TConstruct> findNearestSymbol(std::string name) {
            std::optional<TConstruct> result = std::nullopt;

            this->traverseScopes([&, this](Self& scope) -> bool {
                OptPtr<TConstruct> symbol = scope.getSymbolTable()->lookup(name);
                bool hasValue = util::hasValue(symbol);

                if (hasValue) {
                    result = symbol;
                }

                return hasValue;
            });

            return result;
        }

        [[nodiscard]] std::optional<TConstruct> findNearestSymbol(
            std::string name,
            TConstructKind constructKind
        ) {
            std::optional<TConstruct> result = std::nullopt;

            this->traverseScopes([&, this](Self& scope) -> bool {
                OptPtr<TConstruct> symbol = scope.getSymbolTable()->lookup(name);

                if (util::hasValue(symbol)
                    && symbol->get()->constructKind == constructKind) {
                    result = symbol;

                    return false;
                }

                return true;
            });

            return result;
        }
    };
}
