#include <ionshared/error_handling/notice_factory.h>

namespace ionshared {
    NoticeFactory::NoticeFactory(NoticeContext context) : context(context) {
        //
    }

    NoticeContext &NoticeFactory::getContext() {
        return this->context;
    }

    void NoticeFactory::setContext(NoticeContext &context) {
        this->context = context;
    }

    Notice NoticeFactory::make(NoticeType type, std::string message) {
        return Notice(this->context, type, message);
    }
}
