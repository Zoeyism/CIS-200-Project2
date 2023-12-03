#include "ErrorLogger.h"

using namespace std;

ErrorLogger::ErrorLogger(string FileName, string FileType)
{
	// Creates new error file. If the file already exists, appends a number to the end of the filename.
	int error_num = 0;
	bool added_num = false;
	bool file_exists = true;
	bool invalid_type = false;
	ifstream initial_open;
	if (!CheckFileTypeValidity(FileType))
	{
		FileType = DEFAULT_TYPE;
		invalid_type = true;
	}

	while (file_exists) // By default, will start as closed
	{
		initial_open.open(FileName + FileType, ios::in);
		if (initial_open) // If error_file already exists...
		{
			initial_open.close();			// Close it 
			if (added_num)
				FileName.pop_back();	// Remove number from file name, if already added
			else
				added_num = true;
			error_num++;
			FileName += to_string(error_num);	// Add new number to file name
		}
		else
		{
			file_exists = false;
			initial_open.close(); // Close file 
		}
	}

	// Now that a filename that ISN'T used has been found,creates the file as an output
	//		and applies the filename and filetype to instance's members.
	error_file.open(FileName + FileType, ios::out);

	file_name = FileName;
	file_type = FileType;

	if (invalid_type)
		LogError("Error: File type given when initializing ErrorLogger was invalid. Defaulted to '.txt' instead.");
};

bool ErrorLogger::CheckFileTypeValidity(string FileType)
{
	if (FileType.length() > 0)
	{
		if (FileType[0] == '.' && FileType.find_last_of('.') == 0)
			return true;
		else
			return false;

	}
	else
		return false;
}

void ErrorLogger::LogError(string ErrorInfo)
{
	// Logs a given error to the error_file.
	if (!error_file)
		error_file.open(file_name + file_type, ios::app);
	error_file << ErrorInfo << endl;

	if (post_errors)
		cout << ErrorInfo << endl;
}
