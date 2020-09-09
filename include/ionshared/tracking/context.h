#pragma once

#include <vector>
#include <ionshared/tracking/symbol_table.h>
#include <ionshared/tracking/scoped.h>

namespace ionshared {
    template<typename T>
    using Scope = PtrSymbolTable<T>;

    template<typename T>
    class Context {
    private:
        std::vector<Scope<T>> scopes;

        Scope<T> globalScope;

    public:
        explicit Context(
            Scope<T> globalScope = util::makePtrSymbolTable<T>(),
            std::vector<Scope<T>> scopes = {}
        ) :
            globalScope(std::move(globalScope)),
            scopes(std::move(scopes)) {
            //
        }

        [[nodiscard]] std::vector<Scope<T>> getScopes() const noexcept {
            return this->scopes;
        }

        void setScopes(std::vector<Scope<T>> scopes) noexcept {
            this->scopes = std::move(scopes);
        }

        [[nodiscard]] Scope<T> getGlobalScope() const noexcept {
            return this->globalScope;
        }

        void setGlobalScope(Scope<T> globalScope) noexcept {
            this->globalScope = std::move(globalScope);
        }

        void appendScope(const Scope<T> &scope) noexcept {
            // Scope is already on the scopes vector.
            if (util::locateInVector(this->scopes, scope) != std::nullopt) {
                return;
            }

            /**
             * Otherwise, push the scope onto the front of the vector.
             * This will allow vector traversal starting from the last
             * added scope, to the first added one.
             */
            this->scopes.insert(this->scopes.begin(), scope);
        }

        void appendScope(const Ptr<ionshared::Scoped<T>> &scopeAnchor) noexcept {
            this->appendScope(scopeAnchor->getSymbolTable());
        }

        /**
         * Removes the lastly added scope from the scopes list.
         * Nothing will happen if the scopes list is empty.
         */
        void popScope() {
            if (!this->scopes.empty()) {
                this->scopes.erase(this->scopes.begin());
            }
        }

        /**
         * Attempt to locate the nearest (starting from most recent
         * scopes) construct by it's id in the scope symbol tables.
         */
        [[nodiscard]] OptPtr<T> findNearest(const std::string &id) {
            /**
             * Scopes vector is already in the correct order because
             * whenever a new scope is pushed, it is added at the beginning
             * instead of the end of the scopes vector, essentially reversing
             * the order from last added to first added.
             */
            for (const auto &scope : this->scopes) {
                if (scope->contains(id)) {
                    return scope->lookup(id);
                }
            }

            // Lastly, check the global scope.
            return this->globalScope->lookup(id);
        }
    };
}
