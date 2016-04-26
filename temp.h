// !!!NOTE!!!
// All rights reserved. No part of this publication may be reproduced,
// distributed, or transmitted in any form or by any means, including
// photocopying, recording, or other electronic or mechanical methods,
// without the prior written permission of the publishers.
// Copyright © 2016 by Gagik Papikyan and Tigran Sedrakyan.
//
// !!Description!!
// Matrix is an ultimate tool for matrix arithmetics. The goal of this
// program is to save your time.
//
// Version 4.3
//
// !!What's New!!
// Another major update has given Matrix the ability to serve you better.
// Now you can perform as many operations on the initial matix you have
// entered as you want.

#include <iostream>
#include <string>
using namespace std;

class matrix {
    int rows, columns;
    int **data;

    public:
    matrix (int r, int c) {
        rows = r;
        columns = c;
        data = new int*[r];
        for (int i = 0; i < r; i++) {
            data[i] = new int[c];
        }
        initializeZeroMatrix();
    }
    void initializeMatrix();
    void initializeZeroMatrix ();
    void printMatrix();
    void printResMatrix();
    void addMatrices(matrix);
    void multiplyMatrices(matrix);
    void transposeMatrix();
    void refMatrix();
};

void matrix::initializeMatrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> data[i][j];
        }
    }
}

void matrix::initializeZeroMatrix () {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] = 0;
        }
    }
}

void matrix::printMatrix() {
    cout << "Here is the matrix" << endl;
    int maxElement[columns] = {0}, m[columns] = {0};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (maxElement[j] < data[i][j]) {
                maxElement[j] = data[i][j];
            }
        }
    }
    for (int j = 0; j < columns; j++) {
        int temp = maxElement[j];
        if (temp > 0) {
            while (temp > 0) {
            m[j]++;
            temp /= 10;
            }
        }
        else {
            m[j]++;
        }
    }
    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < columns; j++) {
        int space = 0;
        int temp = data[i][j];
        if (temp > 0) {
            while (temp > 0) {
                space++;
                temp /= 10;
            }
        }
        else if (temp == 0) {
            space++;
        }
        int s = m[j] - space + 1;
        while (s > 0) {
            cout << ' ';
            s--;
        }
        cout << data[i][j];
        }
    cout << " |" << endl;
    }
}

void matrix::addMatrices(matrix N) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] += N.data[i][j];
        }
    }
}

void matrix::multiplyMatrices(matrix N) {
    matrix Temp(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Temp.data[i][j] = data[i][j];
        }
    }
    int temp = columns;
    columns = N.columns;
    for (int i = 0; i < temp; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] = 0;
            for (int k = 0; k < temp; k++) {
                data[i][j] += Temp.data[i][k]*N.data[k][j];
            }
        }
    }
}

void matrix::transposeMatrix() {
    matrix Temp(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Temp.data[i][j] = data[i][j];
        }
    }
    int temp = rows;
    rows = columns;
    columns = temp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[j][i] = Temp.data[i][j];
        }
    }
}

void matrix::refMatrix() {
    int rRow = 0, way = 0, temp;
    for (int i = 0; i < rows; i++) {
        if (data[i][0] == 1) {
            way = 1;
            rRow = i;
            break;
        }
    }
    if (way == 1) {
        for (int i = 0; i < rows; i++) {
            temp = data[i][0];
            if (i != rRow) {
                for (int j = 0; j < columns; j++) {
                    data[i][j] -= temp*data[rRow][j];
                }
            }
        }
    }
    else {
        for (int i = 0; i < rows; i++) {
            if (data[i][0] != 0) {
                rRow = i;
                break;
            }
        }
        for (int j = 0; j < columns; j++) {
            data[rRow][j] /= data[rRow][0];
        }
        refMatrix();
    }
}

int main() {
    string answer;
    
    cout << "Hello user" << endl;
    cout << "Please enter the matrix you want to perform operations on" << endl;
    int r, c;
    cout << "Enter the number of rows : ";
    cin >> r;
    cout << "Enter the number of columns : ";
    cin >> c;
    matrix M(r, c);
    M.initializeMatrix();
    
    Loop: do {

        cout << "Please enter the number of the operation you want to perform: " << endl;
    
        int operation;
        cout << "1. Addition" << endl << "2. Multiplication" << endl << "3. Transpose" << endl << "4. Reduce to row echelon form" << endl;
        cin >> operation;
        if (operation == 1) {
            matrix N(r, c);
            cout << "Enter the elements of the second matrix : " << endl;
            N.initializeMatrix();
            M.addMatrices(N);
            M.printMatrix();
        }
        else if (operation == 2) {
            cout << "Now you will be asked to enter two matrices. Note that the number of the rows of the second matrix must be equal to the number of the columns of the first matrix" << endl;
            int c2;
            cout << "Enter the number of the columns of the second matrix : ";
            cin >> c2;
            matrix N(c, c2);
            N.initializeMatrix();
            M.multiplyMatrices(N);
            M.printMatrix();
        }
        else if (operation == 3) {
            M.transposeMatrix();
            M.printMatrix();
        }
        else if (operation == 4) {
            M.refMatrix();
            M.printMatrix();
        }
        else {
            cout << "The number is not valid" << endl;
            }
        
        Ask: do {    
            cout << "Do you wish to perform more operations one the current matrix? : ";
            cin >> answer;
            
            if (answer == "yes") {
                goto Loop;
            }
            else if (answer == "no") {
                cout << "Thanks for using Matrix!!!";
                break;
            }
            else {
                cout << "Command not recognized. Try entering yes or no" << endl;
                goto Ask;
            }
        }while (true);
    }while (answer != "no");
    return 0;
}

