#include "Rule.hh"

using namespace Core;

Rule::Rule() : name(""), on(false)
{ }

Rule::Rule(const std::string & name, bool on) : name(name), on(on)
{ }

Rule::Rule(const Rule & other) : name(other.name), on(other.on)
{ }

Rule::~Rule()
{ }

Rule & Rule::operator=(const Rule & other)
{
    name = other.name;
    on = other.on;
}