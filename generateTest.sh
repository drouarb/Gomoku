#!/usr/bin/env bash

find ./tests/conf/ > .tmp

rm -rf generated
mkdir -p generated
mkdir -p history
rm -rf logs
mkdir -p logs
rm -f ./tests/conf/*.res


while read file
do

    if [ -d "$file" ]; then
        continue
    fi

    echo "Generate test for file $file"

    echo "//Auto Generated tests

#include <Core/Core.hh>
#include <fstream>

int main() {

    Core::Core *core;

    std::ofstream out(\"logs/$(echo $file | cut -d / -f 4 | cut -d . -f 1)\");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());


    try {
        core = new Core::Core(\"$file\");
        delete (core);
    } catch (const std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

        std::cout.rdbuf(coutbuf);


    return 0;
}
    " > "generated/$(echo $file | cut -d '/' -f 4)_test.cpp"

done < .tmp


rm -f .tmp