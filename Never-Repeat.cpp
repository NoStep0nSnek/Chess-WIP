#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// see: https://stackoverflow.com/questions/241533/i-want-a-program-that-writes-every-possible-combination-to-a-different-line-of-a

vector<float> number_to_list(int number, vector<float> words) {
    vector<float> list_out;
    while (number)
    {
        list_out.push_back(number % words.size());
        number = floor(static_cast<float>(number) / words.size());
    }

    return list_out;
}

void combo(vector<vector<float>> &combos, vector<float> words, int length) {
    vector<float> numbers(pow(words.size(), length), 0);
    for (int i = 0; i < pow(words.size(), length); i++) {
        numbers[i] = i;
    }
    for (auto &number:numbers) {
        vector<float> combo = number_to_list(number, words);
        if (combo.size() < length) {
            //combo = [words[0]] * (length - len(combo)) + combo
            vector<float> t1(length - combo.size(), words[0]);

            t1.insert(t1.end(), combo.begin(), combo.end());

            combo = t1;
        }

        combos.push_back(combo);
    }
}

int main() {
    vector<vector<float>> combos;
    vector<float> vec(64,0);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }
    combo(combos, vec, 3); // 3rd arg is expotential
   /* for (int i = 0; i < combos.size(); i++) {
        cout << "\n{";
        for (auto &z:combos[i]) {
            cout << z << ",";
        }
        cout << "}";
    }*/

    cout << "\n SIZE: " << combos.size();
}