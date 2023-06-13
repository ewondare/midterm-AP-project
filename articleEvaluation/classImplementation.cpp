#include "classDeclaration.h"

//User Methods
//User Constructors
User::User() {}

User::User(std::string u , std::string p){
		this->username=u;
		this->password=p;
		}
User::~User()
{
}


//User setters and getters
std::string User::getusername(){
		return this->username;
		}
std::string User::getpassword(){
		return this->password;
		}


//Article Methods
//Article Constructors
Article::Article(std::string user1, std::string name1, std::string date1, std::string author1, int ID1, std::vector<int> IDReference1, std::string filename1 )
{
	user = user1;
	name = name1;
	date = date1;
	author = author1;
	ID = ID1;
	IDReference = IDReference1;
	filename = filename1;
}

Article::~Article()
{

}
//Article setters and getters
void Article::setUser(std::string user1){
	user = user1;
}
void Article::setName(std::string name1){
	name = name1;
}
void Article::setDate(std::string date1){
	date = date1;
}
void Article::setAuthor(std::string author1){
	author = author1;
}
void Article::setID(int ID1){
	ID = ID1;
}
void Article::setIDReference(int numReference){
	int temp;
	for (int i=0 ; i<numReference ; i++) {
		std::cout<<"please enter the id of used article: "<<std::endl;
		std::cin >> temp;
		IDReference.push_back(temp);
	}

}
void Article::setFilename(){
	std::cout << "Please enter the file name (including the .txt extension)" << std::endl;
	std::cin >> filename;
	std::cout << "File entered" << std::endl;
}
std::string Article::getUser(){
	return user;
}
std::string Article::getName(){
	return name;
}
std::string Article::getDate(){
	return date;
}
std::string Article::getAuthor(){
	return author;
}
int Article::getID(){
	return ID;
}

std::vector<int> Article::getIDReference(){
	return IDReference;
}
std::string Article::getFilename(){
	return filename;
}

//Count the number of words in a file
int Article::Words(){
	std::ifstream ifs(filename);
	int words = 0;
	std::string word;
	while(ifs >> word){
		++words;
	}
	return words;

}

//count the number of paragraphs in a file
int Article::Paragraphs(){
	filename = this->filename;
	int paragraph = 0;
	std::string mytext;
	std::ifstream ifs(filename);
	while(getline(ifs, mytext)){
		if(mytext != " "){
			paragraph++;
		}
	}
	return paragraph;
}

//count the number of words in the title
int Article::Title(){
	int title = 1;
	std::string namet = this->getName();
	for (int i = 0; i < namet.length(); i++){
		if (namet[i] == ' '){
			title++;
		}
	}
	return title;
}

//find the most frequent word in a file
int Article::mostFrequent(){
	std::vector<std::string> a = this->convert2Vec(); //first we convert the file into a vector for manipulation
	for(std::string &s : a){
        //convert the whole vector into lowercase
    	transform(s.begin(), s.end(), s.begin(), [](char c){ return tolower(c); });
	}
	sort(a.begin(), a.end());
    // Find the max frequency using linear traversal
    int max_count = 1, curr_count = 1;
    std::string res = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1])
            curr_count++;
        else
            curr_count = 1;

        if (curr_count > max_count) {
            max_count = curr_count;
            res = a[i - 1];
        }
    }
    return max_count;
}

//convert text file to vector for further uses
std::vector<std::string> Article::convert2Vec(){
	std::ifstream myfile(filename);
        std::copy(std::istream_iterator<std::string>(myfile),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(fileVec)); //reads the contents of myfile and
                  //copies them by inserting to the back of vector filevec and returns it
    return fileVec;
}

//convert the whole text file to a string for further uses
std::string Article::file2String(){
	std::string outputstring;
	std::string buffer;
	std::ifstream input(getFilename());
	while (std::getline(input, buffer)){ //read file line by line and appends to the string and return it

		outputstring += (buffer);
        if(outputstring[outputstring.length() - 1] != ' '){
        	outputstring += ' ';
		}
	}
    return outputstring;
}

//check for correct punctuation
bool Article::punctuationcheck () {
    std::string s=this->file2String();
    bool determine=true;
    int i = 1,n = s.size();
    s += " "; //adds a space to the end of file to make the last period uniform with the whole structure
    //index by index search
    while (i < n) {

        //check for space after each punctuation mark
        if(s[i] == '.' || s[i] == '?' || s[i] == '!' || s[i]== ',') {
            if (s[i+1]!=' ' && s[i+1]!='\n') {
            determine=false;
            break;
            }
            // there should be no space before punctuation marks
            else if (s[i-1]==' '){
                determine=false;
                break;
            }
            //if space-punctuation is correct skips to next index
            i++;
        }
        else{
        // if index is not punctuation mark skips to next index
            i++;
        }
    }
    if (determine == true) {
        int countp = 0; //parentheses counter
        i=1;
        while (i < n) {
            if(s[i] == '(') {
            countp++;//counts the number of opening paranthesis
            i++;
            }else if (s[i] == ')') {
                countp--;//counts the number of closing paranthesis
                i++;
            }else {
                i++;
            }
        }
    //checks for equal opening and closing parenthesis
        if (countp != 0) {
            determine = false;
            return determine;
        }
    }//can be merged with the previous if statement

    if (determine == true) {
        i = 1;
  //skips the last character since it's a dot
        while ( i < n - 2) {
            if (s[i]=='.' || s[i]=='?' || s[i]=='!' ) {
            char *x = new char;
            *x = s[i+2]; // the first letter of the word after punctuation mark must be capitalized
            if ( *x < 65 || *x > 90 ) {
                determine = false;
            delete x;
            break;
            }
            }
            i++;
        }
    }
 return determine;
}

//check for similarity between articles
bool Plagarism(int);

//Validates an article by criteria described in the instruction
bool Article::Validation(){
	if (!this->punctuationcheck()){
        errorType = "Puncutuation";
		return false;
	}
	else if (this->Title()>12){
	    errorType = "Title Length";
		return false;
	}
	else if (this->Paragraphs() < 3){
	    errorType = "Number of paragraphs";
		return false;
	}
	else if ((100 > this->Words()) || (this->Words() > 5000)){
	    errorType = "Number of words";
		return false;
	}
	else if (Plagarism(this->ID)){
	    errorType = "Plagarism";
		return false;
	}
	else if (mostFrequent() > 50){
	    errorType = "Repetition";
		return false;
	}
	else{
		return true;
	}

}
void Evaluate(std::string username_); //evaluate all articles of a user

// normal(public functions):

void adduser(std::vector<User>& user , std::string u , std::string p) {
	User temp_persona(u , p);
	user.push_back(temp_persona);

}
bool signupcheck(std::vector<User>& user , std::string u , int s) {

	for (int i=0 ; i<s ; i++) {
		if (user[i].getusername()==u) {
			return false;
		}
	}
	return true;
}

bool logincheck(std::vector<User>& user , std::string u , std::string p , int s ) {
    for (int i=0 ; i<s ; i++) {
		if (user[i].getusername()==u) {
			if (user[i].getpassword()==p) {
				user[i].condition=true;
				return true;
			} else {
				user[i].condition=false;
				return false;
			}

		}
	}
	return false;
}





