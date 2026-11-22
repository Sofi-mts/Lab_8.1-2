// Юніт-тести до лабораторної роботи № 8.1 (рекурсивний спосіб), варіант 8
// 1) чи є в рядку всі букви слова "while"; 2) заміна кожного "while" на "**".
// Запуск: відкрити цей файл у VS Code і натиснути F5 (або Ctrl+F5).

#define main lab_main          // беремо функції з лаби, але без її main()
#include "Lab_8.1(2).cpp"
#undef main

#include <string>

static int passed = 0, failed = 0;

#define CHECK_EQ(expected, actual)                                          \
    do {                                                                    \
        auto e_ = (expected);                                               \
        auto a_ = (actual);                                                 \
        if (e_ == a_) {                                                     \
            ++passed;                                                       \
        } else {                                                            \
            ++failed;                                                       \
            cout << "  FAIL line " << __LINE__ << ": " #actual              \
                 << " = " << a_ << ", expected " << e_ << endl;             \
        }                                                                   \
    } while (0)

#define CHECK(cond) CHECK_EQ(true, (bool)(cond))

static void RunTest(const char* name, void (*test)()) {
    int failedBefore = failed;
    test();
    cout << (failed == failedBefore ? "[ OK ] " : "[FAIL] ") << name << endl;
}

// ---------- ContainsAllLetters ----------

void TestContains_AllInWord() {
    CHECK_EQ(true, ContainsAllLetters("while", "while", 0));
}

void TestContains_Scattered() {
    CHECK_EQ(true, ContainsAllLetters("hello world, i will", "while", 0));
}

void TestContains_Missing() {
    CHECK_EQ(false, ContainsAllLetters("hello", "while", 0));
}

void TestContains_UpperCase() {
    CHECK_EQ(false, ContainsAllLetters("WHILE", "while", 0));
}

void TestContains_Empty() {
    CHECK_EQ(false, ContainsAllLetters("", "while", 0));
}

// ---------- Change ----------

void TestChange_Simple() {
    const char str[] = "do while(x) while";
    char dest[100];
    char* res = Change(dest, str, dest, 0);
    CHECK_EQ(string("do **(x) **"), string(res));
    CHECK_EQ(string("do **(x) **"), string(dest));    // результат і в параметрі
}

void TestChange_Adjacent() {
    const char str[] = "whilewhile";
    char dest[100];
    char* res = Change(dest, str, dest, 0);
    CHECK_EQ(string("****"), string(res));
    CHECK_EQ(string("****"), string(dest));    // результат і в параметрі
}

void TestChange_NoWhile() {
    const char str[] = "hello world, i will";
    char dest[100];
    char* res = Change(dest, str, dest, 0);
    CHECK_EQ(string("hello world, i will"), string(res));
    CHECK_EQ(string("hello world, i will"), string(dest));    // результат і в параметрі
}

void TestChange_Partial() {
    const char str[] = "whil while";
    char dest[100];
    char* res = Change(dest, str, dest, 0);
    CHECK_EQ(string("whil **"), string(res));
    CHECK_EQ(string("whil **"), string(dest));    // результат і в параметрі
}

void TestChange_Empty() {
    const char str[] = "";
    char dest[100];
    char* res = Change(dest, str, dest, 0);
    CHECK_EQ(string(""), string(res));
    CHECK_EQ(string(""), string(dest));    // результат і в параметрі
}


int main() {
    cout << "Lab 8.1 unit tests" << endl;
    RunTest("ContainsAllLetters: the word 'while' itself", TestContains_AllInWord);
    RunTest("ContainsAllLetters: letters scattered over the string", TestContains_Scattered);
    RunTest("ContainsAllLetters: 'w' and 'i' are missing", TestContains_Missing);
    RunTest("ContainsAllLetters: upper-case letters do not count", TestContains_UpperCase);
    RunTest("ContainsAllLetters: empty string", TestContains_Empty);
    RunTest("Change: 'while' in the middle and at the end", TestChange_Simple);
    RunTest("Change: two 'while' in a row", TestChange_Adjacent);
    RunTest("Change: no 'while' - string unchanged", TestChange_NoWhile);
    RunTest("Change: 'whil' is not replaced", TestChange_Partial);
    RunTest("Change: empty string", TestChange_Empty);
    cout << endl << "Checks passed: " << passed << ", failed: " << failed << endl;
    cout << (failed == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << endl;
    system("pause");    // щоб вікно не закривалося одразу
    return failed == 0 ? 0 : 1;
}
