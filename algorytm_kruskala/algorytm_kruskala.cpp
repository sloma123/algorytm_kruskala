#include <iostream>
#include <cstdlib>
using namespace std;

struct Line {
	int begin_point;
	int end_point;
	int weight;
	int tree_num;
	Line* Next;
};

void welcome();
void menu();
Line* input_head();
Line* create_line(Line*);
void add_line(Line*);
Line* sort(Line* line);
void create_trees(Line*);
void merge_trees(Line*);

int main(){
	welcome();
	menu();
}

void welcome(){
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
	head = sort(head); 
	create_trees(head);
	Line* i = head;
	while (i != NULL) { 
		cout << i->weight << endl;
		i = i->Next;
	}
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

Line* sort(Line* line) {

	Line* h = line;
	Line* head = line;
	Line* ptr = line;
	int counter = 0;

	while (h != NULL) {
		counter++;
		h = h->Next;
	} //liczy ile jest linii w liście jednokierunkowej

	int i, j, swapped;

	for (i = 0; i <= counter; i++) {
		h = head;
		swapped = 0;

		for (j = 0; j < counter - i - 1; j++) {
			Line* p1 = h;
			Line* p2 = p1->Next;

			if (p1->weight > p2->weight) {  // zamienia linie miejscami

				Line* buff = new Line();
				buff = p2->Next;
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

void create_trees(Line* head) {
	int tree_num = 1;
	head->tree_num = tree_num;
	Line* current_line = new Line();
	current_line = head;
	if(current_line->begin_point == current_line->Next->begin_point){

		tree->Next->tree_num = tree_num;
	}
}


void merge_trees(Line*){

	
}