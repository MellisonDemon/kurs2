#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <chrono>
#include <stdio.h>
using namespace std;
using namespace chrono;

//ВТОРАЯ_ЛАБА

struct listt
{
	int data;
	listt* next; // указатель на следующий элемент
	listt* prev; // указатель на предыдущий элемент
};

int printList(listt*& first)
{
	listt* curr = first;
	while (curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << "\n\n";
	return 0;
}

listt* listElemIndex(listt* curr, int index, bool err_msg = true)
{
	while (curr && (index--))
		curr = curr->next;
	if (err_msg && !curr)
		cout << "ОШИБКА";
	return curr;
}

listt* listElemValue(listt* curr, int& value, bool err_msg = true)
{
	while (curr && curr->data != value)
		curr = curr->next;
	if (err_msg && !curr)
		cout << "ОШИБКА";
	return curr;
}

listt* takeElem(listt*& first, int& idx, bool print = false)
{
	listt* curr = 0;
	cout << "\n1. По значению\n2. По индексу\n";
	int value;
	string answer;
	cin >> answer;
	value = stoi(answer);
	if (value == 1) {
		cout << "Введите значение: ";
		cin >> answer;
		value = stoi(answer);
		curr = listElemValue(first, value);
		listt* idx_search = first;
		idx = 0;
		while (idx_search && idx_search != curr) {
			idx++;
			idx_search = idx_search->next;
		}
	}
	else if (value == 2) {
		cout << "Введите индекс: ";
		cin >> answer;
		idx = stoi(answer);
		curr = listElemIndex(first, idx);
	}
	else  cout << "ОШИБКА";
	if (print && curr)
		cout << "Ваш элемент: " << curr->data << "\n";
	return curr;
}

int deleteList(listt*& first)
{
	listt* next;
	while (first)
	{
		next = first->next;
		delete first;
		first = next;;
	}
	return 0;
}

int createList(listt*& first, listt*& last, unsigned n)
{
	listt* curr = 0, * next = 0;
	deleteList(first);
	for (unsigned i = 0; i < n; i++) {
		curr = new listt;
		curr->data = rand() % 100;
		curr->next = next;
		if (next) {
			next->prev = curr;
		}
		else
			last = curr;
		next = curr;
	}
	curr->prev = nullptr;
	first = curr;
	return 0;
}

int createMain(listt*& first, listt*& last, int& n, int*& arr)
{
	system_clock::time_point begin = system_clock::now();
	createList(first, last, n);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	int* array = new int[n];
	listt* curr = first;
	for (int i = 0; i < n; ++i, curr = curr->next) {
		array[i] = curr->data;
	}
	delete[]arr;
	arr = array;
	end = system_clock::now();
	cout << "\nУшло времени на создание списка: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int pushFirst(listt*& curr, listt*& first, listt*& last)
{
	curr->prev = nullptr;
	curr->next = nullptr;
	first = curr;
	last = curr;
	return 0;
}

int pushLast(listt*& curr, listt*& last)
{
	curr->prev = last;
	last->next = curr;
	last = curr;
	last->next = nullptr;
	return 0;
}

int enterList(listt*& first, listt*& last, int& n)
{
	n = 0;
	listt* p;
	deleteList(first);
	string theDatas, number;
	cin.ignore();
	cout << "Введите элементы: ";
	getline(cin, theDatas);
	for (int i = 0; i <= theDatas.length(); i++) {
		if (theDatas[i] != ' ' && theDatas[i] != '\0') {
			number += theDatas[i];
		}
		else {
			listt* p = new listt;
			n++;
			p->data = stoi(number);
			if (first == nullptr) {
				pushFirst(p, first, last);
			}
			else {
				pushLast(p, last);
			}
			number.erase(0, number.length());

		}
	}
	return 0;
}

void insertToArray(int*& arr, int& n, const int& idx, const int& value)
{
	if (idx > n || idx < -1) return;
	int* arr_new = new int[++n];
	int i = 0;
	for (i; i <= idx; ++i) {
		arr_new[i] = arr[i];
	}
	if (idx == -1) arr_new[i] = value;
	else arr_new[i] = value;
	for (++i; i < n; ++i) {
		arr_new[i] = arr[i - 1];
	}
	delete[]arr;
	arr = arr_new;
}

int enterArray(int*& arr, listt* first, int& n) {
	int* array = new int[n];
	listt* curr = first;
	string imitation;
	cout << "Введите любое число: ";
	getline(cin, imitation);
	for (int i = 0; i < n && curr; ++i, curr = curr->next) {
		array[i] = curr->data;
	}
	delete[]arr;
	arr = array;
	return 0;
}

int enterMain(listt*& first, listt*& last, int*& arr, int& n)
{
	system_clock::time_point begin = system_clock::now();
	enterList(first, last, n);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	enterArray(arr, first, n);
	end = system_clock::now();
	cout << "\nУшло времени на создание списка: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

void insertToList(listt*& first, listt*& last, const int& idx, const int& val)
{
	listt* curr_1 = 0, * curr_2 = new listt;
	curr_2->data = val;
	if (idx == -1) {
		if (!first)
			pushFirst(curr_2, first, last);
		else {
			first->prev = curr_2;
			curr_2->next = first;
			curr_2->prev = nullptr;
			first = curr_2;
		}
		return;
	}
	curr_1 = listElemIndex(first, idx);
	if (!curr_1) return;;
	if (curr_1 == last) {
		pushLast(curr_2, last);
	}
	else {
		curr_1->next->prev = curr_2;
		curr_2->next = curr_1->next;
		curr_1->next = curr_2;
		curr_2->prev = curr_1;

	}
}

int insertMain(listt*& first, listt*& last, int*& arr, int& n)
{
	int idx, val;
	string answer;
	cout << "\nПосле какого элемента вставить данный элемент (0, если нужно вставить первым)?: ";
	cin >> answer;
	idx = stoi(answer);
	idx = idx - 1;
	cout << "\nВведите значение данного элемента: ";
	cin >> answer;
	val = stoi(answer);
	system_clock::time_point begin = system_clock::now();
	insertToList(first, last, idx, val);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	insertToArray(arr, n, idx, val);
	end = system_clock::now();
	cout << "\nВремя, потраченное на вставку: " << time.count() << " мс\n";
	cout << "\nArray: " << (end - begin).count() << " мс\n";
	return 0;
}

void deleteArray(int*& arr, int& n, const int& idx)
{
	if (idx >= n || idx < 0) return;
	if (n == 0)return;
	int* arr_new = new int[--n];
	int i;
	for (i = 0; i < idx; ++i) {
		arr_new[i] = arr[i];
	}
	for (i = idx; i < n; ++i) {
		arr_new[i] = arr[i + 1];
	}
	delete[]arr;
	arr = arr_new;
}

void deleteCurr(listt*& first, listt*& last, int& idx)
{
	listt* curr = 0;
	curr = takeElem(first, idx);
	if (!curr) {
		cout << "ОШИБКА\n";
		idx = -1;
		return;
	}
	if (curr == first) {
		if (!first->next) {
			first = nullptr;
			cout << "ОШИБКА\n";
			return;
		}
		curr = first->next;
		delete first;
		curr->prev = nullptr;
		first = curr;
		return;
	}
	if (curr == last) {
		curr = last->prev;
		delete last;
		curr->next = nullptr;
		last = curr;
		return;
	}
	if (curr) {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		return;
	}
}

int deleteMain(int*& arr, int& n, listt*& first, listt*& last)
{
	system_clock::time_point begin = system_clock::now();
	int idx = -2;
	deleteCurr(first, last, idx);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	deleteArray(arr, n, idx);
	end = system_clock::now();
	cout << "Время, ушедшее на удаление элемента: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

void exchangeCurr(listt*& first, listt*& last, const int& index_1, const int& index_2)
{
	listt* p_1, * p_2;
	listt* p_mem = new listt;
	p_1 = listElemIndex(first, index_1);
	p_2 = listElemIndex(first, index_2);
	if (!p_1 || !p_2) return;
	if (p_1->next == p_2) {
		p_mem->next = p_2->next;
		p_2->next = p_1;
		p_2->prev = p_1->prev;
		p_1->next = p_mem->next;
		p_1->prev = p_2;
		if (p_1->next != nullptr) {
			p_1->next->prev = p_1;
		}
		if (p_2->prev != nullptr) {
			p_2->prev->next = p_2;
		}
	}
	else if (p_2->next == p_1) {
		p_mem->next = p_1->next;
		p_1->next = p_2;
		p_1->prev = p_2->prev;
		p_2->next = p_mem->next;
		p_2->prev = p_1;
		if (p_2->next != nullptr) {
			p_2->next->prev = p_2;
		}
		if (p_1->prev != nullptr) {
			p_1->prev->next = p_1;
		}
	}
	else {
		if (p_1 != first)
			p_1->prev->next = p_2;
		p_mem->next = p_2->next;
		p_2->next = p_1->next;
		if (p_2 != first)
			p_2->prev->next = p_1;
		p_1->next = p_mem->next;
		p_mem->prev = p_2->prev;
		p_2->prev = p_1->prev;
		p_1->prev = p_mem->prev;
		if (p_1->next != nullptr)
			p_1->next->prev = p_1;
		if (p_2->next != nullptr)
			p_2->next->prev = p_2;
	}
	if (p_1->prev == nullptr)
		first = p_1;
	if (p_2->prev == nullptr)
		first = p_2;
}

int exchangeMain(int*& arr, const int& n, listt*& first, listt*& last)
{
	int index_1, index_2;
	string answer;
	system_clock::time_point begin = system_clock::now();
	cout << "Введите индексы элементов, которые требуется обменять: ";
	cin >> answer;
	index_1 = stoi(answer);
	cin >> answer;
	index_2 = stoi(answer);
	exchangeCurr(first, last, index_1, index_2);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	if (index_1 < n && index_2 < n)
		swap(arr[index_1], arr[index_2]);
	end = system_clock::now();
	cout << "Время, ушедшее на перестановку: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int takeElemMain(int*& arr, const int& n, listt*& first)
{
	system_clock::time_point begin = system_clock::now();
	int found, idx = -1;
	takeElem(first, idx, 1);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	if (idx >= 0 && idx < n) {
		found = arr[idx];
		cout << found << "\n";
	}
	end = system_clock::now();
	cout << "Затрачено времени на поиск: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int menu(listt*& first, listt*& last, int*& arr, int& n)
{
	int countOfDatas = 0, switcher, switcher2, okay = 0;

	while (true)
	{
		cout << "\nВыберите действие:\n1.Создать двусвязный список\n2.Вставка элемента\n3.Удалить элемент\n4.Обмен элементов\n5.Получить элемент\n";
		cin >> switcher;
		switch (switcher)
		{
		case 1:
			cout << "\n1.Создать рандомный список заданной длинны.\n2.Ввести список с клвиатуры\n";
			cin >> switcher2;
			switch (switcher2)
			{
			case 1:
				cout << "\nКакой длинны Вы желаете создать массив?" << endl;
				cin >> countOfDatas;
				n = countOfDatas;
				createMain(first, last, n, arr);
				printList(first);
				okay = 1;
				break;
			case 2:
				enterMain(first, last, arr, n);
				printList(first);
				okay = 1;
				break;
			default:
				cout << "ОШИБКА";
				break;
			}
			break;
		case 2:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			insertMain(first, last, arr, n);
			printList(first);
			break;
		case 3:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			deleteMain(arr, n, first, last);
			printList(first);
			break;
		case 4:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			exchangeMain(arr, n, first, last);
			printList(first);
			break;
		case 5:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			takeElemMain(arr, n, first);
			break;
		default:
			cout << "ОШИБКА";
			break;
		}
	}
	return 0;
}

int mainSecLab()
{
	srand(time(NULL));
	int n = 0;
	listt* first = nullptr;
	listt* last = nullptr;
	int* arr = new int[1];
	menu(first, last, arr, n);
	return 0;
}

//ТРЕТЬЯ_ЛАБА
string operations = "+-*/";

struct list {
	string symbol;
	list* next;
};

struct Stack {
	list* tail;
	Stack() : tail(nullptr) {}  //конструктор
	bool isEmpty() {
		if (tail == nullptr) return 1;
		return 0;
	}
	void output() {
		cout << "Операторы: ";
		list* curr = tail;
		if (!curr) {
			cout << "Пусто";
		}
		while (curr) {
			cout << curr->symbol << " ";
			curr = curr->next;
		}
		cout << "\n";
	}
	string pop(bool print = 1) {
		if (tail == nullptr) return "конец";
		if (print) cout << tail->symbol << " ";
		string answer = tail->symbol;
		list* p = new list;
		p = tail;
		tail = tail->next;
		p->next = nullptr;
		delete p;
		return answer;
	}
	void push(string sym) {
		list* p = new list;
		p->symbol = sym;
		p->next = tail;
		tail = p;
	}
};

int prior(char c) {
	switch (c) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	default: return 0;
	}
}

bool correctInputInf(string& data) {
	bool flag_oper = 0, flag_bracket = 0;
	int count_num = 0, count_oper = 0;
	for (int i = 0; i < data.length(); ++i) {
		if (data[i] == ' ') data.erase(i, 1);
	}
	for (int i = 0; i < data.length(); ++i) {
		if (data[i] == '(') {
			if (!flag_oper && i != 0 || flag_bracket || operations.find(data[i + 1]) != -1) {
				return 0;
			}
			flag_bracket = 1;
		}
		else if (data[i] == ')') {
			if (!flag_bracket || flag_oper || i != data.length() - 1 && operations.find(data[i + 1]) == -1) {
				return 0;
			}
			flag_bracket = 0;
		}
		else if (data[i] >= '0' && data[i] <= '9' || data[i] == '.') {
			flag_oper = 0;
		}
		else if (operations.find(data[i]) != -1) {
			if (i == 0 || i == data.length() - 1) {
				return 0;
			}
			if (flag_oper) {
				return 0;
			}
			flag_oper = 1;
		}
		else if (data[i] == '\0') continue;
		else {
			return 0;;
		}
	}
	return 1;
}

bool correctInputPo(string& data) {
	int count_oper = 0, count_num = 0;
	for (int i = 0; i < data.length(); ++i) {
		if (operations.find(data[i]) != -1) {
			if (i == 0) {
				return 0;
			}
			count_oper++;
		}
		else if (data[i] == ' ') {
			if (operations.find(data[i - 1]) == -1)
				count_num++;
		}
		else if (data[i] >= '0' && data[i] <= '9') {
			if (i == data.length() - 1) {
				return 0;
			}
			continue;
		}
		else if (data[i] == '.' || data[i] == '\0')continue;
		else {
			return 0;
		}
	}
	if (count_oper != count_num - 1) {
		return 0;
	}
	return 1;
}

bool correctInputPre(string& data) {
	int count_oper = 0, count_num = 0;
	if (data[0] == ' ') data.erase(0, 1);
	for (int i = 0; i < data.length(); ++i) {
		if (operations.find(data[i]) != -1) {
			if (i == data.length() - 1) {
				return 0;
			}
			count_oper++;
		}
		else if (data[i] == ' ' || data[i] == '\0') {
			if (operations.find(data[i - 1]) == -1)
				count_num++;
		}
		else if (data[i] >= '0' && data[i] <= '9') {
			if (i == 0) {
				return 0;
			}
			continue;
		}
		else if (data[i] == '.')continue;
		else {
			return 0;
		}
	}
	if (count_oper != count_num - 1) {
		return 0;
	}
	return 1;
}

double action(double& value1, double& value2, string& oper) {
	switch (oper[0]) {
	case '+':
		return value1 + value2;
		break;
	case '-':
		return value1 - value2;
		break;
	case '*':
		return value1 * value2;
		break;
	case '/':
		return value1 / value2;
		break;
	default:
		break;
	}
}

void calculate(string& data, bool prefix) {
	if (prefix) {
		if (!correctInputPre(data)) {
			cout << "ОШИБКА\n";
			return;
		}
		for (int j = data.length() - 1, i = 0; j >= i; --j, ++i) {
			swap(data[j], data[i]);
		}
	}
	else {
		if (!correctInputPo(data)) {
			cout << "ОШИБКА\n";
			return;
		}
	}
	Stack numbers;
	string num;
	string  sym;
	double val_1, val_2;
	for (int i = 0; i <= data.length(); i++) {
		sym = data[i];
		if (operations.find(sym) != -1) {
			if (prefix) {
				val_1 = stod(numbers.pop(0));
				val_2 = stod(numbers.pop(0));
			}
			else {
				val_2 = stod(numbers.pop(0));
				val_1 = stod(numbers.pop(0));
			}

			numbers.push(to_string(action(val_1, val_2, sym)));
		}
		if (sym >= "0" && sym <= "9" || sym == ".") {
			num += sym;
		}
		if (sym == " ") {
			if (operations.find(data[i - 1]) != -1) continue;
			if (prefix) {
				for (int j = num.length() - 1, i = 0; j >= i; --j, ++i) {
					swap(num[j], num[i]);
				}
			}
			numbers.push(num);
			num.erase(0, num.length());
		}
	}
	numbers.pop();
	cout << "\n";
}

void RevPN(string& data, bool print = 1)
{
	Stack steak;
	string note;
	if (!correctInputInf(data))
	{
		cout << "ОШИБКА\n";
		return;
	}
	string sym;
	for (int i = 0; i <= data.length(); ++i) {
		if (data[i] == ' ') data.erase(i, 1);
	}
	for (int i = 0; i < data.length(); i++) {
		sym = data[i];
		if (sym >= "0" && sym <= "9" || sym == ".") {
			note += sym;
			if (sym == "." || data[i + 1] == '.' || data[i + 1] >= '0' && data[i + 1] <= '9') continue;
			note += " ";
			if (print) {
				cout << "\nЧисла: " << note << "\n";
				steak.output();
			}
		}
		if (sym == "(") {
			steak.push(sym);
			if (print) {
				cout << "\nЧисла: " << note << "\n";
				steak.output();
			}
			continue;
		}
		if (sym == ")") {
			while (steak.tail->symbol != "(") {
				note += steak.pop(0);
				note += " ";
			}
			steak.pop(0);
			if (print) {
				cout << "\nЧисла: " << note << "\n";
				steak.output();
			}
			continue;
		}
		if (operations.find(sym) != -1) {

			if (steak.isEmpty() || prior(steak.tail->symbol[0] < prior(sym[0]))) {
				steak.push(sym);
				if (print) {
					cout << "\nЧисла: " << note << "\n";
					steak.output();
				}
			}
			else {
				while (!steak.isEmpty() && prior(steak.tail->symbol[0]) >= prior(sym[0])) {
					note += steak.pop(0);
					note += " ";
				}
				steak.push(sym);
				if (print) {
					cout << "\nЧисла: " << note << "\n";
					steak.output();

				}
			}
		}
	}
	if (print) {
		cout << "\nЧисла: " << note << "\n";
		steak.output();

	}
	while (!steak.isEmpty()) {
		note += steak.pop(0);
		note += " ";
	};
	if (print) {
		cout << "\nСтек: ";
	}
	cout << note << "\n";
	data = note;
}

void StandPN(string& data) {
	if (!correctInputInf(data)) {
		cout << "ОШИБКА\n";
		return;
	}
	string note;
	for (int j = data.length() - 1; j >= 0; --j) {
		if (data[j] == '(') {
			note += ')';
		}
		else if (data[j] == ')') {
			note += '(';
		}
		else if (data[j] == ' ') continue;
		else {
			note += data[j];
		}
	}
	cout << "Инвертированная строка: " << note << "\n" << "Алгоритм: ";
	RevPN(note, 0);
	data.erase(0, data.length());
	for (int j = note.length() - 1; j >= 0; --j) {
		data += note[j];
	}
	data += '\0';
	cout << "Стек: " << data << "\n";
}

void menuThi(string& data)
{
	int switcher;
	cout << "Выберите действие\n" \
		"1. Конвертировать выражение в обратную польскую нотацию(+автоматическая проверка)\n" \
		"2. Конвертировать выражение в польскую нотацию(+автоматическая проверка)\n" \
		"3. Вычислить выражение из обратной польской нотации\n" \
		"4. Вычислить выражение из польской нотации\n" \
		"5. Проверить корректность введёного выражения\n";
	while (true)
	{
		cout << "Выполнить пункт: ";
		cin >> switcher;
		switch (switcher)
		{
		case 1:
			data.erase(0, data.length());
			cin.ignore();
			cout << "Введите выражение: ";
			getline(cin, data);
			RevPN(data);
			break;
		case 2:
			data.erase(0, data.length());
			cin.ignore();
			cout << "Введите выражение: ";
			getline(cin, data);
			StandPN(data);
			break;
		case 3:
			if (!correctInputPo(data)) {
				cout << "You should to enter new reverse(postfix) note: ";
				cin.ignore();
				getline(cin, data);
				data += '\0';
			}
			else {
				cout << "Do you want to enter new reverse(postfix) note? (\'no\'=0) ";
				cin >> switcher;
				if (switcher) {
					data.erase(0, data.length());
					cin.ignore();
					getline(cin, data);
					data += '\0';
				}
			}
			calculate(data, 0);
			break;
		case 4:
			if (!correctInputPre(data)) {
				cout << "You should to enter new prefix note: ";
				cin.ignore();
				getline(cin, data);
				data += '\0';
			}
			else {
				cout << "Do you want to enter new prefix note? (\'no\'=0) ";
				cin >> switcher;
				if (switcher) {
					data.erase(0, data.length());
					cin.ignore();
					getline(cin, data);
					data += '\0';
				}
				else
					cin.ignore();
			}
			calculate(data, 1);
			break;
		case 5:
			cout << "Какой вид нотации проверить?\n1. стандартная (обычная запись)\n2. польская\n3. обратная польская\n";
			cin >> switcher;
			cout << "Введите выражение: ";
			data.erase(0, data.length());
			cin.ignore();
			getline(cin, data);
			data += '\0';
			switch (switcher) {
			case 1:
				if (correctInputInf(data)) {
					cout << "Верно!\n";
				}
				else {
					cout << "Есть ошибка!\n";
				}
				break;
			case 2:
				if (correctInputPre(data)) {
					cout << "Верно!\n";
				}
				else {
					cout << "Есть ошибка!\n";
				}
				break;
			case 3:
				if (correctInputPo(data)) {
					cout << "Верно!\n";
				}
				else {
					cout << "Есть ошибка!\n";
				}
				break;
			default:
				cout << "ОШИБКА\n";
			}
			break;
		default:
			cout << "ОШИБКА\n";
			break;
		}
	}
}

int mainThiLab()
{
	string data = "";
	menuThi(data);
	return 0;
}

//ПЕРВАЯ_ЛАБА

struct student {
	char name[50];
	char sex[2];
	int group;
	int number;
	int exam1;
	int exam2;
	int exam3;
	int test1;
	int test2;
	int test3;
	int test4;
	int test5;
};

int mainFirLab()
{
	int counterOfStudents = 13;
	int studentNumber;
	int helper;
	char names[50];
	int maleCounter = 0;
	int femaleCounter = 0;
	struct student StudentsList[100] = { "Иванов Иван Иванович", "М", 1313, 7, 4, 4, 4, 5, 4, 3, 5, 5, "Горечь Анна Ивановна", "Ж", 1313, 2, 5, 5, 5, 5, 5, 5, 5, 5, "Ломин Виктор Васильевич", "М", 1314, 7, 4, 5, 4, 5, 4, 5, 4, 5, "Корешева Юлия Андреевна", "Ж", 1301, 8, 4, 4, 4, 5, 5, 5, 5, 5, "Бирюкова Анна Андреевна", "Ж", 1313, 1, 3, 5, 4, 4, 4, 4, 4, 4, "Лобызяк Вера Юрьевна", "Ж", 1314, 5, 3, 3, 3, 3, 3, 3, 3, 3, "Мирный Олег Степанович", "М", 1301, 9, 5, 5, 5, 5, 5, 5, 5, 5, "Маратов Гурий Иванович", "М", 1210, 10, 4, 5, 5, 5, 4, 3, 4, 5, "Ива Давид Александрович", "М", 1314, 4, 5, 3, 3, 4, 4, 4, 3, 4, "Акимова Ира Дмитриевна", "Ж", 1203, 1, 4, 4, 4, 5, 4, 5, 5, 4, "Соменюк Артём Иванович", "М", 1313, 9, 5, 4, 5, 5, 3, 4, 4, 3, "Замятин Степан Олегович", "М", 1344, 1, 5, 5, 4, 5, 5, 5, 5, 5, "Лужина Софья Родионовна", "Ж", 1314, 5, 3, 3, 5, 3, 4, 4, 3, 4 };
	cout << "МЕНЮ: " << endl << "1. Создание новой записи о студенте" << endl << "2. Внесение изменений в уже имеющуюся запись" << endl << "3. Вывод всех данных о студентах" << endl << "4. Вывод информации обо всех студентах группы N" << endl << "5. Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию." << endl << "6. Вывод количества студентов мужского и женского пола." << endl << "7. Вывод данных о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»." << endl << "8. Вывод данных о студентах, имеющих номер в списке – k." << endl;
	while (true)
	{
		cout << "Выберите действие из списка меню: ";
		cin >> helper;
		switch (helper)
		{
		case (1):
			//-----1.Создание новой записи о студенте-----//
		{
			for (int i = counterOfStudents; i < counterOfStudents + 1; i++)
			{
				cout << "ФИО: ";
				cin.getline(StudentsList[i].name, 50, '\n');
				cin.getline(StudentsList[i].name, 50, '\n');
				cout << "Пол: ";
				cin >> StudentsList[i].sex;
				cout << "Группа: ";
				cin >> StudentsList[i].group;
				cout << "Номер в группе: ";
				cin >> StudentsList[i].number;
				cout << "Оценка за 1 экзамен: ";
				cin >> StudentsList[i].exam1;
				cout << "Оценка за 2 экзамен: ";
				cin >> StudentsList[i].exam2;
				cout << "Оценка за 3 экзамен: ";
				cin >> StudentsList[i].exam3;
				cout << "Оценка за 1 диф зачёт: ";
				cin >> StudentsList[i].test1;
				cout << "Оценка за 2 диф зачёт: ";
				cin >> StudentsList[i].test2;
				cout << "Оценка за 3 диф зачёт: ";
				cin >> StudentsList[i].test3;
				cout << "Оценка за 4 диф зачёт: ";
				cin >> StudentsList[i].test4;
				cout << "Оценка за 5 диф зачёт: ";
				cin >> StudentsList[i].test5;
			}
			counterOfStudents++;
		}
		break;
		case (2):
			//-----2.Внесение изменений в уже имеющуюся запись-----//
		{
			cout << "Укажите номер студента в списке студентов, чьи данные Вы хотите измeнить: ";
			cin >> studentNumber;
			cout << "Укажите номер данных студента, которые вы хотите изменить." << endl << "1. ФИО" << endl << "2. Пол" << endl << "3. Группа" << endl << "4. Номер в группе" << endl << "5. Оценка за 1 экзамен" << endl << "6. Оценка за 2 экзамен" << endl << "7. Оценка за 3 экзамен" << endl << "8. Оценка за 1 диф зачёт" << endl << "9. Оценка за 2 диф зачёт" << endl << "10. Оценка за 3 диф зачёт" << endl << "11. Оценка за 4 диф зачёт" << endl << "12. Оценка за 5 диф зачёт" << endl;
			cin >> helper;
			switch (helper) {
			case(1):
				cin.getline(StudentsList[studentNumber - 1].name, 50, '\n'); break;
			case(2):
				cin >> StudentsList[studentNumber - 1].sex; break;
			case(3):
				cin >> StudentsList[studentNumber - 1].group; break;
			case(4):
				cin >> StudentsList[studentNumber - 1].number; break;
			case(5):
				cin >> StudentsList[studentNumber - 1].exam1; break;
			case(6):
				cin >> StudentsList[studentNumber - 1].exam2; break;
			case(7):
				cin >> StudentsList[studentNumber - 1].exam3; break;
			case(8):
				cin >> StudentsList[studentNumber - 1].test1; break;
			case(9):
				cin >> StudentsList[studentNumber - 1].test2; break;
			case(10):
				cin >> StudentsList[studentNumber - 1].test3; break;
			case(11):
				cin >> StudentsList[studentNumber - 1].test4; break;
			case(12):
				cin >> StudentsList[studentNumber - 1].test5; break;
			default:
				cout << "Ошибка ввода." << endl; break;
			}
		}
		break;
		case (3):
			//-----3.Вывод всех данных о студентах.-----//
		{
			cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
			cout << "=============================================================================================================" << endl;
			for (int i = 0; i < counterOfStudents; i++)
			{
				cout << i + 1 << '\t' << StudentsList[i].name << '\t' << '\t' << StudentsList[i].sex << '\t' << StudentsList[i].group << '\t' << StudentsList[i].number << '\t' << StudentsList[i].exam1 << '\t' << StudentsList[i].exam2 << '\t' << StudentsList[i].exam3 << '\t' << StudentsList[i].test1 << '\t' << StudentsList[i].test2 << '\t' << StudentsList[i].test3 << '\t' << StudentsList[i].test4 << '\t' << StudentsList[i].test5 << endl << endl;
			}
		}
		break;
		case (4):
			//-----4.Вывод информации обо всех студентах группы N.-----//
		{
			cout << "Укажите номер группы, студентов которой Вы хотите увидеть:";
			cin >> helper;
			cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
			cout << "=============================================================================================================" << endl;
			for (int i = 0; i < counterOfStudents; i++)
			{
				if (StudentsList[i].group == helper)
				{
					cout << i + 1 << '\t' << StudentsList[i].name << '\t' << '\t' << StudentsList[i].sex << '\t' << StudentsList[i].group << '\t' << StudentsList[i].number << '\t' << StudentsList[i].exam1 << '\t' << StudentsList[i].exam2 << '\t' << StudentsList[i].exam3 << '\t' << StudentsList[i].test1 << '\t' << StudentsList[i].test2 << '\t' << StudentsList[i].test3 << '\t' << StudentsList[i].test4 << '\t' << StudentsList[i].test5 << endl;
				}
			}
		}
		break;
		case (5):
			//-----5.Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.-----//
		{
			for (int i = 0; i < counterOfStudents; i++)
			{
				for (int j = 1; j < (counterOfStudents - i); j++)
				{
					if ((StudentsList[j - 1].exam1 + StudentsList[j - 1].exam2 + StudentsList[j - 1].exam3 + StudentsList[j - 1].test1 + StudentsList[j - 1].test2 + StudentsList[j - 1].test3 + StudentsList[j - 1].test4 + StudentsList[j - 1].test5) / double(8) < (StudentsList[j].exam1 + StudentsList[j].exam2 + StudentsList[j].exam3 + StudentsList[j].test1 + StudentsList[j].test2 + StudentsList[j].test3 + StudentsList[j].test4 + StudentsList[j].test5) / double(8))
					{
						swap(StudentsList[j - 1], StudentsList[j]);
					}
				}
			}
			cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
			cout << "=============================================================================================================" << endl;
			for (int i = 0; i < counterOfStudents; i++)
			{
				cout << i + 1 << '\t' << StudentsList[i].name << '\t' << '\t' << StudentsList[i].sex << '\t' << StudentsList[i].group << '\t' << StudentsList[i].number << '\t' << StudentsList[i].exam1 << '\t' << StudentsList[i].exam2 << '\t' << StudentsList[i].exam3 << '\t' << StudentsList[i].test1 << '\t' << StudentsList[i].test2 << '\t' << StudentsList[i].test3 << '\t' << StudentsList[i].test4 << '\t' << StudentsList[i].test5 << endl;
			}
		}
		break;
		case (6):
			//-----6.Вывод количества студентов мужского и женского пола.-----//
		{
			for (int i = 0; i < counterOfStudents; i++)
			{
				if (int(StudentsList[i].sex[0]) == -52 || StudentsList[i].sex == "М")
				{
					maleCounter++;
				}
				if (int(StudentsList[i].sex[0]) == -58 || StudentsList[i].sex == "Ж")
				{
					femaleCounter++;
				}
			}
			cout << "Среди студентов " << maleCounter << " человек являются мужчинами, а " << femaleCounter << " – женщинами" << endl;
		}
		break;
		case (7):
			//-----7.Вывод данных о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;-----//
		{
			cout << "Укажите номер группы студентов, о которых Вы хотите просмотреть информацию:" << endl << "1. Студенты, которые не получают стипендию" << endl << "2. Студенты, учащиеся только на «хорошо» и «отлично»" << endl << "3. Студенты, учащиеся только на «отлично»" << endl;
			cin >> helper;
			switch (helper) {
			case(1):
				cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
				cout << "=============================================================================================================" << endl;
				for (int i = 0; i < counterOfStudents; i++)
				{
					if (StudentsList[i].exam1 < 4 || StudentsList[i].exam2 < 4 || StudentsList[i].exam3 < 4 || StudentsList[i].test1 < 4 || StudentsList[i].test2 < 4 || StudentsList[i].test3 < 4 || StudentsList[i].test4 < 4 || StudentsList[i].test5 < 4)
					{
						{
							cout << i + 1 << '\t' << StudentsList[i].name << '\t' << '\t' << StudentsList[i].sex << '\t' << StudentsList[i].group << '\t' << StudentsList[i].number << '\t' << StudentsList[i].exam1 << '\t' << StudentsList[i].exam2 << '\t' << StudentsList[i].exam3 << '\t' << StudentsList[i].test1 << '\t' << StudentsList[i].test2 << '\t' << StudentsList[i].test3 << '\t' << StudentsList[i].test4 << '\t' << StudentsList[i].test5 << endl;
						}
					}
				}
				break;
			case(2):
				cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
				cout << "=============================================================================================================" << endl;
				for (int j = 0; j < counterOfStudents; j++)
				{
					if (StudentsList[j].exam1 > 3 && StudentsList[j].exam2 > 3 && StudentsList[j].exam3 > 3 && StudentsList[j].test1 > 3 && StudentsList[j].test2 > 3 && StudentsList[j].test3 > 3 && StudentsList[j].test4 > 3 && StudentsList[j].test5 > 3)
					{
						cout << j + 1 << '\t' << StudentsList[j].name << '\t' << '\t' << StudentsList[j].sex << '\t' << StudentsList[j].group << '\t' << StudentsList[j].number << '\t' << StudentsList[j].exam1 << '\t' << StudentsList[j].exam2 << '\t' << StudentsList[j].exam3 << '\t' << StudentsList[j].test1 << '\t' << StudentsList[j].test2 << '\t' << StudentsList[j].test3 << '\t' << StudentsList[j].test4 << '\t' << StudentsList[j].test5 << endl;
					}
				}
				break;
			case(3):
				cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
				cout << "=============================================================================================================" << endl;
				for (int j = 0; j < counterOfStudents; j++)
				{
					if (StudentsList[j].exam1 == 5 && StudentsList[j].exam2 == 5 && StudentsList[j].exam3 == 5 && StudentsList[j].test1 == 5 && StudentsList[j].test2 == 5 && StudentsList[j].test3 == 5 && StudentsList[j].test4 == 5 && StudentsList[j].test5 == 5)
					{
						cout << j + 1 << '\t' << StudentsList[j].name << '\t' << '\t' << StudentsList[j].sex << '\t' << StudentsList[j].group << '\t' << StudentsList[j].number << '\t' << StudentsList[j].exam1 << '\t' << StudentsList[j].exam2 << '\t' << StudentsList[j].exam3 << '\t' << StudentsList[j].test1 << '\t' << StudentsList[j].test2 << '\t' << StudentsList[j].test3 << '\t' << StudentsList[j].test4 << '\t' << StudentsList[j].test5 << endl;
					}
				}
				break;
			default:
				cout << "Ошибка ввода." << endl; break;
			}
		}
		break;
		case (8):
			//-----8.Вывод данных о студентах, имеющих номер в списке – k.-----//
		{
			cout << "Укажите номер из списков групп, студентов-обладателей которых Вы хотите увидеть: ";
			cin >> helper;
			cout << "№\t" << "ФИО\t" << '\t' << '\t' << '\t' << "Пол\t" << "Группа\t" << "Номер\t" << "1 экз\t" << "2 экз\t" << "3 экз\t" << "1 зач.\t" << "2 зач.\t" << "3 зач.\t" << "4 зач.\t" << "5 зач.\t" << endl;
			cout << "=============================================================================================================" << endl;
			for (int i = 0; i < counterOfStudents; i++)
			{
				if (StudentsList[i].number == helper)
				{
					cout << i + 1 << '\t' << StudentsList[i].name << '\t' << '\t' << StudentsList[i].sex << '\t' << StudentsList[i].group << '\t' << StudentsList[i].number << '\t' << StudentsList[i].exam1 << '\t' << StudentsList[i].exam2 << '\t' << StudentsList[i].exam3 << '\t' << StudentsList[i].test1 << '\t' << StudentsList[i].test2 << '\t' << StudentsList[i].test3 << '\t' << StudentsList[i].test4 << '\t' << StudentsList[i].test5 << endl << endl;
				}
			}
		}
		break;
		default:
			cout << "Ошибка ввода." << endl; break;
		}

	}

	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int lab;
	while (true)
	{
		cout << "\nКакую лабораторную выполнить?\n1. Структуры\n2. Двусвязный список\n3. Стек";
		cin >> lab;
		switch (lab)
		{
		case 1:
			mainFirLab();
			break;
		case 2:
			mainSecLab();
			break;
		case 3:
			mainThiLab();
			break;
		default:
			cout << "ОШИБКА\n";
			break;
		}
	}
}