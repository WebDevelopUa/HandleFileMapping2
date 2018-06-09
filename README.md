# HandleFileMapping2

####���������� ����������, C++

*HandleFileMapping2.cpp*: ���������� ����� ����� ��� ����������� ����������.

###������ �������

������ ������� ������� ������ "�������� �����" ��� ������ ������ ������� **CreateFileMapping()** � *INVALID_HANDLE_VALUE* � ������ ��� �������. 

��������� ������ *PAGE_READWRITE*, ������� ����� ����� ���������� ������-������ � ������ ����� ���������� ����� ������������� ������ �����, ������� ���������. 

*������� #1* ����� ���������� ���������� ������� "�������� �����", ������������ **CreateFileMapping()** ��� ������ **MapViewOfFile()**, ����� ������� ������������� ����� � �������� ������������ ��������. 

������� **MapViewOfFile()** ���������� ��������� �� ������������� ������ �����. 

����� �������� ������ �� ����� ������ � ������� "�������� ����� � ������", �� ������ ������� ������� **CloseHandle()**. 

����� ��� ����������� �������, ������� ����� ���������� ������ ����� ��������, ������������� ��������.


 
*Process2.cpp*: ���������� ����� ����� ��� ����������� ����������.

###������ �������

������ **������� #2** ����� �������� ������ � ����� � ��� �� ������ ��� ������ ������ ������� **OpenFileMapping()** � ��� �� ����� ������, ��� � ������ �������.

�� ����� ����� ������������ ������� **MapViewOfFile()**, ����� �������� ��������� �� ������������� ������ �����.
 

-----------------------------------------------------------------------------------------------------

####Console application, C ++


*HandleFileMapping2.cpp*: Specifies the entry point for the console application.

###The First Process

The first process creates the "file projection" object by calling the function **CreateFileMapping()** with *INVALID_HANDLE_VALUE* and the name for the object.

Using the *PAGE_READWRITE* flag, the process will have read-write permission to memory through any data file representations that are created.

*Process #1* then uses the "file projection" object descriptor returned by **CreateFileMapping()** when calling **MapViewOfFile()** to create a file representation in the process address space.

**MapViewOfFile()** function returns a pointer to the data representation of the file.

When the process no longer needs access to the "file-to-memory" object, it must call the **CloseHandle()** function.

When all descriptors are closed, the system can free the swap file section used by the object.


�
*Process2.cpp*: Specifies the entry point for the console application.

###The Second Process

The second **Process #2** can access the same data by calling the **OpenFileMapping()** function with the same name as the first process.

It can then use the **MapViewOfFile()** function to get a pointer to the data representation of the file.



 