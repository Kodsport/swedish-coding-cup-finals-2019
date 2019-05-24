/* usage:
 * ./a.out input_file answer_file feedback_dir < contestants_output
*/
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "not enough arguments" << endl;
        return 1;
    }

    int margin = 0;
    int correctAnswer, provided;
    ifstream answerStream(argv[2]);
    if (answerStream.peek() == ' ') margin = 1; // hack, see data/generator.sh
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
