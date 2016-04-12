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
// Version 4.1
// 
// !!What's New!!
// Matrix returned its abilities to mutiply and transpose matrices. With
// more promts for the user, it is easier than ever to use Matrix to save
// your time.

#include <iostream>
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
    }
    void initializeMatrix();
    void initializeZeroMatrix ();
    void printMatrix();
    void addMatrices(matrix, matrix, matrix);
    void multiplyMatrices(matrix, matrix, matrix);
    void transposeMatrix();
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
    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < columns; j++) {
            cout << data[i][j];
        }
        cout << "|" << endl;
    }
}

void matrix::addMatrices(matrix K, matrix M, matrix N) {
    for (int i = 0; i < N.rows; i++) {
        for (int j = 0; j < M.columns; j++) {
            K.data[i][j] = N.data[i][j] + M.data[i][j];            
        }
    }
}

void matrix::multiplyMatrices(matrix K, matrix M, matrix N) {
    K.rows = M.rows;
    K.columns = N.columns;    
    K.initializeZeroMatrix();
    for (int i = 0; i < K.rows; i++) {
        for (int j = 0; j < K.columns; j++) {
            for (int k = 0; k < M.columns; k++) {
                K.data[i][j] += M.data[i][k]*N.data[k][j];
            }
        }
    }
}

void matrix::transposeMatrix() {
    matrix T(columns, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            T.data[j][i] = data[i][j];
        }
    }
    T.printMatrix();
}


int main() {
    cout << "Hello user" << endl;
    cout << "Please enter the number of the operation you want to perform: " << endl;
    
    while (true) {        
        int operation;
        cout << "1. Addition" << endl << "2. Multiplication" << endl << "3. Transpose" << endl;
        cin >> operation;
        
        if (operation == 1) {
            int r, c;
            cout << "Now you will be asked to enter two matrices. Note that they must have the same number of rows and columns" << endl;
            cout << "Enter the number of rows : ";
            cin >> r;
            cout << "Enter the number of columns : ";
            cin >> c;
            matrix M(r, c);
            cout << "Enter the elements of the first matrix : " << endl;
            M.initializeMatrix();
            matrix N(r, c);
            cout << "Enter the elements of the second matrix : " << endl;
            N.initializeMatrix();
            matrix K(r, c);
            K.addMatrices(K, M, N);
            K.printMatrix();
        }
        
        else if (operation == 2) {
            cout << "Now you will be asked to enter two matrices. Note that the number of the rows of the second matrix must be equal to the number of the columns of the first matrix" << endl;
            int r, c1, c2;
            cout << "Enter the number of the rows of the first matrix : ";
            cin >> r;
            cout << "Enter the number of the columns of the first matrix : ";
            cin >> c1;
            matrix M(r, c1);
            M.initializeMatrix();
            cout << "Enter the number of the columns of the second matrix : ";
            cin >> c2;
            matrix N(c1, c2);
            N.initializeMatrix();
            matrix K(r, c2);
            K.multiplyMatrices(K, M, N);
            K.printMatrix();
        }
        
        else if (operation == 3) {
            cout << "Now you will be asked to enter one matrix" << endl;
            int r, c;
            cout << "Enter the number of rows : ";
            cin >> r;
            cout << "Enter the number of columns : ";
            cin >> c;
            matrix M(r, c);
            M.initializeMatrix();
            M.transposeMatrix();
        }
        
        else {
            cout << "The number is not valid" << endl;
            
        }
        
        cout << "Please enter the number of the operation you want to perform: " << endl;    
    }
    
    return 0;
    
}

