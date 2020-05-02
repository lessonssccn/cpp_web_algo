#include <iostream>
#include "queue.h"
#include "cgi.h"
using namespace std;

void create_queue(queue & q, const char* data)
{
	char* str = _strdup(data);
	char* tmp = str;
	char* cont;
	while (char* part = strtok_s(tmp, "; ", &cont))
	{
		tmp = nullptr;
		double x;
		sscanf_s(part, "%lf", &x);
		pushElement(q, x);
	}
}

void show_stack(queue& q)
{
	int size = q.size;
	while (size != 0)
	{
		double val = popElement(q);
		if (val < 0 && size != 0)
		{
			cout << val << " ";
		}
		else
		{
			pushElement(q, val);
		}
		size--;
	}

	while (!isEmpty(q))
	{
		double val = popElement(q);
		cout << val << " ";
	}
}


int main()
{
	cout << "Content-type: text/html; charset=Winows-1251\n\n";
	cout << "<form action='queue.cgi' method='get'>";
	cout << "Последовательность: <input type='text' name='series'><br>";
	cout << "<input type='submit' value='Отправить'>";
	cout << "</form>";

	queue q = createQueue();
	char* data = nullptr;
	get_form_data(data);
	char* series;
	get_param_value(series, "series", data);

	create_queue(q, series);
	show_stack(q);
	delete[] data;

	return 0;
}