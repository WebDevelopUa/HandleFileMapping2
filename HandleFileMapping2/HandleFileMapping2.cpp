// Консольное приложение, C++
// HandleFileMapping2.cpp: определяет точку входа для консольного приложения.
/** Первый процесс

Первый процесс создает объект "проекция файла" при помощи вызова функции CreateFileMapping()
с INVALID_HANDLE_VALUE и именем для объекта. Используя флажок PAGE_READWRITE,
процесс будет иметь разрешение чтения-записи в память через посредство любых
представлений данных файла, которые создаются. Процесс #1 затем использует дескриптор объекта
"проекция файла", возвращенный CreateFileMapping() при вызове MapViewOfFile(), чтобы создать
представление файла в адресном пространстве процесса. Функция MapViewOfFile() возвращает
указатель на представление данных файла. Когда процессу больше не нужен доступ к объекту
"проекция файла в память", он должен вызвать функцию CloseHandle(). Когда все дескрипторы
закрыты, система может освободить секцию файла подкачки, используемого объектом.
*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#define BUF_SIZE 256
#define COPY_SIZE 256

// MyCopyMemory - обертка для функции CopyMemory - Копирует блок памяти из одного места в другое
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa366535(v=vs.85).aspx

void MyCopyMemory(TCHAR *buf, TCHAR *szMsg, SIZE_T cbData, SIZE_T bufsize)
{
	CopyMemory(buf, szMsg, min(cbData, bufsize));
}

TCHAR szName[] = TEXT("MyFileMappingObject");
TCHAR szMsg[] = TEXT("Message from Process #1");

void main()
{
	HANDLE hMapFile;
	TCHAR *pBuf;

	// создаем объект "проекция файла", связанный с массивом данных по имени - szName
	hMapFile = CreateFileMapping(

		// использование файла подкачки
		INVALID_HANDLE_VALUE,

		// защита по умолчанию 
		NULL,

		// доступ к записи-чтению
		PAGE_READWRITE,

		// макс. размер объекта 
		0,

		// размер буфера  
		BUF_SIZE,

		// имя отраженного в памяти объекта
		szName);

	// Узнать подробности об ошибке можно с помощью GetLastError()
	// Если объекта ядра с указанным именем нет, 
	// функции возвращают NULL, a GetLastError() — код 2 (ERROR_FILE_NOT_FOUND).
	if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE)
		//if (hMapFile == NULL)
	{
		//Не может создать отраженный в памяти объект
		printf("Failed with error %d: | ERROR %x - Can not create a mapped object \n",
			GetLastError());
		return;
	}

	// представление всего массива (szName) на адресном пространстве
	pBuf = (TCHAR*)MapViewOfFile(

		// дескриптор  отраженного в памяти объекта
		hMapFile,

		// разрешение записи-чтению
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

	// Узнать подробности об ошибке можно с помощью GetLastError()
	if (pBuf == NULL)
	{
		// Представление проецируемого файла невозможно 
		printf("Failed with ERROR %x | %d - The projected file can not be displayed \n",
			GetLastError());
		return;
	}

	MyCopyMemory(pBuf, szMsg, COPY_SIZE * sizeof(TCHAR), BUF_SIZE * sizeof(TCHAR));
	_tprintf(TEXT("Destination buffer contents: %s\n"), pBuf);

	// функция ждёт нажатия ENTER
	getwchar();

	// снятие отображения содержимого файла
	UnmapViewOfFile(pBuf);

	// закрытие открытых дескрипторов
	CloseHandle(hMapFile);
}