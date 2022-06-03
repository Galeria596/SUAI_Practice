#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <Windows.h> 

using namespace std;

// прототипы
vector<int> counting_words(vector<string> words);
void removeDupWord(string str);
vector<int> counting_words(vector<string> words);

// merge sort
void mergeSort(vector<string>& a, size_t start, size_t end);

int main() {
    string path = "Texts/Text_0.txt"; // путь к файлу на чтение
    ifstream text;
    text.open(path);
    string analpath = "Analyzes/Analyze_Text_0.txt"; // путь к файлу анализа текста
    ofstream aout;
    aout.open(analpath);
    string pathout = "Results/Result_Text_0.txt"; // путь к файлу на запись
    ofstream fout;
    fout.open(pathout);

    if (!text.is_open() || !fout.is_open()) {
        cout << "Error!\n";
    }
    else {
        string line;
        string textarr; // main string with output
        //remover(text);
        while (getline(text, line)) {
            for (int i = 0; i < line.length(); ++i) {
                if (!isdigit(line[i]) && !ispunct(line[i])) {
                    textarr.push_back(line[i]); //запись текста в строку
                }
                else {
                    textarr.push_back('\0'); //запись текста в строку
                }
            }
        }
        removeDupWord(textarr);

    }
    cout << "\nCheck the result in analysis.txt\n";
    aout.close();
    fout.close();
    text.close();
    return 0;
}

// function to show the words
void removeDupWord(string str) {
    string analpath = "Analyzes/Analyze_Text_0.txt"; // путь к файлу анализа текста
    ofstream aout;
    aout.open(analpath, ios_base::app);
    string pathout = "Results/Result_Text_0.txt"; // путь к файлу на запись
    ofstream fout;
    fout.open(pathout, ios_base::app);

    istringstream ss(str);
    string word; // for storing each word
    int counter = 0; // number of words
    vector <string> maintext;

    while (ss >> word) {
        // print the read word
        transform(word.begin(), word.end(), word.begin(), tolower);
        maintext.push_back(word);
    }

    // вызов сортировки и времени её выполнения
    auto start = chrono::high_resolution_clock::now();
    mergeSort(maintext, 0, maintext.size());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

    // вывод слов
    for (int i = 0; i < maintext.size(); i++) {
        counter++;
        fout << maintext[i] << " ";
    }

    aout << "Words count: " << counter << '\n'; // кол-во слов в тексте
    aout << "Duration: " << duration.count() * 1000 << " ms" << endl; // время выполнения
    vector<int> amount_words = counting_words(maintext);

    aout.close();
    fout.close();
}


// слов на букву алфавита
vector<int> counting_words(vector<string> words) {
    string analpath = "Analyzes/Analyze_Text_0.txt"; // путь к файлу анализа текста
    ofstream aout;
    aout.open(analpath, ios_base::app);
    string pathout = "Results/Result_Text_0.txt"; // путь к файлу на запись
    ofstream fout;
    fout.open(pathout, ios_base::app);

    vector<int> amount_words(26); //вектор длиной 26, заполнен нулями. Каждый элемент - это количество слов на данную букву

    string lo_reg = "abcdefghijklmnoprstuvwxyz";

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 0; j < lo_reg.size(); j++) //проходим по всему массиву количества
        {
            if (lo_reg[j] == words[i][0]) //если первая буква равна какой-то букве из нижнего регистра, то увеличиваем
                amount_words[j]++;
        }
    }
    aout << "Number of words for each letter of the alphabet:\n";
    for (int i = 0; i < amount_words.size(); i++)
    {
        aout << lo_reg[i] << ": " << amount_words[i] << endl; //выводим букву и количество слов на эту букву
    }
    return amount_words;

    aout.close();
    fout.close();
}

// merge sort
void mergeSort(vector<string>& a, size_t start, size_t end) {
    if (end - start < 2)
        return;
    if (end - start == 2) {
        if (a[start] > a[start + 1])
            swap(a[start], a[start + 1]);
        return;
    }
    mergeSort(a, start, start + (end - start) / 2);
    mergeSort(a, start + (end - start) / 2, end);
    vector<string> b;
    size_t b1 = start; // начало первой половины
    size_t e1 = start + (end - start) / 2; // the end of the first половины
    size_t b2 = e1; // start of the second половины
    while (b.size() < end - start) {
        if (b1 >= e1 || (b2 < end && a[b2] <= a[b1])) {
            b.push_back(a[b2]);
            ++b2;
        }
        else {
            b.push_back(a[b1]);
            ++b1;
        }
    }
    for (size_t i = start; i < end; ++i) {
        a[i] = b[i - start];
    }
}