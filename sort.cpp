#include<iostream>
#include<limits>
#include<string>
#include<iomanip>

#define array_length 8
#define format_width 30

using namespace std;

void array_input(int a[]) {
//Takes in user input and creates an array.
	cout << "Please enter " << array_length << " integers to be put into an array: ";
	for (int i = 0; i < array_length; ++i) {
		cin >> a[i];
		while (cin.fail()) {
		//Error-handling if input is not an integer.
		//Dumps garbage input to string and requests again.
			cin.clear();
			string invalidInput;
			getline(cin, invalidInput);
			cout << "That's not quite right. Try again! ";
			cin >> a[i];
		}
	}
}

void set_array(int a[], int b[]) {
//Sets the first array to the second.
	for (int i = 0; i <array_length; ++i) {
		a[i] = b[i];
	}
}	

void print_array(int (&a)[array_length]) {
//Prints input array to console.
	for (int i = 0; i < array_length; ++i) {
	
		cout << a[i] << " ";
	}
	cout << endl;
}

void insert_sort(int a[]) {
//Insertion sorts the input array.
	for (int i = 1; i < array_length; ++i) {
	//There's no need to check the first element,
	//so we start at the second.
		int key = a[i];
		int j = i -1;
		while (j >= 0 && a[j] > key) {
		//Checks each element in the array backwards.
		//Once we find a smaller element, we stop.
			//If the previous element is larger,
			//we set the current element to it.
			a[j + 1] = a[j];
			--j;
		}
		//If the previous element is smaller, we set
		//the current element to our original integer.
		a[j + 1] = key;
	}
}

void merge(int a[], int p, int q, int r) {
//Merges two arrays into one in sorted order.
//Assumes that the arrays are already sorted.
	int left_length = q - p + 1;
	int right_length = r - q;
	int left[left_length + 1];
	int right[right_length + 1];
	
	//Setting our left and right arrays to the appropriate
	//values from our main array.
	for (int i = 0; i < left_length; ++i) {
		left[i] = a[p + i - 1];
	}

	for (int i = 0; i < right_length; ++i) {
		right[i] = a[q + i];
	}
	
	//Since infinity is unobtainble using integers, 
	//we use the highest possible value for a sentinel value.
	//(This is why we added one to the length of our arrays).
	left[left_length] = numeric_limits<int>::max();
	right[right_length] = numeric_limits<int>::max();
	
	int x = 0;
	int y = 0;

	for (int i = p - 1; i < r; i++) {
	//Checking our arrays against each other and putting
	//the smaller integer first in the main array.
		if (left[x] <= right[y]) {
			a[i] = left[x];
			++x;
		} else {
			a[i] = right[y];
			++y;
		}
	}
}

void merge_sort(int a[], int p, int r) {
//Recursively makes one integer sub-sections of an array
//(the largest possible sub-section that is guaranteed to be sorted)
//and merge sorts them using our merge function
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

int main() {
//Creates two arrays to be sorted: 
//one by insertion and one by merging
	int insert_array[array_length], merge_array[array_length];

//Defines the arrays with user input.
	array_input(insert_array);

//Repeats the input array to user.
	cout << setw(format_width) << "Your array: ";
	print_array(insert_array);

//Then, sets merge array to insert array and sorts both.
	set_array(merge_array, insert_array);
	insert_sort(insert_array);
	merge_sort(merge_array, 1, array_length);

//Outputs sorted arrays to user.
	cout << endl << setw(format_width) << "Insertion sorted: ";
	print_array(insert_array);

	cout << endl << setw(format_width) << "Merge sorted: ";
	print_array(merge_array);
	
//Pauses to read output.
	cin.ignore();
	cin.get();

//Program termination.
	return 0;
}

