/*************************************************************************************************************************
Program: seqGen
Contributors: Dan Mourich [mourichd@sarepta.com] Cas Donoghue [cas.donoghue@gmail.com] , [Michelle Domini dominimn@gmail.com]
Purpose: Print the reverse compliment of discrete lengths of a target sequence representing PMO design. 
*************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std; 

string check(string s);

int main()
{
	string spliceA_in = "0";
	string exon_in = "0";
	string spliceD_in = "0";
	string spliceA = "0";
	string exon = "0";
	string spliceD = "0";
	string total = "0"; 
	string setName; 
	string totalComp; 
	int compoundName; 
	int walkVar; 
	int compoundLen; 
	int counter = 0; 
	vector<char> holdVector; 
	string outFileName;
	string outFileName2; 
	int SP;
	int SAI;
	int EXE;
	int SDI;
	int b; 
	int SDa; 
	int FLAG = 0; 
	
	cout << "***************************************************************************************************" << endl; 
	cout << "					Welcome to seqGen!					    " << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl; 	 
	cout << "The user will provide target sequence data and targeting information." << endl;
	cout << "The program will output data to two text files named according to the input sequence identifier." << endl;
	cout << "The data text files will be populated in the directory that the instance of seqGen you are running." << endl;
	cout << "****************************************************************************************************" << endl;
	cout << endl; 
   
	cout << "Enter compound Name Identifier. This identifier will be used in sequence and file naming." << endl; 
	getline(cin, setName);

	cout << "Enter target Splice Acceptor intron (5'->3') or enter the number 0 if NA" << endl; 
	getline(cin, spliceA_in);
	cout << "Enter target Exon (5'->3') or enter the number 0 if NA" << endl; 
	getline(cin, exon_in);
	cout << "Enter target Splice Donor intron (5'->3') or enter the number 0 if NA" << endl; 
	getline(cin, spliceD_in);

	if(spliceA_in != "0")
	{
		spliceA = check(spliceA_in);
		for(int c= 0; c < spliceA.size();c++)
		{
			spliceA[c] = tolower(spliceA[c]);
		}
	}

	if(exon_in != "0")
	{
		exon = check(exon_in);
		for(int c= 0; c < exon.size();c++)
		{
			exon[c] = toupper(exon[c]);
		}
		 
	}

	if(spliceD_in != "0")
	{
		spliceD = check(spliceD_in);
		for(int c= 0; c < spliceD.size();c++)
		{
			spliceD[c] = tolower(spliceD[c]);
		}
		
	}


	if(spliceA != "0" && exon != "0" && spliceD != "0") //all input
	{
		total = spliceA + exon + spliceD;
		SAI = spliceA.size();
		EXE = exon.size();
		SDI = spliceD.size();
		SP = -SAI; 
	}

	if(spliceA == "0" && exon != "0" && spliceD != "0") //exon SD
	{
		total = exon + spliceD;
		EXE = exon.size();
		SDI = spliceD.size();
		SAI = 0; 
		SP = 1;
	}

	if(spliceD == "0" && exon != "0" && spliceA != "0") //sa exon
	{
		total = spliceA + exon;
		SAI = spliceA.size();
		EXE = exon.size();
		SDI = 0;
		SP = -SAI; 

	}

	if(spliceD == "0" && exon == "0" && spliceA != "0") //sa
	{
		total = spliceA;
		SAI = spliceA.size();
		EXE = 0; 
		SDI = 0; 
		SP = -SAI; 
	}

	if(spliceD != "0" && exon == "0" && spliceA == "0") //sd
	{
		total = spliceD;
		SAI = 0; 
		EXE = 0;
		SDI = SDI = spliceD.size();
		SP = -1; 
		FLAG = 1; 
	}

	if(spliceD == "0" && exon != "0" && spliceA == "0") //exon
	{
		total = exon; 
		SAI = 0; 
		SDI = 0; 
		EXE = exon.size();
		SP = 1; 
	}

	for (int d = 0; d < total.size(); d++)
	{
		if(total[d] == 'A')
		{
			totalComp += "T";
		}
		else if(total[d] == 'a')
		{
			totalComp += "t";
		}
		else if(total[d] == 'C')
		{
			totalComp += "G";
		}
		else if(total[d] == 'c')
		{
			totalComp += "g";
		}
		else if(total[d] == 'G')
		{
			totalComp += "C";
		}
		else if(total[d] == 'g')
		{
			totalComp += "c";
		}
		else if(total[d] == 'T')
		{
			totalComp += "A";
		}
		else if(total[d] == 't')
		{
			totalComp += "a";
		}
		else if(total[d] == 'U')
		{
			totalComp += "A";
		}
		else if(total[d] == 'u')
		{
			totalComp += "a";
		}
	}

	cout << "Enter the length of the compound you want to make" << endl; 
	cin >> compoundLen; 
	cout << "Enter the walk frequency" << endl; 
	cin >> walkVar; 



	ofstream outputFile;
	ofstream outputFile2; 
	outFileName = setName; 
	outFileName += ".txt";
	outputFile.open(outFileName.c_str());
	outFileName2 = setName; 
	outFileName2 += "0S.txt";
	outputFile2.open(outFileName2.c_str());
	outputFile << "Sequence Number   " << "	" << "  Sequence (3' - 5')  " << "	" << "  Sequence (5' - 3')  "<< "	" << " Sequence Name   " << endl; 

	if(FLAG == 0)
	{
		for(int e = 0; e <= (totalComp.size() - compoundLen); e += walkVar)
		{
			counter ++; 
			outputFile << counter << "	";

			for(int k = e; k < (e + compoundLen); k++)
			{
				holdVector.push_back(totalComp[k]);
				outputFile << totalComp[k];
			}
			outputFile << "	";
			for(int k = (holdVector.size() -1); k >= 0; k--)
			{
				outputFile << holdVector[k]; 
				outputFile2 << holdVector[k];
			}
			outputFile2 << endl; 
			holdVector.clear();

			if(SP + compoundLen < 0)
			{
				b = (SP + compoundLen) -1;
				outputFile << "	" << setName << ".SA.(" << SP << ":" << b << ")" << endl; 
			}
			else if((SP + compoundLen) == 0)
			{
				b = -1;
				outputFile << "	" << setName << ".SA.(" << SP << ":" << b << ")" << endl; 
			}
			else if (((SP + compoundLen) > 0) && ((SP + (compoundLen-1) <= EXE )))
			{
				b = (SP + compoundLen)-1;			
				if (SP<0)
				{
					b = SP + compoundLen;
				}			
				if(SP==0)
				{	
					SP=1;
					b = (0 + compoundLen);
				}
				if (b==0)
					{
						b=1;
					}
				outputFile << "	" << setName << ".SA.(" << SP << ":" << b << ")" << endl;
			}
			else if((SP + (compoundLen -1) > EXE))
			{
						
				b=-((SP+compoundLen -1)-EXE);
				SDa = compoundLen + b;

				if(SDa <=0)
				{
					SDa = b + (compoundLen-1);
				}

				outputFile << "	" << setName << ".SD.(" << SDa << ":" << b << ")" << endl;
						
			}

			if((SP < 0) && ((SP + walkVar) > 0))
			{
				SP += walkVar;
				SP +=1;
			}
			else
			{
				SP+=walkVar; 
			}


		}
	}

	if(FLAG == 1)
	{
		for(int e = 0; e <= (totalComp.size() - compoundLen); e += walkVar)
		{
			counter ++; 
			outputFile << counter << "	";

			for(int k = e; k < (e + compoundLen); k++)
			{
				holdVector.push_back(totalComp[k]);
				outputFile << totalComp[k];
			}
			outputFile << "	";
			for(int k = (holdVector.size() -1); k >= 0; k--)
			{
				outputFile << holdVector[k]; 
				outputFile2 << holdVector[k];
			}
			outputFile2 << endl; 
			holdVector.clear();

			b = SP - (compoundLen -1); 

			outputFile << "	" << setName << ".SD.(" << SP << ":" << b << ")" << endl;

			SP-=walkVar; 
		}

	}

	outputFile.close();
	outputFile2.close();

	return 0; 


}

string check(string s)
{
	string checkedString;

	checkedString.clear();

	for(int b = 0; b < s.size(); b++)
	{
		if(s[b] == 'a' || s[b] == 'A' || s[b] == 'g' || s[b] == 'G' || s[b] == 'c' || s[b] == 'C' || s[b] == 't' || s[b] == 'T'|| s[b] == 'u' || s[b] == 'U')
		{
			checkedString += s[b];
		}
		else
		{
			cout << "Invalid Input Character Detected!: " << s[b] << " Character Ignored" << endl; 

		}
	}

	return checkedString; 
}
