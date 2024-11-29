#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "matrix.h"
#include "formnodes.h"
#include "functions.h"

int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		return 1;
	}

	std::ifstream inFile(argv[1]);
	if (!inFile)
	{
		return 2;
	}

	std::ofstream outFile(argv[2]);
	if (!outFile)
	{
		inFile.close();
		return 3;
	}

	char str[1024];
	char buf[32]; // буфер для записи констант, имен переменных и функций.
	int count = 0; // счетчик выражений. Используется для вывода ошибки.

	while (inFile.peek () != EOF)
	{
		std::stack <unsigned char> op; // стек для хранения операций.
		std::stack <FormNode*> vars; // стек для хранения операндов.
		FormNode* left = nullptr;
		FormNode* right = nullptr;
		FormNode* result = nullptr;
		AVLTree<VarValue>::iterator pos;

		vars.push (nullptr); // метка конца стека.

		size_t in_buf = 0;
		inFile.getline (str, 1024);
		++count;
			
		int ch;
		size_t i = 0;

		try
		{
			while ((ch = str[i++]) != '\0')
			{
				if (ch == '(')
				{
					vars.push (nullptr);
				} 
				else if (ch == ')')
				{
					if (in_buf > 0)
					{
						buf[in_buf] = '\0';
						unsigned char fun = find (buf);
						if (fun != '\0')
						{
							op.push (fun); // функция.
						} 
						else if (isdigit (buf[0]))
						{
							vars.push (new NumNode (Matrix (buf))); // константа.
						} 
						else
						{
							vars.push (new VarNode (buf)); // переменная.
						}

						in_buf = 0;
					}


					unsigned char oper = op.top ();
					op.pop ();

					switch (oper)
					{
					case '+':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc () + right->calc ()));

						break;
					case '*':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc () * right->calc ()));

						break;
					case '/':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc () / right->calc ()));

						break;
					case '^':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc () ^ right->calc ()));

						break;
					case '|':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc () | right->calc ()));

						break;
					case '=':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						pos = global::Workspace.find (VarValue (left->name ()));
						(*pos).set (right->calc ());

						break;
					case '-':
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							vars.pop ();
							vars.push (new NumNode (-right->calc ()));
						} else
						{
							left = vars.top ();
							vars.pop ();

							if (vars.top () != nullptr)
							{
								throw "error";
							}
							vars.pop ();

							vars.push (new NumNode (left->calc () - right->calc ()));
						}

						break;
					case 128:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (zeros (left->calc (), right->calc ())));

						break;
					case 129:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (ones (left->calc (), right->calc ())));

						break;
					case 130:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (eye (left->calc ())));

						break;
					case 131:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						result = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (linspace (result->calc (), left->calc (), right->calc ())));
						delete result;
						result = nullptr;

						break;
					case 132:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();


						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						result = new NumNode (vcat (left->calc (), right->calc ()));

						while (vars.top () != nullptr)
						{
							delete left;
							left = nullptr;
							delete right;
							right = nullptr;

							left = vars.top ();
							vars.pop ();

							right = result;

							result = new NumNode (vcat (left->calc (), right->calc ()));
						}
						vars.pop ();
						vars.push (result);

						break;
					case 133:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();


						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						result = new NumNode (hcat (left->calc (), right->calc ()));

						while (vars.top () != nullptr)
						{
							delete left;
							left = nullptr;
							delete right;
							right = nullptr;

							left = vars.top ();
							vars.pop ();

							right = result;
							result = new NumNode (hcat (left->calc (), right->calc ()));
						}
						vars.pop ();
						vars.push (result);

						break;
					case 134:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc ().transpose ()));

						break;
					case 135:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc ().det ()));

						break;
					case 136:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc ().inv ()));

						break;
					case 137:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc ().sum ()));

						break;
					case 138:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (left->calc ().prod ()));

						break;
					case 139:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (min (left->calc (), right->calc ())));

						break;
					case 140:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						right = vars.top ();
						vars.pop ();

						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						vars.push (new NumNode (max (left->calc (), right->calc ())));

						break;
					case 141:
						if (vars.top () == nullptr)
						{
							throw "error";
						}
						left = vars.top ();
						vars.pop ();

						if (vars.top () != nullptr)
						{
							throw "error";
						}
						vars.pop ();

						outFile << left->name() << " = " << left->calc () << std::endl;

						break;
					}
					delete left;
					left = nullptr;
					delete right;
					right = nullptr;
				} 
                else if (ch == ' ' || ch == '\t' || ch == '\r')
				{
					if (in_buf > 0)
					{
						buf[in_buf] = '\0';
						unsigned char fun = find (buf);
						if (fun != '\0')
						{
							op.push (fun);
						} else if (isdigit (buf[0]))
						{
							vars.push (new NumNode (Matrix (buf)));
						} else
						{
							vars.push (new VarNode (buf));
						}

						in_buf = 0;
					}
				} 
				else if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
				{
					op.push (ch);
				} 
				else if (ch == '.')
				{
					ch = str[i++];
					if (ch == '*')
					{
						op.push ('^');
					} 
					else if (ch == '/')
					{
						op.push ('|');
					} 
					else
					{
						throw "error";
					}
				} 
				else if (isdigit (ch) || isalpha (ch))
				{
					buf[in_buf++] = ch;
				} 
				else
				{
					throw "error";
				}
			}
		}
		catch (...) {
			delete left;
			delete right;
			delete result;

			while (!vars.empty ())
			{
				result = vars.top();
				vars.pop();
				delete result;
			}

			outFile.close ();
			outFile.open (argv[2]);
			outFile << "Error in line " << count;
			break;
		}
	}
	
	inFile.close();
	outFile.close();
	return 0;
}