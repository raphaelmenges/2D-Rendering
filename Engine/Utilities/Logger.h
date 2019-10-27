#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "../Types.h"

// TODO: INEFFICIENT TO OPEN / CLOSE LOG EACH WRITE

/* Settings */
const bool LOG_CONSOLE_OUTPUT = true;
const bool LOG_FILE_OUTPUT = true;
const bool PRINT_DEBUG = false;

class Logger
{
public:

	/* Method to print information */
	template<typename... Args>
	static void info(Args... args)
	{
		getInstance()->print("INFO      : ", args...);
	}

	/* Method to print warnings */
	template<typename... Args>
	static void warning(Args... args)
	{
		getInstance()->print("WARNING   : ", args...);
	}

	/* Method to print errors */
	template<typename... Args>
	static void error(Args... args)
	{
		getInstance()->print("ERROR     : ", args...);
	}

	/* Method to print undefined */
	template<typename... Args>
	static void undefined(Args... args)
	{
		getInstance()->print("UNDEFINED: ", args...);
	}

	/* Method to print debug information */
	template<typename... Args>
	static void debug(Args... args)
	{
		if (PRINT_DEBUG)
		{
			getInstance()->print("DEBUG     : ", args...);
		}
	}

private:

	/* Private constructor */
	Logger()
	{
		/* Delete old log */
		if (LOG_FILE_OUTPUT)
		{
			std::ofstream file;
			file.open("Log.txt", std::ios::out | std::ios::ate);
			file.close();
		}
	}

	/* Destructor */
	virtual ~Logger() {}

	/* Private copy constuctor */
	Logger(Logger const&) {}

	/* Private assignment operator */
	Logger& operator = (Logger const&) { return *this; }

	/* Check for instance existence */
	static Logger* getInstance()
	{
		if (pInstance == _null)
		{
			static Logger logger;
			pInstance = &logger;
		}
		return pInstance;
	}

	/* Printing it out */
	template <typename T>
	void printOut(T t, bool breakLine) const
	{
		if (LOG_CONSOLE_OUTPUT)
		{
			/* Use console for output */
			std::cout << t;
			if (breakLine)
			{
				std::cout << std::endl;
			}
		}
		if (LOG_FILE_OUTPUT)
		{
			/* Use file for output */
			std::ofstream file;
			file.open("Log.txt", std::ios::out | std::ios::app);
			file << t;
			if (breakLine)
			{
				file << "\n";
			}
			file.close();
		}
	}

	/* Recursive printing for one string method */
	template <typename T>
	void print(T t) const
	{
		printOut(t, true);
	}

	/* Recursive printing for multiple strings method */
	template<typename T, typename... Args>
	void print(T t, Args... args) const
	{
		printOut(t, false);
		print(args...);
	}

	/* The pointer to the single instance */
	static Logger* pInstance;
};

#endif
