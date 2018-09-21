#include "iostream"
#include "fstream"      
#include "string" 
#include <sstream>

using namespace std;

int blosum62[23][23],DNA[100][4],MatriksNW[100][100];  
string A, B;
int gap = -6;
void LoadBlosum();
void ChangeString();
void SkoringMatriks();
void PrintAlignment(int x,int y,int iterasi);
void ChangeNumber(int iterasi);
string to_string(int i);
int Maximum (int a,int b,int c);
int main (){
	cout<<"Masukkan DNA 1 : "; cin>>A;
	cout<<endl<<"Masukkan DNA 2 : "; cin>>B; cout<<endl;
	LoadBlosum();
	ChangeString();
	SkoringMatriks();
	PrintAlignment(A.length(),B.length(),0);
	return 0;
}

void LoadBlosum() {
  int x, y;
  ifstream in("BLOSUM62.txt");

  if (!in) {
    cout << "Cannot open file.\n";
    return;
  }

  for (y = 0; y < 23; y++) {
    for (x = 0; x < 23; x++) {
      in >> blosum62[x][y];
    }
    
  }

  in.close();
}

void ChangeString(){
	for (int i=0;i<A.length();i++)
    {
        switch (A[i]){
        	case 'A': DNA[i][1] = 0; break;
			case 'R': DNA[i][1] = 1; break;
			case 'N': DNA[i][1] = 2; break;
			case 'D': DNA[i][1] = 3; break;
			case 'C': DNA[i][1] = 4; break;
			case 'Q': DNA[i][1] = 5; break;
			case 'E': DNA[i][1] = 6; break;
			case 'G': DNA[i][1] = 7; break;
			case 'H': DNA[i][1] = 8; break;
			case 'I': DNA[i][1] = 9; break;
			case 'L': DNA[i][1] = 10; break;
			case 'K': DNA[i][1] = 11; break;
			case 'M': DNA[i][1] = 12; break;
			case 'F': DNA[i][1] = 13; break;
			case 'P': DNA[i][1] = 14; break;
			case 'S': DNA[i][1] = 15; break;
			case 'T': DNA[i][1] = 16; break;
			case 'W': DNA[i][1] = 17; break;
			case 'Y': DNA[i][1] = 18; break;
			case 'V': DNA[i][1] = 19; break;
			case 'B': DNA[i][1] = 20; break;
			case 'Z': DNA[i][1] = 21; break;
			case 'X': DNA[i][1] = 22; break;
		}
    }
    for (int i=0;i<B.length();i++)
    {
        switch (B[i]){
        	case 'A': DNA[i][2] = 0; break;
			case 'R': DNA[i][2] = 1; break;
			case 'N': DNA[i][2] = 2; break;
			case 'D': DNA[i][2] = 3; break;
			case 'C': DNA[i][2] = 4; break;
			case 'Q': DNA[i][2] = 5; break;
			case 'E': DNA[i][2] = 6; break;
			case 'G': DNA[i][2] = 7; break;
			case 'H': DNA[i][2] = 8; break;
			case 'I': DNA[i][2] = 9; break;
			case 'L': DNA[i][2] = 10; break;
			case 'K': DNA[i][2] = 11; break;
			case 'M': DNA[i][2] = 12; break;
			case 'F': DNA[i][2] = 13; break;
			case 'P': DNA[i][2] = 14; break;
			case 'S': DNA[i][2] = 15; break;
			case 'T': DNA[i][2] = 16; break;
			case 'W': DNA[i][2] = 17; break;
			case 'Y': DNA[i][2] = 18; break;
			case 'V': DNA[i][2] = 19; break;
			case 'B': DNA[i][2] = 20; break;
			case 'Z': DNA[i][2] = 21; break;
			case 'X': DNA[i][2] = 22; break;
		}
}
}
void SkoringMatriks(){
	int x, y;
	MatriksNW[0][0] = 0;
	for (y = 1; y <= A.length(); y++) {
	MatriksNW[y][0] = gap*y;
	}
	cout<<"       ";
    for (x = 1; x <= B.length(); x++) {
    MatriksNW[0][x] = gap*x;
    cout<<B[x-1]<<"   ";
    }
    cout<<endl;
  
  for (y = 1; y <= A.length(); y++) {
    for (x = 1; x <= B.length(); x++) {
    MatriksNW[y][x] = Maximum(MatriksNW[y-1][x-1]+blosum62[DNA[y-1][1]][DNA[x-1][2]] , MatriksNW[y][x-1]+gap , MatriksNW[y-1][x]+gap);	
	}
  }
  cout<<"  ";
  int i;
  string matriks;
  for (y = 0; y <= A.length(); y++) {
    for (x = 0; x <= B.length(); x++) {
   	matriks = to_string(MatriksNW[y][x]);
   	cout<<matriks;
    for (i = matriks.length(); i < 4 ; i++){
    cout<<" ";
	}
	
	}
	cout<<endl;
	cout<<A[y]<<" ";
  }
 }
string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
int Maximum (int a,int b,int c)
{
	if(a>=b && a>=c)
   {
		return a;
	}
   else if(b>=a && b>=c)
   {
      	return b;
   }
   else
   {
      	return c;
   }
}
void PrintAlignment(int x,int y,int iterasi){
	if (x<=0 && y<=0){
		ChangeNumber(iterasi);
	}
	else if (MatriksNW[x][y] == (MatriksNW[x-1][y]+gap)) {
	if (x < 1) {PrintAlignment(x-1,y,iterasi);
	} else{
     DNA[iterasi][0] = DNA[x-1][1];
     DNA[iterasi][3] = 50;
     PrintAlignment(x-1,y,iterasi+1);}
	} else if (MatriksNW[x][y] == (MatriksNW[x][y-1]+gap)){
	if (y < 1) {PrintAlignment(x,y-1,iterasi);
	} else {
	 DNA[iterasi][0] = 50;
	 DNA[iterasi][3] = DNA[y-1][2];
	 PrintAlignment(x,y-1,iterasi+1);
	} 
	} else {
			if (x < 1) {
				 DNA[iterasi][0] = 50;
				 DNA[iterasi][3] = DNA[y-1][2];
	} else if (y < 1) {
				 DNA[iterasi][3] = 50;
				 DNA[iterasi][0] = DNA[x-1][2];
	} else {
	 DNA[iterasi][0] = DNA[x-1][1];
	 DNA[iterasi][3] = DNA[y-1][2];
	}
	 PrintAlignment(x-1,y-1,iterasi+1);
	}
}

void ChangeNumber(int iterasi){
	cout<<endl<<"DNA 1 : ";
	for (int i = iterasi-1;i >= 0;i--)
    {
        switch (DNA[i][0]){
        	case 0: cout<<'A'; break;
			case 1: cout<<'R'; break;
			case 2: cout<<'N'; break;
			case 3: cout<<'D'; break;
			case 4: cout<<'C'; break;
			case 5: cout<<'Q'; break;
			case 6: cout<<'E'; break;
			case 7: cout<<'G'; break;
			case 8: cout<<'H'; break;
			case 9: cout<<'I'; break;
			case 10: cout<<'L'; break;
			case 11: cout<<'K'; break;
			case 12: cout<<'M'; break;
			case 13: cout<<'F'; break;
			case 14: cout<<'P'; break;
			case 15: cout<<'S'; break;
			case 16: cout<<'T'; break;
			case 17: cout<<'W'; break;
			case 18: cout<<'Y'; break;
			case 19: cout<<'V'; break;
			case 20: cout<<'B'; break;
			case 21: cout<<'Z'; break;
			case 22: cout<<'X'; break;
			default: cout<<"-";
		}
    }
	cout<<endl<<"DNA 2 : ";
	for (int i = iterasi-1;i >= 0;i--)
    {
        switch (DNA[i][3]){
        	case 0: cout<<'A'; break;
			case 1: cout<<'R'; break;
			case 2: cout<<'N'; break;
			case 3: cout<<'D'; break;
			case 4: cout<<'C'; break;
			case 5: cout<<'Q'; break;
			case 6: cout<<'E'; break;
			case 7: cout<<'G'; break;
			case 8: cout<<'H'; break;
			case 9: cout<<'I'; break;
			case 10: cout<<'L'; break;
			case 11: cout<<'K'; break;
			case 12: cout<<'M'; break;
			case 13: cout<<'F'; break;
			case 14: cout<<'P'; break;
			case 15: cout<<'S'; break;
			case 16: cout<<'T'; break;
			case 17: cout<<'W'; break;
			case 18: cout<<'Y'; break;
			case 19: cout<<'V'; break;
			case 20: cout<<'B'; break;
			case 21: cout<<'Z'; break;
			case 22: cout<<'X'; break;
			default : cout<<"-";
		}
    }
    cout<<endl<<"Best Score : "<<MatriksNW[A.length()][B.length()];
}
