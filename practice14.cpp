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

		//string x = "赤澤晃輝 program14 0\n伊藤光 19142029 0\n嶺井博希 19142039 0\n山本祐大 19142050 0";
		//ofstream outfile("People.txt", ios_base::out);
		//outfile << x;
		//outfile.close();

		ifstream datafile("People.txt");
		if (!datafile) {
			throw runtime_error("ファイルが見つかりません。");
		}
		else {
			string a, b;
			int c;

			while (datafile >> a >> b >> c) {
				Person.emplace_back(a, b, c);
			}
		}

		while (1) {

			cout << "名前を入力してください。" << endl;
			string name;
			cin >> name;

			int idx = findidx(Person, "name", name);

			if (idx != -1) {
				string pass;
				string yn;

				if (idx == 0) {
					cout << "パスワードを入力してください。" << endl;
					cin >> pass;

					if (pass == Person[0].Pass()) {
						system("cls");
						cout << "管理者モードです。" << endl
							<< "[1]：講義を開始　[2]：参加者を追加　[3]：終了　[その他の数字]：戻る" << endl;
						int c;
						cin >> c;

						switch (c) {
						case 1: {
							system("cls");
							cout << "講義を開始します。" << endl
								<< "何回目の講義ですか？" << endl
								<< "前回の設定：第" << Person[0].Attendance() << "回" << endl;
							cin >> week;

							Person[0].SetAttendance(week);
							began = true;

							cout << "第" << week << "回目の講義を開始しました。" << endl
								<< "[任意の入力]：終了" << endl;
							cin >> yn;

							break;
						}
						case 2: {
							system("cls");
							cout << "参加者を追加します。" << endl
								<< "参加者の名前を入力してください。" << endl;
							string newname;
							cin >> newname;

							cout << "参加者の学修番号を入力してください。" << endl;
							string newpass;
							cin >> newpass;

							int idx2 = findidx(Person, "pass", newpass);

							if (idx2 != -1) {
								cout << "既に登録された参加者です。" << endl
									<< "[任意の入力]：終了" << endl;
								cin >> yn;
							}
							else {
								cout << "出席回数を入力してください。" << endl;
								int newatd;
								cin >> newatd;

								cout << "内容に間違いはありませんか？" << endl
									<< "[y]：yes　[その他の入力]：no" << endl;
								cin >> yn;

								if (yn == "y") {
									Person.emplace_back(newname, newpass, newatd);
									cout << "参加者を追加しました。" << endl
										<< "[任意の入力]：終了" << endl;
									cin >> yn;
								}
							}

							break;
						}
						case 3: {
							cout << "終了しますか？" << endl
								<< "[y]：yes　[その他の入力]：no" << endl;
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
					cout << "学修番号を入力してください。" << endl;
					cin >> pass;
					if (pass == Person[idx].Pass()) {

						if (Person[idx].Check() == false) {
							Person[idx].Attended();
							int absence = week - Person[idx].Attendance();

							cout << "出席を確認しました。" << endl
								<< "出席：" << Person[idx].Attendance() << endl
								<< "欠席：" << absence << endl
								<< "[任意の入力]：終了" << endl;
							cin >> yn;
						}
						else {
							cout << "既に出席確認済みです。" << endl
								<< "[任意の入力]：終了" << endl;
							cin >> yn;
						}
					}
				}
				else {
					system("cls");

					cout << "まだ講義が開始されていません。" << endl
						<< "[任意の入力]：終了" << endl;
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