#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <random>

using namespace std;

class BankCard;
vector<BankCard> card_accounts;
class Card {
public:
    virtual string GetCardNo() const = 0;
    Card(string a, string b) :id(a), key(b) {}
protected:
    string id, key;
};

void inputPassword(const BankCard& a);
void menu(BankCard& a, vector<BankCard>& obj);
BankCard log(vector<BankCard>(obj));
class BankCard :public Card {
public:
    string GetCardNo() const override { // 重写基类的纯虚函数
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);
        string number;
        for (int i = 0; i < 16; ++i) {
            number += to_string(dis(gen));
        }
        return number;
    }
    float money;
    BankCard(string id, string key, float value) :Card(id, key), money(value) {
        card_accounts.push_back(*this);
    }
    void remove();
    void Transfer(vector<BankCard>& (obj));
    void Balance() const {
        cout << "current balance is :$" << money << endl;
    }
    void Withdraw();
    void Deposit();
    /*~BankCard(){
        cout<<"Thanks for using"<<endl;
    }*/
    friend void inputPassword(const BankCard& a);
    friend BankCard log(vector<BankCard>(obj));
    /*private:
        string id;
        string key;
       */
};
int main() {
    BankCard("123", "123456", 1000.0);
    BankCard("456", "123456", 1000.0);
    BankCard("789", "123456", 1000.0);
    BankCard a = log(card_accounts);
    menu(a, card_accounts);
    return 0;
}
void inputPassword(const BankCard& a) {
    string str;
    do {
        cout << "Please enter a 6-digit bank card PIN :";
        char c;
        int size = 7;
        int count = 0;
        char* password = new char[size]; // ?????????
        while ((c = _getch()) != '\r') {

            if (c == 8) { // ???
                if (count == 0) {
                    continue;
                }
                putchar('\b'); // ???????
                putchar(' '); // ??????????????*????
                putchar('\b'); // ??????????????
                count--;
            }
            if (count == size) { // ?????size-1
                //cout<<endl<<"To achieve the maximum password length"<<endl;
                continue;
            }
            if (c >= '0' && c <= '9') {  // ??????п???????????????
                putchar('*');  // ?????????????, ??????*
                password[count] = c;
                count++;
            }
        }
        //password[count] = '\0';
        str = password;
        cout << endl << str << endl;
        delete[] password; // ?????
        if (str != a.key) {
            cout << "Wrong password" << endl;
        }
        else {
            cout << "Password correct" << endl;
            break;
        }
    } while (str != a.key);
}
void BankCard::remove() {
    for (unsigned int i = 0; i < card_accounts.size(); i++) {
        if (card_accounts[i].id == id && card_accounts[i].key == key) {
            card_accounts.erase(card_accounts.begin() + i);
            cout << "delete success" << endl;
            break;
        }
    }
}
void BankCard::Transfer(vector<BankCard>& (obj))
{
    inputPassword(*this);
    string id_object;
    cout << "Transfer account ID :";
    cin >> id_object;
    for (vector<BankCard>::iterator i = obj.begin(); i != obj.end(); i++) {
        if (i->id == id_object) {
            string num;
            float amount;
            int j = 0;
            label1:
            cout << "transfer amount :";
            cin >> num;
            while (num[j]) {
                if (isdigit(num[j])) {
                    j++;
                    continue;
                }
                else {
                    cout << "Invalid input" << endl;
                    break;
                }
            }
            amount = strtof(num.c_str(), NULL);
            if (money <= amount) {
                cout << "Do not have enough money" << endl;
                Sleep(5000);
                goto label1;
            }
            else {
                money -= amount;
                i->money += amount;
                cout << "Transfer successfully" << endl;
                return;
            }
        }
        else if (i == obj.end()) {
            cout << "Do not have this account" << endl;
            Sleep(5000);
            return;
        }
    }

}
void BankCard::Withdraw() {
    while (true) {
        inputPassword(*this);
        string num;
        float amount;
        int i = 0;
        cout << "How much do you want to withdraw? ";
        cin >> num;
        while (num[i]) {
            if (isdigit(num[i])) {
                i++;
                continue;
            }
            else {
                cout << "Invalid input" << endl;
                break;
            }
        }
        amount = strtof(num.c_str(), NULL);
        if (amount > money) {
            cout << "You don't have enough money" << endl;
            continue;
        }
        else {
            money -= amount;
            cout << "Withdrawal successful" << endl;
            cout << "Your current balance is :$" << money << endl;
            break;
        }
    }
}
void BankCard::Deposit() {
    while (true) {
        string num;
        float amount;
        inputPassword(*this);
        int i = 0;
        cout << "How much do you want to deposit? ";
        cin >> num;
        while (num[i]) {
            if (isdigit(num[i])) {
                i++;
                continue;
            }
            else {
                cout << "Invalid input" << endl;
                return;
            }
        }
        amount = strtof(num.c_str(), NULL);
        money += amount;
        cout << "Deposit successful" << endl;
        cout << "Your current balance is :$" << money << endl;
        break;
    }
}
void menu(BankCard& a, vector<BankCard>& obj) {
    while (true) {
        system("cls");
        char choice;
        cout << " ======Welcome to XXX Bank======" << endl;
        cout << "You want to perform the service :" << endl;
        cout << "a:Check the balance" << endl;
        cout << "b:Deposit" << endl;
        cout << "c:Withdraw" << endl;
        cout << "d:Transfer" << endl;
        cout << "e:Delete" << endl;
        cout << "f:Show BankCard number" << endl;
        cout << "g:Exit" << endl;
        cin >> choice;
        switch (choice) {
            case 'a':
                a.Balance();
                break;
            case 'b':
                a.Deposit();
                break;
            case 'c':
                a.Withdraw();
                break;
            case 'd':
                a.Transfer(obj);
                break;
            case 'e':
                a.remove();
                cout << "======Thank you for using XXX Bank======" << endl;
                return;
            case 'g':
                cout << "======Thank you for using XXX Bank======" << endl;
                return;
            case 'f': {
                Card* cardPtr = &a; // 创建指向Card对象的基类指针
                cout << "BankCard Number: " << cardPtr->GetCardNo() << endl; // 使用基类指针调用虚函数
                break;
            }
            default:
                cout << "Wrong input" << endl;
                Sleep(3000);
                system("cls");
                break;
        }
        Sleep(2000);
    }
}
BankCard log(vector<BankCard>(obj)) {
    string id;
    string cipher;
    while (true) {
        cout << " ======Welcome to XXX Bank======" << endl;
        cout << "Enter your ID :";
        cin >> id;
        for (vector<BankCard>::iterator i = obj.begin(); i != obj.end(); i++) {
            if (i->id == id) {
                inputPassword(*i);
                return *i;
            }
        }
    }
}
