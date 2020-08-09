#pragma once

#include <concepts>
#include <vector>
#include <queue>
#include <ionshared/misc/helpers.h>
#include <ionshared/construct/bare_construct.h>

namespace ionshared {
    enum class PassPriority {
        /**
         * Highest priority. This precedence
         * will be executed first.
         */
        Important,

        Normal,

        Low,

        Lowest
    };

    template<typename T>
    struct PassManagerItem {
        Ptr<T> pass;

        PassPriority priority = PassPriority::Normal;
    };

    template<typename TPass, typename TConstruct>
    class BarePassManager {
    private:
        /**
         * Internal container on which pass manager items will
         * be both stored and processed from.
         */
        std::vector <PassManagerItem<TPass>> passes;

    public:
        explicit BarePassManager(std::vector<PassManagerItem<TPass>> passes = {}) : passes(passes) {
            //
        }

        std::vector<PassManagerItem<TPass>> &getPasses() {
            return this->passes;
        }

        void setPasses(std::vector<PassManagerItem<TPass>> passes) {
            this->passes = passes;
        }

        /**
         * Register a pass in the set. Returns whether the provided
         * pass was successfully registered in the internal set.
         *
         */
        void registerPass(PassManagerItem<TPass> item) {
            this->passes.push_back(item);
        }

        void registerPass(Ptr<TPass> pass) {
            this->registerPass(PassManagerItem<TPass>{
                pass
            });
        }

        void run(const Ast<TConstruct> &ast) {
            auto compare = [](PassManagerItem<TPass> left, PassManagerItem<TPass> right) {
                // TODO: Ensure correct order.
                return left.priority > right.priority;
            };

            std::priority_queue<
                PassManagerItem<TPass>,
                std::vector<PassManagerItem<TPass>>,
                decltype(compare)
            > runQueue(compare);

            // Push pass manager items onto the queue, thus ordering them.
            for (const auto item : this->passes) {
                runQueue.push(item);
            }

            /**
             * Loop through the resulting ordered queue
             * and start executing passes.
             */
            while (!runQueue.empty()) {
                PassManagerItem<TPass> item = runQueue.top();

                runQueue.pop();

                for (auto &topLevelConstruct : ast) {
                    item.pass->prepare();
                    item.pass->visit(topLevelConstruct);
                    item.pass->finish();
                }
            }
        }
    };
}
