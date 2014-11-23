/*
 * Utils.h
 *
 *  Created on: Nov 22, 2014
 *      Author: adam
 */

#ifndef INTERVIEW_UTILS_H_
#define INTERVIEW_UTILS_H_

#include <functional>
#include <iostream>
#include <vector>

struct Utils {

	template<class T>
	static T** create2DArray(int N, int M) {

		T** mat = new T*[N];
		for(int i = 0; i < N; ++i) {
			mat[i] = new T[M];
		}
		return mat;
	}

	template<class T>
	static void delete2DArray(T** mat, int N) {
		for(int i = 0; i < N; ++i) {
			delete[] mat[i];
		}
		delete[] mat;
	}

	template<class T>
	static void fill2DArray(T** mat, int N, int M, std::function<T(int, int)> fun) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				mat[i][j] = fun(i, j);
			}
		}
	}

	template<class T>
	static void printVec(const std::vector<T>& vec, std::string space = " ") {
		for(auto elem : vec) {
			std::cout << elem << space;
		}
		std::cout << std::endl;
	}

	template<class T>
	static void printArray(T* arr, int N, std::string space = " ") {
		for(int i = 0; i < N; ++i) {
			std::cout << arr[i] << space;
		}
		std::cout << std::endl;
	}

	template<class T>
	static void print2DArray(T** arr, int N, int M, std::string space = " ") {
		for(int i = 0; i < N; ++i) {
			printArray(arr[i], M, space);
		}
	}

	template<class T>
	static bool arrayEqual(T* a1, T* a2, int N) {
		for(int i = 0; i < N; ++i) {
			if(a1[i] != a2[i]) {
				return false;
			}
		}
		return true;
	}

	template<class T>
	static bool array2DEqual(T** a1, T** a2, int N, int M) {
		for(int i = 0; i < N; ++i) {
			if(!arrayEqual(a1[i], a2[i], M)) {
				return false;
			}
		}
		return true;
	}

};

#endif /* INTERVIEW_UTILS_H_ */