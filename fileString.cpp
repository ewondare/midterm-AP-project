#include <bits/stdc++.h>
std::string file2String(){
	std::string outputstring;
	std::string buffer;
	std::ifstream input("a1.txt");
	while (std::getline(input, buffer)){ //read file line by line and appends to the string and return it
		outputstring += (buffer);
        if(outputstring[outputstring.length() - 1] != ' '){
        	outputstring += ' ';
		}
	}
    return outputstring;
}
int main(){
	std::cout << file2String();
	return 0;
}