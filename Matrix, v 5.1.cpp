// !!!NOTE!!!
// All rights reserved. No part of this program may be reproduced,
// distributed, or transmitted in any form or by any means, including
// photocopying, recording, or other electronic or mechanical methods,
// without the prior written permission of the publishers.
// Copyright © 2016 by Gagik Papikyan and Tigran Sedrakyan.
//
// !!Description!!
// Matrix is an ultimate tool for matrix arithmetics. The goal of this
// program is to save your time.
//
// Version 5.1
//
// !!What's New!!
// A quick update is here to make Matrix more powerful. Have you ever 
// had an concerns about how Matrix printed matrices that included
// negative elements? It's all over, the problem is fixed. Enjoy a
// brand new version of this tool and wait a new update very soon.

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
    void addMatrices(matrix);
    void scalarMultiplication(int);
    void multiplyMatrices(matrix);
    void powerMatrix(int);
    void transposeMatrix();
    //void refMatrix();
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
            int temp = data[i][j];               // what if we write data[j][i], so that code checks column by column rather than row by row
            if (maxElement[j] <= 0) {
                if (temp < 0 && temp < maxElement[j]) {
                    maxElement[j] = temp;
                }
                else if (temp > 0 && temp*-1 < maxElement[j]) {
                    maxElement[j] = temp;
                }
            }
            else if (maxElement[j] >= 0) {
                if (temp > 0 && temp > maxElement[j]) {
                    maxElement[j] = temp;
                } 
                else if (temp < 0 && temp*-1 > maxElement[j]) {
                    maxElement[j] = temp;
                }
            }
        }
    }
    for (int j = 0; j < columns; j++) {
        int temp = maxElement[j];
        if (temp == 0) {
            m[j]++;
        }
        else if (temp < 0) {
            temp *= -1;
        }
        while (temp > 0) {
            m[j]++;
            temp /= 10;
        }
        if (maxElement[j] < 0) {
            m[j]++;
        }
    }
    for (int j = 0; j < columns; j++) {
        cout << j << "th column's maxElement is " << maxElement[j] << ", which has " << m[j] << " digits" << endl;
    }
    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < columns; j++) {
            int elementDigit = 0;
            int temp = data[i][j];
            if (temp == 0) {
                elementDigit++;
            }
            if (temp < 0) {
                temp *= -1;
            }
            while (temp > 0) {
                elementDigit++;
                temp /= 10;
            }
            if (data[i][j] < 0) {
                elementDigit++;
            }
            int s = m[j] - elementDigit + 1;
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

void matrix::scalarMultiplication(int c) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] *= c;
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

void matrix::powerMatrix(int p) {
    if (rows == columns) {
        matrix Temp(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                Temp.data[i][j] = data[i][j];
            }
        }
        for (int i = 0; i < p-1; i++) {
            this->multiplyMatrices(Temp);
        }
    }
    else {
        cout << "Current matrix cannot be multiplied by itself" << endl;
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

/*
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
*/

int main() {
    cout << "Hello user" << endl;
    cout << "Please enter the matrix you want to perform operations on" << endl;
    int r, c;
    cout << "Enter the number of rows : ";
    cin >> r;
    cout << "Enter the number of columns : ";
    cin >> c;
    matrix M(r, c);
    M.initializeMatrix();
    
    while (true) {
        string answer = " ";
        int operation;

        cout << "Please enter the number of the operation you want to perform: " << endl;
    
        cout << "1. Addition" << endl << "2. Scalar multiplication" << endl << "3. Multiplication" << endl << "4. Power of a matrix" << endl << "5. Transpose" << endl << "6. Reduce to row echelon form" << endl;
        cin >> operation;
        if (operation == 1) {
            matrix N(r, c);
            cout << "Enter the elements of the second matrix : " << endl;
            N.initializeMatrix();
            M.addMatrices(N);
            M.printMatrix();
        }
        else if (operation == 2) {
            int c;
            cout << "Enter the scalar : ";
            cin >> c;
            M.scalarMultiplication(c);
            M.printMatrix();
        }
        else if (operation == 3) {
            cout << "Now you will be asked to enter two matrices. Note that the number of the rows of the second matrix must be equal to the number of the columns of the first matrix" << endl;
            int c2;
            cout << "Enter the number of the columns of the second matrix : ";
            cin >> c2;
            matrix N(c, c2);
            N.initializeMatrix();
            M.multiplyMatrices(N);
            M.printMatrix();
        }
        else if (operation == 4) {
            int p;
            cout << "Enter the exponent : ";
            cin >> p;
            M.powerMatrix(p);
            M.printMatrix();
        }
        else if (operation == 5) {
            M.transposeMatrix();
            M.printMatrix();
        }
        else if (operation == 6) {
            /*
            M.refMatrix();
            M.printMatrix();
            */
            cout << "This feature will be available in the nearest future" << endl;
        }
        else {
            cout << "The number is not valid" << endl;
            }
        
        while(answer != "yes" or "no") {
            cout << "Do you wish to perform more operations on the current matrix? : ";
            cin >> answer;
            
            if (answer == "yes") {
                break;
            }
            else if (answer == "no") {
                cout << "Thanks for using Matrix!!!";
                break;
            }
            else {
                cout << "Command not recognized. Try entering yes or no" << endl;
            }
        }
        if (answer == "no") {
                break;
        }
    }
    return 0;
}