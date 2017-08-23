#include "cucumber-cpp/internal/CukeEngine.hpp"
#include <cucumber-cpp/internal/utils/move.hpp>

namespace cucumber {
namespace internal {

InvokeException::InvokeException(std::string message) :
    message(move(message)) {
}

InvokeException::InvokeException(const InvokeException &rhs) :
    message(rhs.message) {
}

const std::string& InvokeException::getMessage() const {
    return message;
}


InvokeFailureException::InvokeFailureException(std::string message, std::string exceptionType) :
    InvokeException(move(message)),
    exceptionType(move(exceptionType)) {
}

InvokeFailureException::InvokeFailureException(const InvokeFailureException &rhs) :
    InvokeException(rhs),
    exceptionType(rhs.exceptionType) {
}

const std::string& InvokeFailureException::getExceptionType() const {
    return exceptionType;
}


PendingStepException::PendingStepException(const std::string & message) :
        InvokeException(message) {
}

PendingStepException::PendingStepException(const PendingStepException &rhs) :
    InvokeException(rhs) {
}

}
}
