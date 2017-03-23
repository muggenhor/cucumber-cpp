#ifndef CUKE_CUKECOMMANDS_HPP_
#define CUKE_CUKECOMMANDS_HPP_

#include "ContextManager.hpp"
#include "Scenario.hpp"
#include "Table.hpp"
#include "step/StepManager.hpp"

#include <map>
#include <string>
#include <sstream>

#include "utils/unique_ptr.hpp"

namespace cucumber {
namespace internal {

/**
 * Legacy class to be removed when feature #31 is complete, substituted by CukeEngineImpl.
 */
class CukeCommands {
public:
	CukeCommands();
	virtual ~CukeCommands();

    void beginScenario(const TagExpression::tag_list& tags = TagExpression::tag_list());
    void endScenario();
    const std::string snippetText(const std::string stepKeyword, const std::string stepName) const;
    MatchResult stepMatches(const std::string description) const;
    InvokeResult invoke(step_id_type id, const InvokeArgs * pArgs);

protected:
	const std::string escapeRegex(const std::string regex) const;
	const std::string escapeCString(const std::string str) const;

private:
    StepManager stepManager;
    ContextManager contextManager;
    bool hasStarted;

private:
    static unique<Scenario>::ptr currentScenario;
};

}
}

#endif /* CUKE_CUKECOMMANDS_HPP_ */
