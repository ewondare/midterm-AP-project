//Midterm Project AP
//Authors: Parinaz Kanan, Nazanin Zareirad
#include "classDeclaration.h"
#include <bits/stdc++.h>
using namespace std;
vector <Article> articles;
//calculate the similarity between two articles using the Jaccard Index.
//For further information please refer to https://www.learndatasci.com/glossary/jaccard-similarity/
int Similarity(int id1, int id2){
	std::string s;
	std::vector<std::string> v1, v2, v3;
	//convert files into vector
	v1 = articles[id1].convert2Vec();
	v2 = articles[id2].convert2Vec();
	//converts vectors to lowercase
	for(std::string &s : v1){
    	transform(s.begin(), s.end(), s.begin(), [](char c){ return tolower(c); });
	}
	for(std::string &s : v2){
    	transform(s.begin(), s.end(), s.begin(), [](char c){ return tolower(c); });
	}

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int size1, size2, size3;
    size1 = v1.size();
    size2 = v2.size();
    size3 = v3.size();

    //find the intersection of two vectors and insert it into a new one
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    //percentage of similarity using the set intersection formula
    int similarity = (100 * size3) / (size1 + size2 - size3);
    return similarity;
}

//check for similarity between articles of a user with other articles except the references
bool Plagarism(int id1){
	for (int i = 0; i < articles.size(); i++){
		for (int j = 0; j < articles[id1].getIDReference().size(); j++){
			if (i != articles[id1].getIDReference()[j]){
				if (Similarity(id1 , i) > 50){ //plagarism is detected by over %50 similarity
					return true;
				}
			}
		}
	}
	return false;
}
void Evaluate(std::string username_){
	// Evaluates the function based on parameters determined by preceding functions
	for (int i = 0; i < articles.size(); i++){
        if (articles[i].getUser() == username_){
            if(articles[i].Validation()){
                cout << "Article with id number " << i << " is accepted." << endl;
            }
            else {
                cout << "Article with id number " << i << " is rejected due to problems in: " << articles[i].errorType << endl;
            }
        }
	}
	return;
}

int main() {
	cout << "Hi";
	vector <User> user;
	string command,instruction;
	while (true) {
            //menu
		cout << "Welcome to Article Evaluation Program!\n"
			 "Please enter your chosen command:\n"
			 "SignUp\n"
			 "LogIn\n"
			 "Exit\n";
		cin >> command;
		if (command == "SignUp") {
			cout << "please enter your chosen username and password." << endl;
			string u,p;
			int s = user.size();
			cin >> u;
			cin >> p;
			if (signupcheck(user, u, s)) {
				adduser(user, u, p);
				cout << "user succesfully made." << endl;
			} else {
				cout<<"username already exists."<<endl;
			}
		}
		else if (command == "LogIn") {
			cout << "please enter your username and password." << endl;
			string u, p;
			cin >> u;
			cin >> p;
			int s = user.size();
			if(!logincheck(user, u, p, s)) {
				cout << "entered username or password is not correct." << endl;
				cout << "please try again" << endl;
			}
			if (logincheck(user, u, p, s)){
				cout << "successfully logged in." << endl;
				int whiletemp=0;
				while(whiletemp<10){
                    cout << "Please enter the instruction:\n"
                                "1.SendArticle\n"
                                "2.TrackArticle\n"
                                "3.EvaluateArticle\n"
                                "4.LogOut\n";
					cin>>instruction;
					if (instruction == "1"){
                        string name_, date_, author_,filename_;
                        int numReference, reference_;
                        vector<int> references;
                        cout << "Please enter the details of your article including:" << endl;
                        cout <<  "Name: " << endl;
                        cin.ignore();
                        getline(cin, name_);
                        cout << "Date: " << endl;
                        cin >> date_;
                        cout << "Author: " << endl;
                        cin >> author_;
                        cout << "Enter the number of articles you are referencing:" << endl;
                        cin >> numReference;
                        cout << "Enter the id number of articles you are referencing: " << endl;
                        for (int i = 0; i < numReference; i++){
                            cin >> reference_;
                            references.push_back(reference_);
                        }
                        cout << "Filename: (including the .txt extension)" << endl;
                        cin >> filename_;
                        Article temp(u, name_, date_, author_, articles.size(), references, filename_);
                        cout << "Article was submitted." << endl;
                        articles.push_back(temp);
                        cout<<articles.size()-1;

					} else if (instruction=="2") {
						int _id;
						cout<<"please enter your article's id"<<endl;
						cin>>_id;
                        if (articles[_id].Validation()) {
                            cout << "Article with id number " << _id << " was accepted." << endl;
                        }
                        else{
                                cout << "Article with id number " << _id << " was rejected due to problems in: " << articles[_id].errorType << endl;
                        }
                    }
					else if (instruction == "3"){
						Evaluate(u);
					}
                    else if (instruction=="4") {
						cout<<"logged out."<<endl;
						whiletemp=12;
					}
				}
			}
		}
		else if  (command=="Exit") {
			return false;
		}
	}
	return 0;
}




