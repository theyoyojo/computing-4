#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void elimDups(vector<string> &words)
{
	// sort words alphabetically so we can find the duplicates
	sort(words.begin(), words.end());
	
	// unique reorders the input range so that each word appears once in the
	// front portion of the range and returns an iterator one past the unique range
	auto end_unique = unique(words.begin(), words.end());
	
	// erase uses a vector operation to remove the nonunique elements
	words.erase(end_unique, words.end());
}

void biggies(vector<string> &words,
             vector<string>::size_type sz)
{
	elimDups(words); // put words in alphabetical order
	
	// sort words by size, but maintain alphabetical order for words of the same size
	stable_sort(words.begin(), words.end(),
				[](const string &a, const string &b)
					{ return a.size() < b.size(); });
	
	// get an iterator to the first element whose size() is >= sz
	auto wc = find_if(words.begin(), words.end(),
					  [sz](const string &a) { return a.size() >= sz; });
					  
	// compute the number of elements with size >= sz
	auto count = words.end() - wc;
	
	cout << count << " word(s) of length " << sz << " or longer" << endl;
	
	// print words of the given size or longer, each one followed by a space	 
	for_each(wc, words.end(),
			 [](const string &s){ cout << s << " "; });
			 
	cout << endl;
}

int main()
{
	vector<string> my_words = {"A", "An", "Any", "And", "Albatross", "Aardvark"};
	
	biggies(my_words, 3);
	
	return 0;
}