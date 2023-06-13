#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H
#include <bits/stdc++.h>
class Article
{
	private:
		std::string user, name, date, author, filename;
		int ID;
		std::vector <int> IDReference;
	public:
		std::vector<std::string> fileVec;
		std::string errorType;
		Article(std::string user1, std::string name1, std::string date1, std::string author1, int ID1, std::vector<int> IDReference1, std::string filename1);
		~Article();
		void setUser(std::string);
		void setName(std::string);
		void setDate(std::string);
		void setAuthor(std::string);
		void setID(int);
		void setIDReference(int);
		void setFilename();
		std::string getUser();
		std::string getName();
		std::string getDate();
		std::string getAuthor();
		int getID();
		std::vector<int> getIDReference();
		std::string getFilename();
		int Words();
		int Paragraphs();
		int Title();
		std::vector<std::string> convert2Vec(); //converts a text file into a vector
		std::string file2String(); //convert a text file into string
		int mostFrequent(); //most frequent word
		bool punctuationcheck();
		bool Validation(); //validates a single article
		bool Evaluate(std::string username_); //evaluates all articles submitted by a certain user
};
class User {
		private:
		std::string username;
	    std::string password;
	public:
		bool condition;
		User();
		User(std::string , std::string);
		~User();
		std::string getusername();
		std::string getpassword();

};

int Similarity(int, int); //find the percentage of similarity between two articles using the Jaccard's algorithm
void adduser(std::vector<User>& , std::string , std::string);
bool signupcheck(std::vector<User>& , std::string , int); //check for unique username
bool logincheck(std::vector<User>&, std::string , std::string , int); //check for correct login info
#endif
