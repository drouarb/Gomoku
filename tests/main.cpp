//
// Created by greg on 11/11/16.
//

#include <Core/Core.hh>

int main() {
    Core::Core *core;

    try {
 /*       core = new Core::Core("./tests/conf/basic_test_1");
        delete (core);

        core = new Core::Core("./tests/conf/basic_test_2");
        delete (core);
*/
        core = new Core::Core("./tests/conf/Breakable_five_enable");
        delete (core);
    } catch (const std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}