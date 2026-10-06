#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    long long balance;

public:
    BankAccount(std::string accNum, long long initialBalance)
        : accountNumber(accNum), balance(initialBalance < 0 ? 0 : initialBalance) {}

    std::string getAccountNumber() const {
        return accountNumber;
    }

    long long getBalance() const {
        return balance;
    }

    void deposit(long long amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposit: Rp" << amount << " | Saldo baru: Rp" << balance << "\n";
        } else {
            std::cout << "Gagal deposit: Nilai harus lebih besar dari 0.\n";
        }
    }

    bool withdraw(long long amount) {
        if (amount <= 0) {
            std::cout << "Gagal tarik dana: Nilai tidak valid.\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Gagal tarik dana: Saldo tidak mencukupi.\n";
            return false;
        }
        balance -= amount;
        std::cout << "Tarik dana: Rp" << amount << " | Sisa saldo: Rp" << balance << "\n";
        return true;
    }
};

int main() {
    // Alur: Buat akun -> baca via getter -> mutasi via method tervalidasi
    BankAccount account("ICHIRO-BANK-001", 1000000);

    std::cout << "Nomor Rekening : " << account.getAccountNumber() << "\n";
    std::cout << "Saldo Awal     : Rp" << account.getBalance() << "\n\n";

    account.deposit(500000);
    account.withdraw(300000);
    account.withdraw(2000000); // Uji validasi saldo

    return 0;
}
