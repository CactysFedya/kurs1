// Курсовая работа.cpp 

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>

class Function {
private:
	std::string m_function;
	std::string m_code;
	int m_position;
	int m_end;
	int m_beginning;
	double m_result;

public:

	// Конструктор по умолчанию 
	Function() {
		m_function = "";
		m_code = "";
		m_position = 0;
		m_result = 0;
	}

	// Конструктор 
	Function(std::string name) : m_function(name) {
		m_code = "";
		m_position = 0;
		m_result = 0;
		if (m_function[0] == '+') m_function.erase(0, 1);
		if (m_function[0] == '(') {
			m_function.erase(0, 1);
			m_function.erase(m_function.length() - 1, 1);
		}
	}

	//
	void asd() {
		while (m_position != m_function.length() + 1) {

			// Поиск числа 
			if (number(m_function[m_position])) {

				if (m_position == 0) {
					m_function = '+' + m_function;
					m_position++;
				}

				m_beginning = m_position;
				while (number(m_function[m_position])) m_position++;
				m_end = m_position - 1;

				if (m_function[m_beginning - 1] == '-')
					m_code += '-';
				if (m_function[m_beginning - 1] == '+')
					m_code += '+';
				if (m_function[m_beginning - 1] == '*' || m_function[m_beginning - 3] == '*')
					m_code += '*';

				m_code += m_function.substr(m_beginning, m_end - m_beginning + 1) + ';';

			}

			// Поиск аргумента
			if (m_function[m_position] == 'x') {

				if (m_position == 0) {
					m_function = '+' + m_function;
					m_position++;
				}

				if (m_function[m_position - 1] == '-')
					m_code += '-';
				if (m_function[m_position - 1] == '+')
					m_code += '+';
				if (m_function[m_position - 1] == '*')
					m_code += '*';

				m_code += "x;";

			}

			// Следующий символ функции 
			m_position++;
		}

		// Обнуление позиции 
		m_position = 0;

		std::cout << m_code << "\n";
	}

	void result(double argument) {

		// Начально значение функции 
		m_result = 0;

		while (m_position != m_code.length() + 1) {

			// 
			if (m_code[m_position] == '+') {
				if (m_code[m_position + 1] == 'x')

					m_result += argument;

				else {
					m_beginning = m_position + 1;
					m_position++;
					while (number(m_code[m_position])) m_position++;
					m_end = m_position - 1;
					m_result += atof((m_code.substr(m_beginning, m_end - m_beginning + 1).c_str()));
					std::cout << m_result << "\n";
				}
			}

			// 
			if (m_code[m_position] == '-' && m_code[m_position + 1] != '*') {
				if (m_code[m_position + 1] == 'x')

					m_result -= argument;

				else {

					m_beginning = m_position + 1;
					m_position++;
					while (number(m_code[m_position])) m_position++;
					m_end = m_position - 1;
					m_result -= atof((m_code.substr(m_beginning, m_end - m_beginning + 1).c_str()));

				}
			}

			//
			if (m_code[m_position] == '*') {

				if (m_code[m_position + 1] == 'x')
					m_result *= argument;

				else {

					m_beginning = m_position + 1;
					m_position++;
					while (number(m_code[m_position])) m_position++;
					m_end = m_position - 1;
					m_result *= atof((m_code.substr(m_beginning, m_end - m_beginning + 1).c_str()));

				}
			}

			// Следующий символ функции 
			m_position++;

		}

		std::cout << m_result;

	}

private:

	bool number(char number) {
		char m_number[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < 10; i++)
			if (number == m_number[i]) return true;
		return false;
	}

};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Ввод апроксимирующей функции
	std::string function;
	std::cout << "Введите выражение для аппроксимирующей функции: ";
	std::cin >> function;

	// Кол-во базисных функций 
	int count = 1;
	int position = 0;
	int bracket = 0;
	{
		while (position != function.length()) {
			if (function[position] == '(') bracket++;
			if (function[position] == ')') bracket--;
			if ((function[position] == '+' || function[position] == '-') && bracket == 0) count++;
			position++;
		}
	}

	// Выделение базисных функций 
	Function* arrayFunction = new Function[count];
	bracket = 0; position = 0; count = 0;
	{
		int beginning = 0;
		int end;
		while (position != function.length() + 1) {
			if (function[position] == '(') bracket++;
			if (function[position] == ')') bracket--;
			if ((function[position] == '+' || function[position] == '-' || position == function.length()) && bracket == 0) {
				end = position - 1;
				arrayFunction[count] = { function.substr(beginning, end - beginning + 1) };
				beginning = end + 1;
				count++;
			}
			position++;
		}
	}

	arrayFunction[0].asd();
	arrayFunction[0].result(5);

	// Очищение динамической памяти
	delete[]arrayFunction;

	return 0;
}