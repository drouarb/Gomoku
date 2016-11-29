#ifndef CORE_RULE_HH_
#define CORE_RULE_HH_

#include "Definitions.hpp"
#include <string>

namespace Core
{
    struct Rule
    {
        Rule();
        Rule(const std::string &, bool);
        Rule(const Rule &);
        ~Rule();

        Rule & operator=(const Rule &);

        std::string name;
        bool on;
    };
}

#endif
