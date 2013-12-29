Run the main.exe file and give the query

***Note: You can give nested queries also.

***ASSUMPTIONS:

1. The value in the tuples does not contain any spaces in between.

2. For a file:
a). First line contains the no. of columns
b). Second line contains the data type of those columns
c). Remaining each line represent one tuple.


3. Input assumtion:

select input:

 A = ( Select < ( [ name = rahul ] OR [ age = 19 ] ) > data.txt ) 

 A = ( Select < [ name = rahul ] > data.txt ) 

with space given as above


project input:

 A = ( Project < name > data.txt ) 

 A = ( Project < name , id > data.txt )	



join input:

 A = ( data.txt Join < [ name = aname ] > data2.txt )


*** After the query is executed you will get the result table of the query as a file created in your directory.