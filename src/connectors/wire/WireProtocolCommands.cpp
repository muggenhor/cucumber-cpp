#include <cucumber-cpp/internal/connectors/wire/WireProtocolCommands.hpp>
#include <cucumber-cpp/internal/utils/move.hpp>
#include <boost/make_shared.hpp>

namespace cucumber {
namespace internal {

ScenarioCommand::ScenarioCommand(CukeEngine::tags_type tags) :
    tags(move(tags)) {
}


BeginScenarioCommand::BeginScenarioCommand(CukeEngine::tags_type tags) :
    ScenarioCommand(move(tags)) {
}

boost::shared_ptr<WireResponse> BeginScenarioCommand::run(CukeEngine& engine) const {
    engine.beginScenario(tags);
    return boost::make_shared<SuccessResponse>();
}


EndScenarioCommand::EndScenarioCommand(CukeEngine::tags_type tags) :
    ScenarioCommand(move(tags)) {
}

boost::shared_ptr<WireResponse> EndScenarioCommand::run(CukeEngine& engine) const {
    engine.endScenario(tags);
    return boost::make_shared<SuccessResponse>();
}


StepMatchesCommand::StepMatchesCommand(std::string stepName) :
    stepName(move(stepName)) {
}

boost::shared_ptr<WireResponse> StepMatchesCommand::run(CukeEngine& engine) const {
    std::vector<StepMatch> matchingSteps = engine.stepMatches(stepName);
    return boost::make_shared<StepMatchesResponse>(matchingSteps);
}


InvokeCommand::InvokeCommand(std::string                          stepId,
                             CukeEngine::invoke_args_type         args,
                             const CukeEngine::invoke_table_type& tableArg) :
    stepId(move(stepId)),
    args(move(args)),
    tableArg(tableArg) {
}

boost::shared_ptr<WireResponse> InvokeCommand::run(CukeEngine& engine) const {
    try {
        engine.invokeStep(stepId, args, tableArg);
        return boost::make_shared<SuccessResponse>();
    } catch (const InvokeFailureException& e) {
        return boost::make_shared<FailureResponse>(e.getMessage(), e.getExceptionType());
    } catch (const PendingStepException& e) {
        return boost::make_shared<PendingResponse>(e.getMessage());
    } catch (...) {
        return boost::make_shared<FailureResponse>();
    }
}


SnippetTextCommand::SnippetTextCommand(std::string keyword, std::string name, std::string multilineArgClass) :
    keyword(move(keyword)),
    name(move(name)),
    multilineArgClass(move(multilineArgClass)) {
}

boost::shared_ptr<WireResponse> SnippetTextCommand::run(CukeEngine& engine) const {
    return boost::make_shared<SnippetTextResponse>(engine.snippetText(keyword, name, multilineArgClass));
}


boost::shared_ptr<WireResponse> FailingCommand::run(CukeEngine& /*engine*/) const {
    return boost::make_shared<FailureResponse>();
}

}
}
