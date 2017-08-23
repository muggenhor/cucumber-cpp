#include <cucumber-cpp/internal/connectors/wire/WireProtocolCommands.hpp>
#include <cucumber-cpp/internal/utils/make_unique.hpp>

namespace cucumber {
namespace internal {

ScenarioCommand::ScenarioCommand(const CukeEngine::tags_type& tags) :
    tags(tags) {
}


BeginScenarioCommand::BeginScenarioCommand(const CukeEngine::tags_type& tags) :
    ScenarioCommand(tags) {
}

unique<WireResponse>::ptr BeginScenarioCommand::run(CukeEngine& engine) const {
    engine.beginScenario(tags);
    return unique<WireResponse>::ptr(
            make_unique<SuccessResponse>()
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}


EndScenarioCommand::EndScenarioCommand(const CukeEngine::tags_type& tags) :
    ScenarioCommand(tags) {
}

unique<WireResponse>::ptr EndScenarioCommand::run(CukeEngine& engine) const {
    engine.endScenario(tags);
    return unique<WireResponse>::ptr(
            make_unique<SuccessResponse>()
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}


StepMatchesCommand::StepMatchesCommand(const std::string & stepName) :
    stepName(stepName) {
}

unique<WireResponse>::ptr StepMatchesCommand::run(CukeEngine& engine) const {
    std::vector<StepMatch> matchingSteps = engine.stepMatches(stepName);
    return unique<WireResponse>::ptr(
            make_unique<StepMatchesResponse>(matchingSteps)
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}


InvokeCommand::InvokeCommand(const std::string & stepId,
                             const CukeEngine::invoke_args_type& args,
                             const CukeEngine::invoke_table_type& tableArg) :
    stepId(stepId),
    args(args),
    tableArg(tableArg) {
}

unique<WireResponse>::ptr InvokeCommand::run(CukeEngine& engine) const {
    try {
        engine.invokeStep(stepId, args, tableArg);
        return unique<WireResponse>::ptr(
                make_unique<SuccessResponse>()
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
            );
    } catch (const InvokeFailureException& e) {
        return unique<WireResponse>::ptr(
                make_unique<FailureResponse>(e.getMessage(), e.getExceptionType())
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
            );
    } catch (const PendingStepException& e) {
        return unique<WireResponse>::ptr(
                make_unique<PendingResponse>(e.getMessage())
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
            );
    } catch (...) {
        return unique<WireResponse>::ptr(
                make_unique<FailureResponse>()
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
            );
    }
}


SnippetTextCommand::SnippetTextCommand(const std::string & keyword, const std::string & name, const std::string & multilineArgClass) :
    keyword(keyword),
    name(name),
    multilineArgClass(multilineArgClass) {
}

unique<WireResponse>::ptr SnippetTextCommand::run(CukeEngine& engine) const {
    return unique<WireResponse>::ptr(
            make_unique<SnippetTextResponse>(engine.snippetText(keyword, name, multilineArgClass))
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}


unique<WireResponse>::ptr FailingCommand::run(CukeEngine& /*engine*/) const {
    return unique<WireResponse>::ptr(
            make_unique<FailureResponse>()
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}

}
}
