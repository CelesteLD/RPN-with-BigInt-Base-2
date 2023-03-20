// MAIN

/**
 * @file main.cc
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Programa cliente
 *  ** Compilar utilizando el comando: make
 *  ** Ejecutar utilizando el comando: make run
 *  ** Limpiar utilizando el comando: make clean
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <fstream>
#include <stack>

#include "../include/bigint.h"

std::vector<std::string> readData(std::string filename);
int getBase(std::string line);

template<size_t Base>
void processData(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string data);

template<size_t Base>
int getIndexOfKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key);

template<size_t Base>
bool checkKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key);

template <size_t Base>
void printBoard(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::ofstream &fileout);

int main(int argc, char const *argv[]) {
    
    const int baseHex = 16;
    const int baseDecimal = 10;
    const int baseOctal = 8;
    const int baseBinary = 2;

    std::vector<std::string> data = readData(argv[1]);
    int base = getBase(data[0]);

    switch (base) {
        
        case 2:
            {
                std::vector<std::pair<std::string, BigInt<baseBinary>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseBinary>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseBinary>(board, fileout);
                fileout.close();
                break;
            }
        case 8:
            {
                std::vector<std::pair<std::string, BigInt<baseOctal>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseOctal>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseOctal>(board, fileout);
                fileout.close();
                break;
            }
        
        case 10:
            {
                std::vector<std::pair<std::string, BigInt<baseDecimal>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseDecimal>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseDecimal>(board, fileout);
                fileout.close();
                
                break;
            }

        case 16:
            {
                std::vector<std::pair<std::string, BigInt<baseHex>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseHex>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseHex>(board, fileout);
                fileout.close();
                break;
            }
        default:
            std::cout << "Base not supported" << std::endl;
            break;
    }   

    return 0;
}

std::vector<std::string> readData(std::string filename) {
    std::ifstream filein(filename);
    std::vector<std::string> data;
    std::string line;
    while (std::getline(filein, line)) {
        data.push_back(line);
    }
    return data;
}

int getBase(std::string line) {
    line.erase(0, line.find("=") + 1);
    // Delete spaces
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    return std::stoi(line);
}

template<size_t Base>
void processData(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string data) {

    std::string key;
    std::string value;

    std::stack<std::string> stack;

    // Si la línea contiene un = es una asignación
    if(data.find("=") != std::string::npos) {

        key = data.substr(0, data.find("=") - 1);
        value = data.substr(data.find("=") + 2, data.size() - 2);
        //Eliminar la ultima posición de value
        value.pop_back();
        // // Imprimir valores
        // std::cout << "Key: " << key << std::endl;
        // std::cout << "Value: " << value << std::endl;

        BigInt<Base> num(value);
        board.push_back(std::make_pair(key, num));

    } else if(data.find("?") != std::string::npos) {

        key = data.substr(0, data.find("?") - 1);
        // // // Imprimir valores
        // std::cout << "Key: " << key << std::endl;

        std::vector<std::string> tokens;
        std::istringstream iss(data.substr(data.find("?") + 1));
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "+") {
                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num1 = value1;
                stack.pop();

                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num2 = value2;
                stack.pop();

                BigInt<2> result = num2 + num1;


                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);

            } else if (tokens[i] == "-") {

                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num1 = value1;
                stack.pop();

                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num2 = value2;
                stack.pop();

                BigInt<2> result = num2 - num1;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);

            } else if (tokens[i] == "*") {

                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num1 = value1;
                stack.pop();

                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num2 = value2;
                stack.pop();

                BigInt<2> result = num2 * num1;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);

            } else if (tokens[i] == "/") {

                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num1 = value1;
                stack.pop();

                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                BigInt<2> num2 = value2;
                stack.pop();

                BigInt<2> result = num2 / num1;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);

            } else if (tokens[i] == "%") {
                    
                    BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                    BigInt<2> num1 = value1;
                    stack.pop();
    
                    BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                    BigInt<2> num2 = value2;
                    stack.pop();
    
                    BigInt<2> result = num2 % num1;
    
                    if (checkKey(board, key)) {
                        board[getIndexOfKey(board, key)].second = result;
                    } else {
                        board.push_back(std::make_pair(key, result));
                    }
    
                    stack.push(board[getIndexOfKey(board, key)].first);

            } else {
                stack.push(tokens[i]);
            }
        }
    } 
}

template<size_t Base>
int getIndexOfKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i].first == key) {
            return i;
        }
    }
    return -1;
}

template <size_t Base>
bool checkKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i].first == key) {
            return true;
        }
    }
    return false;
}

template <size_t Base>
void printBoard(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::ofstream &fileout) {
    for (int i = 0; i < board.size(); i++) {
        fileout << board[i].first << " => " << board[i].second << std::endl;
    }
}

