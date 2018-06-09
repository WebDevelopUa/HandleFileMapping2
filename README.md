# HandleFileMapping2

#### Консольное приложение, C++

*HandleFileMapping2.cpp*: определяет точку входа для консольного приложения.

### Первый процесс

Первый процесс **Процесс #1** создает объект "проекция файла" при помощи вызова функции **CreateFileMapping()** с *INVALID_HANDLE_VALUE* и именем для объекта. 

Используя флажок *PAGE_READWRITE*, процесс будет иметь разрешение чтения-записи в память через посредство любых представлений данных файла, которые создаются. 

**Процесс #1** затем использует дескриптор объекта "проекция файла", возвращенный **CreateFileMapping()** при вызове **MapViewOfFile()**, чтобы создать представление файла в адресном пространстве процесса. 

Функция **MapViewOfFile()** возвращает указатель на представление данных файла. 

Когда процессу больше не нужен доступ к объекту "проекция файла в память", он должен вызвать функцию **CloseHandle()**. 

Когда все дескрипторы закрыты, система может освободить секцию файла подкачки, используемого объектом.




 
*Process2.cpp*: определяет точку входа для консольного приложения.

### Второй процесс

Второй **Процесс #2** может получить доступ к одним и тем же данным при помощи вызова функции **OpenFileMapping()** с тем же самым именем, что и первый процесс.

Он может затем использовать функцию **MapViewOfFile()**, чтобы получить указатель на представление данных файла.
 

 

-----------------------------------------------------------------------------------------------------

#### Console application, C ++


*HandleFileMapping2.cpp*: Specifies the entry point for the console application.

### The First Process

The first process creates the "file projection" object by calling the function **CreateFileMapping()** with *INVALID_HANDLE_VALUE* and the name for the object.

Using the *PAGE_READWRITE* flag, the process will have read-write permission to memory through any data file representations that are created.

**Process #1** then uses the "file projection" object descriptor returned by **CreateFileMapping()** when calling **MapViewOfFile()** to create a file representation in the process address space.

**MapViewOfFile()** function returns a pointer to the data representation of the file.

When the process no longer needs access to the "file-to-memory" object, it must call the **CloseHandle()** function.

When all descriptors are closed, the system can free the swap file section used by the object.





 
*Process2.cpp*: Specifies the entry point for the console application.

### The Second Process

The second **Process #2** can access the same data by calling the **OpenFileMapping()** function with the same name as the first process.

It can then use the **MapViewOfFile()** function to get a pointer to the data representation of the file.



 
