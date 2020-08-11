#pragma once

#include <ionshared/construct/base_construct.h>
#include <ionshared/tracking/symbol_table.h>
#include <ionshared/misc/util.h>

namespace ionshared {
    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename T>
    class ScopeAnchor {
    private:
        PtrSymbolTable<T> symbolTable;

    public:
        explicit ScopeAnchor(PtrSymbolTable<T> symbolTable = Util::makePtrSymbolTable<T>())
            : symbolTable(symbolTable) {
            //
        }

        virtual PtrSymbolTable<T> getSymbolTable() const {
            return this->symbolTable;
        }

        virtual void setSymbolTable(PtrSymbolTable<T> symbolTable) {
            this->symbolTable = symbolTable;
        }
    };
}
