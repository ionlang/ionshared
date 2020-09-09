#pragma once

#include <concepts>
#include <vector>
#include <queue>
#include <ionshared/misc/helpers.h>
#include <ionshared/construct/base_construct.h>
#include "pass_info.h"

namespace ionshared {
    enum class PassPriority {
        /**
         * Highest priority. This precedence will be executed first.
         */
        Important,

        /**
         * The default priority.
         */
        Normal,

        Low,

        Lowest
    };

    /**
     * Holds passes which will traverse the construct AST once
     * invoked. Passes can be registered with prerequisites.
     */
    template<PassLike TPass, typename TConstruct>
        requires std::derived_from<TPass, BasePass<TConstruct>>
    class BasePassManager {
    public:
        struct Item;

    private:
        Set<PassId> initializedPasses;

        std::vector<Item> passes;

    public:
        struct Item {
            Ptr<TPass> pass;

            PassInfo info;

            PassPriority priority;
        };

        explicit BasePassManager(std::vector<Item> passes = {}) :
            passes(passes),
            initializedPasses() {
            //
        }

        [[nodiscard]] const std::vector<Item> &getPasses() const noexcept {
            return this->passes;
        }

        void setPasses(std::vector<Item> passes) noexcept {
            this->passes = passes;
        }

        bool registerPass(Ptr<TPass> pass, PassPriority priority = PassPriority::Normal) {
            PassInfo info = PassInfo();

            pass->initialize(info);

            std::set<PassId> requirements = info.getRequirements().unwrap();

            for (const auto &requirement : requirements) {
                if (!this->initializedPasses.contains(requirement)) {
                    return false;
                }
            }

            // TODO: Handle invalidations.

            this->initializedPasses.add(&TPass::id);

            this->passes.push_back(Item{
                pass,
                info,
                priority
            });

            return true;
        }

        /**
         * Traverse all nodes and visit each one of them, and their
         * child nodes if applicable.
         */
        void run(const Ast<TConstruct> &ast) {
            auto compare = [](Item left, Item right) {
                // TODO: Ensure correct order.
                return left.priority > right.priority;
            };

            std::priority_queue<
                Item,
                std::vector<Item>,
                decltype(compare)
            > runQueue(compare);

            // Push pass manager items onto the queue, thus ordering them.
            for (const auto &item : this->passes) {
                runQueue.push(item);
            }

            /**
             * Loop through the resulting ordered queue
             * and start executing passes.
             */
            while (!runQueue.empty()) {
                Item item = runQueue.top();

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
