//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. Последовательная версия. MyRadixSort_Lin.cpp
#include "MyRadixSort_Lin.h"

//функция получения требуемого разряда числа
int get_dig(int num, int dig_num)
{
	num = abs(num);
	for (int i = 0; i < (dig_num - 1); ++i)
	{
		num /= 10;
	}
	return num % 10;
}

// Поразрядная сортировка (Алгоритм №1)
/*void radix_sort(vector<int>& vec)
{
	//максимальное количество разрядов сортируемых чисел (по верхней границе)
	int max_num_of_dig = 10;
	//количество сортируемых чисел
	int num_of_numbers = static_cast<int>(vec.size());
	//вектор очередей для положительных чисел
	vector<queue<int>> p_vec_of_queue(10);
	//вектор стеков для отрицательных чисел
	vector<queue<int>> n_vec_of_queue(10);
	//isSorted - флаг проверки отсортированности для досрочного завершения
	bool isSorted = false;

	int k;

	for (int i = 0; i < max_num_of_dig; ++i)
	{
		if (isSorted)
			break;
		isSorted = true;
		for (int j = 0; j < num_of_numbers; ++j)
		{
			if (vec[j] < 0)
				n_vec_of_queue[get_dig(vec[j], i + 1)].push(vec[j]);
			else
				p_vec_of_queue[get_dig(vec[j], i + 1)].push(vec[j]);
		}
		k = 0;
		for (int j = 0; j < 10; ++j)
		{
			while (!n_vec_of_queue[j].empty())
			{
				vec[k++] = n_vec_of_queue[j].front();
				n_vec_of_queue[j].pop();
			}
		}
		for (int j = 0; j < 10; ++j)
		{
			while (!p_vec_of_queue[j].empty())
			{
				vec[k++] = p_vec_of_queue[j].front();
				p_vec_of_queue[j].pop();
			}
		}
		for (int j = 0; j < (num_of_numbers - 1); ++j)
		{
			if (abs(vec[j]) > abs(vec[j + 1]))
			{
				isSorted = false;
				break;
			}
		}
	}
	vector<int>::iterator minpos = std::min_element(vec.begin(), vec.end());
	std::reverse(vec.begin(), minpos + 1);
} */

// Поразрядная сортировка (Алгоритм №2)
void radix_sort(vector<int>& vec)
{
	int max_dig_count = 10;
	int max_dig = 10;
	int num_of_numbers = static_cast<int>(vec.size());
	int count, tmp;
	int num_threads = 4;
	vector<int> buffer(num_of_numbers);
	vector<int> pos_vec(10);

	for (int i = 0; i < max_dig_count; ++i)
	{
		for (int j = 0; j < max_dig; ++j)
			pos_vec[j] = 0;
		for (int j = 0; j < num_of_numbers; ++j)
		{
			++pos_vec[get_dig(vec[j], i)];
		}
		count = 0;
		for (int j = 0; j < max_dig; ++j)
		{
			tmp = pos_vec[j];
			pos_vec[j] = count;
			count += tmp;
		}
		for (int j = 0; j < num_of_numbers; ++j)
		{
			buffer[pos_vec[get_dig(vec[j], i)]++] = vec[j];
		}
		vec = buffer;
	}
	vec.clear();
	std::copy_if(buffer.rbegin(), buffer.rend(), std::back_inserter(vec), [](int i) { return i < 0; });
	std::copy_if(buffer.begin(), buffer.end(), std::back_inserter(vec), [](int i) { return i >= 0; });
}