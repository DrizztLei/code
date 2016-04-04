namespace pers
{
	const int LEN = 40;
	struct Person{
		char fname[LEN];
		char lname[LEN];
	};
	void getPerson(Person &);
	void showPerson(const Person &);
}

namespace debt
{
	using namespace pers ;
	struct Debt{
		Person name;
		double amount;
	};

	void get_debt(Debt & );
	void show_debt(const Debt &);
	void sum_debts(const Debt array[] , int n)
}
