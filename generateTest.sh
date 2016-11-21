#!/usr/bin/env bash

find ./tests/conf/ > .tmp

rm -rf generated
mkdir -p generated
mkdir -p history
rm -f ./tests/conf/*.res


while read file
do

    if [ -d "$file" ]; then
        continue
    fi

    echo "Generate test for file $file"

    echo "//Auto Generated tests

#include <Core/Core.hh>

int main() {

    Core::Core *core;


    try {
        core = new Core::Core(\"$file\");
        delete (core);
    } catch (const std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
    " > "generated/$(echo $file | cut -d '/' -f 4)_test.cpp"

rm -f  $(echo $file | cut -d / -f 4 | cut -d . -f 1)

done < .tmp


rm -f .tmp