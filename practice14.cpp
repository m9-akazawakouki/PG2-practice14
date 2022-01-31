#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class People {
	string name;
	string pass;
	int attendance;
	bool check;

public:
	People(string N, string P, int A):
		name(N), pass(P), attendance(A), check(false) {}
	string Name() {
		return name;
	}
	string Pass() {
		return pass;
	}
	int Attendance() {
		return attendance;
	}
	bool Check() {
		return check;
	}
	void SetAttendance(int atd) {
		attendance = atd;
	}
	void Attended() {
		attendance += 1;
		check = true;
	}
};

int findidx(vector<People> vec, string kind, string key) {
	for (auto itr = vec.begin(); itr < vec.end(); itr++) {
		if (kind == "name") {
			if ((*itr).Name() == key) {
				return itr - vec.begin();
			}
		}
		else if (kind == "pass") {
			if ((*itr).Pass() == key) {
				return itr - vec.begin();
			}
		}
	}
	return -1;
}


int main() {
	try {
		bool end = false;
		bool began = false;
		vector<People> Person;
		int week;

		//string x = "���V�W�P program14 0\n�ɓ��� 19142029 0\n��䔎�� 19142039 0\n�R�{�S�� 19142050 0";
		//ofstream outfile("People.txt", ios_base::out);
		//outfile << x;
		//outfile.close();

		ifstream datafile("People.txt");
		if (!datafile) {
			throw runtime_error("�t�@�C����������܂���B");
		}
		else {
			string a, b;
			int c;

			while (datafile >> a >> b >> c) {
				Person.emplace_back(a, b, c);
			}
		}

		while (1) {

			cout << "���O����͂��Ă��������B" << endl;
			string name;
			cin >> name;

			int idx = findidx(Person, "name", name);

			if (idx != -1) {
				string pass;
				string yn;

				if (idx == 0) {
					cout << "�p�X���[�h����͂��Ă��������B" << endl;
					cin >> pass;

					if (pass == Person[0].Pass()) {
						system("cls");
						cout << "�Ǘ��҃��[�h�ł��B" << endl
							<< "[1]�F�u�`���J�n�@[2]�F�Q���҂�ǉ��@[3]�F�I���@[���̑��̐���]�F�߂�" << endl;
						int c;
						cin >> c;

						switch (c) {
						case 1: {
							system("cls");
							cout << "�u�`���J�n���܂��B" << endl
								<< "����ڂ̍u�`�ł����H" << endl
								<< "�O��̐ݒ�F��" << Person[0].Attendance() << "��" << endl;
							cin >> week;

							Person[0].SetAttendance(week);
							began = true;

							cout << "��" << week << "��ڂ̍u�`���J�n���܂����B" << endl
								<< "[�C�ӂ̓���]�F�I��" << endl;
							cin >> yn;

							break;
						}
						case 2: {
							system("cls");
							cout << "�Q���҂�ǉ����܂��B" << endl
								<< "�Q���҂̖��O����͂��Ă��������B" << endl;
							string newname;
							cin >> newname;

							cout << "�Q���҂̊w�C�ԍ�����͂��Ă��������B" << endl;
							string newpass;
							cin >> newpass;

							int idx2 = findidx(Person, "pass", newpass);

							if (idx2 != -1) {
								cout << "���ɓo�^���ꂽ�Q���҂ł��B" << endl
									<< "[�C�ӂ̓���]�F�I��" << endl;
								cin >> yn;
							}
							else {
								cout << "�o�ȉ񐔂���͂��Ă��������B" << endl;
								int newatd;
								cin >> newatd;

								cout << "���e�ɊԈႢ�͂���܂��񂩁H" << endl
									<< "[y]�Fyes�@[���̑��̓���]�Fno" << endl;
								cin >> yn;

								if (yn == "y") {
									Person.emplace_back(newname, newpass, newatd);
									cout << "�Q���҂�ǉ����܂����B" << endl
										<< "[�C�ӂ̓���]�F�I��" << endl;
									cin >> yn;
								}
							}

							break;
						}
						case 3: {
							cout << "�I�����܂����H" << endl
								<< "[y]�Fyes�@[���̑��̓���]�Fno" << endl;
							cin >> yn;

							if (yn == "y")
								end = true;
							break;
						}
						default:
							break;
						}

					}

				}
				else if (began == true) {
					cout << "�w�C�ԍ�����͂��Ă��������B" << endl;
					cin >> pass;
					if (pass == Person[idx].Pass()) {

						if (Person[idx].Check() == false) {
							Person[idx].Attended();
							int absence = week - Person[idx].Attendance();

							cout << "�o�Ȃ��m�F���܂����B" << endl
								<< "�o�ȁF" << Person[idx].Attendance() << endl
								<< "���ȁF" << absence << endl
								<< "[�C�ӂ̓���]�F�I��" << endl;
							cin >> yn;
						}
						else {
							cout << "���ɏo�Ȋm�F�ς݂ł��B" << endl
								<< "[�C�ӂ̓���]�F�I��" << endl;
							cin >> yn;
						}
					}
				}
				else {
					system("cls");

					cout << "�܂��u�`���J�n����Ă��܂���B" << endl
						<< "[�C�ӂ̓���]�F�I��" << endl;
					cin >> yn;
				}

			}

			if (end == true) {
				ofstream outfile("People.txt", ios_base::out);
				for (auto itr = Person.begin();itr < Person.end();itr++) {
					outfile << (*itr).Name() << " " << (*itr).Pass() << " " << (*itr).Attendance() << endl;
				}
				outfile.close();

				break;
			}

			system("cls");
		}
	}
	catch(exception& e){
		cerr << e.what() << endl;
	}
}