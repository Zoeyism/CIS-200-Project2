#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ErrorLogger
{
public:
	ErrorLogger(string FileName = "errorlog", string FileType = ".txt");
	bool CheckFileTypeValidity(string FileType);	// Checks if string FileType (.txt, .dat, etc) is valid
	void LogError(string ErrorInfo);				// Logs an error to the file.
	void SetToPostErrors()							// Sets the LogError method to post to cout, as well as to log file.
	{
		post_errors = true;
		cout << "\n\tErrors will now be posted through cout, as well as being logged.\n";
	}					
	~ErrorLogger()
	{
		// Closes error file upon destruction of instance.
		error_file.close();
	}

private:
	ofstream error_file;
	string file_name;
	string file_type;
	bool post_errors;
	const string DEFAULT_TYPE = ".txt";
	const string DEFAULT_NAME = "errorlog";
};