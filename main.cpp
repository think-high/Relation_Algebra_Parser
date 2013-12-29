#include<iostream>
#include<fstream>
#include<cstdio>

using namespace std;
/*
char strin[50];
char table_name[35];
char arg_name[35];
char match_name[35];
*/

int select_instance=0;
int project_instance=0;int union_instance=0;int join_instance=0;int njoin_instance=0;


//function for select...   (Wrong)

//There is a structure for each file.

/*
struct file1
{
	int id;
	string name;
	int ssn_no;
};

// union 

// operations:
Parser
Creating database
Using delimiter
initialize files in join
check for dottted attributes
memory management
remove similar tuples
trim strings before comparing
checking conditions
select
project
join
njoin
left outer join
right outer join
rename
union
intersection
set difference
divide
min
max
other aggregate
*/

//bool select()
struct Condition
{
//	string Left_side;
	char Left_side[16];
	int sign;		// (1-- =),(2-- <),(3-- >),(4-- <=),(5-- >=),(6-- !=)
//	string Right_side;
	char Right_side[16];
	Condition * next;
	int L_type;		// (1-- OR)  , (2-- AND)
	int R_type;
};


class Stack
{
							// debugging overflow underflow implementation
	private:
		struct stack
		{
			int n;
			stack * next;
		};
		stack * top;
	public:
		Stack()
		{
			top=NULL;
		}
		void push(int n)
		{
//			printf("got ... %d\n",n);		// debugging
			stack * p;
			p=(stack *)malloc(sizeof(stack));
			p->next=top;
			top=p;
			top->n=n;
		}

		int pop()
		{
			stack * p;
			int temp=top->n;
			p=top->next;
			free(top);
			top=p;
//			printf("send.... %d",temp);			// debugging
			return temp;
		}	
		void setNull()
		{
			top=NULL;
		}
		
		bool isNull()
		{
			if(top==NULL)
				return true;
			else
				return false;
		}
		
};









class Select
{
	private:
		int instance;
		int n;			// no. of attributes
//		istream infile
		ofstream Result_handler;
//		Condition * start;
		ifstream Query_handler;
		char ** attribute;
		Stack s;
		char * conditions[100];
		char * infile;
		
	public:
	
		void readFileName(char *infile)	
		{
			this->infile=(char *)malloc(sizeof(char)*50);
			this->infile=infile;			
		}
		
		char * execute(int i)
		{
			char o_name[100],i_name[100];
			char stre[7];
			char * temp=(char *)malloc(sizeof(char)*50);
			temp="Select_Result_";
			
			strcpy(o_name,temp);
			
			strcpy(i_name,infile);
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(o_name,strcat(o_name,stre));
	
			
			Result_handler.open(o_name);		// may require concatenation
			Query_handler.open(i_name);
	//		this->start=start;
		//    printf("yes\n");
			do_work();	
	//		printf("yes2\n");	
			Query_handler.close();
			Result_handler.close();
	//		strcpy(temp,o_name);
	//		int rah=strlen(temp);
	//		printf("%d",rah);
	//		temp[15]=(char)instance;
	//		temp[16]='.';
	//		temp[17]='t';
	//		temp[18]='x';
	//		temp[19]='t';
	//		temp[20]='\0';
//			temp="Select_Result_0.txt";
			return temp;
		}
		
		Select()
		{
			
		}
		
	
	/*	Select(int i,,Condition * start)
		{
			char stre[7];
			char * name=(char *)malloc(sizeof(char)*50);
			name="Select_Result_";
			
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(name,strcat(name,stre));
	
			
			Result_handler.open(name);		// may require concatenation
			Query_handler.open(infile);
			this->start=start;
			do_work();
		}
	*/	
		int takeConditions()
		{
		//	char * conditions[100];
			for(int i=0;i<100;i++)
			{
				conditions[i]=(char *)malloc(sizeof(char)*50);
				scanf("%s",conditions[i]);
				if(!strcmp(conditions[i],">"))
					break;
			}
		}
		
		int getAttributeI(char * attr)
		{
			for(int i=0;i<n;i++)
			{
				if(strcmp(attr,attribute[i])==0)
					return i;
			}
			return -1;
			
		}
		
		void do_work()
		{
			union data_type
			{
				int number;
				char varchar[16];
				float decimal;
			};
			
			
			int i;
			Query_handler>>n;
//			cout<< n; // debugging
			Result_handler <<n << " \n";
//			printf("yesee\n");     // debugging
			char temp[15];
			data_type * data_list=(data_type *)malloc(n*sizeof(data_type));
			int * type=(int *)malloc(n*sizeof(int));
			
			attribute=(char **)malloc(n*sizeof(char *));
			for(i=0;i<n;i++)
			{
				attribute[i]=(char *)malloc(sizeof(char)*16);
				Query_handler>>attribute[i];
			//	printf("%s\n",attribute[i]);			// debugging
				Result_handler<<attribute[i]<<" ";
			//	 Query_handler.getline(attribute[i],16," ");
			}
			Result_handler<<"\n";
			for(i=0;i<n;i++)
			{
				Query_handler>>temp;
				Result_handler<<temp<<" ";
				if(temp[0]=='i')		// improvement
				{
					type[i]=0;
			//		printf("yesee0\n");     // debugging
				}	
				else if(temp[0]=='v')		// improvement
				{
					type[i]=1;
			//		printf("yesee1\n");     // debugging
				}
				else
				{
					type[i]=2;
			//		printf("yesee2\n");     // debugging
				}
			}
			Result_handler<<"\n";
		
			
			
			
		while(!Query_handler.eof())
		{
		//	file1 a;
	//		Condition * p=start;
		//		Query_handler.read((char *)&a,sizeof(file1));
		
			int l;
			
			for(i=0;i<n;i++)
			{
				if(type[i]==0)
				{
					Query_handler>>data_list[i].number;
				//	printf("%d",data_list[i].number); 		   debugging
				}
				else if(type[i]==1)
				{
					Query_handler>>data_list[i].varchar;
				//		printf("%s",data_list[i].varchar); 			debugging
				}	
				else
				{
					Query_handler>>data_list[i].decimal;
				//	printf("%f",data_list[i].decimal);           debugging
				}

			}			
	//		start->L_type=2;
			bool prevt=true;
			bool t=false;
			
			
									// mega debugging			
			s.setNull();
			i=0;
			do
			{
				if(!strcmp(conditions[i],"("))
				{
//					printf("pushed....%s\n",conditions[i]);				// debugging
					s.push(4);
				}
				else if(!strcmp(conditions[i],"AND")  || !strcmp(conditions[i],"And") || !strcmp(conditions[i],"and"))
				{
//										printf("pushed....%s\n",conditions[i]);				// debugging
					s.push(2);
				}
	
				else if(!strcmp(conditions[i],"OR")  || !strcmp(conditions[i],"Or") || !strcmp(conditions[i],"or"))
				{
//										printf("pushed....%s\n",conditions[i]);				// debugging
					s.push(3);
				}
				else if(!strcmp(conditions[i],"["))
				{
					char left_side[100],right_side[100],sign[4];
					// debugging
			//		scanf("%s",left_side);
					i++;
					strcpy(left_side,conditions[i]);			// debugging
					i++;
					strcpy(sign,conditions[i]);			// debugging
			
			//			scanf("%s",right_side);
//					data_type right_side;
					i++;
					l=getAttributeI(left_side);
			//		printf("Printing l %d\n",l);		// debugging
					t=false;
					if(!strcmp(sign,"="))
					{
						if(type[l]==0)
						{
						//	right_side.number=(atoi)conditions[i];				// check for more than 1 digit.
							if(data_list[l].number==atoi(conditions[i]))				// check for more than 1 digit.
								t=true;
						}
						else if(type[l]==1)
						{
							if(!strcmp(data_list[l].varchar,conditions[i]))
								t=true;
						}
						else 
						{
							if(data_list[l].decimal==atof(conditions[i]))
									t=true;
						
				//	if(a.(*(start.Left_side))==start.Right_side)
						}
					}
					else if(!strcmp(sign,">"))
					{
						if(type[l]==0)
						{
							if(data_list[l].number>(atoi(conditions[i])))
								t=true;
						}
						else if(type[l]==1)
						{
							if(strcmp(data_list[l].varchar,conditions[i])>0)		// debugging
								t=true;
						}
						else 
						{
							if(data_list[l].decimal>(atof(conditions[i])))   // debugging
								t=true;
						}
					}
					else if(!strcmp(sign,"<"))								// debugging do for <= and >= also
					{
						if(type[l]==0)
						{
							if(data_list[l].number<(atoi(conditions[i])))
							t=true;
						}
			
						else if(type[l]==1)
						{
							if(strcmp(data_list[l].varchar,conditions[i])<0)
							t=true;
						}
				
						else
						{
							if(data_list[l].decimal<(atof(conditions[i])))
								t=true;
						}
					}
					i++;
				if(!strcmp(conditions[i],"]"))
				{
				if(t)
				{
//					printf("pushed....1\n");				// debugging
					s.push(1);
				}
				else
				{
//						printf("pushed....0\n");				// debugging
					s.push(0);
				}
				}
				else
				{
				// error state
					printf("Error in input\n");
					exit(0);
				}
		}
/*			if(prevt)
			{
				for(i=0;i<n;i++)
				{
					if(type[i]==0)
						Result_handler<<data_list[i].number;
					else if(type[i]==1)
						Result_handler<<data_list[i].varchar;
					else
						Result_handler<<data_list[i].decimal;
				}			
				Result_handler<<"\n";
			}
			
		}	


		//  debugging
		
*/		
	else if(!strcmp(conditions[i],")"))
	{
		int right,logic,left,temp;
		right=s.pop();
		logic=s.pop();
		left=s.pop();
		
		if(logic==2)
		{
			logic=(right && left);
		}
		else if(logic ==3)
		{
			logic=(right || left);
		}
		if(s.pop()!=4)
		{
			// unexpected error.
		}	
		else
		{
			s.push(logic);
		}	
	}
	else if(!strcmp(conditions[i],">"))
		break;
	i++;
}while(!s.isNull());

			
			
			
			
			
			
			
			
			
			
			/*
			while(p!=NULL)
			{	
				l=getAttributeI(p->Left_side);
				t=false;
				if(p->sign==1)
				{
					if(type[l]==0)
					{
						if(data_list[l].number==atoi(p->Right_side))
							t=true;
					}
					else if(type[l]==1)
					{
						if(!strcmp(data_list[l].varchar,p->Right_side))
							t=true;
					}
					else 
						if(data_list[l].decimal==(float)atoi(p->Right_side))
							t=true;
						
				//	if(a.(*(start.Left_side))==start.Right_side)
				}
				else if(p->sign==2)
				{
					if(type[l]==0)
					{
						if(data_list[l].number>(int)p->Right_side)
							t=true;
					}
					else if(type[l]==1)
					{
						if(strcmp(data_list[l].varchar,p->Right_side)>0)
							t=true;
					}
					else 
						if(data_list[l].decimal>(float)atoi(p->Right_side))
							t=true;
				}
				else if(p->sign==3)
				{
					if(type[l]==0)
					{
						if(data_list[l].number<(int)p->Right_side)
							t=true;
					}
					else if(type[l]==1)
					{
						if(strcmp(data_list[l].varchar,p->Right_side)<0)
							t=true;
					}	
					else 
						if(data_list[l].decimal<(float)atoi(p->Right_side))
							t=true;
				}
				if(p->L_type==1)
					prevt=prevt || t;
				else 
					prevt=prevt && t;
				
				
		//		if((p->L_type==1 || p->R_type==1) && t=true)
		//		{
		//			p=true;
		//			break;
		//		}
		//		else if(p->L_type==2 && p->R_type==2 && t=false)
						
	

	
				p=p->next;
			}
*/			

			if(s.pop())
			{
				for(i=0;i<n;i++)
				{
					if(type[i]==0)
						Result_handler<<data_list[i].number << " ";
					else if(type[i]==1)
						Result_handler<<data_list[i].varchar << " ";
					else
						Result_handler<<data_list[i].decimal << " ";
				}			
				Result_handler<<"\n";
			}
			
		}	
		// Rahul Kumar Bhojwani 2003@gmail.com
		// Thanks for your support...
		// With love.. Rahul Kumar Bhojwani...
		}			
		
};




//project statement block

class Project
{
	private:
		int instance;
		int n;			// no. of attributes
//		istream infile
		ofstream Result_handler;
		char ** Requested_attr;
		int noOfAttributes;
		ifstream Query_handler;
		char ** attribute;
		char * infile;
		
	public:
		void readFileName(char *infile)	
		{
			this->infile=(char *)malloc(sizeof(char)*50);
			this->infile=infile;			
		}
		
		char * execute(int i)
		{
			
			char o_name[100],i_name[100];
			char stre[7];
			char * temp=(char *)malloc(sizeof(char)*50);
			temp="Project_Result_";
			
			strcpy(o_name,temp);
			
			strcpy(i_name,infile);
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(o_name,strcat(o_name,stre));
	
			
			Result_handler.open(o_name);		// may require concatenation
			Query_handler.open(i_name);
	//		this->start=start;
		//    printf("yes\n");
			do_work();	
	//		printf("yes2\n");	
			Query_handler.close();
			Result_handler.close();			
	//		strcpy(temp,o_name);
			return temp;
	
		}
		
		
		Project()
		{
			
		}
		
	
	//	Project(int i,char *infile,char ** Requested_attr,int noOfAttributes)
	//	{
	//		instance='0'+i;	
	//		Result_handler.open("Project_Result" + instance);		// debugging  limitation of less than 10;
	//		Query_handler.open(infile);
	//		this->Requested_attr=Requested_attr;
	//		this->noOfAttributes=noOfAttributes;
	//		do_work();
	//	}
		
		int getAttributeI(char * attr)
		{
			for(int i=0;i<n;i++)
			{
				if(strcmp(attr,attribute[i])==0)
					return i;
			}
			return -1;
			
		}
		
		void takeAttributes()
		{
			Requested_attr =(char **)malloc(100*sizeof(char *));
			char attr[100];
			int i;
			for(i=0;i<100;i++)
			{
				scanf("%s",attr);
				Requested_attr[i]=(char *)malloc(sizeof(char)*100);
		//						printf("Yesss1\n");
				strcpy(Requested_attr[i],attr);			// debugging error possible
		//		printf("%s",Requested_attr[i]);
		//		printf("Yesss\n");
				scanf("%s",attr);
		//		printf("%s",attr);
		//		if(!strcmp(attr,","))
		//		{
		//			
		//		}
				if(!strcmp(attr,">"))
				{
					break;
				}
			}
			noOfAttributes=i+1;
			
		}
		
		void do_work()
		{

			union data_type
			{
				int number;
				char varchar[16];
				float decimal;
			};
			
			
			int i,j;
			Query_handler>>n;
			Result_handler<<noOfAttributes<<"\n";
			char temp[15];
			data_type * data_list=(data_type *)malloc(n*sizeof(data_type));
			int * type=(int *)malloc(n*sizeof(int));
			
			attribute=(char **)malloc(n*sizeof(char *));
			for(i=0;i<n;i++)
			{
				attribute[i]=(char *)malloc(sizeof(char)*16);
				Query_handler>>attribute[i];
			//	Result_handler<<attribute[i]<<" ";
			//	 Query_handler.getline(attribute[i],16," ");
			}
			
			int matchArray[noOfAttributes],k=0;
			
			for(j=0;j<n;j++)
			{
				for(i=0;i<noOfAttributes;i++)
				{
					if(!strcmp(attribute[j],Requested_attr[i]))		// one error case is missing
					{
						Result_handler<<Requested_attr[i]<<" ";
						matchArray[k]=i;
						k++;
					}
				}
			
			}
			Result_handler<<"\n";
		/*	for(j=0;j<noOfAttributes;j++)
			{
				for(i=0;i<n;i++)
				{
					Query_handler>>temp;
					if(getAttributeI(Requested_attr[j])==i)
					{
						Result_handler<<temp<<" ";
						break;
					}
			}
		
		*/	
			
			for(i=0;i<n;i++)
			{
				Query_handler>>temp;
				for(j=0;j<noOfAttributes;j++)
				{
//					if(getAttributeI(Requested_attr[j])==i)
					if(!strcmp(attribute[i],Requested_attr[j]))
					{
						Result_handler<<temp<<" ";
						break;
					}
				}
				if(temp[0]=='i')
					type[i]=0;
				else if(temp[0]=='v')	
					type[i]=1;
				else
					type[i]=2;
			}
			Result_handler<<"\n";
		
			
			
			
		while(!Query_handler.eof())
		{
		
			int k=0;
			
			for(i=0;i<n;i++)
			{
				if(type[i]==0)
					Query_handler>>data_list[i].number;
				else if(type[i]==1)
					Query_handler>>data_list[i].varchar;
				else
					Query_handler>>data_list[i].decimal;
			}			
			
			for(i=0;i<noOfAttributes;i++)
			{
				k=getAttributeI(Requested_attr[matchArray[i]]);
//				k=matchArray[i];
				if(type[k]==0)
					Result_handler<<data_list[k].number << " ";
				else if(type[k]==1)
					Result_handler<<data_list[k].varchar << " ";
				else
					Result_handler<<data_list[k].decimal  << " ";
			}	
			Result_handler<<"\n";
		}
			
			
		
		// Rahul Kumar Bhojwani 2003@gmail.com
		// Thanks for your support...
		// With love.. Rahul Kumar Bhojwani...
		}					
};



//code block for join:

class Join
{
	private:
		int instance;
		ifstream Query_handler_A;
		ifstream Query_handler_B;
		
		int nA;			// no. of attributes in handler A
		int nB;			// no. of attributes in handler B
//		istream infile
		ofstream Result_handler;
//		char ** Requested_attr;
//		int noOfAttributes;
		//Condition * start;
		char * conditions[100];
		char ** attribute_A;
		char ** attribute_B;
		char * infile_A;
		char * infile_B;
		Stack s;
		
	public:
	
		void readFileName(char *infile_A,char * infile_B)	
		{
			this->infile_A=(char *)malloc(sizeof(char)*50);
			this->infile_A=infile_A;			
			this->infile_B=(char *)malloc(sizeof(char)*50);
			this->infile_B=infile_B;			
			
		}
	
	
		char * execute(int i)
		{
			char o_name[100];
			char stre[7];
			char * name=(char *)malloc(sizeof(char)*50);
			name="Join_Result_";
			
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(o_name,name);
			
			strcpy(o_name,strcat(o_name,stre));
	
			
			Result_handler.open(o_name);		// may require concatenation
			Query_handler_A.open(infile_A);
			Query_handler_B.open(infile_B);
	//		this->start=start;
			do_work();		
			Query_handler_A.close();
			Query_handler_B.close();
			Result_handler.close();
	//		return name;
	//		strcpy(name,o_name);
			return name;
	
		}
	
	
		Join()
		{
			
		}
	
	
/*		Join(int i,char *infile_A,char * infile_B,Condition * start)
		{
			instance='0'+i;	
			Result_handler.open("Join_Result" + instance);
			Query_handler_A.open(infile_A);
			Query_handler_B.open(infile_B);
//			this->start=start;
//			this->Requested_attr=Requested_attr;
//			this->noOfAttributes=noOfAttributes;
			do_work();
		}
		
*/		
		
		int takeConditions()
		{
		//	char * conditions[100];
			for(int i=0;i<100;i++)
			{
				conditions[i]=(char *)malloc(sizeof(char)*50);
				scanf("%s",conditions[i]);
				if(!strcmp(conditions[i],">"))
					break;
			}
		}
		
		
		int getAttribute_BI(char * attr)
		{
			for(int i=0;i<nB;i++)
			{
				if(strcmp(attr,attribute_B[i])==0)
					return i;
			}
			return -1;
		}
		
		int getAttribute_AI(char * attr)
		{
			for(int i=0;i<nA;i++)
			{
				if(strcmp(attr,attribute_A[i])==0)
					return i;
			}
			return -1;
		}
		
		
		void do_work()
		{

			union data_type
			{
				int number;
				char varchar[16];
				float decimal;
			};
			
			
			int i,l,m;
			Query_handler_A>>nA;
			Query_handler_B>>nB;
			Result_handler<<(nA + nB)<<"\n";
			char temp[15];
			data_type * data_list_A=(data_type *)malloc(nA*sizeof(data_type));
			data_type * data_list_B=(data_type *)malloc(nB*sizeof(data_type));
			int * type_A=(int *)malloc(nA*sizeof(int));
			int * type_B=(int *)malloc(nB*sizeof(int));
			
			attribute_A=(char **)malloc(nA*sizeof(char *));
			for(i=0;i<nA;i++)
			{
				attribute_A[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_A>>attribute_A[i];
				Result_handler<<attribute_A[i]<<"\t";
			//	 Query_handler.getline(attribute[i],16," ");
			}
			
			
			attribute_B=(char **)malloc(nB*sizeof(char *));
			for(i=0;i<nB;i++)
			{
				attribute_B[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_B>>attribute_B[i];
				Result_handler<<attribute_B[i] << "\t";
			}
			Result_handler<<"\n";
			
			for(i=0;i<nA;i++)
			{
				Query_handler_A>>temp;
				Result_handler<<temp<<"\t";
				if(temp[0]=='i')
					type_A[i]=0;
				else if(temp[0]=='v')	
					type_A[i]=1;
				else
					type_A[i]=2;
			}
			
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>temp;
				Result_handler<<temp<<"\t";
				if(temp[0]=='i')
					type_B[i]=0;
				else if(temp[0]=='v')	
					type_B[i]=1;
				else
					type_B[i]=2;
			}
			Result_handler<<"\n";
			Result_handler<<"\n";
				Result_handler<<"\n";
			
		while(!Query_handler_A.eof())
		{
		//	printf("YEss");
			for(i=0;i<nA;i++)
			{
				if(type_A[i]==0)
				{
					Query_handler_A>>data_list_A[i].number;
//					printf("%d\n",data_list_A[i].number);
				}
				else if(type_A[i]==1)
				{
					Query_handler_A>>data_list_A[i].varchar;             // use delimter..
//						printf("%s\n",data_list_A[i].varchar);
				}
				else
					Query_handler_A>>data_list_A[i].decimal;
			}			
			
			// initialize the file... i.e open again.
			// flushing start values..
			
			Query_handler_B.clear();
			Query_handler_B.seekg(0,ios::beg);
			char emp[100];
			Query_handler_B>>emp;
//			printf("%s\n",emp);
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>emp;
//							printf("%s\n",emp);
				Query_handler_B>>emp;
//							printf("%s\n",emp);
			}

		
	//	printf("Yupp")	;
		while(!Query_handler_B.eof())
		{
			//	file1 a;
		//		Condition * p=start;
			//		Query_handler.read((char *)&a,sizeof(file1));
			
				int l;
				
			for(i=0;i<nB;i++)
			{
				if(type_B[i]==0)
				{
					Query_handler_B>>data_list_B[i].number;
//						printf("%d\n",data_list_B[i].number);
				}
				else if(type_B[i]==1)
				{
					Query_handler_B>>data_list_B[i].varchar;
//									printf("%s\n",data_list_B[i].varchar);
				}
				else
					Query_handler_B>>data_list_B[i].decimal;
			}			
			
			// debugging
			
		s.setNull();
		i=0;
do
{
	if(!strcmp(conditions[i],"("))
	{
		s.push(4);
	}
	else if(!strcmp(conditions[i],"AND")  || !strcmp(conditions[i],"And") || !strcmp(conditions[i],"and"))
	{
		s.push(2);
	}
	
	else if(!strcmp(conditions[i],"OR")  || !strcmp(conditions[i],"Or") || !strcmp(conditions[i],"or"))
	{
		s.push(3);
	}
	else if(!strcmp(conditions[i],"["))
	{
		char left_side[100],right_side[100],sign[4];
		// debugging
//		scanf("%s",left_side);
		i++;
		strcpy(left_side,conditions[i]);			// debugging
		i++;
			strcpy(sign,conditions[i]);			// debugging
			
//			scanf("%s",right_side);
	//		data_type right_side;
			i++;
			strcpy(right_side,conditions[i]);
			
			
			l=getAttribute_BI(right_side);
			m=getAttribute_AI(left_side);
			bool t=false;			
			if(!strcmp(sign,"="))
			{
				if(type_B[l]==type_A[m]==0)
				{
					if(data_list_B[l].number==data_list_A[m].number)
						t=true;
				}
				else if(type_B[l]==type_A[m]==1)
				{
					if(!strcmp(data_list_A[l].varchar,data_list_B[m].varchar))
						t=true;
				}
				else 
				{
					if(data_list_A[l].decimal==(float)data_list_B[m].decimal)
						t=true;
				}
			}
			
			else if(!strcmp(sign,">"))
			{
				if(type_B[l]==type_A[m]==0)
				{
					if(data_list_B[l].number>data_list_A[m].number)
						t=true;
				}
				else if(type_B[l]==type_A[m]==1)
				{
					if(strcmp(data_list_A[l].varchar,data_list_B[m].varchar)>0)
						t=true;
				}
				else 
				{
					if(data_list_A[l].decimal>(float)data_list_B[m].decimal)
						t=true;
				}
			}

     		else if(!strcmp(sign,"<"))								// debugging do for <= and >= also
			{
				if(type_B[l]==type_A[m]==0)
				{
					if(data_list_B[l].number<data_list_A[m].number)
						t=true;
				}
				else if(type_B[l]==type_A[m]==1)
				{
					if(strcmp(data_list_A[l].varchar,data_list_B[m].varchar)<0)
						t=true;
				}
				else 
				{
					if(data_list_A[l].decimal<(float)data_list_B[m].decimal)
						t=true;
				}
			}			
			
			i++;
			if(!strcmp(conditions[i],"]"))
			{
				if(t)
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
			else
			{
				printf("Error\n");
			}
	}
/*			if(prevt)
			{
				for(i=0;i<n;i++)
				{
					if(type[i]==0)
						Result_handler<<data_list[i].number;
					else if(type[i]==1)
						Result_handler<<data_list[i].varchar;
					else
						Result_handler<<data_list[i].decimal;
				}			
				Result_handler<<"\n";
			}
			
		}	


		//  debugging
		
*/		
	else if(!strcmp(conditions[i],")"))
	{
		int right,logic,left,temp;
		right=s.pop();
		logic=s.pop();
		left=s.pop();
		
		if(logic==2)
		{
			logic=(right && left);
		}
		else if(logic ==3)
		{
			logic=(right || left);
		}
		if(s.pop()!=4)
		{
			// unexpected error.
			printf("Unexpected error..\n");
			exit(0);
		}	
		else
		{
			s.push(logic);
		}	
	}
	else if(!strcmp(conditions[i],">"))
		break;
	i++;
}while(!s.isNull());
			
	if(s.pop())
	{
			for(i=0;i<nA;i++)
			{
				if(type_A[i]==0)
					Result_handler<<data_list_A[i].number << "\t";
				else if(type_A[i]==1)
					Result_handler<<data_list_A[i].varchar << "\t";
				else
					Result_handler<<data_list_A[i].decimal << "\t";
			}			
				for(i=0;i<nB;i++)
				{
					if(type_B[i]==0)
						Result_handler<<data_list_B[i].number<< "\t";
					else if(type_B[i]==1)
						Result_handler<<data_list_B[i].varchar<< "\t";
					else
						Result_handler<<data_list_B[i].decimal<< "\t";
				}			
				Result_handler<<"\n";
			}
		}
	}
    }
};



	
	


// code block for NJOIN

class NJoin
{
	private:
		int instance;
		ifstream Query_handler_A;
		ifstream Query_handler_B;
		
		int nA;			// no. of attributes in handler A
		int nB;			// no. of attributes in handler B
//		istream infile
		ofstream Result_handler;
//		char ** Requested_attr;
//		int noOfAttributes;
		Condition * start;
		char ** attribute_A;
		char ** attribute_B;
		char * infile_A,* infile_B;
		
	public:
	
		void readFileName(char *infile_A,char * infile_B)	
		{
			this->infile_A=(char *)malloc(sizeof(char)*50);
			this->infile_A=infile_A;			
			this->infile_B=(char *)malloc(sizeof(char)*50);
			this->infile_B=infile_B;			
			
		}	
		
		
		
		char * execute(int i)
		{
			char stre[7];
			char * name=(char *)malloc(sizeof(char)*50);
			name="NJoin_Result_";
			
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(name,strcat(name,stre));
	
			
			Result_handler.open(name);		// may require concatenation
			Query_handler_A.open(infile_A);
			Query_handler_B.open(infile_B);
	//		this->start=start;
			do_work();
			Query_handler_A.close();
			Query_handler_B.close();
			Result_handler.close();					
			return name;
		}
	
		NJoin()	
		{
			
		}
		
	//	NJoin(int i,char *infile_A,char * infile_B)
	//	{
	//		instance='0'+i;	
	//		Result_handler.open("NJoin_Result" + instance);
	//		Query_handler_A.open(infile_A);
	//		Query_handler_B.open(infile_B);
		//	this->start=start;
//			this->Requested_attr=Requested_attr;
//			this->noOfAttributes=noOfAttributes;
	//		do_work();
	//	}
		
		int getAttribute_BI(char * attr)
		{
			for(int i=0;i<nB;i++)
			{
				if(strcmp(attr,attribute_B[i])==0)
					return i;
			}
			return -1;
		}
		
		int getAttribute_AI(char * attr)
		{
			for(int i=0;i<nA;i++)
			{
				if(strcmp(attr,attribute_A[i])==0)
					return i;
			}
			return -1;
		}
		
		
		
		void do_work()
		{
			union data_type
				{
					int number;
					char varchar[16];
					float decimal;
				};
			
			
				int i,j,m;
				Query_handler_A>>nA;
				Query_handler_B>>nB;
				Result_handler<<(nA + nB)<<" ";
				char temp[15];
				data_type * data_list_A=(data_type *)malloc(nA*sizeof(data_type));
				data_type * data_list_B=(data_type *)malloc(nB*sizeof(data_type));
				int * type_A=(int *)malloc(nA*sizeof(int));
				int * type_B=(int *)malloc(nB*sizeof(int));
			
			attribute_A=(char **)malloc(nA*sizeof(char *));
			for(i=0;i<nA;i++)
			{
				attribute_A[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_A>>attribute_A[i];
				Result_handler<<attribute_A[i]<<" ";
			//	 Query_handler.getline(attribute[i],16," ");
			}
			
			
			attribute_B=(char **)malloc(nB*sizeof(char *));
			for(i=0;i<nB;i++)
			{
				attribute_B[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_B>>attribute_B[i];
				Result_handler<<attribute_B[i];
			}
			Result_handler<<"\n";
			
			for(i=0;i<nA;i++)
			{
				Query_handler_A>>temp;
				Result_handler<<temp<<" ";
				if(temp[0]=='i')
					type_A[i]=0;
				else if(temp[0]=='v')	
					type_A[i]=1;
				else
					type_A[i]=2;
			}
			
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>temp;
				Result_handler<<temp<<" ";
				if(temp[0]=='i')
					type_B[i]=0;
				else if(temp[0]=='v')	
					type_B[i]=1;
				else
					type_B[i]=2;
			}
			Result_handler<<"\n";
		
		start=(Condition *)malloc(sizeof(Condition));	
		Condition * p=start;
		Condition * q=p;
		for(i=0;i<nA;i++)	
		{
			for(j=0;j<nB;j++)
			{
				if(strcmp(attribute_A[i],attribute_B[j])==0)
				{	// match type..
					strcpy(p->Left_side,attribute_A[i]);
					strcpy(p->Right_side,attribute_B[j]);
					p->sign=1;
					p->L_type=2;
					p->next=(Condition *)malloc(sizeof(Condition));
					q=p;
					p=p->next;
					break;
				}
			}
		}
		q->next=NULL;
			
		while(!Query_handler_A.eof())
		{
			for(i=0;i<nA;i++)
			{
				if(type_A[i]==0)
					Query_handler_A>>data_list_A[i].number;
				else if(type_A[i]==1)
					Query_handler_A>>data_list_A[i].varchar;
				else
					Query_handler_A>>data_list_A[i].decimal;
			}	
			
			// debugging intialize b again
			Query_handler_B.clear();
			Query_handler_B.seekg(0,ios::beg);
			char temp[100];
			Query_handler_B>>temp;
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>temp;
				Query_handler_B>>temp;
			}
			
			
			while(!Query_handler_B.eof())
			{
			
					
			//	file1 a;
				Condition * p=start;
			//		Query_handler.read((char *)&a,sizeof(file1));
			
				int l;
				
			for(i=0;i<nB;i++)
			{
				if(type_B[i]==0)
					Query_handler_B>>data_list_B[i].number;
				else if(type_B[i]==1)
					Query_handler_B>>data_list_B[i].varchar;
				else
					Query_handler_B>>data_list_B[i].decimal;
			}			
			start->L_type=2;
			bool prevt=true;
			bool t=false;
			while(p!=NULL)
			{	
				l=getAttribute_BI(p->Right_side);
				m=getAttribute_AI(p->Left_side);
				t=false;
				if(p->sign==1)
				{
					if(type_B[l]==type_A[m]==0)
					{
						if(data_list_B[l].number==data_list_A[m].number)
							t=true;
					}
					else if(type_B[l]==type_A[m]==1)
					{
						if(!strcmp(data_list_A[l].varchar,data_list_B[m].varchar))
							t=true;
					}
					else 
						if(data_list_A[l].decimal==(float)data_list_B[m].decimal)
							t=true;
						
				//	if(a.(*(start.Left_side))==start.Right_side)
				}
				/*
				else if(p->sign==2)
				{
					if(type[l]==0)
					{
						if(data_list[l].number>(int)p->Right_side)
							t=true;
					}
					else if(type[l]==1)
					{
						if(strcmp(data_list[l].varchar,p->Right_side)>0)
							t=true;
					}
					else 
						if(data_list[l].decimal>(float)atoi(p->Right_side))
							t=true;
				}
				else if(p->sign==3)
				{
					if(type[l]==0)
					{
						if(data_list[l].number<(int)p->Right_side)
							t=true;
					}
					else if(type[l]==1)
					{
						if(strcmp(data_list[l].varchar,p->Right_side)<0)
							t=true;
					}	
					else 
						if(data_list[l].decimal<(float)atoi(p->Right_side))
							t=true;
				}
				if(p->L_type==1)
					prevt=prevt || t;
				else 
					prevt=prevt && t;
				
			*/	
	/*			if((p->L_type==1 || p->R_type==1) && t=true)
				{
					p=true;
					break;
				}
				else if(p->L_type==2 && p->R_type==2 && t=false)
	*/		
	

					
				p=p->next;
			}
			if(prevt)
			{
				for(i=0;i<nA;i++)
				{
					if(type_A[i]==0)
						Result_handler<<data_list_A[i].number << " ";
					else if(type_A[i]==1)
						Result_handler<<data_list_A[i].varchar << " ";
					else
						Result_handler<<data_list_A[i].decimal << " ";
				}			
				for(i=0;i<nB;i++)
				{
					if(type_B[i]==0)
						Result_handler<<data_list_B[i].number;
					else if(type_B[i]==1)
						Result_handler<<data_list_B[i].varchar;
					else
						Result_handler<<data_list_B[i].decimal;
				}			
				Result_handler<<"\n";
			}
			}
		}
			}
};


class Union
{
	private:
		int instance;
		ifstream Query_handler_A;
		ifstream Query_handler_B;
		int nA;			// no. of attributes in handler A
		int nB;			// no. of attributes in handler B
//		istream infile
		ofstream Result_handler;
//		char ** Requested_attr;
//		int noOfAttributes;
//		Condition * start;
		char ** attribute_A;
		char ** attribute_B;
		char * infile_A;
		char * infile_B;
		
	public:
	
	
	
		void readFileName(char *infile_A,char * infile_B)	
		{
			this->infile_A=(char *)malloc(sizeof(char)*50);
			this->infile_A=infile_A;			
			this->infile_B=(char *)malloc(sizeof(char)*50);
			this->infile_B=infile_B;			
			
		}	
		
		char * execute(int i)
		{
			char o_name[100];
			char stre[7];
			char * name=(char *)malloc(sizeof(char)*50);
			name="Union_Result_";
			
			instance=i;	
			stre[0]=(char)instance;
			stre[1]='.';
			stre[2]='t';
			stre[3]='x';
			stre[4]='t';
			stre[5]='\0';
			
			strcpy(o_name,name);
			
			strcpy(o_name,strcat(o_name,stre));
	
			
			Result_handler.open(o_name);		// may require concatenation
			Query_handler_A.open(infile_A);
			Query_handler_B.open(infile_B);
	//		this->start=start;
			do_work();		
			Query_handler_A.close();
			Query_handler_B.close();
			Result_handler.close();
//			strcpy(name,o_name);
			return name;
		}
	
		
	
		Union()
		{
			
		}
	
		
//		Union(int i,char *infile_A,char * infile_B)
//		{
//			instance='0'+i;	
//			Result_handler.open("Union_Result" + instance);
//			Query_handler_A.open(infile_A);
//			Query_handler_B.open(infile_B);
//		//	this->start=start;
//			this->Requested_attr=Requested_attr;
//			this->noOfAttributes=noOfAttributes;
//			do_work();
//		}
		
		int getAttribute_BI(char * attr)
		{
			for(int i=0;i<nB;i++)
			{
				if(strcmp(attr,attribute_B[i])==0)
					return i;
			}
			return -1;
		}
		
		int getAttribute_AI(char * attr)
		{
			for(int i=0;i<nA;i++)
			{
				if(strcmp(attr,attribute_A[i])==0)
					return i;
			}
			return -1;
		}
		
		
		
		void do_work()
		{
			union data_type
			{
					int number;
					char varchar[16];
					float decimal;
			};
			
			int i,j,m;
			bool prevt,t;
			Query_handler_A>>nA;
			Query_handler_B>>nB;
			Result_handler<<(nA)<<"\n";
			char temp[15];
			data_type * data_list_A=(data_type *)malloc(nA*sizeof(data_type));
			data_type * data_list_B=(data_type *)malloc(nB*sizeof(data_type));
			int * type_A=(int *)malloc(nA*sizeof(int));
			int * type_B=(int *)malloc(nB*sizeof(int));
			attribute_A=(char **)malloc(nA*sizeof(char *));
			for(i=0;i<nA;i++)
			{
				attribute_A[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_A>>attribute_A[i];
				Result_handler<<attribute_A[i]<<" ";
			//	 Query_handler.getline(attribute[i],16," ");
			}
			
			
			attribute_B=(char **)malloc(nB*sizeof(char *));
			for(i=0;i<nB;i++)
			{
				attribute_B[i]=(char *)malloc(sizeof(char)*16);
				Query_handler_B>>attribute_B[i];
//				Result_handler<<attribute_B[i];
			}
			Result_handler<<"\n";
			
			for(i=0;i<nA;i++)
			{
				Query_handler_A>>temp;
				Result_handler<<temp<<" ";
				if(temp[0]=='i')
					type_A[i]=0;
				else if(temp[0]=='v')	
					type_A[i]=1;
				else
					type_A[i]=2;
			}
			
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>temp;
//				Result_handler<<temp<<" ";
				if(temp[0]=='i')
					type_B[i]=0;
				else if(temp[0]=='v')	
					type_B[i]=1;
				else
					type_B[i]=2;
			}
			Result_handler<<"\n";
		
//		start=(Condition *)malloc(sizeof(Condition));	
//		Condition * p=start;
//		Condition * q=p;
		int AtoB[nA];				// relation of a to b..
		for(i=0;i<nA;i++)	
		{
			for(j=0;j<nB;j++)
			{
				if(strcmp(attribute_A[i],attribute_B[j])==0 && type_A[i]==type_B[j])
				{
					AtoB[i]=j;
					break;
				//	// match type..
				//	strcpy(p->Left_side,attribute_A[i]);
				//	strcpy(p->Right_side,attribute_B[j]);
				//	p->sign=1;
				////	p->L_type=2;
				//	p->next=(Condition *)malloc(sizeof(Condition));
				//	q=p;
				//	p=p->next;
				//	break;
				}
			}
			if(j>=nB)
			{
				printf("Error in union operation.. InCompatible...\n");		// halt the process
				exit(0);
				break;			
			}
		}
//		q->next=NULL;
			
		while(!Query_handler_A.eof())
		{
			for(i=0;i<nA;i++)
			{
				if(type_A[i]==0)
					Query_handler_A>>data_list_A[i].number;
				else if(type_A[i]==1)
					Query_handler_A>>data_list_A[i].varchar;
				else
					Query_handler_A>>data_list_A[i].decimal;
			}			
			// open query handler b again..
		//	Query_handler_B.seekp(SEEK_SET);
		//	Query_handler_B
//			Query_handler_B>>
// empty query handler till main content
/* int a;
	char str[100];
	fscanf(Query_handler_B,"%d",a);
	Query_handler_B>>a;
	for(i=0;i<nB;i++)
	{
			Query_handler_B>>str;
			Query_handler_B>>str;
			
	}
	*/
				Query_handler_B.clear();
			Query_handler_B.seekg(0,ios::beg);
			char emp[100];
			Query_handler_B>>emp;
//			printf("%s\n",emp);
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>emp;
//							printf("%s\n",emp);
				Query_handler_B>>emp;
//							printf("%s\n",emp);
			}

			while(!Query_handler_B.eof())
			{
			
					
			//	file1 a;
			//	Condition * p=start;
			///		Query_handler.read((char *)&a,sizeof(file1));
			
				int l;
				
			for(i=0;i<nB;i++)
			{
				if(type_B[i]==0)
					Query_handler_B>>data_list_B[i].number;
				else if(type_B[i]==1)
					Query_handler_B>>data_list_B[i].varchar;
				else
					Query_handler_B>>data_list_B[i].decimal;
			}			
	//		start->L_type=2;
	//		bool prevt=true;
	//		bool t=false;
	//		while(p!=NULL)
	//		{	
	//			l=getAttribute_BI(p->Right_side);
	//			m=getAttribute_AI(p->Left_side);
	//			t=false;
	//			if(p->sign==1)
	//			{
				prevt=true;
				for(i=0;i<nA;i++)
				{
					t=false;
					if(type_B[AtoB[i]]==type_A[i]==0)
					{
						if(data_list_B[AtoB[i]].number==data_list_A[i].number)
							t=true;
					}
					else if(type_B[AtoB[i]]==type_A[i]==1)
					{
						if(!strcmp(data_list_A[i].varchar,data_list_B[AtoB[i]].varchar))
							t=true;
					}
					else 
						if(data_list_A[i].decimal==(float)data_list_B[AtoB[i]].decimal)
							t=true;
						
					prevt=prevt && t;
				//	if(a.(*(start.Left_side))==start.Right_side)
				}
			if(prevt)
			{
				break;
			}
		}
		if(Query_handler_B.eof() && prevt==false)
		{
					for(i=0;i<nA;i++)
					{
						if(type_A[i]==0)
							Result_handler<<data_list_A[i].number << " ";
						else if(type_A[i]==1)
							Result_handler<<data_list_A[i].varchar << " ";
						else
							Result_handler<<data_list_A[i].decimal << " ";
					}			
					Result_handler<<"\n";
		}
	}
//	Query_handler_B.seekp(SEEK_SET);

//			Query_handler_B.close();
//			Query_handler_B.open(infile_B);
			Query_handler_B.clear();
			Query_handler_B.seekg(0,ios::beg);
			char emp[100];
			Query_handler_B>>emp;
//			printf("%s\n",emp);
			for(i=0;i<nB;i++)
			{
				Query_handler_B>>emp;
//							printf("%s\n",emp);
				Query_handler_B>>emp;
//							printf("%s\n",emp);
			}


	while(!Query_handler_B.eof())
	{
		for(i=0;i<nB;i++)
		{
				if(type_B[i]==0)
					Query_handler_B>>data_list_B[i].number;
				else if(type_B[i]==1)
					Query_handler_B>>data_list_B[i].varchar;
				else
					Query_handler_B>>data_list_B[i].decimal;
		}			
		for(i=0;i<nB;i++)
		{
				if(type_B[i]==0)
					Result_handler<<data_list_B[i].number << " ";
				else if(type_B[i]==1)
					Result_handler<<data_list_B[i].varchar << " ";
				else
					Result_handler<<data_list_B[i].decimal << " ";
		}			
		Result_handler<<"\n";
				
	}
	
			}
};

Select se[100];
Project p[100];
Join j[100];
NJoin n[100];
Union u[100];


char * executeQuery()
{
	
	int s_instance=select_instance;
	int p_instance=project_instance;
	int j_instance=join_instance;
	int nj_instance=njoin_instance;
	int u_instance=union_instance;
	char * fileName;
	fileName=(char *)malloc(sizeof(char)*100);
	
	
	char str[100];
	
	scanf("%s",str);	// select project..... or (
//	printf("%s",str);
	if(!strcmp(str,"Select") || !strcmp(str,"select") || !strcmp(str,"SELECT"))
	{
	//	printf("yes");
		select_instance++;
		
		scanf("%s",str);
		if(strcmp(str,"<"))
		{
			printf("Error\n");			
		}			
		
		else
		{
		//	printf("yes1\n");
			se[s_instance].takeConditions();			// method to be defined
		//	printf("yes2\n");
			scanf("%s",str);
		//	printf("%s\n",str);
			if(!strcmp(str,"("))
			{
				fileName=executeQuery();
			//	{
				//	printf("%s",fileName);
			//	}
			}
			else 
				strcpy(fileName,str);
				
		//	printf("%s\n",fileName);
			se[s_instance].readFileName(fileName);
		//	printf("yes1\n");						// debugging
			scanf("%s",str);
			if(!strcmp(str,")"))
			{
	//			printf("yes1\n");						// debugging
//				se[s_instance]
		//		fileName = 
		     (se[s_instance].execute(s_instance+48));
	//			return (se[s_instance].execute(s_instance+48));	// execute query.
//					printf("yes1\n");
				if(s_instance==0)
				{
					fileName="Select_instance_0.txt";
				}
				else if(s_instance==1)
				{
					fileName="Select_instance_1.txt";
				}
				else if(s_instance==2)
				{
					fileName="Select_instance_2.txt";
				}

				return fileName;
			
	//			return "Result_Select_" + select_instance; // to be rifined
			}
			else
			{
				printf("Error\n");
			}
			
		}		
		
	}
	
	else if(!strcmp(str,"Project") || !strcmp(str,"project") || !strcmp(str,"PROJECT"))
	{
		project_instance++;
		
		scanf("%s",str);
		if(strcmp(str,"<"))
		{
			printf("Error\n");			
		}			
		
		else
		{
			p[p_instance].takeAttributes();			// method to be defined
			scanf("%s",str);
			if(!strcmp(str,"("))
				fileName=executeQuery();
			else 
				strcpy(fileName,str);
				
			p[p_instance].readFileName(fileName);
			scanf("%s",str);
			if(!strcmp(str,")"))
			{

				fileName=(p[p_instance].execute(p_instance+48));	// execute query.
				if(p_instance==0)
				{
					fileName="Project_instance_0.txt";
				}
				else if(p_instance==1)
				{
					fileName="Project_instance_1.txt";
				}
				else if(p_instance==2)
				{
					fileName="Project_instance_2.txt";
				}			
	//			printf("%s\n",fileName);      // debugging
				return fileName;
//				return "Result_Select_instance"; // to be rifined.
			}
			else
			{
				printf("Error\n");
			}
		
		}
	}
		
	else if(!strcmp(str,"attr:"))
	{
		//aggregate
	}
	
	
		
	else
	{	
	//	char * fileName;
	//	fileName=(char *)malloc(sizeof(char)*100);
		
		char * leftTbl, * rightTbl;
		leftTbl=(char *)malloc(sizeof(char)*100);
		rightTbl=(char *)malloc(sizeof(char)*100);
	
		if(!strcmp(str,"("))
		{
			leftTbl=executeQuery();
		}
		else
		{
			strcpy(leftTbl,str);	
		}
		scanf("%s",str);
//		printf("%s",str);
		if(!strcmp(str,"Join") || !strcmp(str,"JOIN") || !strcmp(str,"join") )
		{
		//	printf("es\n");
			// join tables
			
			join_instance++;
			scanf("%s",str);
			if(strcmp(str,"<"))
			{
				printf("Error\n");
							printf("error\n");
							exit(0);
			}			
	
			else
			{
			//	printf("yes1");
				j[j_instance].takeConditions();			// method to be defined
			//	printf("yes");
				scanf("%s",str);
				if(!strcmp(str,"("))
					rightTbl=executeQuery();
				else 
					strcpy(rightTbl,str);
				scanf("%s",str);
				if(!strcmp(str,")"))
				{
					j[j_instance].readFileName(leftTbl,rightTbl);
					return(j[j_instance].execute(j_instance+48));	// execute query.
			//		return "Result_join_instance"; // to be rifined. concatenate them
				}
				else
				{
					printf("Error\n");
				}
			}				
		}
		else if(!strcmp(str,"Union"))
		{
			union_instance++;
			scanf("%s",str);
//			if(strcmp(str,"<"))
//			{
//				printf("Error\n");			
//			}			
	
//			else
//			{
//				j[join_instance].takeAttributes();			// method to be defined
//				scanf("%s",str);
				if(!strcmp(str,"("))
					rightTbl=executeQuery();
				else 
					strcpy(rightTbl,str);
				scanf("%s",str);
				if(!strcmp(str,")"))
				{
					u[union_instance].readFileName(leftTbl,rightTbl);	// execute query.
					return(u[union_instance].execute(u_instance+48));	// execute query.
	//				return "Result_join_instance"; // to be rifined. concatenate them
				}
				else
				{
					printf("Error\n");
				}
		}				
		else if(!strcmp(str,"NJoin"))
		{
			njoin_instance++;
			scanf("%s",str);
	//		if(strcmp(str,"<"))
	//		{
	//			printf("Error\n");			
	//		}			
	
	//		else
	//		{
	//			j[join_instance].takeAttributes();			// method to be defined
	//			scanf("%s",str);
				if(!strcmp(str,"("))
					rightTbl=executeQuery();
				else 
					strcpy(rightTbl,str);
				scanf("%s",str);
				if(!strcmp(str,")"))
				{
					n[join_instance].readFileName(leftTbl,rightTbl);	// execute query.
					return (n[join_instance].execute(nj_instance+48));	// execute query.
//					return "Result_join_instance"; // to be rifined. concatenate them
				}
				else
				{
					printf("Error\n");
				}
			}				
	/*	else if(!strcmp(str,"Intersection"))
		{
			intersection_instance++;
			scanf("%s",str)
//			if(strcmp(str,"<"))
//			{
//				printf("Error\n");			
//			}			
//	
//			else
//			{
//				j[join_instance].takeAttributes();			// method to be defined
//				scanf("%s",str);
				if(strcmp(str,"("))
					rightTbl=executeQuery();
				else 
					strcpy(rightTbl,str);
				scanf("%s",str);
				if(!strcmp(str,")"))
				{
					i[intersection_instance].execute();	// execute query.
					return "Result_join_instance"; // to be rifined. concatenate them
				}
				else
				{
					printf("Error\n");
				}
			}				
	
			
			
		}
		
		else if(!strcmp(str,"Setdifference"))
		{
			
		}
*/		
	//	else
	//	{
			printf("Error\n");
	//	}
	}	
	
}
		

		






int main()
{
	//printf("Proper front page\n"); // debugging
	
	printf("Enter query\t:");
	
	char fileName[100],leftTbl[100],rightTbl[100],str[100];
	
//	ofstream o;
	
	scanf("%s",fileName);
	
	if(!strcmp(fileName,"Select") || !strcmp(fileName,"Project") || !strcmp(fileName,"Join"))
	{
		//syntax error state : invalid name given to ouput file
	}
	
	
	scanf("%s",str);
	if(strcmp(str,"="))
	{
			//syntax error state : invalid name given to ouput file
	}
	
	scanf("%s",str);
	
	if(!strcmp(str,"("))
	{
		char * a=(char *)malloc(sizeof(char)*50);
		a=executeQuery();
	//	printf("%s %s\n",a,fileName);
	//	u[99].readFileName(a,a);
	//	a=u[99].execute(9);
//		rename(a,fileName);
		
//		o.is_open(a);
//		o
		
	//	fileName=executeQuery();
		
	}
	
	else
	{
			//syntax error state : invalid name given to ouput file	
			printf("Error\n");
	}
	
	// ouput result
	
}
//	implementing parser
	
	
	
/*	
	gets(strin);
	if(strin[0]=='s')
	{
		state=1,2,3;
	}
	if(strin[7]=='*')
	{
		state=1,3;
	}
	int j=0;
	for(i=13;i<strlen(strin);i++)
	{
		if(strin[i]==32)
			break;
		table_name[j]=strin[i];
		j++;
	}
	// join part
	i+=7;
	j=0;
	for(;i<strlen(strin);i++)												// 1---==, 2----<=, 3---->= //
	{
		if(strin[i]==32)
			break;
		else if(strin[i]=='=')
		{
			opr_flag=1;
			break;
		}
		else if(strin[i]=='<')
		{
			opr_flag=2;
			break;
		}
		else if(strin[i]=='>')
		{
			opr_flag=3;
			break;
		}
		
		arg_name[j]=strin[i];
	}
	i+=2;
	j=0;
	if(strin[i]==32)
		i++;
	for(;i<strlen(strin);i++)
	{
		if(strin[i]==32)
			break;
		else
			match_name[j]=strin[i];
	}
	File * temp=fopen("temp.bin","ab+");
	if(table_name=="ID")
	{
		FILE * ptr=fopen("IDS.bin","rb+");
		while(!feof(ptr))
		{
			fread(r,sizeof(r),1,ptr);
			if(arg_name=="UID")
			{
				if(r.uid==(int)match_name)
					fwrite(r,sizeof(r),1,temp);
			}
			else if(arg_name=="passport_id")
			{
				if(r.passport_id==int(match_name))
					fwrite(r,sizeof(r),1,temp);
			}
		}
		
	}
*/	
//	return 0;
//}
