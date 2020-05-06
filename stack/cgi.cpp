#include "cgi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_get()
{
	//REQUEST_METHOD
	size_t realsize;
	char* value = new char[5];
	getenv_s(&realsize, value, 5, "REQUEST_METHOD");
	bool res = !_strcmpi(value, "GET");
	delete[] value;
	return res;
}

size_t get_content_length()
{
	//CONTENT_LENGTH
	size_t realsize;
	char* value = new char[11];
	getenv_s(&realsize, value, 11, "CONTENT_LENGTH");
	size_t size;
	if (!realsize) size = 0;
	else sscanf_s(value, "%d", &size);
	delete[] value;
	return size;
}

void get_form_data(char*& data)
{
	if (data) delete[] data;
	if (is_get())
	{
		//QUERY_STRING
		size_t realsize;
		char* value = new char[65536];
		getenv_s(&realsize, value, 65536, "QUERY_STRING");
		data = new char[realsize+1];
		strcpy_s(data, realsize+1, value);
		delete[] value;
	} else
	{
		size_t bufSize = get_content_length();
		data = new char[bufSize + 1];
		fread_s(data, 
			bufSize+1, 
			sizeof(char), 
			bufSize, 
			stdin
		);
		data[bufSize] = 0;
	}
}

void str_decode(char*& dec_str, const char* enc_str)
{
	char* res = new char[strlen(enc_str)+1];
	int i = 0, j = 0;
	while (enc_str[i])
	{
		if (enc_str[i]=='+')
		{
			res[j] = ' ';
		} else
		{
			if (enc_str[i]=='%')
			{
				char ch[3] = {enc_str[i+1], enc_str[i+2], 0};
				int c;
				sscanf_s(ch, "%X", &c);
				res[j] = c;
				i += 2;
			} else
			{
				res[j] = enc_str[i];
			}
		}
		i++;
		j++;
	}
	res[j] = 0;
	size_t len = strlen(res)+1;
	dec_str = new char[len];
	strcpy_s(dec_str, len, res);
	delete[] res;
}

void get_param_value(char*& value, const char* param_name, const char* data)
{
	char* str = _strdup(data);
	char* tmp = str;
	char* cont;
	while (char* part = strtok_s(tmp, "&", &cont))
	{
		tmp = nullptr;
		char* val;
		char* key = strtok_s(part, "=", &val);
		if (!_strcmpi(param_name, key))
		{
			str_decode(value, val);
			delete[] str;
			return;
		}
	}
	delete[] str;
	value = new char[1];
	value[0] = 0;
}