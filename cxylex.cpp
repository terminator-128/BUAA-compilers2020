#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>


using namespace std;

enum lexType
{
	UNKOWNSY,//	0
	BEGINSY,//	1
	ENDSY,//	2
	FORSY,//	3
	IFSY,//		4
	THENSY,//	5
	ELSESY,//	6
	IDENTSY,//	7
	INTSY,//	8
	COLONSY,//	9
	PLUSSY,//	10
	STARSY,//	11
	COMMASY,//	12
	LPARSY,//	13
	RPARSY,//	14
	ASSIGNSY,//	15
};


lexType symbol;


fstream infile;		// 当前文件流，参数路径读入的文件内容

vector<char> token;	// 字符数组，用于存放单词的字符串

string identity;

char current;		// 单个字符，存放当前读入的字符

int num;			// 整形数字，存放当前读入整形数值


void clearToken()	// 清空单词字符数组
{
	token.clear();
	return;
}


bool getChar()	// 向前读进一个字符
{
	if (infile.get(current)){
		infile.flush();
		return true;
	}
	return false;
}

void retract()	// 向后退回上个字符
{
	infile.putback(current);
	return;
}

void identify()
{
	identity.assign(token.begin(),token.end());
	return;
}


lexType reserver()	// 查找保留字, 返回值为0, 则代表token中的字符串是一个标识符; 否则为保留字编码, 返回当前保留字的类编码
{
	identify();
	if(!identity.compare("BEGIN")) return BEGINSY;
	else if (!identity.compare("END")) return ENDSY;
	else if (!identity.compare("FOR")) return FORSY;
	else if (!identity.compare("IF")) return IFSY;
	else if (!identity.compare("THEN")) return THENSY;
	else if (!identity.compare("ELSE")) return ELSESY;
	else return IDENTSY;
}

void catToken()	// 每次电泳把当前char中读进的字符与当前token字符数组的字符串连接
{
	token.push_back(current);
	return;
}

int transNum()	// 将token中的字符串转换成整数数值，返回这个数值
{
	string token_str;
	return stoi(token_str.assign(token.begin(),token.end()));
}

void error()	// 出错处理函数
{
	// perror("好像发生了什么错误\n");
	return;
}




bool isSpace()
{

	return current==' '? true : false;
}

bool isNewline()
{
	return current=='\r'||current=='\n'? true : false;
}

bool isTab()
{
	return current=='\t'? true : false;
}

bool isLetter()
{
	if (current>='A'&& current<='Z')
		return true;
	else if (current >= 'a' && current<='z')
		return true;
	else
		return false;
}

bool isDigit()
{
	return (current>='0'&&current<='9')? true : false;
}

bool isColon()
{
	return current==':'? true : false;
}


bool isPlus()
{
	return current=='+'? true : false;
}

bool isStar()
{
	return current=='*'? true : false;
}

bool isComma()
{
	return current==','? true : false;
}

bool isLpar()
{
	return current=='('? true : false;
}

bool isRpar()
{
	return current==')'? true : false;
}

bool isEqu()
{
	return current=='='? true : false;
}

int getsysm()
{
	// 清空标识符
	clearToken();
	
	do{getChar();}
	while(isSpace()||isNewline()||isTab());

	// cout << current;

	if(isLetter())	// 判断是否为标识符 
	{
		while(isLetter() || isDigit()){
			catToken();
			if(!getChar())
				break;
		}

		if(!infile.eof())
			retract();
		
		// string token_str;
		// cout <<token_str.assign(token.begin(),token.end());

		symbol = reserver();
	}
	else if(isDigit()) // 判断是否为常数(整数)
	{	
		while(isDigit()){
			catToken();
			if(!getChar())
				break;
		}
		if(!infile.eof())
			retract();

		num = transNum();

		symbol = INTSY;
	}
	else if (isColon())
	{
		getChar();

		if (isEqu())
		{
			symbol = ASSIGNSY;
		}
		else{
			retract();
			symbol = COLONSY;
		}
	}
	else if (isPlus())	{ symbol = PLUSSY;}		// 	判断 +
	else if (isStar())	{ symbol = STARSY;}		// 	判断 *
	else if (isComma())	{ symbol = COMMASY;}		// 	判断 ,
	else if (isLpar())	{ symbol = LPARSY;}		// 	判断 (
	else if (isRpar())	{ symbol = RPARSY;}		// 	判断 )
	else{
		error();
		symbol = UNKOWNSY;
		return UNKOWNSY;
	}


	return symbol;
}


int main(int argc, char const *argv[])
{
	// 目前只会有一个路径名, 即 argc = 1
	// 打开文件
	infile.open(argv[1], ios::in);

	// 定位到 infile 第一个字节
	infile.seekg(0,ios::beg);

	// if(infile.fail())
	// 	cout << "fail to read the file \""<<argv[1]<<"\" by the given location." << endl;
	// else
	// 	cout << "open file \""<<argv[1]<<"\" successfully"<<endl;


	while(!infile.eof()&&getsysm()){
		switch(symbol){
			case  1: cout<<"Begin\n";break;
			case  2: cout<<"End\n";break;
			case  3: cout<<"For\n";break;
			case  4: cout<<"If\n";break;
			case  5: cout<<"Then\n";break;
			case  6: cout<<"Else\n";break;
			case  7: cout<<"Ident("<<identity<<")\n";break;
			case  8: cout<<"Int("<<num<<")\n";break;
			case  9: cout<<"Colon\n";break;
			case 10: cout<<"Plus\n";break;
			case 11: cout<<"Star\n";break;
			case 12: cout<<"Comma\n";break;
			case 13: cout<<"LParenthesis\n";break;
			case 14: cout<<"RParenthesis\n";break;
			case 15: cout<<"Assign\n";break;
		}
	}

	if(!infile.eof()){
		cout<<"Unknown\n";
	}

	infile.close();

	return 0;
}
