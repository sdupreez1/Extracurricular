#include <stdio.h>
#include <iostream>

// Each LinkedNode has a corresponding value and pointer to the next LinkedNode
struct LinkedNode {
	int val;
	LinkedNode *next;
	LinkedNode() : val(0), next(nullptr) {}
	LinkedNode(int x) : val(x), next(nullptr) {}
	LinkedNode(int x, LinkedNode* next) : val(x), next(next) {}
};

class LinkedList {
public:
	LinkedNode* head;

	LinkedList(){
		head = nullptr; // Initialise empty linked list as a null pointer with no corresponding value
	}
	
	void addNode(int val){

		// `new` dynamically allocates and initializes specified object and returns a pointer to it
		// Added node becomes head node, current head becomes what new node points to
		LinkedNode* newNode = new LinkedNode(val, head); 
				/* (`new` also allocates the OS-managed heap memory [of which there is lots] to vars instead of the [limited] stack
				    memory allocated to the program which static or automatic memory allocation assigns to variables/arrays) */

		/* ?? Does the below make head a copy of newNode or does it copy newNode into head? ?? */
		head = newNode; 
		
		printf("%i added\n\n", head->val);
	}	

	void printList(){
		LinkedNode* temp;
		temp = head;
		while (temp != nullptr){
			if (temp->next != nullptr){
				printf("%i -> ", temp->val);
			}
			else{
				printf("%i\n", temp->val);
			}
			temp = temp->next;
		}	
	}

	~LinkedList() {
		LinkedNode* temp;
		while (head){
				temp = head;
				head = head->next;
				delete temp; 	   // `delete` only destroys data pointed to, not the pointer itself
		}
	}
};

LinkedNode* addTwoNumbers(LinkedNode* l1, LinkedNode* l2){
	int digit_sum;

	LinkedNode* current_l1_node;
	current_l1_node = l1;

	LinkedNode* current_l2_node;
	current_l2_node = l2;
	
	LinkedNode* full_sum_list = nullptr;

	int sum_counter{ 0 };
	while (current_l1_node != nullptr && current_l2_node != nullptr){
		printf("attempting to sum digits at position %i:\n", sum_counter);	
		printf("[digit %i] num1 = %i, num2 = %i\n", sum_counter, current_l1_node->val, current_l2_node->val);
		digit_sum = current_l1_node->val + current_l2_node->val;
		printf("digit_sum = %i\n", digit_sum);
		
		printf("creating new LinkedNode to become updated list\n");
		LinkedNode* newNode = new LinkedNode(digit_sum, full_sum_list);
		
		printf("updating full_sum_list");
		full_sum_list = newNode;
		printf("full_sum_list first node = %i\n", full_sum_list->val);

		printf("moving current num1 and num2 nodes forward\n");
		current_l1_node = current_l1_node->next;
		current_l2_node = current_l2_node->next;
		printf("pointers successfully moved\n");

		printf("initialising vars for checks of whether num1 or num2 are nullptrs");
		int l1_null_check{ 0 };
		int l2_null_check{ 0 };

		if (current_l1_node == nullptr){
			l1_null_check = 1;
		}
		if (current_l2_node == nullptr){
			l2_null_check = 2;
		}
		printf("value of l1_null_check = %i\n", l1_null_check);
		printf("value of l2_null_check = %i\n", l2_null_check);

		switch (l1_null_check + l2_null_check){
			case 0: // l1 and l2 are non-nullptrs
				printf("updated num1 val = %i, updated num2 val = %i\n\n", current_l1_node->val, current_l2_node->val);
				break;
			case 1: // only l1 is nullptr
				printf("updated num1 is nullptr, updated num2 val = %i\n\n", current_l2_node->val);
				break;
			case 2: // only l2 is nullptr
				printf("updated num1 val = %i, updated num2 is nullptr\n\n", current_l1_node->val);
				break;
			case 3: // both l1 and l2 are nullptrs
				printf("both updated nums are nullptrs\n\n");
				break;
		}

		sum_counter++;
	}

	// Either l1 or l2 will run out first so while loop for the list that ran out first will not run
	// These loops add the remaining digits from the larger number
	int l1_counter { 0 };	
	while (current_l1_node != nullptr){ 
		printf("attatching extra digits [count: %i] from l1 to answer\n", l1_counter);
		printf("current num1 val = %i\n", current_l1_node->val);

		printf("creating new LinkedNode to become updated list\n");
		LinkedNode* newNode = new LinkedNode(current_l1_node->val, full_sum_list);

		printf("updating full_sum_list'n");
		full_sum_list = newNode;
		printf("new first full_sum_list value = %i\n", full_sum_list->val);
		
		printf("moving current num1 node forward\n");
		current_l1_node = current_l1_node->next;
		printf("updated num1 val = %i\n\n", current_l1_node->val);

		l1_counter++;
	}

	int l2_counter { 0 };
	while (current_l2_node != nullptr){
		printf("attatching extra digits [count: %i] from l2 to answer\n", l2_counter);
		printf("current num2 val = %i\n", current_l2_node->val);

		printf("creating new LinkedNode to become updated list\n");
		LinkedNode* newNode = new LinkedNode(current_l2_node->val, full_sum_list);

		printf("updating full_sum_list'n");
		full_sum_list = newNode;
		printf("new first full_sum_list value = %i\n", full_sum_list->val);

		printf("moving current num2 node forward\n");
		current_l2_node = current_l2_node->next;
		printf("updated num2 val = %i\n\n", current_l2_node->val);

		l2_counter++;
	}	
	
	return full_sum_list;
}

int main() {
	LinkedList num1;
	LinkedList num2;

	printf("attempting to initialise num1 as 1->3->2 (representing 231):\n");
	num1.addNode(2);
	num1.addNode(3);
	num1.addNode(1);
	
	printf("num1 successfully initialised as:\n)");
	num1.printList();
	printf("\n");

	printf("attempting to initialise num2 as 7->8->9 (representing 987):\n");
	num2.addNode(9);
	num2.addNode(8);
	num2.addNode(7);
	
	printf("num2 successfully initialised as:\n");
	num2.printList();
	printf("\n");

	printf("initialising answer as sum of num1 and num2\n");
	LinkedNode* answer { addTwoNumbers(num1.head, num2.head) };

	printf("attempting to print answer:\n");
	LinkedNode* temp;
	temp = answer;
	while (temp != nullptr){
		if (temp->next != nullptr){
			printf("%i -> ", temp->val);
		}
		else{
			printf("%i\n", temp->val);
		}
		temp = temp->next;
	}	

 
	return 0;
}
