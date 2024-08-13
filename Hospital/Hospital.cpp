#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
using namespace std;
class Doctor//Entity num ==> 1
{
public:
	char name[20], id[10], number[15], department[20]; //total size ==65+4*4=81(suppos),65(Right now)
};
class Patient//Entity num ==> 2
{
public:
	char name[20], id[10], Case[15]; //total size ==65 supose to be 61
};


/*
	Doctor's Methods
*/

void Insert_Doctors_Data(fstream& logicalfile, Doctor& doctor, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Doctor, map<string, string>& name_Doctor)
{
	logicalfile.open("Doctorsfile.txt", ios::binary | ios::in | ios::out);
	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)
		{
			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&header, sizeof(int));//write header for first
			cout << "How many Doctors you want to sign In\n";
			cin >> number_of_total_sign;
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//weite number_of_total_sign after header
			system("cls");//to rewrite consol
			for (int i = 0; i < number_of_total_sign; i++)
			{
				system("cls");//to rewrite consol
				cout << "\nEnter your Doctor Id:\n";
				cin >> doctor.id;
				cout << "\nEnter your Doctor name:\n";
				cin >> doctor.name;
				cout << "\nEnter your Doctor number:\n";
				cin >> doctor.number;
				cout << "\nEnter your Doctor department:\n";
				cin >> doctor.department;

				off_set = 8 + (i * 65);
				logicalfile.seekp(off_set, ios::beg);

				Id_Doctor[doctor.id] = off_set;// add pair id and off_set into map
				name_Doctor[doctor.name] = doctor.id;//add pair id and name

				field_length = strlen(doctor.id);
				logicalfile.write((char*)&field_length, sizeof(int));
				logicalfile.write(doctor.id, field_length);

				field_length = strlen(doctor.name);
				logicalfile.write((char*)&field_length, sizeof(int));
				logicalfile.write(doctor.name, field_length);

				field_length = strlen(doctor.number);
				logicalfile.write((char*)&field_length, sizeof(int));
				logicalfile.write(doctor.number, field_length);

				field_length = strlen(doctor.department);
				logicalfile.write((char*)&field_length, sizeof(int));
				logicalfile.write(doctor.department, field_length);


			}
		}
		else
		{
			//update numbers of sign Doctors
			int num;
			logicalfile.seekp(4, ios::beg);
			logicalfile.read((char*)&number_of_total_sign, sizeof(int));
			int cur = 8 + ((number_of_total_sign) * 65);
			cout << "How many Doctors you want to sign in\n";
			cin >> num;
			number_of_total_sign += num;
			logicalfile.seekp(4, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));
			//end of update
			for (int k = 0; k < num; k++)
			{
				logicalfile.seekg(0, ios::beg);
				logicalfile.read((char*)&header, sizeof(int));//write header for first
				if (header == -1)
				{
					for (int i = 0; i < num; i++)
					{
						system("cls");//to rewrite consol
						cout << "\nenter your doctor id:\n";
						cin >> doctor.id;
						cout << "\nenter your doctor name:\n";
						cin >> doctor.name;
						cout << "\nenter your doctor number:\n";
						cin >> doctor.number;
						cout << "\nenter your doctor department:\n";
						cin >> doctor.department;

						off_set = (i * 65);

						logicalfile.seekp((off_set + cur), ios::beg);//continue from the last record

						Id_Doctor[doctor.id] = (off_set + cur);// add pair id and off_set+cur into map
						name_Doctor[doctor.name] = doctor.id;//add pair id and name


						field_length = strlen(doctor.id);
						logicalfile.write((char*)&field_length, sizeof(int));
						logicalfile.write(doctor.id, field_length);

						field_length = strlen(doctor.name);
						logicalfile.write((char*)&field_length, sizeof(int));
						logicalfile.write(doctor.name, field_length);

						field_length = strlen(doctor.number);
						logicalfile.write((char*)&field_length, sizeof(int));
						logicalfile.write(doctor.number, field_length);

						field_length = strlen(doctor.department);
						logicalfile.write((char*)&field_length, sizeof(int));
						logicalfile.write(doctor.department, field_length);


					}

				}

				else
				{
					// get header and update it
					logicalfile.seekg(0, ios::beg);
					logicalfile.read((char*)&header, sizeof(int));
					int cur_Header = header;
					logicalfile.seekg(0, ios::beg);

					off_set = 13 + (header * 65); // to ignore *
					logicalfile.seekg(off_set, ios::beg);
					logicalfile.read((char*)&header, sizeof(int));

					logicalfile.seekp(0, ios::beg);
					logicalfile.write((char*)&header, sizeof(int));
					off_set = 8 + (cur_Header * 65);
					//end
					cout << "cur header " << cur_Header << endl;
					cout << " header " << header << endl;
					Id_Doctor[doctor.id] = off_set;// add pair id and off_set into map
					name_Doctor[doctor.name] = doctor.id;//add pair id and name

					logicalfile.seekp(off_set, ios::beg);
					system("cls");//to rewrite consol
					cout << "\nEnter your Doctor Id:\n";
					cin >> doctor.id;
					cout << "\nEnter your Doctor name:\n";
					cin >> doctor.name;
					cout << "\nEnter your Doctor number:\n";
					cin >> doctor.number;
					cout << "\nEnter your Doctor department:\n";
					cin >> doctor.department;

					field_length = strlen(doctor.id);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(doctor.id, field_length);

					field_length = strlen(doctor.name);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(doctor.name, field_length);

					field_length = strlen(doctor.number);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(doctor.number, field_length);

					field_length = strlen(doctor.department);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(doctor.department, field_length);
				}
			}
		}


		cout << "Data writen to database sucessfully :)\n";
		logicalfile.close();
	}
	else
		cout << "Sorry cant open this file :(\n";
}

void Update_Insert_Doctor_primary_index(fstream& logicalfile, Doctor& doctor, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Doctor, map<string, int>::iterator it_Doctor)
{

	logicalfile.open("DoctorPrimary.txt", ios::binary | ios::in | ios::out);//open primary file
	int OFF_SET;

	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)//first time to write in map
		{
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Doctor = Id_Doctor.begin(); it_Doctor != Id_Doctor.end(); it_Doctor++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Doctor = Id_Doctor.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Doctor->first.size();//get first id size
				logicalfile.write((char*)&field_length, sizeof(int));//write id length
				logicalfile.write(it_Doctor->first.c_str(), field_length);//write id note 

				field_length = it_Doctor->second;//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write((char*)&it_Doctor->second, sizeof(int));//write off_set length

				++it_Doctor;//increament iterotor
			}
			//end of write part
		}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else//Update map and re insert it
		{
			//update map part
			logicalfile.seekg(0, ios::beg);
			logicalfile.read((char*)&number_of_total_sign, sizeof(int));//read total number of id in primary file
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				logicalfile.read((char*)&field_length, sizeof(int));//read id length
				logicalfile.read(doctor.id, field_length);//read id
				doctor.id[field_length] = '\0';

				logicalfile.read((char*)&field_length, sizeof(int));//read off_set length
				logicalfile.read((char*)&off_set, sizeof(int));//read off_set

				Id_Doctor[doctor.id] = off_set;
			}
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Doctor = Id_Doctor.begin(); it_Doctor != Id_Doctor.end(); it_Doctor++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS
			//start of write part
			it_Doctor = Id_Doctor.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Doctor->first.size();//get first id size
				logicalfile.write((char*)&field_length, sizeof(int));//write id length
				logicalfile.write(it_Doctor->first.c_str(), field_length);//write id note 

				field_length = it_Doctor->second;//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write((char*)&it_Doctor->second, sizeof(int));//write off_set length

				++it_Doctor;//increament iterotor
			}
			//end of write part
		}


		cout << "Updated primary index suessfully :)\n";
		logicalfile.close();
	}
	else
		cout << "Sorry cant read Doctor Primary file :(\n";
}

void Update_Insert_Doctor_Secondry_index(fstream& logicalfile, Doctor& doctor, int off_set, int header, int number_of_total_sign, int field_length, map<string, string>& name_Doctor, map<string, string>::iterator it_Doctorname)
{
	logicalfile.open("DoctorSecondry.txt", ios::binary | ios::in | ios::out);//open Secondry file
	int OFF_SET;
	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)//first time to write in map
		{
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Doctorname = name_Doctor.begin(); it_Doctorname != name_Doctor.end(); it_Doctorname++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Doctorname = name_Doctor.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Doctorname->first.size();//get first name size
				logicalfile.write((char*)&field_length, sizeof(int));//write name length
				logicalfile.write(it_Doctorname->first.c_str(), field_length);//write name note 

				field_length = it_Doctorname->second.size();//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write(it_Doctorname->second.c_str(), field_length);//write off_set length

				++it_Doctorname;//increament iterotor
			}
			//end of write part
		}
		else//Update map and re insert it
		{
			//update map part
			logicalfile.seekg(0, ios::beg);
			logicalfile.read((char*)&number_of_total_sign, sizeof(int));//read total number of id in secondary file
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				logicalfile.read((char*)&field_length, sizeof(int));//read name length
				logicalfile.read(doctor.name, field_length);//read name
				doctor.name[field_length] = '\0';

				logicalfile.read((char*)&field_length, sizeof(int));//read id length
				logicalfile.read(doctor.id, field_length);//read id
				doctor.id[field_length] = '\0';

				name_Doctor[doctor.name] = doctor.id;//add pair id and name
			}
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Doctorname = name_Doctor.begin(); it_Doctorname != name_Doctor.end(); it_Doctorname++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Doctorname = name_Doctor.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Doctorname->first.size();//get first name size
				logicalfile.write((char*)&field_length, sizeof(int));//write name length
				logicalfile.write(it_Doctorname->first.c_str(), field_length);//write name note 

				field_length = it_Doctorname->second.size();//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write(it_Doctorname->second.c_str(), field_length);//write off_set length

				++it_Doctorname;//increament iterotor
			}
			//end of write part
		}


		cout << "Updated Secondry index suessfully :)\n";
		logicalfile.close();
	}
	else
		cout << "Sorry cant read Doctor Primary file :(\n";
}

void Update_Doctors_using_Id(fstream& logicalfile, Doctor& doctor, int search, int number_of_total_sign, int field_length, map<string, string>& name_Doctor)
{
	logicalfile.open("Doctorsfile.txt", ios::in | ios::out | ios::binary);
	if (logicalfile.is_open())
	{
		system("cls");//to rewrite consol
		cout << "///////////////////UPDATEEEEEE!!!!////////////////////////";
		cout << "\nEnter your Doctor name:\n";
		cin >> doctor.name;
		cout << "\nEnter your Doctor number:\n";
		cin >> doctor.number;
		cout << "\nEnter your Doctor department:\n";
		cin >> doctor.department;

		logicalfile.seekp(search, ios::beg);
		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(doctor.id, field_length);

		name_Doctor[doctor.name] = doctor.id;//////////////

		logicalfile.seekp(search, ios::beg);

		field_length = strlen(doctor.id);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(doctor.id, field_length);

		field_length = strlen(doctor.name);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(doctor.name, field_length);

		field_length = strlen(doctor.number);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(doctor.number, field_length);

		field_length = strlen(doctor.department);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(doctor.department, field_length);

		logicalfile.close();
	}
	else
		cout << "Sorry can't Open this file :(\n";
}

int Search_Doctor_Data(fstream& logicalfile, Doctor& doctor, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Doctor)
{
	logicalfile.open("DoctorPrimary.txt", ios::binary | ios::in);
	if (logicalfile.is_open())
	{
		string search_key;
		cout << "Enter the Id you want to search on it \n";
		cin >> search_key;
		auto it_begin = Id_Doctor.begin();
		auto it_end = Id_Doctor.end();
		while (it_begin != it_end)
		{
			auto it_middle = next(it_begin, distance(it_begin, it_end) / 2);
			if (it_middle->first == search_key)
			{
				cout << "found\n";
				logicalfile.close();
				return it_middle->second;
			}
			if (it_middle->first < search_key)
				it_begin = next(it_middle);
			else
				it_end = it_middle;
		}
		cout << "not found\n";
		logicalfile.close();
		return -1;
	}
	else
		cout << "Sorry cant open this file\n";
}

int Search_Doctor_Secondry_Data(fstream& logicalfile, Doctor& doctor, int off_set, int Header, int number_of_total_sign, int field_length, map<string, string>& name_Doctor, map<string, int>& Id_Doctor)
{
	logicalfile.open("DoctorSecondry.txt", ios::binary | ios::in);//open Secondry file
	if (logicalfile.is_open())
	{
		string target;
		cout << "Enter the name you want to search for \n";
		cin >> target;

		// Check if name exists
		auto name_range = name_Doctor.equal_range(target);
		if (name_range.first != name_range.second)
		{
			cout << "Name : " << target << endl;
			cout << "Matching IDs:\n";
			for (auto it = name_range.first; it != name_range.second; ++it)
			{
				cout << "ID: " << it->second << endl;
			}
			cout << "Enter the your Id \n";
			cin >> target;
			auto it = Id_Doctor.find(target);
			if (it != Id_Doctor.end())
			{
				cout << "Secceful search :)\n";
				logicalfile.close();
				return Id_Doctor[target];
			}
		}
		else
		{
			cout << "Name not found.\n";
		}

		logicalfile.close();
		return -1;
	}
	else
	{
		cout << "Sorry Can't open this file :(\n";
		logicalfile.close();
		return -1;
	}
}

void Result_of_search(fstream& logicalfile, Doctor& doctor, int search, int header, int number_of_total_sign, int field_length)
{
	logicalfile.open("Doctorsfile.txt", ios::in | ios::binary);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(search, ios::beg);

		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(doctor.id, field_length);
		doctor.id[field_length] = '\0';

		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(doctor.name, field_length);
		doctor.name[field_length] = '\0';

		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(doctor.number, field_length);
		doctor.number[field_length] = '\0';

		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(doctor.department, field_length);
		doctor.department[field_length] = '\0';
		cout << "\n/////////////////////////Doctor////////////////////////////////////////\n";
		cout << "\nName : " << doctor.name;
		cout << "\nID : " << doctor.id;
		cout << "\nNumber : " << doctor.number;
		cout << "\nDepartment : " << doctor.department;
		cout << "\n//////////////////////////////////////////////////////////////////////// \n";
	}
	else
		cout << "Sorry cant open this file :(\n";
	logicalfile.close();
}

void Delete_Doctors_using_Id(fstream& logicalfile, Doctor& doctor, int Header, int search, int number_of_total_sign, int field_length, map<string, int>& Id_Doctor)
{
	logicalfile.open("Doctorsfile.txt", ios::in | ios::out | ios::binary);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(0, ios::beg);
		logicalfile.read((char*)&Header, sizeof(4));//read main header

		logicalfile.seekg(search, ios::beg);
		logicalfile.read((char*)&field_length, sizeof(4));//read size of id

		logicalfile.read(doctor.id, field_length);//////////////////////////////
		Id_Doctor[doctor.id] = -1;////////////////////////////

		logicalfile.seekp(search + 4, ios::beg);
		logicalfile.put('*');//deletion mark :)
		logicalfile.write((char*)&Header, sizeof(4));

		logicalfile.seekp(0, ios::beg);
		Header = (search - 8) / 65;
		logicalfile.write((char*)&Header, sizeof(4));
		cout << "New Header = " << Header << "\n";
	}
	else
		cout << "Sorry Cant open this file :(\n";

	logicalfile.close();
}

void Display_Doctors_Data(fstream& logicalfile, Doctor& doctor, int off_set, int number_of_total_sign, int field_length)
{
	logicalfile.open("Doctorsfile.txt", ios::binary | ios::in);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(4, ios::beg);
		logicalfile.read((char*)&number_of_total_sign, 4);
		system("cls");//to rewrite consol
		int choice;
		cout << "Do you want to display All data or first five?\n1-All\n2-first five\n";
		cin >> choice;
		system("cls");//to rewrite consol
		if (choice == 2)
		{
			if (number_of_total_sign >= 5)
				number_of_total_sign = 5;
		}
		for (int i = 0; i < number_of_total_sign; i++)
		{
			//to seek
			off_set = 8 + (i * 65);
			logicalfile.seekp(off_set, ios::beg);
			//
			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(doctor.id, field_length);
			doctor.id[field_length] = '\0';

			if (doctor.id[0] == '*')
			{
				cout << "\n/////////////////////////Doctor" << i + 1 << "/////////////////////////////////////////\n";
				cout << "Was been deleted";
				cout << "\n//////////////////////////////////////////////////////////////////////////////////////\n";
				continue;
			}

			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(doctor.name, field_length);
			doctor.name[field_length] = '\0';

			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(doctor.number, field_length);
			doctor.number[field_length] = '\0';

			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(doctor.department, field_length);
			doctor.department[field_length] = '\0';


			cout << "\n/////////////////////////Doctor" << i + 1 << "////////////////////////////////////////\n";
			cout << "\nName : " << doctor.name;
			cout << "\nID : " << doctor.id;
			cout << "\nNumber : " << doctor.number;
			cout << "\nDepartment : " << doctor.department;
			cout << "\n//////////////////////////////////////////////////////////////////////////////////////\n";

		}
		logicalfile.close();
	}
	else
		cout << "Sorry cant open this file :(\n";
}

/*
	Patient's Methods

*/

void Insert_Patient_Data(fstream& logicalfile, Patient& patient, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Patient, map<string, string>& name_Patient)
{
	logicalfile.open("Patientsfile.txt", ios::binary | ios::in | ios::out);
	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)
		{
			logicalfile.seekp(0);
			logicalfile.write((char*)(&header), sizeof(int));
			cout << "How Many Patients You Want To Sign In:\n";
			cin >> number_of_total_sign;
			logicalfile.write((char*)(&number_of_total_sign), sizeof(int));
			system("cls");
			for (int i = 0; i < number_of_total_sign; i++)
			{
				system("cls");
				cout << "\nEnter Your Patient ID: \n";
				cin >> patient.id;

				cout << "\nEnter Your Patient Name: \n";
				cin >> patient.name;

				cout << "\nEnter Your Patient Case: \n";
				cin >> patient.Case;

				off_set = 8 + (i * 65);
				logicalfile.seekp(off_set, ios::beg);

				Id_Patient[patient.id] = off_set;//////////////////

				name_Patient[patient.name] = patient.id;

				field_length = strlen(patient.id);
				logicalfile.write((char*)(&field_length), sizeof(int));
				logicalfile.write(patient.id, field_length);

				field_length = strlen(patient.name);
				logicalfile.write((char*)(&field_length), sizeof(int));
				logicalfile.write(patient.name, field_length);

				field_length = strlen(patient.Case);
				logicalfile.write((char*)(&field_length), sizeof(int));
				logicalfile.write(patient.Case, field_length);
			}
		}
		else {
			int num;
			logicalfile.seekp(4, ios::beg);
			logicalfile.read((char*)(&number_of_total_sign), sizeof(int));
			int cur = 8 + ((number_of_total_sign) * 65);
			cout << "How Many Patients You Want To Sign in: \n";
			cin >> num;
			number_of_total_sign += num;
			logicalfile.seekp(4, ios::beg);
			logicalfile.write((char*)(&number_of_total_sign), sizeof(int));



			for (int k = 0; k < num; k++)
			{
				logicalfile.seekp(0);
				logicalfile.read((char*)(&header), sizeof(int));
				if (header == -1)
				{
					for (int i = 0; i < num; i++) {
						system("cls");

						cout << "\nEnter Your Patient ID: \n";
						cin >> patient.id;

						cout << "\nEnter Your Patient Name: \n";
						cin >> patient.name;

						cout << "\nEnter Your Patient Case: \n";
						cin >> patient.Case;

						off_set = (i * 65);

						logicalfile.seekp((off_set + cur), ios::beg);////////////////////////

						Id_Patient[patient.id] = (off_set + cur);
						name_Patient[patient.name] = patient.id;

						field_length = strlen(patient.id);
						logicalfile.write((char*)(&field_length), sizeof(int));
						logicalfile.write(patient.id, field_length);

						field_length = strlen(patient.name);
						logicalfile.write((char*)(&field_length), sizeof(int));
						logicalfile.write(patient.name, field_length);


						field_length = strlen(patient.Case);
						logicalfile.write((char*)(&field_length), sizeof(int));
						logicalfile.write(patient.Case, field_length);
					}
				}
				else {
					// get header and update it
					logicalfile.seekg(0, ios::beg);
					logicalfile.read((char*)&header, sizeof(int));
					int cur_Header = header;
					logicalfile.seekg(0, ios::beg);

					off_set = 13 + (header * 65); // to ignore *
					logicalfile.seekg(off_set, ios::beg);
					logicalfile.read((char*)&header, sizeof(int));

					logicalfile.seekp(0, ios::beg);
					logicalfile.write((char*)&header, sizeof(int));
					off_set = 8 + (cur_Header * 65);
					//end
					cout << "cur header " << cur_Header << endl;
					cout << " header " << header << endl;
					Id_Patient[patient.id] = off_set;// add pair id and off_set into map
					name_Patient[patient.name] = patient.id;

					logicalfile.seekp(off_set, ios::beg);
					system("cls");//to rewrite consol
					cout << "\nEnter your Doctor Id:\n";
					cin >> patient.id;
					cout << "\nEnter your Doctor name:\n";
					cin >> patient.name;
					cout << "\nEnter your Doctor number:\n";
					cin >> patient.Case;


					field_length = strlen(patient.id);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(patient.id, field_length);

					field_length = strlen(patient.name);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(patient.name, field_length);

					field_length = strlen(patient.Case);
					logicalfile.write((char*)&field_length, sizeof(int));
					logicalfile.write(patient.Case, field_length);
				}
			}
		}

		cout << "Data Written To Database Successfully :)\n";
		logicalfile.close();
	}
	else {
		cout << "Sorry Can't Open This File :(\n";
	}
}

void Update_Insert_Patient_primary_index(fstream& logicalfile, Patient& patient, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Patient, map<string, int>::iterator it_Patient)
{
	logicalfile.open("PatientPrimary.txt", ios::binary | ios::in | ios::out);//open primary file
	int OFF_SET;

	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)//first time to write in map
		{
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Patient = Id_Patient.begin(); it_Patient != Id_Patient.end(); it_Patient++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Patient = Id_Patient.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Patient->first.size();//get first id size
				logicalfile.write((char*)&field_length, sizeof(int));//write id length
				logicalfile.write(it_Patient->first.c_str(), field_length);//write id note 

				field_length = it_Patient->second;//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write((char*)&it_Patient->second, sizeof(int));//write off_set length

				++it_Patient;//increament iterotor
			}
			//end of write part
		}
		else//Update map and re insert it
		{
			//update map part
			logicalfile.seekg(0, ios::beg);
			logicalfile.read((char*)&number_of_total_sign, sizeof(int));//read total number of id in primary file
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				logicalfile.read((char*)&field_length, sizeof(int));//read id length
				logicalfile.read(patient.id, field_length);//read id
				patient.id[field_length] = '\0';

				logicalfile.read((char*)&field_length, sizeof(int));//read off_set length
				logicalfile.read((char*)&off_set, sizeof(int));//read off_set

				Id_Patient[patient.id] = off_set;
			}
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Patient = Id_Patient.begin(); it_Patient != Id_Patient.end(); it_Patient++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS
			//start of write part
			it_Patient = Id_Patient.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Patient->first.size();//get first id size
				logicalfile.write((char*)&field_length, sizeof(int));//write id length
				logicalfile.write(it_Patient->first.c_str(), field_length);//write id note 

				field_length = it_Patient->second;//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write((char*)&it_Patient->second, sizeof(int));//write off_set length

				++it_Patient;//increament iterotor
			}
			//end of write part
		}


		cout << "Updated primary index successfully :)\n";
		logicalfile.close();
	}
	else
		cout << "Sorry can't read Patient Primary file :(\n";
}

void Update_Insert_Patient_Secondry_index(fstream& logicalfile, Patient& patient, int off_set, int header, int number_of_total_sign, int field_length, map<string, string>& name_Patient, map<string, string>::iterator it_Patientname)
{
	logicalfile.open("PatientSecondry.txt", ios::binary | ios::in | ios::out);//open Secondry file
	int OFF_SET;
	if (logicalfile.is_open())
	{
		logicalfile.seekp(0, ios::end);
		if (logicalfile.tellp() == 0)//first time to write in map
		{
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Patientname = name_Patient.begin(); it_Patientname != name_Patient.end(); it_Patientname++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Patientname = name_Patient.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Patientname->first.size();//get first name size
				logicalfile.write((char*)&field_length, sizeof(int));//write name length
				logicalfile.write(it_Patientname->first.c_str(), field_length);//write name note 

				field_length = it_Patientname->second.size();//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write(it_Patientname->second.c_str(), field_length);//write off_set length

				++it_Patientname;//increament iterotor
			}
			//end of write part
		}
		else//Update map and re insert it
		{
			//update map part
			logicalfile.seekg(0, ios::beg);
			logicalfile.read((char*)&number_of_total_sign, sizeof(int));//read total number of id in primary file
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				logicalfile.read((char*)&field_length, sizeof(int));//read name length
				logicalfile.read(patient.name, field_length);//read name
				patient.name[field_length] = '\0';

				logicalfile.read((char*)&field_length, sizeof(int));//read id length
				logicalfile.read(patient.id, field_length);//read id
				patient.id[field_length] = '\0';

				name_Patient[patient.name] = patient.id;//add pair id and name
			}
			//intialize number of total idS
			number_of_total_sign = 0;
			for (it_Patientname = name_Patient.begin(); it_Patientname != name_Patient.end(); it_Patientname++)
			{
				++number_of_total_sign;
			}
			//end of intialize number of total idS

			//start of write part
			it_Patientname = name_Patient.begin();// make iterotor refers to the first of map ,map is id sorted

			logicalfile.seekp(0, ios::beg);
			logicalfile.write((char*)&number_of_total_sign, sizeof(int));//writ total number at first
			for (int i = 0; i < number_of_total_sign; i++)
			{
				OFF_SET = 4 + (i * 22);//size of number_of_total_sign+field length+id +field length+off set=4+4+10+4+4

				field_length = it_Patientname->first.size();//get first name size
				logicalfile.write((char*)&field_length, sizeof(int));//write name length
				logicalfile.write(it_Patientname->first.c_str(), field_length);//write name note 

				field_length = it_Patientname->second.size();//get id off_set size =sizeof(int)=4
				logicalfile.write((char*)&field_length, sizeof(int));//write off_set length
				logicalfile.write(it_Patientname->second.c_str(), field_length);//write off_set length

				++it_Patientname;//increament iterotor
			}
			//end of write part
		}


		cout << "Updated Secondry index suessfully :)\n";
		logicalfile.close();
	}
	else
		cout << "Sorry cant read Patient Primary file :(\n";
}

void Update_Patients_using_Id(fstream& logicalfile, Patient& patient, int search, int number_of_total_sign, int field_length, map<string, string>& name_Patient)
{
	logicalfile.open("Patientsfile.txt", ios::in | ios::out | ios::binary);
	if (logicalfile.is_open())
	{
		system("cls"); // Clear the console

		// Input new data for the patient
		cout << "\nEnter the new Patient name:\n";
		cin >> patient.name;
		cout << "\nEnter the new Patient case:\n";
		cin >> patient.Case;

		logicalfile.seekp(search, ios::beg);
		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(patient.id, field_length);

		name_Patient[patient.name] = patient.id;
		logicalfile.seekp(search, ios::beg);

		// Write the updated data to the file
		field_length = strlen(patient.id);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(patient.id, field_length);

		field_length = strlen(patient.name);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(patient.name, field_length);


		field_length = strlen(patient.Case);
		logicalfile.write((char*)&field_length, sizeof(int));
		logicalfile.write(patient.Case, field_length);

		logicalfile.close();
	}
	else
		cout << "Sorry, can't open the file.\n";
}

int Search_Patient_Data(fstream& logicalfile, Patient& patient, int off_set, int header, int number_of_total_sign, int field_length, map<string, int>& Id_Patient)
{
	logicalfile.open("PatientPrimary.txt", ios::binary | ios::in);
	if (logicalfile.is_open())
	{
		string search_key;
		cout << "Enter the ID of the patient you want to search for: \n";
		cin >> search_key;

		auto it_begin = Id_Patient.begin();
		auto it_end = Id_Patient.end();

		while (it_begin != it_end)
		{
			auto it_middle = next(it_begin, distance(it_begin, it_end) / 2);
			if (it_middle->first == search_key)
			{
				cout << "Patient found.\n";
				logicalfile.close();
				return it_middle->second; // Return the offset if found
			}
			if (it_middle->first < search_key)
				it_begin = next(it_middle);
			else
				it_end = it_middle;
		}
		cout << "Patient not found.\n";
		logicalfile.close();
		return -1; // Return -1 if not found
	}
	else
	{
		cout << "Sorry, can't open the patient file.\n";
		logicalfile.close();
		return -1;
	}
}

int Search_Patient_Secondry_Data(fstream& logicalfile, Patient& patient, int off_set, int Header, int number_of_total_sign, int field_length, map<string, string>& name_Patient, map<string, int>& Id_Patient)
{
	logicalfile.open("PatientSecondry.txt", ios::binary | ios::in);//open Secondry file
	if (logicalfile.is_open())
	{
		string target;
		cout << "Enter the name you want to search for \n";
		cin >> target;

		// Check if name exists
		auto name_range = name_Patient.equal_range(target);
		if (name_range.first != name_range.second)
		{
			cout << "Name : " << target << endl;
			cout << "Matching IDs:\n";
			for (auto it = name_range.first; it != name_range.second; ++it)
			{
				cout << "ID: " << it->second << endl;
			}
			cout << "Enter the your Id \n";
			cin >> target;
			auto it = Id_Patient.find(target);
			if (it != Id_Patient.end())
			{
				cout << "Secceful search :)\n";
				logicalfile.close();
				return Id_Patient[target];
			}
		}
		else
		{
			cout << "Name not found.\n";
		}

		logicalfile.close();
		return -1;
	}
	else
	{
		cout << "Sorry Can't open this file :(\n";
		logicalfile.close();
		return -1;
	}
}

void Result_of_pateint_search(fstream& logicalfile, Patient& patient, int search, int header, int number_of_total_sign, int field_length)
{
	logicalfile.open("Patientsfile.txt", ios::in | ios::binary);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(search, ios::beg);

		// Read the patient data from the file
		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(patient.id, field_length);
		patient.id[field_length] = '\0';

		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(patient.name, field_length);
		patient.name[field_length] = '\0';



		logicalfile.read((char*)&field_length, sizeof(int));
		logicalfile.read(patient.Case, field_length);
		patient.Case[field_length] = '\0';

		// Display the patient data
		cout << "\n/////////////////////////Patient////////////////////////////////////////\n";
		cout << "Name: " << patient.name << endl;
		cout << "ID: " << patient.id << endl;
		cout << "Case: " << patient.Case << endl;
		cout << "//////////////////////////////////////////////////////////////////////// \n";
	}
	else
	{
		cout << "Sorry, can't open the patient file.\n";
	}
	logicalfile.close();
}

void Display_Patients_Data(fstream& logicalfile, Patient& patient, int off_set, int number_of_total_sign, int field_length)
{
	logicalfile.open("Patientsfile.txt", ios::binary | ios::in);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(4, ios::beg);
		logicalfile.read((char*)&number_of_total_sign, 4);
		int choice;
		system("cls");//to rewrite consol
		cout << "Do you want to display All data or first five?\n1-All\n2-first five\n";
		cin >> choice;
		system("cls");//to rewrite consol
		if (choice == 2)
		{
			if (number_of_total_sign >= 5)
				number_of_total_sign = 5;
		}
		for (int i = 0; i < number_of_total_sign; i++)
		{
			//to seek
			off_set = 8 + (i * 65);
			logicalfile.seekp(off_set, ios::beg);
			//
			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(patient.id, field_length);
			patient.id[field_length] = '\0';
			if (patient.id[0] == '*')
			{
				cout << "\n/////////////////////////Patient" << i + 1 << "/////////////////////////////////////////\n";
				cout << "Was been deleted";
				cout << "\n//////////////////////////////////////////////////////////////////////////////////////\n";
				continue;
			}
			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(patient.name, field_length);
			patient.name[field_length] = '\0';

			logicalfile.read((char*)&field_length, sizeof(int));
			logicalfile.read(patient.Case, field_length);
			patient.Case[field_length] = '\0';

			cout << "\n///////////////////////////////////Patient" << i + 1 << "////////////////////////////////////////\n";
			cout << "\nName : " << patient.name;
			cout << "\nID : " << patient.id;
			cout << "\nCase : " << patient.Case;
			cout << "\n//////////////////////////////////////////////////////////////////////////////////////\n";
		}
		logicalfile.close();
	}
	else
		cout << "Sorry cant open this file :(\n";
}

void Delete_Patients_using_Id(fstream& logicalfile, Patient& patient, int Header, int search, int number_of_total_sign, int field_length, map<string, int>& Id_Patient)
{
	logicalfile.open("Patientsfile.txt", ios::in | ios::out | ios::binary);
	if (logicalfile.is_open())
	{
		logicalfile.seekg(0, ios::beg);
		logicalfile.read((char*)&Header, sizeof(4));

		logicalfile.seekg(search, ios::beg);
		logicalfile.read((char*)&field_length, sizeof(4));

		logicalfile.read(patient.id, field_length);//////////////////////////////
		Id_Patient[patient.id] = -1;////////////////////////////

		logicalfile.seekp(search + 4, ios::beg);
		logicalfile.put('*');//deletion mark :)
		logicalfile.write((char*)&Header, sizeof(4));

		logicalfile.seekp(0, ios::beg);
		Header = (search - 8) / 65;
		logicalfile.write((char*)&Header, sizeof(4));
		cout << "New Header = " << Header << "\n";
	}
	else
		cout << "Sorry Cant open this file :(\n";

	logicalfile.close();

}

int main()
{
	Doctor doctor;
	Patient patient;
	fstream logicalfile;
	int field_length = 0, off_set = 0, Header = -1;//
	int your_want, more_process = 0, number_of_total_sign = 0;
	map<string, int>Id_Doctor;
	map<string, int>::iterator it_Doctor;// to control map
	map<string, int>::iterator it_Patient;// to control map
	map<string, int>Id_Patient;

	map<string, string>name_Doctor;//secondry key
	map<string, string>name_patient;//secondry key 
	map<string, string>::iterator it_Doctorname;// to control map
	map<string, string>::iterator it_Patientname;// to control map   //end of variables
	do
	{
		cout << "What do you want to do?\n1-Insert Data\n2-Display\n3-Delete\n4-Search\n5-Update\n";//Menu
		cin >> your_want;//option
		system("cls");//to rewrite consol
		if (your_want == 1)
		{
			cout << "You want to insert Data for \n1-Doctor\n2-Patient\nEnter your answer ===>>> ";
			cin >> your_want;
			system("cls");//to rewrite consol
			if (your_want == 1)
			{
				Insert_Doctors_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, name_Doctor);
				Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//call Pimary after insert
				Update_Insert_Doctor_Secondry_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, it_Doctorname);//call Pimary after insert
			}
			else if (your_want == 2) //patient 
			{
				Insert_Patient_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, name_patient);
				Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);
				//missed secondry one
			}
			else
				cout << "Sorry invalid choice\n";
		}


		else if (your_want == 2)//complete!!
		{
			system("cls");//to rewrite consol
			cout << "Do you want to print\n1-Doctors\n2-Patient\n";
			cin >> your_want;
			if (your_want == 1)
				Display_Doctors_Data(logicalfile, doctor, off_set, number_of_total_sign, field_length);
			else if (your_want == 2)//patient
				Display_Patients_Data(logicalfile, patient, off_set, number_of_total_sign, field_length);
			else
				cout << "Sorry invalid choice\n";

		}


		else if (your_want == 3)
		{
			int  search;
			cout << "You want to delete Data for \n1-Doctor\n2-Patient\nEnter your answer ===>>> ";
			cin >> your_want;
			system("cls");//to rewrite consol
			if (your_want == 1)//Doctor part
			{
				cout << "You want to delete Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that map is updated
					search = Search_Doctor_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Delete_Doctors_using_Id(logicalfile, doctor, Header, search, number_of_total_sign, field_length, Id_Doctor);
						Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that map is updated
					}
				}
				else if (your_want == 2)//name part
				{
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that Id/offset map is updated
					Update_Insert_Doctor_Secondry_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, it_Doctorname);//to make sure that name/id map is updated
					search = Search_Doctor_Secondry_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Delete_Doctors_using_Id(logicalfile, doctor, Header, search, number_of_total_sign, field_length, Id_Doctor);
						Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that map is updated
					}

				}
				else
					cout << "Sorry invalid choice\n";
			}



			else if (your_want == 2)//Patient Part
			{
				cout << "You want to delete Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that map is updated
					search = Search_Patient_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Delete_Patients_using_Id(logicalfile, patient, Header, search, number_of_total_sign, field_length, Id_Patient);
						Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that map is updated
					}
				}
				else if (your_want == 2)//name part
				{
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that Id/offset map is updated
					Update_Insert_Patient_Secondry_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, it_Patientname);//to make sure that name/id map is updated
					search = Search_Patient_Secondry_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Delete_Patients_using_Id(logicalfile, patient, Header, search, number_of_total_sign, field_length, Id_Patient);
						Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that Id/offset map is updated
					}

				}
				else
					cout << "Sorry invalid choice\n";
			}
		}

		else if (your_want == 4)
		{
			int search;
			cout << "You want to Search Data for \n1-Doctor\n2-Patient\nEnter your answer ===>>> ";
			cin >> your_want;
			system("cls");//to rewrite consol
			if (your_want == 1)//Doctor part
			{
				cout << "You want to Search Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that Id/offset map is updated
					search = Search_Doctor_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id or This Record Deleted :(\n";
					}
					else
						Result_of_search(logicalfile, doctor, search, Header, number_of_total_sign, field_length);
				}
				else if (your_want == 2)//name part
				{
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that Id/offset map is updated
					Update_Insert_Doctor_Secondry_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, it_Doctorname);//to make sure that name/id map is updated
					search = Search_Doctor_Secondry_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id or This Record Deleted :(\n";
					}
					else
						Result_of_search(logicalfile, doctor, search, Header, number_of_total_sign, field_length);
				}
				else
					cout << "Sorry invalid choice\n";
			}
			else if (your_want == 2)
			{
				cout << "You want to Search Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that map is updated
					search = Search_Patient_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
						Result_of_pateint_search(logicalfile, patient, search, Header, number_of_total_sign, field_length);
				}
				else if (your_want == 2) { //name part
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that Id/offset map is updated
					Update_Insert_Patient_Secondry_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, it_Patientname);//to make sure that name/id map is updated
					search = Search_Patient_Secondry_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
						Result_of_pateint_search(logicalfile, patient, search, Header, number_of_total_sign, field_length);
				}
				else
					cout << "Sorry invalid choice\n";
			}
		}


		else if (your_want == 5)
		{
			int  search;
			cout << "You want to update Data for \n1-Doctor\n2-Patient\nEnter your answer ===>>> ";
			cin >> your_want;
			system("cls");//to rewrite consol
			if (your_want == 1)//Doctor part
			{
				cout << "You want to update Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{	//////////////////////////////////////////////////////////////////////////////////
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that map is updated
					search = Search_Doctor_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Update_Doctors_using_Id(logicalfile, doctor, search, number_of_total_sign, field_length, name_Doctor);//////////////////////////////
						Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that map is updated
					}
				}
				else if (your_want == 2)//name part
				{
					Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that Id/offset map is updated
					Update_Insert_Doctor_Secondry_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, it_Doctorname);//to make sure that name/id map is updated
					search = Search_Doctor_Secondry_Data(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, Id_Doctor);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Update_Doctors_using_Id(logicalfile, doctor, search, number_of_total_sign, field_length, name_Doctor);//////////////////////////////
						Update_Insert_Doctor_primary_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, Id_Doctor, it_Doctor);//to make sure that Id/offset map is updated
						Update_Insert_Doctor_Secondry_index(logicalfile, doctor, off_set, Header, number_of_total_sign, field_length, name_Doctor, it_Doctorname);//to make sure that name/id map is updated
					}

				}
				else
					cout << "Sorry invalid choice\n";
			}
			else if (your_want == 2)//Patient part
			{
				cout << "You want to update Data using \n1-Id\n2-Name\nEnter your answer ===>>> ";
				cin >> your_want;
				system("cls");//to rewrite consol
				if (your_want == 1)
				{
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that map is updated
					search = Search_Patient_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Update_Patients_using_Id(logicalfile, patient, search, number_of_total_sign, field_length, name_patient);
						Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that map is updated
					}

				}
				else if (your_want == 2) //name part
				{
					Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that Id/offset map is updated
					Update_Insert_Patient_Secondry_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, it_Patientname);//to make sure that name/id map is updated
					search = Search_Patient_Secondry_Data(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, Id_Patient);
					if (search == -1)
					{
						cout << "Sorry can`t find this Id :(\n";
					}
					else
					{
						Update_Patients_using_Id(logicalfile, patient, search, number_of_total_sign, field_length, name_patient);
						Update_Insert_Patient_primary_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, Id_Patient, it_Patient);//to make sure that Id/offset map is updated
						Update_Insert_Patient_Secondry_index(logicalfile, patient, off_set, Header, number_of_total_sign, field_length, name_patient, it_Patientname);//to make sure that name/id map is updated
					}

				}

				else
					cout << "Sorry invalid choice\n";
			}
		}

		else if (your_want >= 6 || your_want <= 0) {
			cout << "Sorry Invalid Choice :(";
			exit(0);
		}

		cout << "\nYou need more process sir?\n1-No,thanks.\n2-Yes,please\nYour answer====>>>>";
		cin >> more_process;
		more_process -= 1;
		system("cls");//to rewrite consol
	} while (more_process);
	cout << "Thanks for using our Code :)\n";
	return 0;
}