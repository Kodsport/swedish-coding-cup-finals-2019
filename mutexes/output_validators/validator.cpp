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

	ifstream answerStream(argv[2]);
	bool equivalentErrors;
    if (answerStream.peek() == ' ') equivalentErrors = 1; // hack, see data/generator.sh

	string correct, user;
	answerStream >> correct;
	cin >> user;

	if (!cin) {
		cout << "WA: empty output" << endl;
		return 43;
	}

    string extra;
    if (cin >> extra) {
        cout << "WA: more than one token" << endl;
        return 43;
    }

	for (char& c : user) c = (char)tolower(c);
	for (char& c : correct) c = (char)tolower(c);

	string origu = user, origc = correct;

	if (equivalentErrors) {
		if (user == "deadlock" || user == "corruption") user = "error";
		if (correct == "deadlock" || correct == "corruption") correct = "error";
	}

	if (user != correct) {
		cout << "WA: " << origu << " vs " << origc << endl;
		return 43;
	}
	return 42;
}
