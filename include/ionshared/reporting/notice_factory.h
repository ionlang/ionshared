#pragma once

#include "notice.h"

namespace ionshared {
    class NoticeFactory {
    private:
        NoticeContext context;

    public:
        explicit NoticeFactory(NoticeContext context);

        NoticeContext &getContext();

        void setContext(NoticeContext &context);

        Notice make(NoticeType type, std::string message);
    };
}
