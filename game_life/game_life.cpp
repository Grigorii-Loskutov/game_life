// game_life.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>

unsigned alive_cells_count = 0;
unsigned generation_count = 1;
bool swap = false;

char** create_two_dim_char_array(unsigned rows = 0, unsigned cols = 0) {
    char** arr = new char* [rows];
    for (unsigned iter_r = 0; iter_r < rows; ++iter_r) {
        arr[iter_r] = new char[cols]();
        for (unsigned iter_c = 0; iter_c < cols; ++iter_c) {
            arr[iter_r][iter_c] = '-';
        }
    }
    return arr;
}

void print_two_dim_char_array(char** arr, unsigned rows, unsigned cols) {
    for (unsigned iter_r = 1; iter_r < rows - 1; ++iter_r) {
        for (int iter_c = 1; iter_c < cols - 1; ++iter_c) {
            std::cout << arr[iter_r][iter_c] << " ";
        }
        std::cout << "\n";
    }
}

void delete_two_dim_char_array(char** arr, unsigned rows, unsigned cols) {
    for (unsigned iter = 0; iter < rows; ++iter) {
        delete[] arr[iter];
    }
    delete arr;
}

void copy_two_dim_char_array(char** arr_dest, char** arr_sourse, unsigned rows, unsigned cols) {
    for (unsigned iter_r = 0; iter_r < rows; ++iter_r) {
        for (unsigned iter_c = 0; iter_c < cols; ++iter_c) {
            arr_dest[iter_r][iter_c] = arr_sourse[iter_r][iter_c];
        }
    }
}

void swap_char_arr(char** arr, char** arr_out, unsigned rows, unsigned cols) {
    alive_cells_count = 0;
    for (unsigned iter_r = 1; iter_r < rows - 1; ++iter_r) {
        for (int iter_c = 1; iter_c < cols - 1; ++iter_c) {
            unsigned alive_neighbor_count = 0;
            alive_neighbor_count = (((arr[iter_r - 1][iter_c - 1] == '*') ? 1 : 0) 
                                  + ((arr[iter_r - 1][iter_c] == '*') ? 1 : 0) 
                                  + ((arr[iter_r - 1][iter_c + 1] == '*') ? 1 : 0)
                                  + ((arr[iter_r][iter_c + 1] == '*') ? 1 : 0)
                                  + ((arr[iter_r + 1][iter_c + 1] == '*') ? 1 : 0)
                                  + ((arr[iter_r + 1][iter_c] == '*') ? 1 : 0)
                                  + ((arr[iter_r + 1][iter_c - 1] == '*') ? 1 : 0)
                                  + ((arr[iter_r][iter_c - 1] == '*') ? 1 : 0));
            if (arr[iter_r][iter_c] == '*') {
                if ((2 == alive_neighbor_count) or (3 == alive_neighbor_count)) {
                    arr_out[iter_r][iter_c] = '*';
                    alive_cells_count++;
                }
                else {
                    arr_out[iter_r][iter_c] = '-';
                }
            }
            else {
                if (3 == alive_neighbor_count) {
                    arr_out[iter_r][iter_c] = '*';
                    alive_cells_count++;
                }
                else {
                    arr_out[iter_r][iter_c] = '-';
                }
            }
            if (arr[iter_r][iter_c] != arr_out[iter_r][iter_c]) {
                swap = true;
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string size_of_arr_str, cells_str;
    std::ifstream fin("in.txt");
    if (fin.is_open()) {
        std::getline(fin, size_of_arr_str);
        std::stringstream stream1(size_of_arr_str);
        unsigned rows = 0; 
        unsigned cols = 0; 
        stream1 >> rows; rows+=2;
        stream1 >> cols; cols+=2;
        char** game_arr = create_two_dim_char_array(rows, cols);
        while (!(fin).eof()) {
            unsigned alive_cell_row = 0, alive_cell_col = 0;
            std::getline(fin, cells_str);
            std::stringstream stream(cells_str);
            stream >> alive_cell_row; ++alive_cell_row;
            stream >> alive_cell_col; ++alive_cell_col;
            game_arr[alive_cell_row][alive_cell_col] = '*';
            alive_cells_count++;
        }
  
        fin.close();
        
        char** game_arr_temp = create_two_dim_char_array(rows, cols);
        while (1) {
            print_two_dim_char_array(game_arr, rows, cols);
            std::cout << "Generation: " << generation_count << "." << "Alive cells: " << alive_cells_count;
            std::cout << std::endl;
          
            swap = false;
            swap_char_arr(game_arr, game_arr_temp, rows, cols);
            copy_two_dim_char_array(game_arr, game_arr_temp, rows, cols);
            generation_count++;

       
            if (alive_cells_count == 0) {
                std::system("cls");
                print_two_dim_char_array(game_arr, rows, cols);
                std::cout << "Generation: " << generation_count << "." << "Alive cells: " << alive_cells_count;
                std::cout << std::endl;
                std::cout << "All cells are dead. Game over";
                break;
            }
            if (swap == false) {
                std::cout << "The world has stagnated. Game over";
                break;
            }
            Sleep(100);
            std::system("cls");
        }
        delete_two_dim_char_array(game_arr, rows, cols);
        delete_two_dim_char_array(game_arr_temp, rows, cols);

    }
    else {
        std::cout << "Не получилось открыть файл!";
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
