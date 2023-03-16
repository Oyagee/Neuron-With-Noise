#include <iostream>
#include <vector>
#include <string>


#include <fstream>

#define LINE 100
#define COLUMN 9

using namespace std;


class Neuron {
public:
    int weight = 0;
    int teta = 0;
    int omega[COLUMN + 1] = { 5, 5, 10, 6, 3, 5, 8, 15, 6, 5 }; 
    int err = 0;
    int main_selection[LINE][COLUMN + 1] = {};
    vector <int> errors = {};
    string buffer;
    bool flag_zero = false;
    int temp[COLUMN + 1] = {};
    string path[COLUMN + 1] = {
                    "C:\\noise\\0noise.txt",
                    "C:\\noise\\1noise.txt",
                    "C:\\noise\\2noise.txt",
                    "C:\\noise\\3noise.txt",
                    "C:\\noise\\4noise.txt",
                    "C:\\noise\\5noise.txt",
                    "C:\\noise\\6noise.txt",
                    "C:\\noise\\7noise.txt",
                    "C:\\noise\\8noise.txt",
                    "C:\\noise\\9noise.txt",
    };

    void ADD(int omega[], int main_selection[]) {
        for (int i = 0; i < COLUMN; i++) {
            if (main_selection[i] == 1) {
                omega[i]++;
            }
        }
    }

    void SUB(int omega[], int main_selection[]) {
        for (int i = 0; i < COLUMN; i++) {
            if (main_selection[i] == 1) {
                omega[i]--;
            }
        }
    }

    void AddTeta()
    {
        cout << "Введите тету: ";
        cin >> teta;
        cout << endl;
    }

    void OriginOmega()
    {
        cout << "Исходная омега: | ";
        for (int i = 1; i < COLUMN + 1; i++)
        {
            cout << omega[i] << " | ";
        }
        cout << endl;
        cout << endl;
    }

    void AI_TRAIN()
    {
        for (int file_count = 0; file_count < COLUMN + 1; file_count++)
        {
            int prev_err = 0;
            fstream file(path[file_count]);
            if (file.is_open())
            {
                int i = 0;
                while (getline(file, buffer, '\n'))
                {
                    for (int j = 0; j < COLUMN + 1; j++)
                    {
                        main_selection[i][j] = (int)buffer[j] - 48;
                    }
                    i++;
                }
            }
            else
            {
                cout << "File is not open! Check path!" << endl;
            }
            file.close();

        start:
            prev_err = err;
            err = 0;
            for (int point = 0; point < LINE; point++)
            {
                for (int i = 1; i < COLUMN + 1; i++)
                {
                    weight += omega[i] * main_selection[point][i];
                    temp[i] = main_selection[point][i];
                }
                if (main_selection[point][0] == 0 and weight > teta)
                {
                    flag_zero = true;
                }
                else if (main_selection[point][0] == 0 and weight <= teta)
                {
                    ADD(omega, temp); flag_zero = false; err++;
                }
                else if (main_selection[point][0] != 0 and weight > teta)
                {
                    SUB(omega, temp); flag_zero = false;
                }
                weight = 0;
            };
            if (((err - prev_err) < 0) or ((prev_err - err) < 0))
            {
                goto start;
            }
            errors.push_back(err);
        }
    }

    void NoiseResult() 
    {
        for (int i = 0; i < errors.size(); i++)
        {
            cout << "Кол - во помех: " << i << ", процент ошибки: " << errors[i] << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    Neuron Neuro;
    Neuro.AddTeta(); // Пользовательский ввод омеги
    Neuro.OriginOmega(); // Вывод исходных омег
    Neuro.AI_TRAIN();
    Neuro.NoiseResult();
}