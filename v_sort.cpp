#include<iostream>
#include<limits>
#include<string>
#include<iomanip>
#include<vector>

#define format_width 20

using namespace std;

void vector_input(vector<int>& a) {
//Takes in user input and creates an vector.
	int temp;
	string stop = "q";
	string input;
	string request = "Enter an integer or " + stop + " to stop: ";
	cout << request;
	while (input != stop) {
		cin >> temp;
		if (cin.fail()) {
			cin.clear();
			getline(cin, input);
			if (input != stop) {
				cout << "That's not an integer. Try again." << endl;
				cout << request;
			}
		} else {
			a.push_back(temp);
			cout << setw(request.size()) << "";
		}
	}
}

void set_vector(vector<int>& a, vector<int>& b) {
//Sets the first vector to the second.
	for (int i = 0, size = a.size(); i < size; ++i) {
		a[i] = b[i];
	}
	for (int i = a.size(), size = b.size(); i < b.size(); ++i) {
		a.push_back(b[i]);
	}
}	

void print_vector(vector<int>& a) {
//Prints input vector to console.
	cout << "[ " << a[0];
	for (int i = 1, size = a.size(); i < size; ++i) {
	
		cout << ", " << a[i];
	}
	cout << " ]" << endl;
}

void insert_sort(vector<int>& a) {
//Insertion sorts the input vector.
	for (int i = 1, size = a.size(); i < size; ++i) {
	//There's no need to check the first element,
	//so we start at the second.
		int key = a[i];
		int j = i -1;
		while (j >= 0 && a[j] > key) {
		//Checks each element in the vector backwards.
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

void merge(vector<int>& a, int p, int q, int r) {
//Merges two sub-arrays into one in sorted order.
//Assumes that the sub-arrays are already sorted.
	int left_length = q - p + 1;
	int right_length = r - q;
	int left[left_length + 1];
	int right[right_length + 1];
	
	//Setting our left and right arrays to the appropriate
	//values from our main vector.
	for (int i = 0; i < left_length; ++i) {
		left[i] = a[p + i];
	}

	for (int i = 0; i < right_length; ++i) {
		right[i] = a[q + i + 1];
	}
	
	//Since infinity is unobtainble using integers, 
	//we use the highest possible value for a sentinel value.
	//(This is why we added one to the length of our arrays).
	left[left_length] = numeric_limits<int>::max();
	right[right_length] = numeric_limits<int>::max();
	
	int x = 0;
	int y = 0;

	for (int i = p; i <= r; i++) {
	//Checking our arrays against each other and putting
	//the smaller integer first in the main vector.
		if (left[x] <= right[y]) {
			a[i] = left[x];
			++x;
		} else {
			a[i] = right[y];
			++y;
		}
	}
}

void merge_sort(vector<int>& a, int p, int r) {
//Recursively makes one integer sub-sections of a vector
//(the largest possible sub-section that is guaranteed to be sorted)
//and merge sorts them using our merge function
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

void bubble_sort(vector<int>& a) {
	for (int i = 0, size = a.size(); i < size - 1; ++i) {
		for (int j = a.size() - 1; j > i; --j) {
			if (a[j] < a[j - 1]) {
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}

int main() {
//Creates one base vector and three vectors to be sorted: 
//one by insertion, one by merging, and one by bubble
	vector<int> base_vector;
	vector<int> insert_vector;
	vector<int> merge_vector;
	vector<int> bubble_vector;

//Defines the base vector with user input.
	vector_input(base_vector);

//Repeats the input vector to user.
	cout << setw(format_width) << endl << endl << "Your array:  ";
	print_vector(base_vector);

//Then, sets merge and bubble vector to insert vector and sorts all three.
	set_vector(insert_vector, base_vector);
	set_vector(merge_vector, base_vector);
	set_vector(bubble_vector, base_vector);

	insert_sort(insert_vector);
	merge_sort(merge_vector, 0, merge_vector.size() - 1);
	bubble_sort(bubble_vector);

//Outputs sorted vectors to user.
	cout << endl << setw(format_width) << "Insertion sorted:  ";
	print_vector(insert_vector);

	cout << endl << setw(format_width) << "Merge sorted:  ";
	print_vector(merge_vector);

	cout << endl << setw(format_width) << "Bubble sorted:  ";
	print_vector(bubble_vector);
	
//Pauses to read output.
	cin.ignore();
	cin.get();

//Program termination.
	return 0;
}


