#include <iostream>
#include "stack.h"
#include "cgi.h"

using namespace std;

int checkLine(const char * line, int size)
{
	stack s;
	for (int i=0; i<size; i++)
	{
		if (line[i]=='(' || line[i] == '{' || line[i] == '[')
		{
			s.push(line[i]);
		}

		else if (line[i] == ')' && s.getHead()=='(')
		{
			s.pop();
		}
		else if (line[i] == ')' && s.getHead() != '(')
		{
			return i;
		}

		else if (line[i] == '}' && s.getHead() == '{')
		{
			s.pop();
		}
		else if (line[i] == '}' && s.getHead() != '{')
		{
			return i;
		}

		else if (line[i] == ']' && s.getHead() == '[')
		{
			s.pop();
		}
		else if (line[i] == ']' && s.getHead() != '[')
		{
			return i;
		}
	}

	if (s.getSize()!=0)
	{
		return s.getSize()+1;
	}

	return -1;
}
void show_data(int errorPos, char * data, int size)
{
	if (errorPos==-1)
	{
		for (int i=0; i< size; i++)
		{
			cout << data[i]<<" ";
		}
	}
	else
	{
		int i = 0;
		for (i = 0; i < size && i < errorPos; i++)
		{
			cout << data[i] << " ";
		}
		cout << "<font  color=\"red\">" << data[i] << "</font> ";
		for (i = i+1; i < size ; i++)
		{
			cout << data[i] << " ";
		}
	}
}

int main()
{
	cout << "Content-type: text/html; charset=Winows-1251\n\n";
	cout << "<form action='stack.cgi' method='get'>";
	cout << "Последовательность: <input type='text' name='series'><br>";
	cout << "<input type='submit' value='Отправить'>";
	cout << "</form>";

	char* data = nullptr;
	get_form_data(data);
	int lenData = strlen(data);
	if (lenData > 0)
	{
		char* series;
		get_param_value(series, "series", data);
		int lenSeries = strlen(series);
		int res = checkLine(series, lenSeries);
		show_data(res, series, lenSeries);
		delete[] series;
	}
	if (data)
	{
		delete[] data;
	}
	return 0;
}