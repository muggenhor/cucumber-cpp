#include "cucumber-cpp/internal/CukeCommands.hpp"
#include "cucumber-cpp/internal/hook/HookRegistrar.hpp"
#include "cucumber-cpp/internal/utils/make_unique.hpp"

#include <sstream>
#include <boost/algorithm/string.hpp>

namespace cucumber {
namespace internal {

unique<Scenario>::ptr CukeCommands::currentScenario;

CukeCommands::CukeCommands() : hasStarted(false) {
}

CukeCommands::~CukeCommands() {
    if (hasStarted) {
        HookRegistrar::execAfterAllHooks();
    }
}

void CukeCommands::beginScenario(const TagExpression::tag_list& tags) {
    if (!hasStarted) {
        hasStarted = true;
        HookRegistrar::execBeforeAllHooks();
    }

    // Explicitly using namespace-qualified call to prevent ambiguity with std::make_unique (C++14),
    // which becomes visible due to ADL.
    assign(currentScenario, cucumber::internal::make_unique<Scenario>(tags));
    HookRegistrar::execBeforeHooks(currentScenario.get());
}

void CukeCommands::endScenario() {
    HookRegistrar::execAfterHooks(currentScenario.get());
    contextManager.purgeContexts();
    currentScenario.reset();
}

const std::string CukeCommands::snippetText(const std::string stepKeyword, const std::string stepName) const {
    std::stringstream text;
    text << boost::to_upper_copy(stepKeyword)
        << "(\""
        << escapeCString("^" + escapeRegex(stepName) + "$")
        << "\") {\n"
        << "    pending();\n"
        << "}\n";
    return text.str();
}

const std::string CukeCommands::escapeRegex(const std::string reg) const {
    return regex_replace(reg, boost::regex("[\\|\\(\\)\\[\\]\\{\\}\\^\\$\\*\\+\\?\\.\\\\]"), "\\\\&", boost::match_default | boost::format_sed);
}

const std::string CukeCommands::escapeCString(const std::string str) const {
    return regex_replace(str, boost::regex("[\"\\\\]"), "\\\\&", boost::match_default | boost::format_sed);
}

MatchResult CukeCommands::stepMatches(const std::string description) const {
    return stepManager.stepMatches(description);
}

InvokeResult CukeCommands::invoke(step_id_type id, const InvokeArgs *pArgs) {
    const StepInfo* const stepInfo = stepManager.getStep(id);
    InvokeResult result = HookRegistrar::execStepChain(currentScenario.get(), stepInfo, pArgs);
    HookRegistrar::execAfterStepHooks(currentScenario.get());
    return result;
}

}
}
