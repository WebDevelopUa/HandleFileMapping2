// Консольное приложение, C++
// Process2.cpp: определяет точку входа для консольного приложения.
/* Второй процесс

Второй Процесс #2 может получить доступ к одним и тем же данным при помощи вызова
функции OpenFileMapping() с тем же самым именем, что и первый процесс.
Он может затем использовать функцию MapViewOfFile(), чтобы получить указатель
на представление данных файла.
*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#define BUF_SIZE 256

// LPCWSTR является объявлением typedef для типа const WCHAR *
// LPCWSTR szName[] = TEXT("MyFileMappingObject");
// Если в качестве аргумента используется строковый литерал, то используется перед ним префикс L
	TCHAR szName[] = L"MyFileMappingObject";

void main()
{
	HANDLE hMapFile;
	TCHAR *pBuf;

	// открываем объект "проекция файла", связанный с массивом данных по имени - szName
	hMapFile = OpenFileMapping(

		// доступ к записи-чтению
		FILE_MAP_ALL_ACCESS,

		// имя не наследуется
		FALSE,

		// имя "проецируемого" объекта 
		szName);

	// Узнать подробности об ошибке можно с помощью GetLastError()
	if (hMapFile == NULL)
	{
		//Невозможно открыть объект **проекция файла**
		printf("Failed with error %d: | ERROR %x - Unable to open object * file projection** \n",
			GetLastError());

		// функция ждёт нажатия ENTER
		getwchar();
		return;
	}

	// представление всего массива данных (szName) на адресном пространстве
	pBuf = (TCHAR*)MapViewOfFile(

		// дескриптор "проецируемого" объекта
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

		// функция ждёт нажатия ENTER
		getwchar();
		return;
	}

	MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);

	// снятие отображения содержимого файла
	UnmapViewOfFile(pBuf);

	// закрытие открытых дескрипторов
	CloseHandle(hMapFile);
}