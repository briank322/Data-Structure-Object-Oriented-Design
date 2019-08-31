#include<iostream>
#include<cctype>
#include<string>
#include<fstream>
#include<sstream>
#include"stackstring.h"

using namespace std;

void process(StackString, string);
bool lineempty(string);
bool invalid_operator(char);
string subt(string, string);
string remove(string, string);


//if string is not empty,store string into StackString
void process(StackString s, string chunk)
{

	if(chunk.length()!=0)
	{
		s.push(chunk);
	}
}
//check whether the line is empty or not.
bool lineempty(string line)
{
	for(unsigned int i =0; i<line.size(); i++)
	{
		if(!isspace(line[i]))
		{
			return false;
		}
		
	}
	return true;
}
//check whether the operator(char) is valid
bool invalid_operator(char c)
{
	if( c == '<'||c == '>'||c == '+'
		||c == '-'||c == ')'||c == '(')
	{
		return false;
	}
	else
	{
		return true;
	}
}
//operator"-" erase substring(rhs) from lhs.
string subt(string lhs, string rhs)
{
	if(lhs.find(rhs) != string::npos)
	{
		int index = lhs.find(rhs);
		
		if(index == 0)
		{
			lhs = lhs.substr(index + rhs.length());
		}
		else if (index != 0)
		{
			lhs = lhs.erase(index, index+rhs.length()-1);
		}
	}
	return lhs;
}
//operator"<" and ">" 
//< removes the last letter and > removes the first letter.
string remove(string str, string carrot) 
{
	if(carrot == "<")
	{
		str = str.erase(str.length()-1);
	}
	else if (carrot == ">")
	{
		str = str.substr(1,str.length());
	}
	return str;
	
}

//main function that actually do the operations.
int main(int argc, char* argv[])
{
	if (argc<3)
	{
		cout<<"Error: Double Check the Command line"<<endl;
		return 0;
	}
	ifstream ifile(argv[1]);

	if(ifile.fail())
	{
		cout<<"Error: Invalid input"<<endl;
		return 0;
	}

	ofstream ofile(argv[2]);
	if(ofile.fail())
	{
		cout<<"Error: Invalid output"<<endl;
		return 0;
	}

	
	string line;
	string chunk;
	unsigned int i;
	//variable mal updates whether the given
	//expression is malformed or not.
	bool mal = false;
	//lhs <operator> rhs
	string lhs,rhs;
	
	
	while(getline(ifile, line))

	{
		//Two stackstrings. One for storing the string(letters)
		//The other one is storing the operator.
		StackString str;
		StackString oper;
		
		//if the given file is empty line than break the while and exit.
		if(lineempty(line))
		{
			ofile<<endl;
			break;
		}
		
		//Traversing the line(string) until it hits the end.
		for(i = 0; line[i]!='\0'; i++)
		{
			char c = line[i];
			
			//if valid, then add char to string(chunk).
			if((!isspace(c))&&(islower(c)))
			{
				chunk+=c;
			}
			//process function stores string(chunck) as a stackstring.
			else if(isspace(c))
			{
				process(str,chunk);
			}
			//if the operator is invalid
			else if(!invalid_operator(line[i]))
			{
				//push chunk into stackstring
				if(chunk.length()!=0)
				{
					str.push(chunk);
					chunk.clear();
				}
				
				//handle the operator: grab it and erase it.
				string temp;
				temp.push_back(c);
				oper.push(temp);
				// if the expression ends with ")"
				if(oper.top() == ")")
				{
					//pop the current operator 
					oper.pop();
					//and if it is empty it is malformed
					if (oper.empty()) 
					{
						mal = true;
					}
					// while it is valid
					while(!oper.empty() && !mal && oper.top() != "(")
					{
						//finish the carrot operator first and store the 
						//string to the stackstring.
						lhs = str.top();
						str.pop();
						if(oper.top() == "<" || oper.top() == ">")
						{

							lhs = remove(lhs,oper.top());
							str.push(lhs);
							oper.pop();

						}
						//operate the "-"" operator
						else if(oper.top() == "-")
						{
							oper.pop();
							rhs = str.top();
							str.pop();

							//after the operator "-", no other operator can come right after it.
							if((oper.top()=="+")||(oper.top()=="-")||oper.top()==">")
							{
								mal = true;
							}

							//handle the carrot operator first
							else 
							{

								while(oper.top() == "<" || oper.top() == ">")
								{
									rhs = remove(rhs,oper.top());
									oper.pop();
								}

							}
							//if all sub-operations are done, finally do the minus.
							str.push(subt(rhs, lhs));

						}
						//for plus operator
						else if(oper.top() == "+")
						{
							//rhs has to be a string.
							if(str.empty())
							{
								mal = true;
							}	
							else
							{
								oper.pop();
								rhs=str.top();
								str.pop();
								//minus operator can't come right after the plus operator
								if(oper.empty()||oper.top()=="-")
								{
									mal = true;
								}	
								// do the carrot operator first.
								while(oper.top() =="<"||oper.top()==">")
								{
									rhs = remove(rhs,oper.top());
									oper.pop();

								}
							}
							//finally do the plus operator
							str.push(rhs += lhs);
						}
						//if "(", read the upcoming string.
						else if(oper.top() == "(")
						{
							str.push(lhs);
							oper.push("(");
						}
					}//end of while loop

					if(!oper.empty() && oper.top() == "(")
					{
						oper.pop();
					}
					
				}//end of oper.top() == ")"
			}
			
			else
			{
				mal = true;
				break;
			}
			//the last char of the line
			if(i == (line.length()-1))
			{
				//store the chunk(string) to str(stackstring) 
				if(chunk.length() > 0)
				{
					str.push(chunk);
					chunk.clear();
				}

			}

		}//end of for loop
		
		//if stackstring(stringpart) is not empty
		if(!str.empty())
		{
			//compute two strings
			string tmp = str.top();
			str.pop();
			//if there are more operators
			if(!oper.empty())
			{
				if((oper.top() != "<")&&(oper.top() != ">"))
				{
					mal = true;
				}
				//runs until operator stackstring is not empty.
				while(!oper.empty())
				{
					tmp= remove(tmp,oper.top());
					oper.pop();
				}
			}
			//add new string to stackstring
			str.push(tmp);
			
		}
		
		//for the test case36.
		//if there are more than one string at the end
		//it is malformed. At least something is wrong.
		if(str.size()!=1)
		{
			mal = true;
		}
		
		//if it is valid, then the last element inside the
		//stackstring is our final answer.(output)
		if(mal==0 ||lineempty(line))
		{
			ofile << str.top();
			ofile<<endl;
		}
		

		//if variable mal caught anything malformed
		//during the operations, it is malformed.
		else if(mal== 1)
		{
			ofile<<"Malformed"<<endl;
		}
		
	}

	//close all ifile and ofiles.
	ifile.close();
	ofile.close();
	return 0;

}
