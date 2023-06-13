#include <bits/stdc++.h>
using namespace std;
string file2String(){
	string outputstring;
	string buffer;
	string filename;
	cin >> filename;
	ifstream input(filename);
	while (getline(input, buffer))
    outputstring += (buffer + '\n');
    return outputstring;
}
punctuationcheck () {
 string s = file2String();
 bool determine=true;
 int i=1,n=s.size();
 s+=" ";

 while ( i<n) {

  if (s[i]=='.' || s[i]=='?' || s[i]=='!' || s[i]==',' ) {
    if (s[i+1]!=' '  && s[i+1]!='\n') {
    	cout << "space" << endl;
    determine=false;
    i=s.size()+2;

    }
	else if (s[i-1]==' ') {
    determine=false;
    i=s.size()+2;
   }
   i++;
  }

  else {
   i++;
  }
 }
 if (determine==true) {
 int countp=0;
 i=1;
 while ( i<n) {
  if(s[i]=='(') {
   countp++;
   i++;
  } else if (s[i]==')') {
   countp--;
   i++;
  } else {
   i++;
  }
 }
 if (countp!=0) {
  determine=false;
  cout << "Parathesis" << endl;
 }
 }
 if (determine==true) {
  i=1;
  while ( i<n-1) {
    if (s[i]=='.' || s[i]=='?' || s[i]=='!' ) {
     char *x = new char;
     *x=s[i+2];
     if ( *x<65 || *x>90 ) {
      determine=false;
      cout << "Capitalization" << endl;
      delete x;
      break;
     }

    } else {
      i++;
     }
  }
 }
 return determine;
}
int main(){
	file2String();
	if (punctuationcheck){
		cout << "Accpet";
	}
	else {
		cout << "REject";
	}
}