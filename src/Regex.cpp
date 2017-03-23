#include <cucumber-cpp/internal/utils/Regex.hpp>
#include <cucumber-cpp/internal/utils/make_unique.hpp>
#include <boost/version.hpp>

namespace cucumber {
namespace internal {

Regex::Regex(std::string regularExpression) :
    regexImpl(regularExpression.c_str()) {
}

bool RegexMatch::matches() {
    return regexMatched;
}

const RegexMatch::submatches_type & RegexMatch::getSubmatches() {
    return submatches;
}

std::string Regex::str() const {
    return regexImpl.str();
}

RegexMatch::pointer Regex::find(const std::string &expression) const {
    // Explicitly using namespace-qualified call to prevent ambiguity with std::make_unique (C++14),
    // which becomes visible due to ADL.
    return RegexMatch::pointer(cucumber::internal::make_unique<FindRegexMatch>(regexImpl, expression)
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}

FindRegexMatch::FindRegexMatch(const boost::regex &regexImpl, const std::string &expression) {
    boost::cmatch matchResults;
    regexMatched = boost::regex_search(expression.c_str(), matchResults, regexImpl, boost::regex_constants::match_extra);
    if (regexMatched) {
        for (boost::cmatch::size_type i = 1; i < matchResults.size(); ++i) {
            RegexSubmatch s;
            s.value = matchResults.str(i);
            s.position = matchResults.position(i);
            submatches.push_back(s);
        }
    }
}

RegexMatch::pointer Regex::findAll(const std::string &expression) const {
    // Explicitly using namespace-qualified call to prevent ambiguity with std::make_unique (C++14),
    // which becomes visible due to ADL.
    return RegexMatch::pointer(cucumber::internal::make_unique<FindAllRegexMatch>(regexImpl, expression)
#if BOOST_VERSION < 105900
            // This version of unique_ptr doesn't support implicit conversions to pointers up the class hierarchy
            .release()
#endif
        );
}

FindAllRegexMatch::FindAllRegexMatch(const boost::regex &regexImpl, const std::string &expression) {
    regexMatched = false;
    boost::sregex_token_iterator i(expression.begin(), expression.end(), regexImpl, 1, boost::regex_constants::match_continuous);
    boost::sregex_token_iterator j;
    while (i != j) {
        regexMatched = true;
        RegexSubmatch s;
        s.value = *i;
        s.position = -1;
        submatches.push_back(s);
        ++i;
    }
}

}
}
