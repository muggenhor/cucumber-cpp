#include <cucumber-cpp/internal/Scenario.hpp>
#include <cucumber-cpp/internal/utils/move.hpp>

namespace cucumber {
namespace internal {

Scenario::Scenario(TagExpression::tag_list tags) :
    tags(move(tags)) {
};

const TagExpression::tag_list & Scenario::getTags() {
    return tags;
}

}
}
