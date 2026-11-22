// Lab_8.1(2).cpp
// Лабораторна робота № 8.1. Пошук та заміна символів у літерному рядку.
// Варіант 8. Рекурсивний спосіб.
// Виконала: Кучер Софія.
//
// Дано літерний рядок, який містить послідовність символів s[0], ..., s[n], ...
// 1. Вияснити, чи є серед цих символів всі букви, що входять в слово "while".
// 2. Замінити кожну групу букв "while" парою зірочок "**".

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// чи входить символ c до рядка s, починаючи з позиції i
bool ContainsChar(const char* s, const char c, int i)
{
    if (s[i] == '\0')
        return false;
    if (s[i] == c)
        return true;
    return ContainsChar(s, c, i + 1);
}

// чи входять до рядка s всі букви рядка letters, починаючи з позиції j
bool ContainsAllLetters(const char* s, const char* letters, int j)
{
    if (letters[j] == '\0')
        return true;
    if (!ContainsChar(s, letters[j], 0))
        return false;
    return ContainsAllLetters(s, letters, j + 1);
}

// замінює кожну групу букв "while" рядка str парою зірочок "**";
// dest – початок рядка-результату, t – поточна позиція запису в dest,
// i – поточна позиція в str; повертає dest
char* Change(char* dest, const char* str, char* t, int i)
{
    if (str[i] == '\0')
    {
        *t = '\0';
        return dest;
    }

    if (str[i]     == 'w' &&
        str[i + 1] == 'h' &&
        str[i + 2] == 'i' &&
        str[i + 3] == 'l' &&
        str[i + 4] == 'e')
    {
        *t++ = '*';
        *t++ = '*';
        return Change(dest, str, t, i + 5);   // пропускаємо "while"
    }

    *t++ = str[i];
    return Change(dest, str, t, i + 1);
}

int main()
{
    char str[101];

    cout << "Enter string:" << endl;
    cin.getline(str, 100);

    if (ContainsAllLetters(str, "while", 0))
        cout << "String contains all letters of \"while\"" << endl;
    else
        cout << "String does not contain all letters of \"while\"" << endl;

    char* dest1 = new char[strlen(str) + 1];
    dest1[0] = '\0';

    char* dest2 = Change(dest1, str, dest1, 0);

    cout << "Modified string (param) : " << dest1 << endl;
    cout << "Modified string (result): " << dest2 << endl;

    delete[] dest1;

    system("pause");    // щоб вікно не закривалося одразу
    return 0;
}
