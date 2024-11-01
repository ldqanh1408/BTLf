#include <iostream>
#include <iomanip>
#include "Account.h"
#include "Information.h"
#include "Wallet.h"
#include "gotp.h"
#include "User.h"

// bool valid_money(std::string money) {
//     for(char &c : money) {
//         if(!std::isdigit(c)) return false;
//     }
//     return true;
// }

User::User() {}

void User::set_account(Account _account) {
    this->account = _account;
}

void User::set_full_name(const std::string& name) {
    Information::set_full_name(name);
    if(!gotp::verify_otp()) return;
    std::cout << "Thay đổi họ và tên thành công!" << std::endl;
}

void User::set_address(const std::string& addr) {
    Information::set_address(addr);
    if(!gotp::verify_otp()) return;
    std::cout << "Thay đổi địa chỉ thành công!" << std::endl;
}

void User::set_country(const std::string& country) {
    Information::set_country(country);
    if(!gotp::verify_otp()) return;
    std::cout << "Thay đổi quốc gia thành công!" << std::endl;
}

void User::set_phone_number(const std::string& phone) {
    Information::set_phone_number(phone);
    if(!gotp::verify_otp()) return;
    std::cout << "Thay đổi số điện thoại thành công!" << std::endl;
}

void User::set_age(int age) {
    if (age > 0) {
        Information::set_age(age);
        std::cout << "Thay đổi tuổi thành công!" << std::endl;
        if(!gotp::verify_otp()) return;
    } else {
        std::cout << "Tuổi không hợp lệ. Thay đổi thất bại!" << std::endl;
    }
}

void User::set_gender(bool gender) {
    Information::set_gender(gender);
    if(!gotp::verify_otp()) return;
    std::cout << "Thay đổi giới tính thành công!" << std::endl;
}

bool User::change_password() {
    std::string new_password, confirm_password;

    std::cout << "Nhập mật khẩu mới: ";
    std::cin >> new_password;
    std::cout << "Nhập lại mật khẩu mới: ";
    std::cin >> confirm_password;

    if (new_password != confirm_password) {
        std::cout << "Mật khẩu không khớp. Đổi mật khẩu thất bại." << std::endl;  
        return false;
    }

    if (this->account.set_password(new_password)) {
        if (gotp::verify_otp()) {
            std::cout << "Đổi mật khẩu thành công!" << std::endl;
            return true;
        } else {
            std::cout << "Đổi mật khẩu thất bại." << std::endl;
            return false;
        }
    } else {
        std::cout << "Mật khẩu mới không hợp lệ. Đổi mật khẩu thất bại." << std::endl;
        return false;
    }
}


// void transfer_money(User &b) {
//     auto valid_money = [&](string &money)->bool {
//         for (char &c : money) {
//             if (!isdigit(c)) return false;
//         }
//         return true;
//     };

//     auto error_transaction_log = [&](unsigned long long amount, const string &error_msg) {
//         // Lấy thời gian hiện tại
//         time_t now = time(nullptr);
//         struct tm *tm_info = localtime(&now);
        
//         char time_buffer[80];
//         strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d_%H-%M-%S", tm_info); // Định dạng thời gian
//         string error_log_file = folder5 + string(time_buffer) + ".txt"; // Tạo tên file

//         ofstream error_log(error_log_file, ios::app);
//         if (error_log.is_open()) {
//             error_log << ctime(&now) << " - " << "Transaction Error: " << error_msg
//                     << " | From: " << this->Information::get_full_name() << " (ID: " << this->wallet.get_ID() << ")"
//                     << " | To: " << b.Information::get_full_name() << " (ID: " << b.wallet.get_ID() << ")"
//                     << " | Amount: " << amount << '\n';
//             error_log.flush();
//             error_log.close();
//         } else {
//             //backup
//         }
//     };

//     string hash_a = bcrypt::generateHash(this->wallet.get_ID());
//     string hash_b = bcrypt::generateHash(b.wallet.get_ID());
//     string wallet_b = folder3 + hash_b + ".txt";
//     string wallet_a = folder3 + hash_a + ".txt";

//     if (!fs::exists(wallet_b) || (this->wallet.get_ID() == b.wallet.get_ID())) {
//         cout << "Tài khoản không tồn tại! " << endl;
//         return;
//     }

//     string temp_wallet_a = wallet_a + ".tmp";
//     string temp_wallet_b = wallet_b + ".tmp";

//     ofstream outfile_a(temp_wallet_a);
//     ofstream outfile_b(temp_wallet_b);
//     ifstream infile_a(wallet_a);
//     ifstream infile_b(wallet_b);

//     if (!infile_a || !infile_b || !outfile_a || !outfile_b) {
//         cout << "Lỗi giao dịch vui lòng thử lại!" << endl;
//         return;
//     }

//     unsigned long long balance_a, balance_b, d_valid = 0;
//     infile_a >> balance_a;
//     infile_b >> balance_b;
//     infile_a.close();
//     infile_b.close();

//     string d;
//     cout << "Nhập số tiền cần chuyển: ";
//     getline(cin, d);
//     if (valid_money(d)) {
//         for (char c : d) {
//             d_valid = d_valid * 10ULL + (c - '0');
//         }
//     } else {
//         cout << "Số tiền nhập vào không hợp lệ" << endl;
//         return;
//     }

//     if (balance_a < d_valid) {
//         cout << "Số tiền trong tài khoản không đủ!" << endl;
//         return;
//     } else if (!gotp::verify_otp()) {
//         return;
//     }

//     balance_a -= d_valid;
//     balance_b += d_valid;

//     outfile_a << balance_a;
//     outfile_a.flush();
//     if (!outfile_a.good()) {
//         error_transaction_log(d_valid, "Ghi không thành công vào ví A");
//         return;
//     }

//     outfile_b << balance_b;
//     outfile_b.flush();
//     if (!outfile_b.good()) {
//         error_transaction_log(d_valid, "Ghi không thành công vào ví B");
//         return;
//     }

//     outfile_a.close();
//     outfile_b.close();

//     try {
//         fs::rename(temp_wallet_a, wallet_a);
//         fs::rename(temp_wallet_b, wallet_b);
//     } catch (const exception &e) {
//         error_transaction_log(d_valid, "Lỗi đổi tên tệp sau khi ghi");
//         return;
//     }

//     time_t now = time(nullptr);
//     struct tm *tm_info = localtime(&now);
    
//     char transaction_buffer[80];
//     strftime(transaction_buffer, sizeof(transaction_buffer), "%Y-%m-%d_%H-%M-%S", tm_info); // Định dạng thời gian
//     string transaction_log_file = folder5 + string(transaction_buffer) + ".txt";

//     ofstream update_a(folder4 + this->Information::get_full_name() + ".txt", ios::app);
//     ofstream update_b(folder4 + b.Information::get_full_name() + ".txt", ios::app);
//     ofstream update_transaction_log(transaction_log_file, ios::app);

//     if (update_transaction_log.is_open()) {
//         time_t now = time(nullptr);
//         update_transaction_log << ctime(&now) << " - " << "Completed Transfer"
//                             << " | From: " << this->Information::get_full_name() << " (ID: " << this->wallet.get_ID() << ")"
//                             << " | To: " << b.Information::get_full_name() << " (ID: " << b.wallet.get_ID() << ")"
//                             << " | Amount: " << d_valid << '\n';
//         update_transaction_log.flush();
//         update_transaction_log.close();
//     } else {
//         error_transaction_log(d_valid, "Không ghi được log giao dịch");
//     }

//     update_a << "Bạn đã chuyển " << d_valid << " điểm cho " << b.Information::get_full_name() << endl;
//     update_b << "Bạn đã nhận được " << d_valid << " điểm từ " << this->Information::get_full_name() << endl;

//     update_a.flush();
//     if (!update_a.good()) {
//         error_transaction_log(d_valid, "Không ghi được thông báo update cho tài khoản A");
//     }

//     update_b.flush();
//     if (!update_b.good()) {
//         error_transaction_log(d_valid, "Không ghi được thông báo update cho tài khoản B");
//     }

//     update_a.close();
//     update_b.close();
// }