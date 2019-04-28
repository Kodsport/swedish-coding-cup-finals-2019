/* usage:
 * ./a.out input_file answer_file feedback_dir answer_margin < contestants_output
 * ./a.out input_file answer_file < contestants_output
 *
 * input_file and feedback_dir are unused but must be provided to comply with format.
*/
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "not enough arguments" << endl;
        return 1;
    }

    int margin = 0;
    for (int i = 4; i < argc; i++) {
        string arg = argv[i];
        size_t index = arg.find('=');
        if (index == string::npos) continue;

        auto name = arg.substr(0, index), value = arg.substr(index + 1);
        if (name == "margin") {
            margin = stoi(value);
        }
    }

    int correctAnswer, provided;
    ifstream answerStream(argv[2]);
    answerStream >> correctAnswer;
    cin >> provided;

    if (!cin) {
        cout << "io error" << endl;
        return 43;
    }

    if (provided < 0) {
        cout << "WA: out of range" << endl;
        return 43;
    }

    if (abs(correctAnswer - provided) > margin) {
        cout << "WA: not within margin" << endl;
        return 43;
    }

    return 42;
}