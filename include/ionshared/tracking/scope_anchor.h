#pragma once

//#include <queue>
#include <ionshared/construct/base_construct.h>
#include <ionshared/tracking/symbol_table.h>
#include <ionshared/misc/util.h>

namespace ionshared {
    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename T>
    class ScopeAnchor /*: public std::enable_shared_from_this<ScopeAnchor<T>>*/ {
    private:
        PtrSymbolTable<T> symbolTable;

    public:
        explicit ScopeAnchor(PtrSymbolTable<T> symbolTable = util::makePtrSymbolTable<T>())
            : symbolTable(symbolTable) {
            //
        }

        virtual PtrSymbolTable<T> getSymbolTable() const {
            return this->symbolTable;
        }

        virtual void setSymbolTable(PtrSymbolTable<T> symbolTable) {
            this->symbolTable = symbolTable;
        }

        // TODO
//        void traverse(int callback) {
//            std::queue<ionshared::Ptr<ScopeAnchor<T>>> analysisQueue = {
//                this->shared_from_this()
//            };
//
//            std::queue<ionshared::Ptr<T>> queue = {};
//
//            for (const ScopeAnchor<T> &scopeAnchor : analysisQueue) {
//                if (scopeAnchor.)
//            }
//        }
    };
}
