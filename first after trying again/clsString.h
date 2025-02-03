#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsString
{
private:
	string _value;

	static char _InvertCharCase(char cr)
	{
		if (isalpha(cr))
		{
			if (islower(cr))
				return toupper(cr);

			if (isupper(cr))
				return tolower(cr);
		}
		return cr;
	}
	static bool _IsVowel(char cr)
	{
		return (cr == 'a' || cr == 'o' || cr == 'i' || cr == 'e' || cr == 'u');
	}

public:

	clsString()
	{
		_value = "";
	}
	clsString(string s1)
	{
		_value = s1;
	}
	void setString(string s1)
	{
		_value = s1;
	}
	string getString()
	{
		return _value;
	}
	_declspec(property(get = getString, put = setString))string value;

	static void PrintEveryFirstLetter(string sentence)
	{
		if (!isspace(sentence[sentence.find(" ") + 1]))
			cout << sentence.at(0) << endl;
		while (sentence.find(" ") != sentence.npos)
		{
			if (!isspace(sentence[sentence.find(" ") + 1]))
			{
				cout << sentence[sentence.find(" ") + 1] << endl;
			}
			sentence = sentence.substr(sentence.find(" ") + 1);
		}
	}
	void PrintEveryFirstLetter()
	{
		PrintEveryFirstLetter(_value);
	}
	static void MakeEveryFirstLetterCapital(string sentence)
	{
		bool isfirstletter = true;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (isfirstletter && isalpha(sentence[i]))
			{

				sentence[i] = toupper(sentence[i]);
			}
			isfirstletter = (sentence[i] == ' ' ? true : false);
		}
		cout << sentence;
	}
	void MakeEveryFirstLetterCapital()
	{
		MakeEveryFirstLetterCapital(_value);
	}

	static void MakeEveryFirstLetterLowerCase(string sentence)
	{
		bool isfirstletter = true;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (isfirstletter && isalpha(sentence[i]))
			{

				sentence[i] = tolower(sentence[i]);
			}
			isfirstletter = (sentence[i] == ' ' ? true : false);
		}
		cout << sentence;
	}

	void MakeEveryFirstLetterLowerCase()
	{
		MakeEveryFirstLetterLowerCase(_value);
	}

	static string UpperEveryLetter(string sentence)
	{

		for (int i = 0; i < sentence.length(); i++)
		{
			sentence[i] = toupper(sentence[i]);

		}
		return sentence;
	}

	string UpperEveryLetter()
	{
		return UpperEveryLetter(_value);
	}

	static string LowerEveryLetter(string sentence)
	{

		for (int i = 0; i < sentence.length(); i++)
		{
			sentence[i] = tolower(sentence[i]);
		}
		return sentence;
	}

	string LowerEveryLetter()
	{
		return LowerEveryLetter(_value);
	}

	static string InverWholeSentenceCase(string sentence)
	{
		for (int i = 0; i < sentence.length(); i++)
		{
			sentence[i] = _InvertCharCase(sentence[i]);
		}
		return sentence;
	}
	string InverWholeSentenceCase()
	{
		return InverWholeSentenceCase(_value);
	}


	static int CountCapitalLetters(string& sentence)
	{
		int counter = 0;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (isupper(sentence[i]))
				counter++;
		}
		return counter;
	}
	int CountCapitalLetters()
	{
		return CountCapitalLetters(_value);
	}
	static int CountSmallLetters(string &sentence)
	{
		int counter = 0;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (islower(sentence[i]))
				counter++;
		}
		return counter;
	}
	int CountSmallLetters()
	{
		return CountSmallLetters(_value);
	}

	static int CountLetter(string& sentence, char lettertocheck)
	{
		int counter = 0;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (sentence[i] == lettertocheck)
				counter++;
		}
		return counter;
	}

	int CountLetter(char lettertocheck)
	{
		return CountLetter(_value, lettertocheck);
	}

	static int CountLetterWihtoutCaseSensitivity(string& sentence, char lettertocheck)
	{
		int counter = 0;
		char invertedletter = _InvertCharCase(lettertocheck);
		for (int i = 0; i < sentence.length(); i++)
		{
			if (sentence[i] == lettertocheck || sentence[i] == invertedletter)
				counter++;
		}
		return counter;
	}
	int CountLetterWihtoutCaseSensitivity(char lettertocheck)
	{
		return CountLetterWihtoutCaseSensitivity(_value, lettertocheck);
	}

	static int CountVowels(string sentence)
	{
		int counter = 0;
		for (int i = 0; i < sentence.length(); i++)
		{
			_IsVowel(sentence[i]) == (true) ? counter++ : NULL;
		}
		return counter;
	}
	int CountVowels()
	{
		return CountVowels(_value);
	}
	static void PrintVowels(string sentence)
	{
		for (int i = 0; i < sentence.length(); i++)
		{
			if (_IsVowel(sentence[i]))
			{
				cout << sentence[i] << "  ";
			}
		}
		cout << endl;
	}
	void PrintVowels()
	{
		PrintVowels(_value);
	}

	static void PrintEachWord(string sentence)
	{

		string delim = " ";
		short pos = 0;
		string sword;
		while ((pos = sentence.find(delim)) != std::string::npos)
		{
			sword = sentence.substr(0, pos);
			if (sword != "")
			{
				cout << sword << endl;
			}
			sentence.erase(0, pos + delim.length());

		}
		if (sentence != "")
		{
			cout << sentence << endl;
		}
	}

	void PrintEachWord()
	{
		PrintEachWord(_value);
	}

	static int CountWords(string sentence)
	{

		string delim = " ";
		short pos = 0;
		int counter = 0;
		string sword;
		while ((pos = sentence.find(delim)) != std::string::npos)
		{
			sword = sentence.substr(0, pos);
			if (sword != "")
			{
				counter++;
			}
			sentence.erase(0, pos + delim.length());

		}
		if (sentence != "")
		{
			counter++;
		}
		return counter;
	}
	int CountWords()
	{
		return CountWords(_value);
	}
	static vector<string> Split(string sentence, string delimiter)
	{

		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = sentence.find(delimiter)) != std::string::npos)
		{
			sWord = sentence.substr(0, pos); // store the word   
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			sentence.erase(0, pos + delimiter.length());  /* erase() until positon and move to next word. */
		}

		if (sentence != "")
		{
			vString.push_back(sentence); // it adds last word of the string.
		}

		return vString;
	}
	vector<string> Split(string delimiter)
	{
		return Split(_value, delimiter);
	}

	static string TrimLeft(string sentence)
	{
		if (sentence == "")
		{
			return "";
		}
		short pos = 0;

		while (!isalpha(sentence[pos]))
		{
			pos++;
		}

		sentence.erase(0, pos);

		return sentence;
	}
	string TrimLeft()
	{
		return TrimLeft(_value);
	}
	static string TrimRight(string sentence)
	{
		if (sentence == "")
		{
			return "";
		}
		short pos = sentence.length();

		while (!isalpha(sentence[pos]))
		{
			pos--;
		}

		sentence.erase(pos + 1, sentence.length());

		return sentence;
	}
	string TrimRight()
	{
		return	TrimRight(_value);
	}
	static string Trim(string sentence)
	{

		return TrimRight(TrimLeft(sentence));
	}
	string Trim()
	{
		return Trim(_value);
	}
	static string ReverseWordsInString(string sentence)
	{
		vector<string> vString;
		string S2 = "";
		vString = Split(sentence, " ");
		
		vector<string>::iterator iter = vString.end();
		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1); //remove last space.
		return S2;
	}
	string ReverseWordsInString()
	{
		return ReverseWordsInString(_value);
	}
	static string ReplaceWordInString(string s1, string strtoreplace, string replaceto)
	{
		short pos = s1.find(strtoreplace);


		while (pos != std::string::npos)
		{
			s1 = s1.replace(pos, strtoreplace.length(), replaceto);
			pos = s1.find(strtoreplace);

		}
		return s1;

	}
	string ReplaceWordInString( string strtoreplace, string replaceto)
	{
		return ReplaceWordInString(_value, strtoreplace, replaceto);
	}

	static string RemovePunctuation(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}
	string RemovePunctuation()
	{
		return RemovePunctuation(_value);
	}
	static string JoinString(vector <string>& seperate, string delim ="#//#")
	{

		string fullsentence = "";
		for (string& word : seperate)
		{
			fullsentence = fullsentence + word + delim;
		}
		return fullsentence.substr(0, fullsentence.length() - delim.length());
	}

};

