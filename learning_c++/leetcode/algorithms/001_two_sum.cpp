#include <iostream>
#include <vector>
#include <stdio.h>
#include <chrono>

using namespace std;

vector<int> twoSumV1(vector<int>& nums, int target){
	vector<int> solution_indexes;
	for (int i=0; i < nums.size(); i++){
		for (int j=0; j < nums.size(); j++){
			if ( i != j && (nums[i] + nums[j] == target) ){
				solution_indexes = {i,j};
				return solution_indexes;
			} 
		}
	}
	return solution_indexes;
}


vector<int> twoSumV2(vector<int>& nums, int target){
	vector<int> solution_indexes;
	for (int i=0; i < nums.size(); i++){
		for (int j=0; j < i; j++){
			if (nums[i] + nums[j] == target){
				solution_indexes = {i,j};
				return solution_indexes;
			} 
		}
	}
	return solution_indexes;
}

vector<int> twoSumV3(vector<int>& nums, int target){
	vector<int> solution_indexes;
	for (int i=0; i < nums.size(); i++){
		for (int j=i+1; j < nums.size(); j++){
			if (nums[i] + nums[j] == target){
				solution_indexes = {i,j};
				return solution_indexes;
			} 
		}
	}
	return solution_indexes;
}

vector<int> twoSumV4(vector<int>& nums, int target){
	vector<int> solution_indexes;
	vector<int> nums_copy = nums;
	int n_removed = 0;
	for (int i=0; i < nums.size(); i++){
		for (int j=1; j < nums_copy.size(); j++){
			if (nums_copy[0] + nums_copy[j] == target){
				solution_indexes = {n_removed, j+n_removed};
				return solution_indexes;
			} 
		}
		nums_copy.erase(nums_copy.begin());
		n_removed++;
	}
	return solution_indexes;
}

vector<int> quicksort(vector<int>& vec){ 
// Passing variables by reference saves some memory, fct doesn't create a copy of variable, instead it just uses passed-in var directly (via the reference)
	if (vec.size() == 0){
//		printf("inputted empty vector");
		return vec;	
	}
	else if (vec.size() == 1){
/*
		printf("inputted single element vector:\n");
		for (int n : vec){
			printf("%i ", n);
		}
		printf("\n\n");
*/
		return vec;
	}
	else {
/*
		printf("inputted vector:\n");
		for (int n : vec){
			printf("%i ", n);
		}
		printf("\n");
*/
		int pivot_index;
		if (vec.size() % 2 == 0){
			pivot_index = vec.size()/2;	
		}
		else {
			pivot_index = (vec.size()+1)/2;
		}	
		int pivot = vec[pivot_index];
//		printf("pivot = %i, pivot_index = %i\n", pivot, pivot_index);
		
		for (int i=0; i < pivot_index; i++){
			if (vec[i] >= pivot){
//				printf("vec[%i] = %i >= pivot = %i\n", i, vec[i], pivot);
				bool swap_found = false;
				for (int j=vec.size()-1; j > pivot_index; j--){
					if (vec[j] <= pivot){
//						printf("vec[%i] = %i <= pivot = %i\n", j , vec[j], pivot);

						int temp = vec[i];
						vec[i] = vec[j];
						vec[j] = temp;	

						swap_found = true;

						break;
					}
				} 
				if (swap_found == false){
					vec.insert(vec.end(), vec[i]);
					vec.erase(vec.begin() + i);
					i--;
					pivot_index--;
				}
/*
				printf("after this catch, vec is now:\n");
				for (int n : vec){
				printf("%i ", n);
				}
				printf("\n");
				printf("pivot_index = %i\n", pivot_index);
*/
			}
		}
/*
		printf("after sorting left side:\n");
		for (int n : vec){
			printf("%i ", n);
		}
		printf("\n");
		printf("pivot_index = %i\n", pivot_index);
*/

		for (int i=vec.size()-1; i > pivot_index; i--){
			if (vec[i] <= pivot) {
//				printf("vec[%i] = %i <= pivot = %i\n", i, vec[i], pivot);
				bool swap_found = false;
				for (int j=0; j < pivot_index; j++){
					if (vec[j] >= pivot){
//						printf("vec[%i] = %i >= pivot = %i\n", j , vec[j], pivot);

						int temp { vec[i] };
						vec[i] = vec[j];
						vec[j] = temp;	

						swap_found = true;

						break;
					}
				} 
				if (swap_found == false){
					vec.insert(vec.begin(), vec[i]);
					vec.erase(vec.begin() + i + 1);
					i++;
					pivot_index++;
				}
/*				printf("after this catch, vec is now:\n");
				for (int n : vec){
				printf("%i ", n);
				}
				printf("\n");
				printf("pivot_index = %i\n", pivot_index); 
*/
			} 
		}
		
/*
		printf("after sorting right side:\n");
		for (int n : vec){
			printf("%i ", n);
		}	
		printf("\n");
		printf("pivot_index = %i\n", pivot_index);
*/

		// Vector initialisation requires const_interators since these point to a single value of an aggregate type and cannot change, unlike regular iterators
		// (Produces a " no matching constructor for initialization of 'vector<int>' " error when initialising as first_half(vec.start(), up_to_pivot) since vec.start() is not a const_iterator unless assigned to a const_iterator variable, as is done above)
		vector<int>::const_iterator up_to_pivot = vec.begin() + pivot_index;
		vector<int>::const_iterator vec_start = vec.begin();

		vector<int> first_half(vec_start, up_to_pivot); 
		vector<int> second_half(up_to_pivot + 1, vec.end());

/*
		printf("first_half:\n");
		for (int n : first_half){
			printf("%i ", n);
		}
		printf("\n");

		printf("second_half:\n");
		for (int n : second_half){
			printf("%i ", n);
		}
		printf("\n\n");
*/

		vector<int> sorted_vec;
		for (int n : quicksort(first_half)){
			sorted_vec.push_back(n);
		}
		sorted_vec.push_back(pivot);
		for (int n : quicksort(second_half)){
			sorted_vec.push_back(n);
		}

/*
		printf("sorted vector:\n");
		for (int n : sorted_vec){
			printf("%i ", n);
		}
		printf("\n\n");
*/

		return sorted_vec;
	}
}	

vector<int> twoSumQSBS(vector<int>& nums, int target){ // Quicksort + Binary Search
	return quicksort(nums);
}

int main() {
	// Assign vars
//	vector<int> myNums = {1,3,7,9,11,26,89,1,2991,2,200,1,99,38,9929,12367889,111,50000000}; // answer is [1,9]
//	vector<int> myNums = {5,12,2,8,4,2,7,8,9};
	vector<int> myNums = {2,6,12,13,2,1,9,0,7,56};
//	int myTarget = 5;
	int myTarget = 6;
	vector<int> indexes;
/*
	// V1
	auto main_startV1 = chrono::high_resolution_clock::now();

	indexes = twoSumV1(myNums, myTarget);

	printf("V1 answer: [%i,%i]\n", indexes[0], indexes[1]);

	auto main_endV1 = chrono::high_resolution_clock::now();

	chrono::duration<double, std::milli> elapsed_timeV1 = main_endV1 - main_startV1;
	printf("(V1 time elapsed: %f ms)\n", elapsed_timeV1.count());

	// V2
	auto main_startV2 = chrono::high_resolution_clock::now();

	indexes = twoSumV2(myNums, myTarget);

	printf("V2 answer: [%i,%i]\n", indexes[0], indexes[1]);

	auto main_endV2 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> elapsed_timeV2 = main_endV2 - main_startV2;
	printf("(V2 time elapsed: %f ms)\n", elapsed_timeV2.count());

	// V3
	auto main_startV3 = chrono::high_resolution_clock::now();

	indexes = twoSumV3(myNums, myTarget);

	printf("V3 answer: [%i,%i]\n", indexes[0], indexes[1]);

	auto main_endV3 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> elapsed_timeV3 = main_endV3 - main_startV3;
	printf("(V3 time elapsed: %f ms)\n", elapsed_timeV3.count());

	// V4
	auto main_startV4 = chrono::high_resolution_clock::now();

	indexes = twoSumV4(myNums, myTarget);

	printf("V4 answer: [%i,%i]\n", indexes[0], indexes[1]);

	auto main_endV4 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> elapsed_timeV4 = main_endV4 - main_startV4;
	printf("(V4 time elapsed: %f ms)\n", elapsed_timeV4.count());
*/
	// Quicksort + Binary Search
	auto main_startQSBS = chrono::high_resolution_clock::now();

	indexes = twoSumQSBS(myNums, myTarget);

	printf("QSBS answer: [%i,%i]\n", indexes[0], indexes[1]);

	auto main_endQSBS = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> elapsed_timeQSBS = main_endQSBS - main_startQSBS;
	printf("(QSBS time elapsed: %f ms)\n", elapsed_timeQSBS.count());

	return 0;	
}
