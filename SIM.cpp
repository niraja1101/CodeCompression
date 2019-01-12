#include<iostream>
#include<fstream>
#include<sstream>
#include<bitset>
#include<map>
#include<cstring>
#include<cstdlib>
#include <numeric>    //inner_product
#include <functional> //plus, equal_to, not2
 
#include <stdexcept>
#include <typeinfo>
#include<stdexcept>

using namespace std;
string twomismatch(string);
string d_bitmask(int dictindex,int location,string bitmask);
string d_onemismatch(int,int);
string d_twomismatch(int dictindex,int location);
string d_twormismatch(int dictindex,int location1,int location2);
string d_directmatch(int m);
string onemismatch(string);
string bitmask(string);
string originalbin (string bitstream);
string directmatch (string);
string tworandmismatch(string);
string rle (int numrpt);
std::string maxstrings[8];
std::string givendict[8];
void printdict();

 int hammingdist(string s1,string s2)
{

    int count=0;
    int i;
    
    for(i=0;i<32;i++)
    {
      

      if(s1[i]!=s2[i])
      {
        //cout<<s1[i]<<endl;
        //cout<<s2[i]<<endl;
        count++;
      }
    }
    //cout<<"Hamming dist "<<count<<endl;
    return count;
}

 int main(int argc,char* argv[])
 { 
    //printdict();
  if(argc<2)
  {
     cout<<"Ussage: ./SIM 1 or ./SIM 2";
  }

  int option = atoi(argv[1]);
  //cout<<option<<endl;

  if(option==1)
 {  

  ofstream outfile("cout.txt",ios::out);
 	ifstream inputFile("original.txt",ios::in);
    
    if(!inputFile)
    {

        cerr<< "Couldnt open"<<endl;
        cerr<<strerror(errno)<<endl;
    }

    string original;
    string input[100];
    int i=0;
    
    while(getline(inputFile,original))
    {
    	
        input[i]=original;
        //cout<<input[i]<<endl;
        i++;
    }



    int size=i;
    //cout<<"Current size is "<<size;
    int arrcount[size];
    for(int j=0;j<size;j++)
    { 
        arrcount[j]=0;
    }


    for(int j=0;j<size;j++)
    { 

    	for(int k=0;k<size;k++)
    	{
              
             if(!input[j].compare(input[k]))
             {
             	arrcount[j]++;
             }
    	}

    }

   //cout<<endl<<"Printing"<<endl;
    /*for(int j=0;j<size;j++)
    { 
        
        cout<<j<<":"<<arrcount[j]<<endl;
    }*/
   

  //cout<<"Finding max"<<endl;
    //string maxstrings[8];
    int maxiter=0;
    int max=0;
   
   while(maxiter<8)
{
   //find index of maximum repeated
   for(int j=0;j<size;j++)
    { 
        //cout<<j<<":"<<arrcount[j]<<endl;
        if(arrcount[j]>arrcount[max])
        {
        	max=j;
        }
    }
    //cout<<endl<<"Max repeated string now at"<<max<<"and is"<<arrcount[max];
    
    maxstrings[maxiter]=input[max];

    //cout<<endl<<"Max is "<<maxstrings[maxiter]<<endl;
    maxiter++;

    for(int j=0;j<size;j++)
    { 
        
        if(!input[j].compare(input[max]))
        {
        	arrcount[j]=0;
        }
    }
    /*cout<<endl<<"Printing"<<endl;
    for(int j=0;j<size;j++)
    { 
        
        cout<<j<<":"<<arrcount[j]<<endl;
    }*/


    
}



string superfinal;
int count_rle=0;
int finalcntrle =0;

for(int i=0;i<size;i++)
{ 



if(i>0)
{  
if(!input[i].compare(input[i-1]))
{
  
  count_rle++;
  continue;
  
}
else
{
  finalcntrle=count_rle;
  //cout<<"Final RLE cnt"<<finalcntrle<<endl;
  count_rle=0;
}

}

//cout <<"Count_RLE is"<<count_rle<<endl;
string finalstr;
string rlestr     = "";

if(finalcntrle!=0)
{
   
    //cout<<i<<":"<<finalstr<<endl;
    rlestr      = rle(finalcntrle);
    finalstr    = rlestr;
    //cout<<i-1<<":"<<finalstr<<endl;
    superfinal.append(finalstr);
    finalcntrle = 0;

}

 
  

string directstr  = directmatch(input[i]);
string onebitstr  = onemismatch(input[i]);
string twobitstr  = twomismatch(input[i]);
string bitmaskstr = bitmask(input[i]);
string tworbitstr = tworandmismatch(input[i]);
string origstr    = originalbin(input[i]);




//cout<<"Printing all "<<endl;

//cout<<"i="<<i<<"Directmatch: "<<directstr<<endl;
//cout<<"One mismatch: "<<onebitstr<<endl;
//cout<<"Two mismatch: "<<twobitstr<<endl;
//cout<<"Bitmask: "<<bitmaskstr<<endl;
//cout<<"Tworandom mis:"<<tworbitstr<<endl;
//cout<<"Original bin: "<<origstr<<endl;
//int hd =hammingdist(maxstrings[0],input[4]);
//cout<<"Hamming :"<<hd<<endl;
int strsize[6];
//map<string,int>strsize;

    //strsize[0]= rlestr.length();
    strsize[0]= directstr.length();
    //cout<<"0:"<<strsize[0]<<endl;
    strsize[1]= onebitstr.length();
    //cout<<"1:"<<strsize[1]<<endl;
    strsize[2]= twobitstr.length();
    //cout<<"2:"<<strsize[2]<<endl;
    strsize[3]= bitmaskstr.length();
    //cout<<"3:"<<strsize[3]<<endl;
    strsize[4]= tworbitstr.length();
    //cout<<"4:"<<strsize[4]<<endl;
    strsize[5]= origstr.length();
    //cout<<"5:"<<strsize[5]<<endl;

int minlen=50;
int minpos =-1;
for (int i=0;i<6;i++)
{
  //if((strsize[i]<strsize[finalindex]) and (strsize[i]!=0))
  if((strsize[i]<minlen) and (strsize[i]!=0))
  {
    minlen=strsize[i];
    minpos=i;
  }
}

//cout<<"Final index is "<<minpos<<endl;



switch(minpos)
{
  //case 0: finalstr = rlestr; break;
  case 0: finalstr = directstr; break;
  case 1: finalstr = onebitstr; break;
  case 2: finalstr = twobitstr; break;
  case 3: finalstr = bitmaskstr; break;
  case 4: finalstr = tworbitstr; break;
  case 5: finalstr = origstr; break;

}

superfinal.append(finalstr);


//cout<<i<<":"<<finalstr<<endl;

}





int padding;
//cout<<"Length is"<<superfinal.length()<<endl;
//padding = (superfinal.length()%32);
int numlines;
numlines = (superfinal.length()/32);
padding = ((32*(numlines+1))-superfinal.length());
//cout<<"Padding is"<<padding<<endl;
if(padding!=0)
{
  numlines= numlines+1;
  for(i=0;i<padding;i++)
  {
    superfinal=superfinal+'1';
  }

}
//cout<<"numlines is"<<numlines<<endl;

for(int index=0;index<numlines;index++)
{

  //cout<<"Now printing"<<superfinal.substr(index*32,32)<<endl;
  outfile<<superfinal.substr(index*32,32)<<endl;
  

}
outfile<<"xxxx"<<endl;
for(int k=0;k<8;k++)
   {
      if(k==7)
        outfile<<maxstrings[k];
      else
        outfile<<maxstrings[k]<<endl;
  }

  return 0;

}
else if(option==2)
{
 
  ofstream outfile("dout.txt",ios::out);
  ifstream inputFile("compressed.txt",ios::in);
  if(!inputFile)
    {

        cerr<< "Couldnt open"<<endl;
        cerr<<strerror(errno)<<endl;
    }
  string original;
  string input;
  int index=0;

  while(getline(inputFile,original))
{
    
   // cout<<original<<endl;
   // maxstrings[index]=original;
    //index++;
    //cout<<maxstrings[index]<<endl;
    if(original[0]!='0' and original[0]!='1')
    {
        //cout<<original;
        break;
    }
    else
    {
      input.append(original);  
    }
    
    
  
}

 

 for(int k=0;k<8;k++)
  {
      getline(inputFile,maxstrings[k]);
      //cout<<"Max at "<<k<<"is "<<maxstrings[k];
  }


string finalrun;
string prevcode;
//cout<<input<<endl;
int size=input.length();
int i=0;
while(i<size)
{  

string comp = input.substr(i,3);
i=i+3;
//cout<<"Comp is"<<comp<<endl;
if(!comp.compare("000"))
{
  int finalcount =0;
  string count=input.substr(i,2);
  i=i+2;
  if(!count.compare("00"))
  {
     finalcount=1;
  }
  if(!count.compare("01"))
  {
     finalcount=2;
  }
  if(!count.compare("10"))
  {
     finalcount=3;
  }
  if(!count.compare("11"))
  {
     finalcount=4;
  }  
  //cout<<"finalcount"<<finalcount<<endl;
  for(int index=0;index<finalcount;index++)
  { 

    outfile<<prevcode<<endl;
    finalrun.append(prevcode);
  }
}
if(!comp.compare("001"))
{
  //cout<<"Bitmask"<<endl;
   string startloc =input.substr(i,5);
   i=i+5;
   int loc1=stoi(startloc,nullptr,2);
   //cout<<"Loc1"<<loc1<<endl;
   string bitm =input.substr(i,4);
   i=i+4;
   string dictstr =input.substr(i,3);
   i =i+3;
   //cout<<"Index:"<<dictstr<<endl;
   int dictindex = stoi(dictstr,nullptr,2);
   //cout<<"dictindex"<<dictindex<<endl;
   string op= d_bitmask(dictindex,loc1,bitm);
   prevcode=op;
   outfile<<op<<endl;
   finalrun.append(op);
}
else if(!comp.compare("101"))
{
   //cout<<"Direct match"<<endl;
   string dictstr =input.substr(i,3);
   i =i+3;
   //cout<<"Index:"<<dictstr<<endl;
   int dictindex = stoi(dictstr,nullptr,2);
   //cout<<"dictindex"<<dictindex<<endl;
   string op = d_directmatch(dictindex);
   prevcode=op;
   finalrun.append(op);
   outfile<<op<<endl;
}
else if(!comp.compare("011"))
{
   //cout<<"Twoconsecutivemismatch"<<endl;
   string start =input.substr(i,5);
   i=i+5;
   //cout<<"Start loc is"<<start<<endl;
   int startloc = stoi(start,nullptr,2);
   //cout<<"Startloc is"<<startloc<<endl;
   string dictstr =input.substr(i,3);
   i =i+3;
   //cout<<"Index:"<<dictstr<<endl;
   int dictindex = stoi(dictstr,nullptr,2);
   //cout<<"dictindex"<<dictindex<<endl;
   string op = d_twomismatch(dictindex,startloc);
   prevcode=op;
   outfile<<op<<endl;
   finalrun.append(op);
}
else if(!comp.compare("110"))
{
   //cout<<"Originalbinary: "<<endl;
   string bitstream =input.substr(i,32);
   i=i+32;
   string op= bitstream;
   prevcode=op;
   outfile<<op<<endl;
   finalrun.append(op);
}
else if(!comp.compare("100"))
{
   //cout<<"tworandmismatch"<<endl;
   string pos1 =input.substr(i,5);
   i=i+5;
   int loc1=stoi(pos1,nullptr,2);
   //cout<<"Loc1"<<loc1<<endl;
   string pos2 =input.substr(i,5);
   i=i+5;
   string dictstr =input.substr(i,3);
   i =i+3;
   //cout<<"Index:"<<dictstr<<endl;
   int dictindex = stoi(dictstr,nullptr,2);
   int loc2=stoi(pos2,nullptr,2);
   //cout<<"Loc2"<<loc2<<endl;
   //cout<<"dictindex"<<dictindex<<endl;
   string op= d_twormismatch(dictindex,loc1,loc2);
   prevcode=op;
   outfile<<op<<endl;
   finalrun.append(op);
}
else if(!comp.compare("010"))
{
   //cout<<"Onemismatch"<<endl;
   string start =input.substr(i,5);
   i=i+5;
   //cout<<"Start loc is"<<start<<endl;
   int startloc = stoi(start,nullptr,2);
   //cout<<"Startloc is"<<startloc<<endl;
   string dictstr =input.substr(i,3);
   i =i+3;
   //cout<<"Index:"<<dictstr<<endl;
   int dictindex = stoi(dictstr,nullptr,2);
   //cout<<"dictindex"<<dictindex<<endl;
   string op = d_onemismatch(dictindex,startloc);
   prevcode=op;
   outfile<<op<<endl;
   finalrun.append(op);
}
else if(!comp.compare("111"))
{
  break;
}


}
//string orig = d_bitmask(5,4,"1110");
//cout<<orig<<endl;



// cout<<input[33]<<endl;
// string ret1 = bitmask(input[33]);
// cout<<"Bitmask OP:"<<ret1<<endl;
// string ret2 = tworandmismatch(input[33]);
// cout<<"Randmis OP:"<<ret2<<endl;





}
return 0;
}





string onemismatch(string currentstr)
{
  string answer;
  int hammingdist1[8];
  int hammingmin=50;
  int hammingpos;
  int hmindex;
  for(hmindex=0;hmindex<8;hmindex++)
  {   
    //cout<<endl<<currentstr<<":"<<maxstrings[hmindex]<<endl;    
      hammingdist1[hmindex]=hammingdist(currentstr,maxstrings[hmindex]);
      //cout<<"With string at"<<hmindex<<" in dictionary,hamming dist is"<<hammingdist1[hmindex]<<endl;
      if(hammingdist1[hmindex]<hammingmin)
      {
        hammingmin=hammingdist1[hmindex];
        hammingpos=hmindex;
      }

  }

  //printdict();
  //cout<<"Minimum HM for string is "<<hammingmin<<" with string at "<<hammingpos<<endl;
  string dictentry =maxstrings[hammingpos];

  if(hammingmin==1)
  {  

   int pos=-1;
   for(int i=0;i<32;i++)
    {
      if(currentstr[i]!=dictentry[i])
      {
        pos=i;
        //cout<<"Difference pos "<<pos<<endl;
        break;
      }
    }
   
   bitset<11>answer;

   bitset<11>answer1;
   answer1.reset(10);
   answer1.set(9);
   answer1.reset(8);
   
   bitset<11>position(pos);
   position <<= 3;

   bitset<11>dict(hammingpos);

   answer=answer1|position|dict;

   return answer.to_string();
 }
 else
{
 return "";
}

}

string twomismatch(string currentstr)
{
   

  string answer;
  int hammingdist1[8];
  int hammingmin=50;
  int hammingpos;
  int hmindex;
  for(hmindex=0;hmindex<8;hmindex++)
  {   
    //cout<<endl<<currentstr<<":"<<maxstrings[hmindex]<<endl;    
      hammingdist1[hmindex]=hammingdist(currentstr,maxstrings[hmindex]);
      //cout<<"With string at"<<hmindex<<" in dictionary,hamming dist is"<<hammingdist1[hmindex]<<endl;
      if(hammingdist1[hmindex]<hammingmin)
      {
        hammingmin=hammingdist1[hmindex];
        hammingpos=hmindex;
      }

  }



  //printdict();
  //cout<<"Minimum HM for string is "<<hammingmin<<" with string at "<<hammingpos<<endl;
  string dictentry =maxstrings[hammingpos];

  if(hammingmin==2)
  {  

   int pos=-1;
   for(int rev=0;rev<32;rev++)
    {
       //cout<<"rev is"<<rev<<endl;
      if(currentstr[rev]!=dictentry[rev])
      { 
       
        if(currentstr[rev+1]!=dictentry[rev+1])
       {    pos=rev;
           //cout<<"Difference pos "<<pos<<endl;
            break;
        }
        else
        {
           return "";
        }
      }
    }
  

   
   bitset<11>answer;

   bitset<11>answer1;
   answer1.reset(10);
   answer1.set(9);
   answer1.set(8);
  
   bitset<11>position(pos);
   position <<= 3;

   bitset<11>dict(hammingpos);

   answer=answer1|position|dict;


  return answer.to_string();

}
else
{
   return "";
}
}
string bitmask(string currentstr)
{

  int hammingdist1[8];
  int hammingmin=50;
  int hammingpos;
  int hmindex;
  for(hmindex=0;hmindex<8;hmindex++)
  {   
    //cout<<endl<<currentstr<<":"<<maxstrings[hmindex]<<endl;    
      hammingdist1[hmindex]=hammingdist(currentstr,maxstrings[hmindex]);
      //cout<<"With string at"<<hmindex<<" in dictionary,hamming dist is"<<hammingdist1[hmindex]<<endl;
      if(hammingdist1[hmindex]<hammingmin)
      {
        hammingmin=hammingdist1[hmindex];
        hammingpos=hmindex;
      }

  }

 

  //printdict();
  //cout<<"Minimum HM for string is "<<hammingmin<<" with string at "<<hammingpos<<endl;
  string dictentry =maxstrings[hammingpos];
  //cout<<"Dict:"<<dictentry<<endl;
  //cout<<"Crnt:"<<currentstr<<endl;


  if(hammingmin<5 and hammingmin!=0)
{   //dictentry[0]^currentstr[0];

   //bitset<32>a(string(currentstr));
   //bitset<32>b(string(dictentry));

   //bitset<32>c;
   //c=a^b;
   //cout<<"Xor is "<<c.to_string()<<endl;

  int pos=-1;
   
   
    //cout<<"Current string:"<<currentstr<<endl;
    //cout<<"Directoryentry:"<<dictentry<<endl;
    
    string xor1="00000000000000000000000000000000";
   for(int k=0;k<32;k++)
    {
        //cout << typeid(xor1[k]).name() << endl;
          

         if(currentstr[k]!=dictentry[k])
         {
            xor1[k]='1';
         }
         else
         {
            xor1[k]='0';
         }
          

          
              
    }

   for(int m=0;m<32;m++)
   {
     if(xor1[m]=='1')
     {
       pos=m;
       break;
     }
   }
    //cout<<"Xor1 is"<<xor1<<endl;

    //cout<<"Position is"<<pos<<endl;
    string finalmask="";
    string maskstr;
    string s1="00000000000000000000000000000000";
    int maskint;
    int i;
    for( i=0;i<16;i++)
    {
      bitset<32>mask((i));
      mask <<= 28-pos;

      maskstr = mask.to_string();
      //cout<<"Mask is"<<maskstr<<endl;
      //cout << typeid(maskstr).name() << endl;
      for(int m=0;m<32;m++)
      { 
        
          if(maskstr[m]!=currentstr[m])
          {
            s1[m]='1';
          }
          else
          {
            s1[m]='0';
          }
          //s1[m] = ((maskstr[m]-'0')^(currentstr[m]-'0'))+ '0';
        //s1[m]=(a^b)+'0';
        //cout<<"s1 of"<<m<<"is "<<s1[m]<<endl;
         
      }

      //cout<<"s1 now for "<<i<<" is "<<s1<<endl;
      if(!s1.compare(dictentry))
      {
        finalmask=maskstr;
        maskint=i;
        break;
      }
    }
 
  //cout<<"S1 is "<<s1<<endl;
  //cout<<"Final Mask is"<<finalmask<<endl;
  
 /* string bitmask="0000";
  for(int k=pos;k<pos+4;k++)
  {
    if(finalmask[k]==1)
    {
      bitmask[k]='1';
    }
    else
    {
      bitmask[k]='0';
    }
  }*/
  //cout<<"bitmask is"<<bitmask<<endl;
  if(finalmask.compare(""))
	{
  bitset<15>answer;
	answer.reset(14);
	answer.reset(13);
	answer.set(12);
    bitset<15>position(pos);
    position <<= 7;
	bitset<15>newbitmask(maskint);
    newbitmask <<= 3;
	bitset<15>dictentrynew(hammingpos);

	answer = answer|position|newbitmask|dictentrynew;
	//return answer.to_string();
    return answer.to_string();
  }
  else
  {
    return "";
  }
}
else
   {
       return "";
   }
}

string tworandmismatch(string currentstr)
{
  
  int hammingdist1[8];
  int hammingmin=50;
  int hammingpos;
  int hmindex;
  for(hmindex=0;hmindex<8;hmindex++)
  {   
    //cout<<endl<<currentstr<<":"<<maxstrings[hmindex]<<endl;    
      hammingdist1[hmindex]=hammingdist(currentstr,maxstrings[hmindex]);
      //cout<<"With string at"<<hmindex<<" in dictionary,hamming dist is"<<hammingdist1[hmindex]<<endl;
      if(hammingdist1[hmindex]<hammingmin)
      {
        hammingmin=hammingdist1[hmindex];
        hammingpos=hmindex;
      }

  }



  //printdict();
  //cout<<"Minimum HM for string is "<<hammingmin<<" with string at "<<hammingpos<<endl;
  string dictentry =maxstrings[hammingpos];



   string xor1;
   int pos1;
   int pos2;

  if(hammingmin==2)
  {
    for(int k=0;k<32;k++)
    {
       if((dictentry[k]^currentstr[k])==1)
       {
           pos1=k;
           currentstr[k]=dictentry[k];
           break;

       }

    }
    for(int k=0;k<32;k++)
    {
       if((dictentry[k]^currentstr[k])==1)
       {
           pos2=k;
           currentstr[k]=dictentry[k];
           break;

       }

    }

  
   //cout<<"Pos1 is "<<pos1<<endl;
   //cout<<"Pos2 is "<<pos2<<endl;
   bitset<16>answer;

   bitset<16>answer1;
   answer1.set(15);
   answer1.reset(14);
   answer1.reset(13);


  
   bitset<16>position1(pos1);
   position1 <<= 8;
   bitset<16>position2(pos2);
   position2 <<= 3;
   bitset<16>dict(hammingpos);

   answer=answer1|position1|position2|dict;

   return answer.to_string();
 }

else
{
  return "";
}

} 

string  directmatch (string currentstr)
{  
  string answer;
  
  int hammingdist1[8];
  int hammingmin=50;
  int hammingpos;
  int hmindex;
  for(hmindex=0;hmindex<8;hmindex++)
  {   
    //cout<<endl<<currentstr<<":"<<maxstrings[hmindex]<<endl;    
      hammingdist1[hmindex]=hammingdist(currentstr,maxstrings[hmindex]);
      if(hammingdist1[hmindex]<hammingmin)
      {
        hammingmin=hammingdist1[hmindex];
        hammingpos=hmindex;
      }

  }

  //printdict();
  //cout<<"Minimum HM for string is "<<hammingmin<<" with string at "<<hammingpos<<endl;
  
  if(hammingmin==0)

 {
        bitset<6>answer(hammingpos);
        //cout<<"Answer is"<<answer;
        answer.set(5);
        answer.reset(4);
        answer.set(3);
        //cout<<"Answer:"<<answer.to_string()<<endl;
        string a = answer.to_string();
        return a;
  } 
  else
  {
    return "";
  }
}

string rle (int numrpt)
{
  bitset<5>answer;
  answer.reset(4);
  answer.reset(3);
  answer.reset(2);

  bitset<5>rpt(numrpt-1);

  answer = answer | rpt;
  return answer.to_string();
}
string originalbin (string bitstream)
{

	bitset<35>answer((string(bitstream)));
	answer.set(34);
	answer.set(33);
	answer.reset(32);
	//cout<<answer<<endl;
	return answer.to_string();

}

string d_directmatch(int m)
{
   return maxstrings[m];
}
string d_originalbin(string bitstream)
{
   return bitstream;
}
string d_onemismatch(int dictindex,int location)
{
   string dictentry;

   dictentry= maxstrings[dictindex];
   //cout<<"Dictentry is "<<dictentry<<endl;
   
   if(dictentry[location]=='0')
   {
     dictentry[location]='1';
   }
   else
   {
     dictentry[location]='0';
   }
   
   //cout<<"Answer1 "<<dictentry<<endl;
   return dictentry;
}
string d_twormismatch(int dictindex,int location1,int location2)
{
   string dictentry;

   dictentry= maxstrings[dictindex];
   //cout<<"Dictentry is "<<dictentry<<endl;
   
   if(dictentry[location1]=='0')
   {
     dictentry[location1]='1';
   }
   else
   {
     dictentry[location1]='0';
   }

   if(dictentry[location2]=='0')
   {
     dictentry[location2]='1';
   }
   else
   {
     dictentry[location2]='0';
   }
   
   //cout<<"Answer1 "<<dictentry<<endl;
   return dictentry;
}

string d_bitmask(int dictindex,int location,string bitmask)
{
   string dictentry;

   dictentry= maxstrings[dictindex];
   //cout<<"Dictentry is "<<dictentry<<endl;
   bitset<32>mask((string(bitmask)));
   //cout<<"Mask is"<<mask<<endl;
   mask = mask << 32-location-4;
   //cout<<"Mask is"<<mask<<endl;
   string finalmask;
   finalmask=mask.to_string();
   //cout<<"Final mask is"<<finalmask<<endl;
   string answer="00000000000000000000000000000000";
   for(int i=0;i<32;i++)
   {
     if(finalmask[i]!=dictentry[i])
     {
         answer[i]='1';
     }
     else
     {
        answer[i]='0';
     }
   }
   
   //cout<<"Answer: "<<answer<<endl;
   return answer;
   
}

string d_twomismatch(int dictindex,int location)
{
   string dictentry;

   dictentry= maxstrings[dictindex];
   //cout<<"Dictentry is "<<dictentry<<endl;
   
   if(dictentry[location]=='0')
   {
     dictentry[location]='1';
   }
   else
   {
     dictentry[location]='0';
   }

   if(dictentry[location+1]=='0')
   {
     dictentry[location+1]='1';
   }
   else
   {
     dictentry[location+1]='0';
   }
   
   //cout<<"Answer1 "<<dictentry<<endl;
   return dictentry;
}