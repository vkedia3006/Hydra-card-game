#include <iostream>
#include "Model.h"
#include "Controller.h"
#include "View.h"
#include "deck.h"
#include <fstream>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
    auto deck = make_shared<Deck>(-1);
    int random = -1;
    if ( argc == 2 ) {
        string commandLine = argv[1];
        if ( commandLine.compare("-testing") == 0 ) {
            istream *in = &cin;
            auto controller = make_shared<Controller>(in);
            auto model = make_shared<Model>(deck, controller, true, random);
            auto view = make_shared<View>(model);
        }
        else {
            istream *in = &cin;
            random = stoi(commandLine);
            auto controller = make_shared<Controller>(in);
            auto model = make_shared<Model>(deck, controller, false, random);
            auto view = make_shared<View>(model);
        }
    }
    else if ( argc == 3) {
        string commandLine = argv[1];
        string inputFileName = argv[2];
        if ( commandLine.compare("-testing") == 0 ) {
            std::shared_ptr<istream> in = std::make_shared<ifstream> (inputFileName.c_str());
            auto controller = make_shared<Controller>(in.get());
            auto model = make_shared<Model>(deck, controller, true, random);
            auto view = make_shared<View>(model);
        }
        else {
            random = stoi(commandLine);
            std::shared_ptr<istream> in = std::make_shared<ifstream> (inputFileName.c_str());
            auto controller = make_shared<Controller>(in.get());
            auto model = make_shared<Model>(deck, controller, false, random);
            auto view = make_shared<View>(model);
        }
    }
    else {
        istream *in = &cin;
        auto controller = make_shared<Controller>(in);
        auto model = make_shared<Model>(deck, controller, false, random);
        auto view = make_shared<View>(model);
    }
}
