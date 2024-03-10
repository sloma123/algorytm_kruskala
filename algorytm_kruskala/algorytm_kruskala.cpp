#include <iostream>
#include <cstdlib>
using namespace std;
const int ARR_MAX = 100;
const int TREE_MAX = 100;

struct Line {
	int begin_point = -2;
	int end_point = -2;
	int weight = -2;
	//int tree_num = -2;
	Line* Next;
};

void welcome();
void menu();
Line* input_head();
Line* create_line(Line*);
void add_line(Line*);
Line* sort(Line* line, const int);
void create_trees(Line*, const int);
void merge_trees(Line*, int[TREE_MAX][ARR_MAX], int[ARR_MAX], int, int);
void compare_trees(const Line*, Line*, int[TREE_MAX][ARR_MAX], int&, int[ARR_MAX]);
void add_point(Line*, int[TREE_MAX][ARR_MAX], int[ARR_MAX], int, bool);
int counter(Line*);
void delete_tree(int[TREE_MAX][ARR_MAX], int[ARR_MAX], int, int, int, int, int&);
void print_trees(Line*, int[TREE_MAX][ARR_MAX], int[ARR_MAX], int);

int main() {
	welcome();
	menu();
}

void welcome() {
	cout <<
		R"(
 _  __               _         _ _              
| |/ /_ __ _   _ ___| | ____ _| ( )___          
| ' /| '__| | | / __| |/ / _` | |// __|         
| . \| |  | |_| \__ \   < (_| | | \__ \         
|_|\_\_|   \__,_|___/_|\_\__,_|_| |___/         
       _                  _ _   _               
  __ _| | __ _  ___  _ __(_) |_| |__  _ __ ___  
 / _` | |/ _` |/ _ \| '__| | __| '_ \| '_ ` _ \ 
| (_| | | (_| | (_) | |  | | |_| | | | | | | | |
 \__,_|_|\__, |\___/|_|  |_|\__|_| |_|_| |_| |_|
         |___/                                  
)";
	system("pause");
	system("CLS");
}

void menu() {
	Line* head = input_head();
	add_line(head);
	int x = counter(head);
	head = sort(head, x);
	Line* i = new Line();
	i = head;
	while (i != NULL) {
		cout << i->weight << endl;
		i = i->Next;
	}cout << endl;
	cout << endl;
	create_trees(head, x);
}

void add_line(Line* line)
{
	cout << "Do you want to add another line?\nYes- press 1\nNo- press 2 \n";
	int answer;
	cin >> answer;
	if (answer == 1) {
		line = create_line(line);
		add_line(line);
	}
	else if (answer == 2) {
		line->Next = NULL;

	}
	else add_line(line);
}

Line* input_head() {
	Line* head = new Line();
	cout << "Input the first line: ";
	cout << "\nInput beginning point: ";
	cin >> head->begin_point;
	cout << "\nInput ending point: ";
	cin >> head->end_point;
	cout << "\nInput weight of the line: ";
	cin >> head->weight;
	return head;
}

Line* create_line(Line* line) {
	Line* new_line = new Line();
	cout << "\nInput the next line: ";
	cout << "\nInput beginning point: ";
	cin >> new_line->begin_point;
	cout << "\nInput ending point: ";
	cin >> new_line->end_point;
	cout << "\nInput weight of the line: ";
	cin >> new_line->weight;
	line->Next = new_line;
	return new_line;
}

int counter(Line* line) {

	int counter = 0;
	while (line != NULL) {
		counter++;
		line = line->Next;
	} //liczy ile jest linii w liście jednokierunkowej
	return counter;
}

Line* sort(Line* line, const int counter) {

	Line* h = line;
	Line* head = line;
	Line* ptr = line;

	int i, j, swapped;

	for (i = 0; i <= counter; i++) {
		h = head;
		swapped = 0;

		for (j = 0; j < counter - i - 1; j++) {
			Line* p1 = h;
			Line* p2 = p1->Next;

			if (p1->weight > p2->weight) {  // zamienia linie miejscami

				Line* buff = p2->Next;
				p2->Next = p1;
				p1->Next = buff;
				h = p2;
				swapped = 1;
			}
			if (j == 0) {
				head = h;
				ptr = h;
			}
			else
			{
				ptr->Next = h;
				ptr = ptr->Next;
			}
			h = h->Next;
		}
		if (swapped == 0)
			break;
	}
	return head; //zwraca linie z najmniejsza waga
}

void create_trees(Line* head, const int counter) {
	int tree_num = 0;
	int sum = 0;
	//head->tree_num = tree_num;
	Line* current_line = new Line();
	current_line = head->Next;
	int trees_arr[TREE_MAX][ARR_MAX];
	for (int a = 0; a < TREE_MAX; a++) {
		for (int b = 0; b < ARR_MAX; b++) {
			trees_arr[a][b] = -5;
		}
	}//tablica[numer drzewa][punkty w drzewie]
	int points_count[ARR_MAX];//licznik ilosci punktów w drzewie points_count[drzewo]=aktualna ilosc punktow
	for (int c = 0; c < ARR_MAX; c++) {
		points_count[c] = -5;
	}
	trees_arr[tree_num][0] = head->begin_point;
	trees_arr[tree_num][1] = head->end_point;//drzewo nr 0, pierwsze dwa elementy to punkty heada
	points_count[tree_num] = 2;//1 i 2
	sum += head->weight;
	for (int i = 1; i < counter; i++) {
		compare_trees(head, current_line, trees_arr, tree_num, points_count);
		current_line = current_line->Next;
	}
	for (int i = 0; i < points_count[0]; i++) {
		cout << trees_arr[0][i] << " ";
	}
	print_trees(head, trees_arr, points_count, counter);
}

void compare_trees(const Line* head, Line* current_line, int trees_arr[TREE_MAX][ARR_MAX], int& tree_num, int points_count[ARR_MAX]) {
	//begin
	bool added = false;
	bool is_begin = false; //przekazuje czy punkt początkowy jest w tablicy czy nie
	bool which_point = false;
	for (int i = 0; i <= tree_num; i++) {
		for (int j = 0; j < points_count[i]; j++) {
			if (current_line->begin_point == trees_arr[i][j]) {
				//current_line->tree_num = i;
				added = true;
				is_begin = true;
				int a = is_point_merging(current_line, trees_arr, tree_num, points_count, is_begin);
				if (a == i) {
					;
				}
				else if (a == -1) {
					add_point(current_line, trees_arr, points_count, i, which_point);//dodanie do drzewa
				}
				else {
					merge_trees(current_line, trees_arr, points_count, a, i);
				}
				//sprawdzenie czy punkt łączy dwa drzewa
				//tak-merge_trees, nie- dodanie do drzewa

			}
		}
	}
	//end
	if (added == false) {
		for (int i = 0; i <= tree_num; i++) {
			for (int j = 0; j < points_count[i]; j++) {
				if (current_line->end_point == trees_arr[i][j]) {
					//current_line->tree_num = i; 
					added = true;
					which_point = true;
					int a = is_point_merging(current_line, trees_arr, tree_num, points_count, is_begin);
					if (a == i) {//CYKKLE JEBANE
						;
					}
					else if (a == -1) {
						add_point(current_line, trees_arr, points_count, i, which_point);
					}
					else {
						merge_trees(current_line, trees_arr, points_count, a, i);
					}
					//sprawdzenie czy punkt łączy dwa drzewa
					//tak-merge_trees, nie- dodanie do drzewa

				}
			}
		}
	}

	if (added == false) {// tworzenie nowego drzewa
		tree_num++;
		//current_line->tree_num = tree_num;
		trees_arr[tree_num][0] = current_line->begin_point;
		trees_arr[tree_num][1] = current_line->end_point;//cos ze sztywnymi zmienic?
		points_count[tree_num] = 2;//do spraawdzenia czy dziala
	}
}

int is_point_merging(Line* current_line, int trees_arr[TREE_MAX][ARR_MAX], const int tree_num, int points_count[ARR_MAX], bool is_begin) {//zwraca numer drzewa polaczonego
	if (is_begin) {//sprawdza end
		for (int i = 0; i <= tree_num; i++) {
			for (int j = 0; j < points_count[i]; j++) {
				if (current_line->end_point == trees_arr[i][j]) {
					return i;
				}
			}
		}
	}
	else {//sprawdza begin
		for (int i = 0; i <= tree_num; i++) {
			for (int j = 0; j < points_count[i]; j++) {
				if (current_line->begin_point == trees_arr[i][j]) {
					return i;
				}
			}
		}
	}
	return -1;

}

void delete_tree(int trees_arr[TREE_MAX][ARR_MAX], int points_count[ARR_MAX], int tree_num_1, int tree_num_2,int counting1, int counting2, int &tree_num){
	if(tree_num_1 > tree_num_2)
	{
		for (int j = 0; j < counting1 ; j++) {
			trees_arr[tree_num_1][j] = trees_arr[tree_num_1 + 1][j];
		}	
		points_count[tree_num_1] = points_count[tree_num_1 + 1];
		if(tree_num>1){
			for(int i = 0; i<points_count[tree_num])
		}
	}
	else
	{
		for (int j = 0; j < counting2; ++j) {
			trees_arr[tree_num_2][j] = trees_arr[tree_num_2 + 1][j];
		}
		points_count[tree_num_2] = points_count[tree_num_2 + 1];
	}
	tree_num--;
	
}

void merge_trees(Line* current_line, int trees_arr[TREE_MAX][ARR_MAX], int points_count[ARR_MAX], int tree_num_1, int tree_num_2, int &tree_num) {

	//bool added_to_one_tree = false; 
	int counting2 = points_count[tree_num_2];
	int counting1 = points_count[tree_num_1];

	if (tree_num_1 > tree_num_2) {
		for (int i = 0; i < points_count[tree_num_2]; i++) { //sprawdza dla dzrewa o mnijszej liczbie punktów
			for (int j = 0; j < points_count[tree_num_1]; j++) { //sprawdza dla drzewa o wiekszej liczbie punktów

				if (current_line->end_point == trees_arr[tree_num_1][j] && current_line->begin_point == trees_arr[tree_num_2][i]) { // sprawdza, który punkt jest w jakim drzewie
					trees_arr[tree_num_2][points_count[tree_num_2]] = trees_arr[tree_num_1][j]; // dodaje punkt z drzewa o wiekszym indeksie do drzewa o mniejszym indeksie
					points_count[tree_num_2]++;
					for (int k = 0; k < points_count[tree_num_1]; k++) {

						if (trees_arr[tree_num_2][counting2 + k] == trees_arr[tree_num_1][j]) { // jesli jest ten punkt to idzie dalej
							continue;
						}
						else
						{
							trees_arr[tree_num_2][counting2 + k] = trees_arr[tree_num_1][k]; //dodaje punkty z drzewa o wiekszym indeksie do drzewa o mniejszym
							points_count[tree_num_2]++;
						}
					}
					delete_tree(trees_arr, points_count, tree_num_1, tree_num_2, counting1, counting2, tree_num);
					return;
				}
				else if (current_line->end_point == trees_arr[tree_num_2][i] && current_line->begin_point == trees_arr[tree_num_1][j]) {
					trees_arr[tree_num_2][points_count[tree_num_2]] = trees_arr[tree_num_1][j];
					points_count[tree_num_2]++;
					for (int k = 0; k < points_count[tree_num_1]; k++) {

						if (trees_arr[tree_num_2][counting2 + k] == trees_arr[tree_num_1][j]) {
							continue;
						}
						else
						{
							trees_arr[tree_num_2][counting2 + k] = trees_arr[tree_num_1][k];
							points_count[tree_num_2]++;
						}
					}
					delete_tree(trees_arr, points_count, tree_num_1, tree_num_2, counting1, counting2, tree_num);
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < points_count[tree_num_1]; i++) {
			for (int j = 0; j < points_count[tree_num_2]; j++) {

				if (current_line->end_point == trees_arr[tree_num_1][i] && current_line->begin_point == trees_arr[tree_num_2][j]) {
					trees_arr[tree_num_1][points_count[tree_num_1]] = trees_arr[tree_num_2][j];
					points_count[tree_num_1]++;
					for (int k = 0; k < points_count[tree_num_2]; k++) {

						if (trees_arr[tree_num_1][counting1 + k] == trees_arr[tree_num_2][j]) {
							continue;
						}
						else
						{
							trees_arr[tree_num_1][counting1 + k] = trees_arr[tree_num_2][k];
							points_count[tree_num_1]++;
						}
					}
					delete_tree(trees_arr, points_count, tree_num_1, tree_num_2, counting1, counting2, tree_num);
					return;
				}
				else if (current_line->end_point == trees_arr[tree_num_2][j] && current_line->begin_point == trees_arr[tree_num_1][i]) {
					trees_arr[tree_num_1][points_count[tree_num_1]] = trees_arr[tree_num_2][j];
					points_count[tree_num_1]++;
					for (int k = 0; k < points_count[tree_num_2]; k++) {

						if (trees_arr[tree_num_1][counting1 + k] == trees_arr[tree_num_2][j]) {
							continue;
						}
						else
						{
							trees_arr[tree_num_1][counting1 + k] = trees_arr[tree_num_2][k];
							points_count[tree_num_1]++;
						}
					}
					delete_tree(trees_arr, points_count, tree_num_1, tree_num_2, counting1, counting2, tree_num);
					return;
				}
			}
		}
	}
}

void add_point(Line* current_line, int trees_arr[TREE_MAX][ARR_MAX], int points_count[ARR_MAX], int current_tree_num, bool which_point) {
	if (which_point)// jeśli jest true to end_point już jest i dodaje begin_point
	{
		trees_arr[current_tree_num][points_count[current_tree_num]] = current_line->begin_point;
	}
	else {
		trees_arr[current_tree_num][points_count[current_tree_num]] = current_line->end_point;//punkty liczymy od 1 nie od 0
	}
	points_count[current_tree_num] = points_count[current_tree_num] + 1;
}

void print_trees(Line* line, int trees_arr[TREE_MAX][ARR_MAX], int points_count[ARR_MAX], const int counter){

	//for(int i = 0; i < points_count[tree_num_1])
}
