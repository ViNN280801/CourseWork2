# CourseWork2
Qt/C++ DB Application
The purpose of the work is to gain skills in problem setting, algorithmization, modular principle of application development and debugging on the example of creating a program with a user interface for working with a database.
As databases, I create 2 files that are not related to each other in any way. In which one table with data is stored. The files have the extension .sql. The table in the first file contains information about users (ID, login and password). The table in the second file contains weather data (ID, day of the week, date, month, main characteristics, and temperature). I created two files for clarity, but, of course, it was possible to do everything in one file, just do not set the relationship between the tables.
The main tasks are to create a program that works with the database in the form of sql files. The program code must support the modular development principle. When implementing the program, you must use OOP.
The DBMS (database management system) must perform the following actions:
1) view the database;
2) search for entries by input parameters;
3) editing a record using different input parameters;
4) adding an entry to the end of the list and anywhere in the table;
5) deleting an entry whose number is set by the user;
6) delete all of the records;
7) sort the records;
8) data encryption and decryption;
9) saving the database state;
10) updating the data display window;

Also, the DBMS must provide for handling error situations.
In my work, I used the topic “analysis of weather data".



Description of the development
1.1 Collection of information
Information was collected in my program using a special library libcurl (https://curl.haxx.se/libcurl/c/) from the site https://sinoptik.ua. The weather is taken from the city of Saint Petersburg. Working with the libcurl library was performed in the htmlThief file.h, to test that it is possible to pre-compile the form htmlThief.sh file. The principle of operation is as follows:
1) Declaring THE curl_global_all flag, which is responsible for connecting various data transfer protocols on the Internet, such as UDP, TCP / IP, outdated TLS, modern SSL, HTTP, HTTPS, FTP, and others;
2) Initialization of the curl session, which implies the return of the standard CURL descriptor, which in turn will be needed for the input signal for other functions;
3) Next is the installation of options:
a) Setting the URL of the desired page, in my case - https://sinoptik.com.ru/погода-санкт-петербург;
b) Enabling full Protocol output/debugging during operation;
c) the Inclusion of a progress bar (not a mandatory option);
d) Enabling an option that is responsible for writing information in a pre-prepared static function writeData of type size_t, which returns the number of bytes written to the FILE stream FILE*, so writeData is of type size_t (integer).
4) Open the file in (“wb") mode to write data in binary format. Next, we write the curl functions to the extension file .html data " stolen” from the site specified earlier, i.e. a small web scrapping;
5) Calling the curl_easy_cleanup(CURL* handle) function to "clean up" the stream that we declared at the very beginning of working with this library. Same principle as closing a file;
6) Next is a function similar to the previous one. It clears the global declared curl stream (applies only if a function has been declared that initializes the global stream, and is not safe if you have not declared the global curl_global_init(void) stream).

1.2 Parsing .html document taken from the site using the previously specified method
For parsing, a library written in pure C by Microsoft – Gumbo-Parser was used (http://matze.github.io/clib-doc/gumbo-parser/index.html). Parsing .an html document consists of finding the necessary characteristics for the future database,then adding the data to the array of structures. The principle of parsing is as follows:
a) Each function that searches for the necessary data (there are several such functions and their principle of operation is almost identical, differs only in that when studying the earlier taken .the html document was found that the necessary data was enclosed in different tags, some tags had classes, of course, a search was performed by the name of the tag class.) included tag verification. The tag was identified during the study .html document itself;
b) checking for a tag (whether the {node} parameter that is being passed to the function is the right tag), and also checking for the class name (which is not mandatory for all functions, because not all functions have a class);
c) Declaring another gumbonode * node and assigning it the child element data;
d) checking the node type (make sure that the node is GUMBO_NODE_TEXT, i.e. text information, also check for GUMBO_NODE_WHITESPACE, so that there is no empty text);
e) Copying text to an array of structures;
f) Checking in the loop (whether there are still child elements, then calling the function in which the work was performed, that is, recursion).

1.3 user interface of the program
When the program starts, a login window appears, and you can also register in the same window. When trying to log in, the program compares records in the database with users and compares them with the entered login data. if the check was successful, the user logs in. if not, the program displays a window with the corresponding message. During registration, you enter your username and password twice. The program adds you to the database and notifies you about it. Also, the following error was processed: when you enter passwords, their compliance is checked. The program pre-created a privileged user-admin, when you log in for which you can see a special admin control panel. In it, accordingly, you can make a variety of changes to the database.

1.4 Functions for working with the database
The following functions are included in the work::
- Creating a database;
- Output data in tabular form in the window;
- Adding an entry to the end of the database;
- Adding an entry to a specific database position;
- Changing a specific record;
- Delete a specific record;
- Delete all entries;
- Encrypted file;
- Decrypt the file;
- Search for entries by input data;
- Sorting records;
- Save the state of the database;
- Database backup;
- Updating the data view window;
- Exit the program.

2.1 creating a database
Creating a database follows a fairly simple algorithm. An object of the QsqlDataBase class is created, then the database is added using QSQLITE. We set the host name for the database and just the name of the database itself, which is the direct path to the database.

2.2 output of data in tabular form in the window
Data output occurs in a window. for this purpose, the tableView class is used, in which you can configure the type of data displayed. For example, in my work, I made the following configuration:
setModel-set the model on my tableView form element;
setSelectionBehavior-row selection mode (SelectRows);
setSelectionMode-single row selection mode (SingleSelection);
resizeColumnsToContents – set the size of columns according to the content size;
setEditTriggers-mode that does not allow you to change data by double-clicking on a specific row and column, and writing other data (NoEditTriggers);
setStretchLastSection-mode that allows you to fill the available space by stretching the last section of the header (set to true);

2.3 Adding an entry to the end of the database
Adding an entry to the end of the database does not require special skills in writing sql queries. That is, to add a record to a database (any), I wrote a simple sql query, in the following form:
INSERT INTO Weather (Weekday, Date_, Month, Label, Temperature)
VALUES ( ... )
Data for filling in the table is sent to the method by a parameter created from the QVariantList class.

2.4 Adding an entry to a specific database position
To add a record to a certain position, just add the required ID to the previous query, that is, the desired row number to which the record should be added:
INSERT INTO Weather (ID, Weekday, Date_, Month, Label, Temperature)
VALUES (...)
Data for filling the table is sent to the method by a parameter created from the QVariantList class.

2.5 Changing a specific record
An sql query that includes an UPDATE sql statement is also used for changes. Example of a request to update a record (naturally, the method works with the incoming ID parameter to change a specific record):
UPDATE Weather
SET Weekday = …,
Date_ = …,
Month = …,
Label = …,
Temperature = …
WHERE ID = …
An ellipsis refers to rows of data that will replace the old data.

2.6 Deleting a specific record
The DELETE operator is used for deletion. Example of deleting a specific record in the database:
DELETE
FROM Weather
WHERE ID = …
Again, I use the ID as a reliable key to the line that needs to be deleted.

2.7 Deleting all records
To delete all records, use a more interesting and tricky composite query that includes 3 queries at once. An example of such a request can be seen below in my DataBase class, in the deleteAllWeatherRecords () method:
1 request:
DELETE FROM Weather
This request simply deletes all records, without deleting the IDS that were used.
2 request:
VACUUM
The following query rebuilds the database file, “repacking " it to the minimum amount of disk space. Running VACUUM to rebuild the database frees up space and reduces the size of the database file. Frequent inserts, updates, and deletions can lead to database file fragmentation when data for a single table or index is scattered throughout the database file. Running VACUUM ensures that each table and index is largely stored continuously in the database file. In some cases, VACUUM can also reduce the number of partially filled pages in the database, further reducing the size of the database file.
3 query:
DROP TABLE Weather
This command simply deletes the table, this is done for the previously described problem with busy IDS.
Next, you must use the table creation method after the delete method.

2.8 data Encryption
In the encryption method, I used the well-known XOR encryption, that is, encryption with the binary operator EXCLUDING OR. In my work, the encryption code can be found in the MainDataBase class, in the xor_encryption method (const std::string &key, std::string &str); encryption Works like this:
str[i] ^= key[i % key.size()];
That is, we use the binary operator exclusive or to each character of the string per key with an index identical to the index of the string character, from which we take the remainder of the index division by the key size. The key is also a string, as you can see above in the method Declaration.

2.9 data
Decryption data Decryption is performed by re-encrypting strings. In my work, I encountered a problem: during string encryption, the encryption characters were line break characters (I tried to replace this character with separators, but this did not help), which caused repeated encryption to give an incomplete picture. The data have been strangely decoded. I fixed this as follows: I save the entire string with all the data and encrypt it twice, that is, decrypt it to clearly demonstrate that the method really works. Then I overwrite the data in the table.

2.10 search for records by input data
search Methods implemented by reading data from the file entered by the user as an input parameter. That is, the user entered. For example, the day of the week is Monday. I read from the file with an sql query, in which I set this Monday with the WHERE operator. Then the request is triggered. I delete all data from the table view of data and fill it with new data taken from the previously described query.

2.11 Sorting of records
The sorting algorithm is quite simple in my work. I used an sql query with the ORDER BY operator, which sorts by table columns. Example of sorting:
SELECT *
FROM Weather
ORDER BY Month
This query returns a tabular view of all data sorted by month.

2.12 Saving the state of the database
The save algorithm works as follows: before making any changes to the database, all data is backed up, which will be described later in paragraph 2.12. That is, before each change, the initial state is saved, so that all data does not lose its structure and memory leaks do not occur. All data is stored in a variable of the QVariantList class for convenient further use of the data.

2.13 database Backup
A backup is a complete reading of data from a table and saving it to a variable of the QVariantList class. For a detailed review of this method, we recommend viewing the file database.cpp, the DataBase class, and the backupDataFromWeatherDB () method.

2.14 Updating the data view window
the Algorithm for updating the data view window is quite primitive. You need to close the window, then open it in order to load the data and make changes.
Example of updating:
this→close();
this→show();


2.15 Exiting the program
The exit algorithm is even simpler. All you need to do is log out of the app. This is done in one line:
QApplication:: exit(EXIT_SUCCESS);
EXIT_SUCCESS is a constant declared by the define command, equivalent in value to zero, that is, a successful exit from the program, in the stdlib.h file or in a newer version, The C++ cstdlib file.
