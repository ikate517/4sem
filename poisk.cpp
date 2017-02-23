#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector> 
#include <iostream>

const int MAX_WORD = 2000;
const int NUM = 50;
std::string prepare(const std::string& s)
{
	std::string result = s;
	std::transform(s.begin(), s.end(), result.begin(), ::tolower);
	std::string symbols = ".,/:;'!?_+=#@";
	
	// result[result.size() - 1] можно написать короче: result.back()
	for(int i = 0; i < symbols.size(); i++)
		if (result[result.size() - 1] == symbols[i])
			result.pop_back();
	return result;
}

struct Statistics 
{
	int count;
	std::string word;
};

/*
Не круто, когда в названии переменных есть цифра...это значит, что фантазия совсем кончилась + из названия 
совсем непонятно, какой смысл несут цифры.
Обычно в случае компараторов или бинарных операторов используют названия переменных
lhs и rhs : left-hand side, right-hand side
*/
bool compare(const Statistics& s1, const Statistics& s2) 
{
	if (s1.count != s2.count) 
	{
		return s1.count > s2.count;
	}
	return s1.word < s2.word;
}

int main()
{
	std::ifstream file("test.txt");
	std::map<std::string, int> m;
	if (file.is_open())
	{
		std::string word;
		while (!file.eof()) 
		{
			file >> word;
			word = prepare(word);
			m[word] += 1;
		}
		file.close();
	}
	std::vector<Statistics> s;
	s.resize(MAX_WORD);
	
	int i = 0;
	
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		s[i].word = it->first;
		s[i].count = it->second;
		i++;
	}
	
	std::sort(s.begin(), s.end(), compare);
	
	std::ofstream fout("result.txt");
	for (i = 0; i < NUM; i++) 
	{
		fout << s[i].word << " : " << s[i].count << std::endl;
	}

	return 0;
}
