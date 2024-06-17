#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/program_options/option.hpp>
#include <boost/program_options.hpp>

#include "./cipher.h"

using namespace std;
namespace po = boost::program_options;

static string open_msg_file(string file_path);

int main(int argc, char* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help, h", "produce help message")
        ("encode, e","encode a message given a key")
        ("decode, d","decode a message given a key")
        ("message, m", po::value<string>(), "input message")
        ("message-file, mf", po::value<string>(), "text file containing the input message")
        ("key, k", po::value<string>()->default_value("OCULORHINOLARINGOLOGY"), "key for the cipher");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("encode")) {
            string key = vm["key"].as<string>();
            string message;

            if (vm.count("message")) {
                message = vm["message"].as<string>();
            } else if (vm.count("message-file")) {
                message = open_msg_file(vm["message-file"].as<string>());
            } else {
                cout << "message not specified";
                return -1;
            }

            encode(message, key);
            cout << message << '\n';

            return 0;
        }

        if (vm.count("decode")) {
            string key = vm["key"].as<string>();
            string message;

            if (vm.count("message")) {
                message = vm["message"].as<string>();
            } else if (vm.count("message-file")) {
                message = open_msg_file(vm["message-file"].as<string>());
            } else {
                cout << "message not specified";
                return -1;
            }

            decode(message, key);
            cout << message << '\n';

            return 0;
        }
    } catch (const po::error &ex) {
        cerr << ex.what() << '\n';
        cout << desc << "\n";
        return 1;
    }

    return 0;
}

static string open_msg_file(string file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer  << file.rdbuf();
    string str = buffer.str();
    std::replace(str.begin(), str.end(), '\n', ' ');
    return str;
}

