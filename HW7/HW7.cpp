#include "main.h"

//Функция сортировки массива методом простой вставки
//Предусловие: на вход поступает указатель на ненулевой массив, количество элементов массива
//Постусловие: функция изменяет расположение элементов
void insertion_sort(int*& array, int n)
{
	comparisons++;
	for (int i = 1;i < n;i++)
	{
		comparisons += 3;
		for (int j = i;j > 0 && array[j - 1] > array[j];j--)
		{
			comparisons += 2;
			movements += 3;
			swap(array[j - 1], array[j]);
		}
	}
}

//Функция сортировки массива методом Шелла со смещениями Д.Кнута (способ 2)
//Предусловие: на вход поступает указатель на ненулевой массив, количество элементов массива
//Постусловие: функция изменяет расположение элементов
void shell_sort(int*& array, int n)
{
	movements++;
	int increment = 1;
	comparisons++;
	for (int i = (int)(log(n) / log(2) - 1);i > 1;i--)
	{
		comparisons++;
		movements++;
		increment = increment * 2 + 1;
	}
	comparisons++;
	while (increment > 0)
	{
		comparisons += 2;
		for (int i = 0; i < n; i++)
		{
			movements += 3;
			comparisons += 3;
			int j = i;
			int temp = array[i];
			while (j >= increment && array[j - increment] > temp)
			{
				comparisons += 2;
				movements += 2;
				array[j] = array[j - increment];
				j = j - increment;
			}
			movements++;
			array[j] = temp;
		}
		comparisons++;
		if (increment > 1)
		{
			movements++;
			increment = (increment - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void merge(int*& array, int top, int bottom)
{
	if (top == bottom)
	{
		return;
	}

	merge(array, top, (top + bottom) / 2);
	merge(array, (top + bottom) / 2 + 1, bottom);
	movements += 3;
	int i = top;
	int j = (top + bottom) / 2 + 1;
	int* array_var = new int[bottom - top + 1];
	comparisons++;
	for (int k = 0; k < bottom - top + 1; k++)
	{
		movements++;
		comparisons += 4;
		if (i <= (top + bottom) / 2 && array[i] < array[j] || j > bottom)
		{
			movements += 2;
			array_var[k] = array[i];
			i++;
		}
		else
		{
			movements += 2;
			array_var[k] = array[j];
			j++;
		}
	}
	comparisons++;
	for (int i = 0; i < bottom - top + 1; i++)
	{
		comparisons++;
		movements += 2;
		array[top + i] = array_var[i];
	}
}

//Функция сортировки массива методом простого слияния
//Предусловие: на вход поступает указатель на ненулевой массив, индекс первого элемента, индекс последнего элемента
//Постусловие: функция изменяет расположение элементов, сортирует массив в порядке возрастания
void merge_sort(int*& array, int n)
{
	merge(array, 0, n - 1);
}

//Функция заполнения массива случайными числами 
void filling_array(int*& array, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		array[i] = rand() % 1000;
	}
}

//Функция вывода массива 
void print_array(int array[], int N) {
	for (int i = 0; i < N; i++) {
		cout << setw(7) << array[i];
	}
	cout << "\n";
}

//Функция тестирования сортировки методом простой вставки
void test_insertion_sort(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простой вставки для массива из " << N << " случайных чисел: " << endl;
	filling_array(array, N);

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	insertion_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом Шелла
void test_shell_sort(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом Шелла для массива из " << N << " случайных чисел: " << endl;
	filling_array(array, N);

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	shell_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом простого смещения
void test_merge_sort(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простого смещения для массива из " << N << " случайных чисел: " << endl;
	filling_array(array, N);

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	merge_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом простой вставки на строго возрастающем массиве
void test_insertion_sort_asc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простой вставки для массива из " << N << " строго возрастающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	insertion_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом Шелла на строго возрастающем массиве
void test_shell_sort_asc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом Шелла для массива из " << N << " строго возрастающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	shell_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом простого смещения на строго возрастающем массиве
void test_merge_sort_asc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простого смещения для массива из " << N << " строго возрастающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	merge_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом простой вставки на строго убывающем массиве
void test_insertion_sort_dsc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простой вставки для массива из " << N << " строго убывающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = N - i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	insertion_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом Шелла на строго убывающем массиве
void test_shell_sort_dsc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом Шелла для массива из " << N << " строго убывающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = N - i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	shell_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

//Функция тестирования сортировки методом простого смещения на строго убывающем массиве
void test_merge_sort_dsc(int N, int*& array) {
	array = new int[N];

	cout << "Тестирование сортировки методом простого смещения для массива из " << N << " строго убывающих чисел: " << endl;
	for (long i = 0;i < N;i++)
	{
		array[i] = N - i;
	}

	//cout << "Не отсортированный массив: " << endl;
	//print_array(array, N);

	movements = 0;
	comparisons = 0;

	auto begin = std::chrono::steady_clock::now();
	merge_sort(array, N);
	auto end = chrono::steady_clock::now();

	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;

	//cout << "Отсортированный массив: " << endl;
	//print_array(array, N);
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int n;
	int* array;

	/*n = 100;
	test_insertion_sort(n, array);
	n = 1000;
	test_insertion_sort(n, array);
	n = 10000;
	test_insertion_sort(n, array);
	n = 100000;
	test_insertion_sort(n, array);
	n = 1000000;
	test_insertion_sort(n, array);

	n = 100;
	test_shell_sort(n, array);
	n = 1000;
	test_shell_sort(n, array);
	n = 10000;
	test_shell_sort(n, array);
	n = 100000;
	test_shell_sort(n, array);
	n = 1000000;
	test_shell_sort(n, array);

	n = 100;
	test_merge_sort(n, array);
	n = 1000;
	test_merge_sort(n, array);
	n = 10000;
	test_merge_sort(n, array);
	n = 100000;
	test_merge_sort(n, array);
	n = 1000000;
	test_merge_sort(n, array);*/


	n = 100;
	test_insertion_sort_asc(n, array);
	n = 1000;
	test_insertion_sort_asc(n, array);
	n = 10000;
	test_insertion_sort_asc(n, array);
	n = 100000;
	test_insertion_sort_asc(n, array);
	n = 1000000;
	test_insertion_sort_asc(n, array);

	n = 100;
	test_shell_sort_asc(n, array);
	n = 1000;
	test_shell_sort_asc(n, array);
	n = 10000;
	test_shell_sort_asc(n, array);
	n = 100000;
	test_shell_sort_asc(n, array);
	n = 1000000;
	test_shell_sort_asc(n, array);

	n = 100;
	test_merge_sort_asc(n, array);
	n = 1000;
	test_merge_sort_asc(n, array);
	n = 10000;
	test_merge_sort_asc(n, array);
	n = 100000;
	test_merge_sort_asc(n, array);
	n = 1000000;
	test_merge_sort_asc(n, array);

	n = 100;
	test_insertion_sort_dsc(n, array);
	n = 1000;
	test_insertion_sort_dsc(n, array);
	n = 10000;
	test_insertion_sort_dsc(n, array);
	n = 100000;
	test_insertion_sort_dsc(n, array);
	n = 1000000;
	test_insertion_sort_dsc(n, array);

	n = 100;
	test_shell_sort_dsc(n, array);
	n = 1000;
	test_shell_sort_dsc(n, array);
	n = 10000;
	test_shell_sort_dsc(n, array);
	n = 100000;
	test_shell_sort_dsc(n, array);
	n = 1000000;
	test_shell_sort_dsc(n, array);

	n = 100;
	test_merge_sort_dsc(n, array);
	n = 1000;
	test_merge_sort_dsc(n, array);
	n = 10000;
	test_merge_sort_dsc(n, array);
	n = 100000;
	test_merge_sort_dsc(n, array);
	n = 1000000;
	test_merge_sort_dsc(n, array);

}