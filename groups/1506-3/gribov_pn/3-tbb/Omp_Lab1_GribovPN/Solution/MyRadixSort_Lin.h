//������ �.�. 381506-3. ����������� ���������� � ������� ��������. ���������������� ������. MyRadixSort_Lin.h
#pragma once

//#include <queue>
#include <vector>
#include <algorithm>

//using std::queue;
using std::vector;

//������� ��������� ���������� ������� �����
int get_dig(int num, int dig_num);

//����������� ����������
void radix_sort(vector<int>& vec);