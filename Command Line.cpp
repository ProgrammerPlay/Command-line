#include "../../../std_lib_facilities.h"
#include <Windows.h>

void get_command(); //get input to generate command

void help(); //the help screen for commands.

//void check_status(account acc) {

//}

void login();

struct account {
	string username;
	string password;
	string status = "not_activated";
	void delete_curr();
	string form = "{ " + username + " , " + password + " , status = " + status + " }";
};

void account::delete_curr() {
	cout << "Please enter your password again: ";
	string password;
	cin >> password;
	if (password == this->password) {
		fstream ofs{ "C:\\Users\\TOMBEO\\Documents\\account", ios_base::out | ios_base::in };
		if (!ofs) cout << "OPEN FAILED\n";
		string update;
		for (string acc; getline(ofs, acc);) {
			if (acc == this->form); // DON'T append update
			else {
				update += (acc + '\n');
			}
		}
		ofs.close();
		remove("C:\\Users\\TOMBEO\\Documents\\account");
		ofstream fs{ "C:\\Users\\TOMBEO\\Documents\\account", ios_base::out };
		fs << update;
		fs.close();
		//rename("C:\\Users\\TOMBEO\\Documents\\account", )
		cout << "Delete successful\nLogging in...\n";
		login();
	}
	else { cout << "Incorrect password !\n"; get_command(); }
}

account current_user;

ostream& operator<<(ostream& os, account acc) { // Only for registering
	os << "{ " << acc.username << " , " << acc.password << " , status = " << acc.status << " }" << '\n';
	return os;
}

void sign_up() {
	cout << "+------------------------------------+\n|";
	cout << "		SIGN_UP\n+------------------------------------+\n";
	cout << "|  Enter new username: ";
	string new_username;
	cin >> new_username;
	//cout << "  |\n";
	//cin.clear();
	cout << "|  Enter new password: ";
	string new_password;
	cin >> new_password;
	//cin.clear();
	cout << "|  Confirm password: ";
	string confirm;
	cin >> confirm;
	//cin.clear();
	ifstream ifs{ "C:\\Users\\TOMBEO\\Documents\\account", ios_base::in };
	for (string a, b, c, d, e, f, g, h, i; ifs >> a >> b >> c >> d >> e >> f >> g >> h >> i;) {
		if (b == new_username) {
			cout << "|  Username already existed !\n+------------------------------------+\n";
			ifs.close();
			login();
		}
	}
	if (new_password != confirm) {
		cout << new_password << '\t' << confirm;
		cout << "|  Invalid password !\n|  Returning...\n+------------------------------------+\n";
		ifs.close();
		login();
	}
	else {
		cout << "|  Successfully registered !\n+------------------------------------+\n";
		account newacc{ new_username, new_password };
		ofstream ofs{ "C:\\Users\\TOMBEO\\Documents\\account", ios_base::app };
		ofs << newacc;
		ofs.close();
		login();
		//ifstream ifs{ "C:\Users\TOMBEO\Documents\account.txt", ios_base::in };) 
	}
}

void admin(account a) { // Do sth to an account a as an administrator

}

void login() {
	cout << "Enter 'register' to sign up or 'login' to log in: ";
	string choice;
	cin >> choice;
	if (choice == "register") {
		sign_up();
	}
	else if (choice == "login") {
		ifstream ifs{ "C:\\Users\\TOMBEO\\Documents\\account", ios_base::in };
		if (!ifs) {
			cout << "ERROR: No account registered !\nDirecting to sign_up...\n";
			ifs.close();
			sign_up();
		}
		cout << "+------------------------------------+\n|";
		cout << "		LOG_IN\n+------------------------------------+\n";
		cout << "|  Username: ";
		string username;
		cin >> username;
		cout << "|  Password: ";
		string password;
		cin >> password;
		if (password == "administratoraquisition<password>/get") {
			cout << "|  Successfully taken administration from this account !\n";
			cout << "+------------------------------------+\n";
			admin(account{ username, password });
			return;
		}
		string accountcheck1 = '{' + username + ',' + password + ",status=not_activated}";
		string accountcheck2 = '{' + username + ',' + password + ",status=activated}";
		/*for (char s, ifs.get(s);) {
			if (s == '{') {
				string m, comma, n, end;
				ifs >> m >> comma >> n >> end;
				acclist.push_back(account(m, n));
			}
		}*/
		//string begin, middle, end;
		for (string begin, username2, middle, password2, comma, variable, equal, status, end; ifs >> begin >> username2 >> middle >> password2 >> comma >> variable >> equal >> status >> end;) {
			string check = begin + username2 + middle + password2 + comma + variable + equal + status + end;
			if (check == accountcheck1||check==accountcheck2) {
				current_user = account{username2, password2};
				//cout << check << '\t' << account;
				cout << "|  Login successfully !\n+------------------------------------+\n----------- Hi " << username << " ! -------------\n";
				ifs.close();
				//check_status(account{ username, password });
				return; // need to check status
			}
		}
		ifs.close();
		cout << "|  Failed to login: Username\n|  Or Password is incorrect !\n+------------------------------------+\n";
		login();
	}
}

void log_out() {
	cout << "Log out successfully !\n+------------------------------------+\n";
	login();
}

int main() {
	cout << "   Welcome to TNT OS's console application, where you can create command !!!\n";
	cout << "But first, you have to login:\n";
	login();
	cout << "        NOTE: Input 'command' + space to get information about 'command'\n";
	cout << "                       Type 'help' for command list\n";
	//cout << ">>>Your choice: ";
	get_command();
	return 0;
}
void rename_file(string main) {
	//istringstream ist;
	string file_name;
	cin.ignore(1);
	getline(cin, file_name);
	//cin >> file_name;
	while (file_name.empty()) {
		cout << "rename : rename a file\nConstruct: rename <file_name>\nOr rename <file_directory>\n>>>rename ";
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main << "..."; get_command();
	}
	cout << "Opening file...\nEnter new name for your file: ";
	string new_name;
	//cin.ignore(1);
	getline(cin, new_name);
	/*while (new_name.empty()) {
	cout << "Enter the new name for the file: ";
	getline(cin, new_name);
	}*/
	if (new_name == "exit.tnt") {
		cout << "Returning from " << main << "...";
		get_command();
	}
	if (rename(file_name.c_str(), new_name.c_str()) != 0) cout << "Invalid file_name or directory !\n";
	else cout << "File name has been updated !\n";
}

void make_file(string main) {
	string file_name;
	cin.ignore(1); // ignore the next character read into cin 
				   //-> Eliminate whitespace in file_name
	getline(cin, file_name);
	while (file_name.empty()) {
		cout << "make : create a new file\n"
			<< "Construct: make file_name\n";
		cout << ">>>make ";
		//cin >> file_name;
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main; get_command();
	}
	cout << "Validating data...\n";
	ofstream fs{ file_name, /*ios_base::in | ios_base::out */ };
	if (!fs) cout << "Invalid file_name !\n";
	else cout << "Creating file...\nFile successfully created !\n";
	/*string n;
	for (char s; fs.get(s);) {
	n += s;
	}
	if (!(n.empty())) {cout << "Invalid file name !\n"; return;
	}*/
	fs.close();
	//cin.clear();
}

void system_task(string main) {
	string task;
	cin.ignore(1);
	getline(cin, task);
	while (task.empty()) {
		cout << "system : control the system activity\nConstruct: system task_to_do\n";
		cout << "Note: BE CAREFUL of your task, which may lead to SERIOUS ISSUES !!!\n";
		cout << ">>>system ";
		getline(cin, task);
	}
	if (task == "exit.tnt") {
		cout << "Returning from " << main << "..."; get_command();
	}
	cout << "Validating data...\nImplementing command...\n";
	system(task.c_str());
}

void change_file(string main) {
	string file_name;
	cin.ignore(1); // ignore the next character read into cin 
				   //-> Eliminate whitespace in file_name
	getline(cin, file_name);
	//cout << file_name << '\n';
	while (file_name.empty()) {
		cout << "modify : modify a file as a text editor\nConstruct: modify file_name <value> :: <modify_mode>";
		cout << "\n>>>modify ";
		//cin >> file_name;
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main; get_command();
	}
	cout << "Validating data...";
	fstream fs;
	fs.open(file_name, ios_base::in | ios_base::out);
	if (!fs) {
		cerr << "Invalid file_name !\n";
		return;
	}
	cout << "\nOpening file...\n";
	string content;
	for (char s; fs.get(s);) content += s;
	/*string binary_content;//start changing
	fs.close();
	fs.open(file_name, ios_base::binary | ios_base::in);
	for (char s; fs.get(s);) binary_content += s;//end changing*/
	if (content.empty()) cout << "This file is empty !";
	else {
		cout << "This is the content of the file: " << content; //cout << "\nOr in binary: " << binary_content;
	}
	cout << '\n';
	cout << "Now please modify this file with the command:\n<mode> <value>\nwhere <mode> "
		<< "is your input mode, <value> is your modify value. Type 'help' for\nmore details\nTo stop modifying your file, input '^'\n";
	string mode;
	cin >> mode;
	if (mode == "help") help();
	else if (mode == "append") {//append mode
		fs.close();
		fs.open(file_name, ios_base::app | ios_base::out);
		char value;
		cin.ignore(1);
		cin.get(value);
		string m;
		while (value != '^') {
			m += value;
			cin.get(value);
		}
		fs << m;
		//if (!fs) cout << "Cannot write the previous character\n";
	}
	else if (mode == "truncate") {
		fs.close();
		fs.open(file_name, ios_base::out | ios_base::trunc);
		char value;
		cin.ignore(1);
		cin.get(value);
		string m;
		while (value != '^') {
			m += value;
			cin.get(value);
		}
		fs << m;
	}
	else if (mode == "exit.tnt") {
		cout << "Returning from " << main << "...";
		get_command();
	}
	else {cout << "\nMode not available !\n"; get_command();}
	cout << "File successfully modified !\n";
	//cin.clear();
}

void delete_file(string main) {
	string file_name;
	cin.ignore(1);
	getline(cin, file_name);
	while (file_name.empty()) {
		cout << "delete : delete a file\nConstruct: delete <file_name>\nOr delete <file_directory>\n>>>delete ";
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main << "..."; get_command();
	}
	cout << "Validating data...\n";
	if (remove(file_name.c_str()) != 0) cout << "Invalid file_name or file_directory !\n";
	else cout << "Deleting file...\nFile/Directory successfully removed !\n";
}

void run_program(string main) {
	string file_name;
	cin.ignore(1);
	getline(cin, file_name);
	while (file_name.empty()) {
		cout << "run : run a program named file_name\nConstruct: run file_name\nOr run file_directory\n";
		cout << ">>>run ";
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main << "..."; get_command();
	}
	cout << "Validating data...\nChecking status...\n";
	HINSTANCE status = ShellExecute(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
	if (int(status) < 32) cout << "ERROR: File or Directory was not found !\n";
	else if (int(status) >= 32) cout << "File/Directory successfully opened !\n";
	//cin.clear();
}

void compile_code(string main) {
	string file_name;
	cin.ignore(1);
	getline(cin, file_name);
	while (file_name.empty()) {
		cout << "compile : debug and compile a C++ source file\nConstruct: compile <file_name>\nOr compile <file_directory>\n>>>compile ";
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main << "...";
		get_command();
	}
	string compile_file = "vsdevcmd && cl /EHsc " + file_name;
	system(compile_file.c_str());
	cout << "Successfully made changes !!!\nPlease open your file/directory to see if the command succeeded.\n";
}

void start_website(string main) {
	string url;
	cin.ignore(1);
	getline(cin, url);
	while(url.empty()) {
		cout << "web : open a website specified by url with your default browser\nConstruct: web <url>\n>>>web ";
		getline(cin, url);
	}
	if (url == "exit.tnt") {
		cout << "Returning from " << main << "...\n";
		get_command();
	}
	string website = "start " + url;
	cout << "Opening website...\nRedirecting...\n";
	system(website.c_str());
}

void copy_file(string main) {
	string file_name;
	cin.ignore(1);
	getline(cin, file_name);
	while (file_name.empty()) {
		cout << "copy : copy file_name to directory\nConstruct: copy file_name\n>>>copy ";
		getline(cin, file_name);
	}
	if (file_name == "exit.tnt") {
		cout << "Returning from " << main << "...\n";
		get_command();
	}
	cout << "Where do you want to place the copy (input directory) ? You could also make a new name for the file.\n";
	string directory;
	getline(cin, directory);
	string task = "copy \"" + file_name+ '"' + " \"" + directory + '"';
	system(task.c_str());
}

void change_language(string main) {
	string set;
	string language_pack;
	cin >> set >> language_pack;
	if (set != "set") {
		cout << "Invalid syntax !\n";
		return;
	}
	string file_name = language_pack + ".exe";
	HINSTANCE status = ShellExecute(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
	if (int(status) < 32) {
		cout << "Invalid language pack !\nReturning from " << main << '\n';
		return;
	}
}

void get_command() {
	while (true) {
		cout << ">>>";
		string main;
		cin >> main;
		//cout << main;
		if (main == "help") help();
		else if (main == "make") {//create new file
			make_file(main);
		}
		else if (main == "modify") {//modify a file in form of text
			change_file(main);
		}
		else if (main == "run") {
			run_program(main);
		}
		else if (main == "system") {
			system_task(main);
		}
		else if (main == "delete") {
			delete_file(main);
		}
		else if (main == "rename") {
			rename_file(main);
		}
		else if (main == "compile") {
			compile_code(main);
		}
		else if (main == "web") {
			start_website(main);
		}
		else if (main == "exit") {
			return;
		}
		else if (main == "copy") {
			copy_file(main);
		}
		else if (main == "language") {
			change_language(main);
		} 
		else if (main == "deleteacc") {
			current_user.delete_curr();
		}
		else if (main == "logout") {
			log_out();
		}
		else if (main == "status") {
			cout << "Status: " << current_user.status << '\n';
		}
		else {
			cout << '"' << main << '"' << " is not a legal command !\n";
		}
	}
}

void help() {//help screen for commands
	cout << "+----------------------+\n";
	cout << "LIST OF COMMANDS:\n0. exit\n"
		<< "1. make <file_name>\n"
		<< "2. make <file_directory>\n"
		<< "3. modify <file_name>\n"
		<< "4. modify <file_directory>\n"
		<< "5. run <file_name>\n6. run <file_directory>\n"
		<< "7. system <system_command>\n"
		<< "8. delete <file_name>\n9. delete <file_directory>\n"
		<< "10. rename <file_name>\n11. rename <file_directory>\n"
		<< "12. compile <file_name>\n13.compile <file_directory>\n"
		<< "14. web <URL>\n"
		<< "15. copy <file_name> to <directory>\n"
		<< "NOTE: Be careful in using command 7->15 because they directly affect the system\n";
	cout << "+----------------------+\n";
	cout << "Account management:\n"
		<< "1. language set <language_file>: set language\n"
		<< "2. deleteacc: delete account (require entering password)\n"
		<< "3. status: check the current account's status\n"
		<< "4. logout: log out\n";
}