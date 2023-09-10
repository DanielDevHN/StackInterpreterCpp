#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Stack.h"
using namespace std;

void displayWelcome() {
    cout << "==================================================================" << endl;
    cout << "                  Interprete de Lenguaje de Pila                  " << endl;
    cout << "==================================================================" << endl;
}

string getFileRoute() {
    string fileRoute;
    cout << "Por favor, introduce la direccion del archivo con el codigo fuente:" << endl;
    cout << "> ";
    getline(cin, fileRoute);
    return fileRoute;
}

vector<string> extractInstructions(const string& fileRoute) {
    ifstream fileInterpreter(fileRoute);
    if (!fileInterpreter) {
        cerr << "---- Archivo no encontrado ----" << endl;
        exit(1);
    }

    string textFile;
    getline(fileInterpreter, textFile);
    fileInterpreter.close();

    vector<string> instructions;
    size_t pos = 0;
    const string delim = " ";
    while ((pos = textFile.find(delim)) != string::npos) {
        instructions.push_back(textFile.substr(0, pos));
        textFile.erase(0, pos + delim.length());
    }
    instructions.push_back(textFile);
    return instructions;
}

void executeInstructions(const vector<string>& instructions, Stack& stack) {
    for (const auto& instruction : instructions) {
        if (instruction == ">>") {
            float value;
            cout << "Introduce un valor numerico:" << endl;
            cout << "> ";
            while (!(cin >> value)) {
                cout << "Error: Introduce un numero válido." << endl;
                cout << "> ";
                cin.clear();
                cin.ignore(123, '\n');
            }   
            stack.push(value);

        } else if (instruction == "TOP") {
            cout << "Top returned: " << stack.top() << endl;
        } else if (instruction == "POP") {
            cout << "Pop returned: " << stack.pop() << endl;
        } else {
            try {
                float value = stof(instruction);
                stack.push(value);
            } catch (const invalid_argument&) {
                cout << "Instruccion " << instruction << " no valida" << endl;
            }
        }
    }
}

int main() {
    displayWelcome();

    string fileRoute = getFileRoute();
    vector<string> instructions = extractInstructions(fileRoute);

    Stack stack;

    // Create a map of function pointers
    unordered_map<string, void (Stack::*)()> funcs = {
        {"CLEAR", &Stack::clear},
        {"DEPTH", &Stack::depth},
        {"DROP", &Stack::drop},
        {"DROPN", &Stack::dropn},
        {"DUP", &Stack::dup},
        {"DUPN", &Stack::dupn},
        {"PICK", &Stack::pick},
        {"ROLLD", &Stack::rolld},
        {"ROLLU", &Stack::rollu},
        {"SHOW", &Stack::show},
        {"SWAP", &Stack::swap},
        {"+", &Stack::add},
        {"-", &Stack::sub},
        {"/", &Stack::div},
        {"*", &Stack::mult},
        {"^", &Stack::pot}
    };

    for (const auto& instruction : instructions) {
        if (funcs.find(instruction) != funcs.end()) {
            (stack.*(funcs[instruction]))();
        } else {
            executeInstructions({instruction}, stack);
        }
    }

    return 0;
}
