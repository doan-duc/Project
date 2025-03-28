#include <iostream>
#include <string.h>
#include <windows.h> //Sử dụng cho lấy Font Tiếng Việt
#include <fstream> //Nhập xuất file
using namespace std;
int countPatient = 0, countDoctor = 0;
//DELAY TIME
void usleep(int n) {
    for (int i = 1;i <= n;i++) {
        for(long long j = 1;j <= 2000000000;j++);
    }
}
//XÓA DÒNG
void eraseLines(int count) {
    if (count > 0) {
        cout << "\x1b[2K"; //Xóa nội dung hiện tại
        for (int i = 1; i < count; i++) {
            cout << "\x1b[1A" << "\x1b[2K"; //Di chuyển con trỏ lên 1 dòng và xóa dòng đó
        }
        cout << "\r"; // Đưa con trỏ về đầu dòng
    }
}
// Đổi chữ sang số
int convert(string s) {
    int kq = 0;
    for (int i = 0;i < s.size();i++) kq = kq*10+((int)s[i]-48);
    return kq;
}
//Viết hoa xâu
void UPCASE(string &s) {
    for (int i = 0; i < s.size();i++) {
        if (s[i] >='a' && s[i] <= 'z') s[i] -= 32;
    }
}
// Cấu trúc ngày, tháng, năm
struct Date {
    int day,month,year;
};
// Cấu trúc thông tin con người
struct conNguoi {
    int num;
    string name;
    int ageid;
    string phone;
    string poshealth;
    Date schedule;

};
//Mở rộng cho mảng cấp phát động
void tangPhanTu(conNguoi *&p, int &COUNT) {
    COUNT++;
    conNguoi *temp = new conNguoi[COUNT];
    for (int i = 0; i < COUNT-1;i++) {
        temp[i].num = p[i].num;
        temp[i].name = p[i].name;
        temp[i].ageid = p[i].ageid;
        temp[i].phone = p[i].phone;
        temp[i].poshealth = p[i].poshealth;
        temp[i].schedule.day = p[i].schedule.day;
        temp[i].schedule.month = p[i].schedule.month;
        temp[i].schedule.year = p[i].schedule.year;
    }
    delete []p;
    p = temp;
}
//Xóa phần tử thứ k khỏi mảng cấp phát động, giảm kích cỡ mảng
void giamPhanTu(conNguoi *&p, int &COUNT, int k) {
    conNguoi *temp1 = new conNguoi[COUNT-1];
    for (int i = k; i < COUNT-1 ;i++) {
        p[i].name = p[i+1].name;
        p[i].ageid = p[i+1].ageid;
        p[i].phone = p[i+1].phone;
        p[i].poshealth = p[i+1].poshealth;
        p[i].schedule.day = p[i+1].schedule.day;
        p[i].schedule.month = p[i+1].schedule.month;
        p[i].schedule.year = p[i+1].schedule.year;
    }
    for (int i = 0; i < COUNT-1 ;i++) {
            temp1[i].num = p[i].num;
            temp1[i].name = p[i].name;
            temp1[i].ageid = p[i].ageid;
            temp1[i].phone = p[i].phone;
            temp1[i].poshealth = p[i].poshealth;
            temp1[i].schedule.day = p[i].schedule.day;
            temp1[i].schedule.month = p[i].schedule.month;
            temp1[i].schedule.year = p[i].schedule.year;
    }

    COUNT -= 1;
    delete []p;
    p = temp1;
}
// Lớp chứa các hàm thành viên xử lí chức năng nhập,sửa,xóa,thống kê
class People {
    private :
        conNguoi *bn = new conNguoi[countPatient];
        conNguoi *nv = new conNguoi[countDoctor];
        int k;
        char c;
    public :
    friend class Chuongtrinh;
    //Gán giá trị cho mảng bn
    void setData(string num,string nameInput,int ageIDInput,string phoneInput,string poshealthInput,int dayInput,int monthInput,int yearInput) {
        tangPhanTu(bn,countPatient);
        bn[countPatient-1].num = convert(num);
        bn[countPatient-1].name = nameInput;
        bn[countPatient-1].ageid = ageIDInput;
        bn[countPatient-1].phone = phoneInput;
        bn[countPatient-1].poshealth = poshealthInput;
        bn[countPatient-1].schedule.day = dayInput;
        bn[countPatient-1].schedule.month = monthInput;
        bn[countPatient-1].schedule.year = yearInput;
    }
    //Gán giá trị cho mảng nv
    void setDataNV(string num,string nameInput,int ageIDInput,string phoneInput,string poshealthInput,int dayInput,int monthInput,int yearInput) {
        tangPhanTu(nv,countDoctor);
        nv[countDoctor-1].num = convert(num);
        nv[countDoctor-1].name = nameInput;
        nv[countDoctor-1].ageid = ageIDInput;
        nv[countDoctor-1].phone = phoneInput;
        nv[countDoctor-1].poshealth = poshealthInput;
        nv[countDoctor-1].schedule.day = dayInput;
        nv[countDoctor-1].schedule.month = monthInput;
        nv[countDoctor-1].schedule.year = yearInput;
    }
    //Tạo thông tin
    void createInfor(conNguoi* &type, int &countType, string role)  {
        tangPhanTu(type, countType);
        type[countType - 1].num = countType;
        cout << "========= TẠO THÔNG TIN " << role << " =========" << endl;
        cout << "STT : " << type[countType-1].num << endl;
        cout << "Tên : " << endl;
        if(role == "BỆNH NHÂN")   {
            cout << "Tuổi : " << endl;
        }
        else if(role == "NHÂN VIÊN")   {
            cout << "Mã số nhân viên : " << endl;
        }
        cout << "Số điện thoại : " << endl;
        if(role == "BỆNH NHÂN")   {
            cout << "Tình trạng bệnh : " << endl;
            cout << "Lịch khám (dd/mm/yyyy): " << endl;
        }
        else if(role == "NHÂN VIÊN")   {
            cout << "Chức vụ : " << endl;
            cout << "Ngày sinh (dd/mm/yyyy): " << endl;
        }
        cout << "===========================================" << endl;
        cout << "\x1b[6A";
        cout << "\x1b[6C";
        cin.ignore();
        getline(cin,type[countType-1].name);
        if(role == "BỆNH NHÂN")   {
            cout << "\x1b[7C";
            cin >> type[countType-1].ageid;
        }
        else if(role == "NHÂN VIÊN")   {
            cout << "\x1b[18C";
            cin >> type[countType-1].ageid;
        }
        cin.ignore();
        cout << "\x1b[16C";
        getline(cin,type[countType-1].phone);
        if(role == "BỆNH NHÂN")   {
            cout << "\x1b[18C";
            getline(cin,type[countType-1].poshealth);
        }
        else if(role == "NHÂN VIÊN")   {
            cout << "\x1b[10C";
            getline(cin,type[countType-1].poshealth);
        }
        cout << "\x1b[24C";
        scanf("%d/%d/%d",&type[countType-1].schedule.day,&type[countType-1].schedule.month,&type[countType-1].schedule.year);
        cin.ignore();
        cout << "\x1b[1B";
        cout << "TẠO "<< role <<" THÀNH CÔNG !";
        usleep(1);
    }
    //Tìm thông tin
    void findInfor(int type) {
        if (type == 0) {
            cout << "========= TÌM THÔNG TIN BỆNH NHÂN =========" << endl;
            cout << "1. Tìm bệnh nhân theo tên" << endl;
            cout << "2. Tìm bệnh nhân theo số điện thoại" << endl;
            cout << "===========================================" << endl;
        } else {
            cout << "========= TÌM THÔNG TIN NHÂN VIÊN =========" << endl;
            cout << "1. Tìm nhân viên theo tên" << endl;
            cout << "2. Tìm nhân viên theo số điện thoại" << endl;
            cout << "===========================================" << endl;
        }

    }
    //Tìm thông tin theo tên
    void findInforName(string findname, int &countK, conNguoi* &k, string role) {   // 1 la bac si, 0 la benh nhan
        bool check = false;
        for(int i = 0; i < countK; i++) {
            string temp1;
            temp1 = k[i].name;
            UPCASE(temp1);
            UPCASE(findname);
            if (temp1 == findname) {
                cout << "========= THÔNG TIN "<<role<<" THEO TÊN =========" << endl;
                cout << "STT : " << k[i].num << endl;
                cout << "Tên : " << k[i].name << endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Mã số : " << k[i].ageid << endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tuổi : " << bn[i].ageid << endl;
                }
                cout << "Số điện thoại : " <<k[i].phone<< endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Chức vụ : " <<k[i].poshealth<< endl;
                    cout << "Ngày sinh (dd/mm/yyyy): " << k[i].schedule.day << "/" << k[i].schedule.month << "/" << k[i].schedule.year <<endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tình trạng bệnh : " <<bn[i].poshealth<< endl;
                    cout << "Lịch khám (dd/mm/yyyy): " << bn[i].schedule.day << "/" << bn[i].schedule.month << "/" << bn[i].schedule.year <<endl;
                }
                check = true;
                }
            }
            if (!check) {
                cout << "KHÔNG TÌM THẤY " << role << " VỪA NHẬP !" << endl;
            }
            cout << "================================================" << endl;
    }
    //Tìm thông tin theo SĐT
    void findInforPhone(string findphone, int &countType, conNguoi* &type, string role) {   // 1 la bac si, 0 la benh nhan
        bool check = false;
        for(int i = 0; i < countType; i++) {
            if (type[i].phone == findphone) {
                cout << "========= THÔNG TIN "<< role <<" THEO SĐT =========" << endl;
                cout << "STT : " << type[i].num << endl;
                cout << "Tên : " << type[i].name << endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Mã số : " << type[i].ageid << endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tuổi : " << type[i].ageid << endl;
                }
                cout << "Số điện thoại : " <<type[i].phone<< endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Chức vụ : " <<type[i].poshealth<< endl;
                    cout << "Ngày sinh (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tình trạng bệnh : " <<type[i].poshealth<< endl;
                    cout << "Lịch khám (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
                }
                check = true;
                }
            }
            if (!check) {
                cout << "Không tìm thấy SĐT vừa nhập !" << endl;
                cout << "================================================" << endl;
            }
    }
    //Xóa thông tin
    void deleteInfor(conNguoi* &type, int &countType, string role)
    {
        cout << "========= XÓA THÔNG TIN " << role <<" =========" << endl;
        cout << "Nhập STT cần xóa : " << endl;
        cout << "===========================================" << endl;
        cout << "\x1b[2A";
        cout << "\x1b[19C";
        cin >> k;
        if (k > countType || k <= 0) {
                system("cls");
                cout << "========= XÓA THÔNG TIN " << role <<" =========" << endl;
                if(role == "BỆNH NHÂN")
                    cout << "Không tìm thấy bệnh nhân vừa nhập !" << endl;
                else if(role == "NHÂN VIÊN")
                    cout << "Không tìm thấy nhân viên vừa nhập !" << endl;
                cout << "===========================================" << endl;
                usleep(2);
                system("cls");
        } else {
                system("cls");
                cout << "========= THÔNG TIN " << role << " =========" << endl;
                cout << "STT : " << type[k-1].num << endl;
                cout << "Tên : " << type[k-1].name << endl;
                if(role =="NHÂN VIÊN") {
                    cout << "Mã số : " << type[k-1].ageid << endl;
                }
                else if(role =="BỆNH NHÂN") {
                    cout << "Tuổi : " << type[k-1].ageid << endl;
                }
                cout << "Số điện thoại : " <<type[k-1].phone<< endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Chức vụ : " <<type[k-1].poshealth<< endl;
                    cout << "Ngày sinh (dd/mm/yyyy): " << type[k-1].schedule.day << "/" << type[k-1].schedule.month << "/" << type[k-1].schedule.year <<endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tình trạng bệnh : " <<type[k-1].poshealth<< endl;
                    cout << "Lịch khám (dd/mm/yyyy): " << type[k-1].schedule.day << "/" << type[k-1].schedule.month << "/" << type[k-1].schedule.year <<endl;
                }
                cout << "===============================================" << endl;
                cout << "Bạn có chắc chắn muốn xóa ? (Y/N) : " ;
                cin >> c;
                if (c == 'Y' || c == 'y') {
                    giamPhanTu(type,countType,k-1);
                    eraseLines(2);
                    cout << "XÓA THÀNH CÔNG !";
                    usleep(1);
                }
            }
    }
    //Sửa thông tin
    void editInfor(conNguoi *&type, int &countType, string role)
{
        cout << "========= SỬA THÔNG TIN " << role <<" =========" << endl;
        if(role =="BỆNH NHÂN")
            cout << "Nhập STT bệnh nhân cần sửa : " << endl;
        else if(role =="NHÂN VIÊN")
            cout << "Nhập STT nhân viên cần sửa : " << endl;
        cout << "===========================================" << endl;
        cout << "\x1b[2A";
        cout << "\x1b[29C";
        cin >> k;
        if (k > countType || k <= 0) {
            system("cls");
            cout << "========= SỬA THÔNG TIN " << role <<" =========" << endl;
            if(role =="BỆNH NHÂN")
                cout << "Không tìm thấy bệnh nhân vừa nhập !" << endl;
            else if(role =="NHÂN VIÊN")
                cout << "Không tìm thấy nhân viên vừa nhập !" << endl;
            cout << "===========================================" << endl;
            usleep(2);
            system("cls");
        } else {
            system("cls");
            cout << "========= THÔNG TIN CŨ CỦA " << role << " =========" << endl;
            cout << "STT : " << type[k-1].num << endl;
            cout << "Tên : " << type[k-1].name << endl;
            if(role =="NHÂN VIÊN")
            {
                cout << "Mã số : " << type[k-1].ageid << endl;
            }
            else if(role =="BỆNH NHÂN")
            {
                cout << "Tuổi : " << type[k-1].ageid << endl;
            }
            cout << "Số điện thoại : " <<type[k-1].phone<< endl;
            if(role =="NHÂN VIÊN")
            {
                cout << "Chức vụ : " <<type[k-1].poshealth<< endl;
                cout << "Ngày sinh (dd/mm/yyyy): " << type[k-1].schedule.day << "/" << type[k-1].schedule.month << "/" << type[k-1].schedule.year <<endl;
            }
            else if(role =="BỆNH NHÂN")
            {
                cout << "Tình trạng bệnh : " <<type[k-1].poshealth<< endl;
                cout << "Lịch khám (dd/mm/yyyy): " << type[k-1].schedule.day << "/" << type[k-1].schedule.month << "/" << type[k-1].schedule.year <<endl;
            }
            cout << "==============================================" << endl;
            cout << "Bạn có chắc chắn muốn sửa ? (Y/N) : " ;
            cin >> c;
            if (c == 'Y' || c == 'y') {
                eraseLines(2);
                cout << endl;
                cout << "========= THÔNG TIN MỚI CỦA " << role << " =========" << endl;
                cout << "STT : " << type[k-1].num << endl;
                cout << "Tên : " << endl;
                if(role == "BỆNH NHÂN")   {
                    cout << "Tuổi : " << endl;
                }
                else if(role == "NHÂN VIÊN")   {
                     cout << "Mã số nhân viên : " << endl;
                }
                cout << "Số điện thoại : " << endl;
                if(role == "BỆNH NHÂN")   {
                    cout << "Tình trạng bệnh : " << endl;
                    cout << "Lịch khám (dd/mm/yyyy): " << endl;
                }
                else if(role == "NHÂN VIÊN")   {
                    cout << "Chức vụ : " << endl;
                    cout << "Ngày sinh (dd/mm/yyyy): " << endl;
                }
                cout << "===========================================" << endl;
                cout << "\x1b[6A";
                cout << "\x1b[6C";
                cin.ignore();
                getline(cin,type[k-1].name);
                if(role == "BỆNH NHÂN")   {
                    cout << "\x1b[7C";
                    cin >> type[k-1].ageid;
                }
                else if(role == "NHÂN VIÊN")   {
                    cout << "\x1b[18C";
                    cin >> type[k-1].ageid;
                }
                cin.ignore();
                cout << "\x1b[16C";
                getline(cin,type[k-1].phone);
                if(role == "BỆNH NHÂN")   {
                    cout << "\x1b[18C";
                     getline(cin,type[k-1].poshealth);
                }
                else if(role == "NHÂN VIÊN")   {
                    cout << "\x1b[10C";
                    getline(cin,type[k-1].poshealth);
                }
                cout << "\x1b[24C";
                scanf("%d/%d/%d",&type[k-1].schedule.day,&type[k-1].schedule.month,&type[k-1].schedule.year);
                cin.ignore();
                cout << "\x1b[1B";
                cout << "SỬA THÔNG TIN THÀNH CÔNG !";
            }
        }
}
    //Thống kê thông tin
    void statisticInfor(string role) {
        cout << "========= THỐNG KÊ THÔNG TIN " << role << " =========" << endl;
        if(role == "BỆNH NHÂN")
        {
            cout << "1. Thống kê thông tin tất cả bệnh nhân" << endl;
            cout << "2. Thống kê bệnh nhân theo ngày, tháng, năm" << endl;
        }
        else if(role == "NHÂN VIÊN")
        {
            cout << "1. Thống kê thông tin tất cả nhân viên" << endl;
            cout << "2. Thống kê nhân viên theo ngày, tháng, năm" << endl;
        }
        cout << "================================================" << endl;
    }
    //Thống kê theo ngày
    void statisticDate(conNguoi* &type, int &countType, string role)
    {
        int dem = 0,searchDay,searchMonth,searchYear;
        bool check = false;
            cout << "========= THỐNG KÊ THÔNG TIN " << role << " THEO NGÀY THÁNG NĂM =========" << endl;
            cout << "Nhập ngày tháng năm (dd/mm/yyyy) : " << endl;
            cout << "====================================================================" << endl;
            cout << "\x1b[2A";
            cout << "\x1b[35C";
            scanf("%d/%d/%d",&searchDay,&searchMonth,&searchYear);
            system("cls");
        for (int i = 0;i < countType;i++) {
            if (type[i].schedule.day == searchDay && type[i].schedule.month == searchMonth && type[i].schedule.year == searchYear) {
                cout << "========= THÔNG TIN "<< role <<" NGÀY "<<searchDay << " THÁNG " <<searchMonth << " NĂM " << searchYear <<" =========" << endl;
                cout << "STT : " << type[i].num << endl;
                cout << "Tên : " << type[i].name << endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Mã số : " << type[i].ageid << endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tuổi : " << type[i].ageid << endl;
                }
                cout << "Số điện thoại : " <<type[i].phone<< endl;
                if(role =="NHÂN VIÊN")
                {
                    cout << "Chức vụ : " <<type[i].poshealth<< endl;
                    cout << "Ngày sinh (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
                }
                else if(role =="BỆNH NHÂN")
                {
                    cout << "Tình trạng bệnh : " <<type[i].poshealth<< endl;
                    cout << "Lịch khám (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
                }
                dem++;
                check = true;
            }
        }
        if (check) cout << "================================================================" << endl;
        else cout << "========= THÔNG TIN "<< role << " NGÀY "<<searchDay << " THÁNG " <<searchMonth << " NĂM " << searchYear <<" =========" << endl;
        if(role == "BỆNH NHÂN")
            cout << "Tổng số lượng bệnh nhân : " << dem << endl;
        else if(role == "NHÂN VIÊN")
            cout << "Tổng số lượng nhân viên : " << dem << endl;
        cout << "================================================================" << endl;
    }
    //Thống kê tất cả thông tin
    void statisticInforAll(conNguoi* &type, int &countType, string role) {
        for (int i = 0;i < countType;i++) {
            cout << "========= THÔNG TIN " << role << " =========" << endl;
            cout << "STT : " << type[i].num << endl;
            cout << "Tên : " << type[i].name << endl;
            if(role =="NHÂN VIÊN") {
                cout << "Mã số : " << type[i].ageid << endl;
            } else {
                cout << "Tuổi : " << type[i].ageid << endl;
            }
            cout << "Số điện thoại : " <<type[i].phone<< endl;
            if(role =="NHÂN VIÊN") {
                cout << "Chức vụ : " <<type[i].poshealth<< endl;
                cout << "Ngày sinh (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
            }
            else {
                cout << "Tình trạng bệnh : " <<type[i].poshealth<< endl;
                cout << "Lịch khám (dd/mm/yyyy): " << type[i].schedule.day << "/" << type[i].schedule.month << "/" << type[i].schedule.year <<endl;
            }
        }
        cout << "=======================================" << endl;
        if(role == "BỆNH NHÂN") cout << "Tổng số lượng bệnh nhân : " << countType << endl;
        else if (role == "NHÂN VIÊN") cout << "Tổng số lượng nhân viên : " << countType << endl;
        cout << "=======================================" << endl;
    }
};
//Lớp chứa các hàm thành viên chức năng cho MENU
class Chuongtrinh {
    private :
        int k;
        People p;
        char c;
        string findName,findPhone;
        fstream fi,fo;
        string num,nameInput,phoneInput,poshealthInput;
        int ageIDInput,dayInput,monthInput,yearInput;
    public :
        //Đọc dữ liệu từ file
        void loadData() {
            fi.open("data_BN.c19",ios::in);
            while(getline(fi,num)) {
                if(num == "" || num == "0") {
                    break;
                }
                fi.ignore();
                getline(fi,nameInput);
                fi >> ageIDInput;
                fi.ignore();
                getline(fi,phoneInput);
                getline(fi,poshealthInput);
                fi>>dayInput;
                fi>>monthInput;
                fi>>yearInput;
                fi.ignore();
                p.setData(num,nameInput,ageIDInput,phoneInput,poshealthInput,dayInput,monthInput,yearInput);
            }
            fi.close();
            fi.open("data_NV.c19",ios::in);
            while(getline(fi,num)) {
                if(num == "" || num == "0") {
                    break;
                }
                fi.ignore();
                getline(fi,nameInput);
                fi >> ageIDInput;
                fi.ignore();
                getline(fi,phoneInput);
                getline(fi,poshealthInput);
                fi>>dayInput;
                fi>>monthInput;
                fi>>yearInput;
                fi.ignore();
                p.setDataNV(num,nameInput,ageIDInput,phoneInput,poshealthInput,dayInput,monthInput,yearInput);
            }
            fi.close();
            MENU();
        }
        //Lưu dữ liệu vào file
        void saveData() {
            fo.open("data_BN.c19", ios::out);
            for (int i = 0; i < countPatient; ++i) {
                fo << p.bn[i].num << endl;
                fo << "0" << p.bn[i].name << endl;
                fo << p.bn[i].ageid << endl;
                fo << p.bn[i].phone << endl;
                fo << p.bn[i].poshealth << endl;
                fo << p.bn[i].schedule.day << ' ' << p.bn[i].schedule.month << ' ' << p.bn[i].schedule.year << endl;
            }

            fo.close();
            fo.open("data_NV.c19", ios::out);
            for (int i = 0; i < countDoctor; ++i) {
                fo << p.nv[i].num << endl;
                fo << "0" << p.bn[i].name << endl;
                fo << p.nv[i].ageid << endl;
                fo << p.nv[i].phone << endl;
                fo << p.nv[i].poshealth << endl;
                fo << p.nv[i].schedule.day << ' ' << p.nv[i].schedule.month << ' ' << p.nv[i].schedule.year << endl;
            }

            fo.close();
        }
        //Giao diện chương trình
        void MENU() {
            system("cls");
            cout <<"==== CHƯƠNG TRÌNH QUẢN LÍ PHÒNG KHÁM NHA KHOA ====" << endl;
            cout <<"1. Quản lý bệnh nhân" << endl;
            cout <<"2. Quản lý nhân viên" << endl;
            cout <<"3. Thoát chương trình " << endl;
            cout <<"==================================================" << endl;
            cout << "Vui lòng chọn thao tác : ";
            cin >> k;
            switch(k) {
            case 1:
                quanLyBN();
                break;
            case 2:
                quanLyNV();
                break;
            case 3:
                saveData();
                system("cls");
                delete [] p.bn;
                cout << "XIN CHÀO VÀ HẸN GẶP LẠI !";
                usleep(1 );
                exit(0);
                break;
            default :
                eraseLines(2);
                cout << "Vui lòng nhập lại !";
                usleep(1);
                MENU();

            }

        }
        //Giao diện quản lí bệnh nhân
        void quanLyBN() {
            system("cls");
            cout <<"==== QUẢN LÝ BỆNH NHÂN ====" << endl;
            cout <<"1. Tạo thông tin bệnh nhân"<< endl;
            cout <<"2. Tìm thông tin bệnh nhân"<< endl;
            cout <<"3. Xoá thông tin bệnh nhân"<< endl;
            cout <<"4. Sửa thông tin bệnh nhân"<< endl;
            cout <<"5. Thống kê bệnh nhân"<< endl;
            cout <<"6. Quay về màn hình chính"<< endl;
            cout <<"==========================="<<endl;
            cout << "Vui lòng chọn thao tác : ";
            cin >> k;
            switch(k) {
            case 1:
                system("cls");
                p.createInfor(p.bn,countPatient, "BỆNH NHÂN");
                saveData();
                quanLyBN();
                break;
            case 2:
                system("cls");
                p.findInfor(0);
                cout << "Vui lòng chọn thao tác : ";
                cin >> k;
                //======================
                if (k == 1) {
                    system("cls");
                        cout << "========= THÔNG TIN BỆNH NHÂN THEO TÊN =========" << endl;
                        cout << "Nhập tên bệnh nhân cần tìm : " << endl;
                        cout << "================================================" << endl;
                        cout << "\x1b[2A";
                        cout << "\x1b[29C";
                        cin.ignore();
                        getline(cin,findName);
                        system("cls");
                        p.findInforName(findName,countPatient,p.bn,"BỆNH NHÂN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyBN();
                                break;
                            } else eraseLines(2);
                        }
                }
                if (k == 2){
                    system("cls");
                        cout << "========= THÔNG TIN BỆNH NHÂN THEO SĐT =========" << endl;
                        cout << "Nhập số điện thoại bệnh nhân cần tìm : " << endl;
                        cout << "================================================" << endl;
                        cout << "\x1b[2A";
                        cout << "\x1b[39C";
                        cin.ignore();
                        getline(cin,findPhone);
                        system("cls");
                        p.findInforPhone(findPhone,countPatient,p.bn,"BỆNH NHÂN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyBN();
                                break;
                            } else eraseLines(2);
                        }
                    }
                //======================
                break;
            case 3:
                system("cls");
                p.deleteInfor(p.bn,countPatient,"BỆNH NHÂN");
                saveData();
                quanLyBN();
                break;
            case 4 :
                system("cls");
                p.editInfor(p.bn,countPatient,"BỆNH NHÂN");
                saveData();
                quanLyBN();
                break;
            case 5 :
                system("cls");
                p.statisticInfor("BỆNH NHÂN");
                cout << "Vui lòng chọn thao tác : ";
                cin >> k;
                //======================
                if (k == 1) {
                    system("cls");
                        p.statisticInforAll(p.bn,countPatient,"BỆNH NHÂN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyBN();
                                break;
                            } else eraseLines(2);
                        }
                }
                if (k == 2){
                    system("cls");
                        p.statisticDate(p.bn,countPatient,"BỆNH NHÂN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyBN();
                                break;
                            } else eraseLines(2);
                        }
                }
                break;
            case 6 :
                MENU();
                break;
            default :
                eraseLines(2);
                cout << "Vui lòng nhập lại !";
                usleep(1);
                quanLyBN();
            }
        }
        //Giao diện quản lí nhân viên
        void quanLyNV() {
            system("cls");
            cout <<"==== QUẢN LÝ NHÂN VIÊN ====" << endl;
            cout <<"1. Tạo thông tin nhân viên"<< endl;
            cout <<"2. Tìm thông tin nhân viên"<< endl;
            cout <<"3. Xoá thông tin nhân viên"<< endl;
            cout <<"4. Sửa thông tin nhân viên"<< endl;
            cout <<"5. Thống kê số lượng nhân viên"<< endl;
            cout <<"6. Quay về màn hình chính"<< endl;
            cout <<"==========================="<<endl;
            cout << "Vui lòng chọn thao tác : ";
            cin >> k;
            switch(k) {
            case 1:
                system("cls");
                p.createInfor(p.nv,countDoctor,"NHÂN VIÊN");
                saveData();
                quanLyNV();
                break;
            case 2:
                system("cls");
                p.findInfor(1);
                cout << "Vui lòng chọn thao tác : ";
                cin >> k;
                //======================
                if (k == 1) {
                    system("cls");
                        cout << "========= THÔNG TIN NHÂN VIÊN THEO TÊN =========" << endl;
                        cout << "Nhập tên nhân viên cần tìm : " << endl;
                        cout << "================================================" << endl;
                        cout << "\x1b[2A";
                        cout << "\x1b[29C";
                        cin.ignore();
                        getline(cin,findName);
                        system("cls");
                        p.findInforName(findName,countDoctor,p.nv,"NHÂN VIÊN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyNV();
                                break;
                            } else eraseLines(2);
                        }
                }
                if (k == 2){
                    system("cls");
                        cout << "========= THÔNG TIN NHÂN VIÊN THEO SĐT =========" << endl;
                        cout << "Nhập số điện thoại nhân viên cần tìm : " << endl;
                        cout << "================================================" << endl;
                        cout << "\x1b[2A";
                        cout << "\x1b[39C";
                        cin.ignore();
                        getline(cin,findPhone);
                        system("cls");
                        p.findInforPhone(findPhone,countDoctor,p.nv,"NHÂN VIÊN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyNV();
                                break;
                            } else eraseLines(2);
                        }
                    }
                //======================
                break;
            case 3:
                system("cls");
                p.deleteInfor(p.nv,countDoctor,"NHÂN VIÊN");
                saveData();
                quanLyNV();
                break;
            case 4 :
                system("cls");
                p.editInfor(p.nv,countDoctor,"NHÂN VIÊN");
                saveData();
                quanLyNV();
                break;
            case 5 :
                system("cls");
                p.statisticInfor("NHÂN VIÊN");
                cout << "Vui lòng chọn thao tác : ";
                cin >> k;
                //======================
                if (k == 1) {
                    system("cls");
                        p.statisticInforAll(p.nv,countDoctor,"NHÂN VIÊN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyNV();
                                break;
                            } else eraseLines(2);
                        }
                }
                if (k == 2){
                    system("cls");
                        p.statisticDate(p.nv,countDoctor,"NHÂN VIÊN");
                        c = '\0';
                        while (c != 'Y' && c != 'y') {
                            cout << "Ấn Y để quay về : " ;
                            cin >> c;
                            if (c == 'Y' || c == 'y') {
                                system("cls");
                                quanLyNV();
                                break;
                            } else eraseLines(2);
                        }
                }
                break;
            case 6 :
                MENU();
                break;
            default :
                eraseLines(2);
                cout << "Vui lòng nhập lại !";
                usleep(1 );
                quanLyNV();
            }
        }
};
int main() {
    SetConsoleOutputCP(65001); // Sử dụng font UTF-8
    Chuongtrinh Nhakhoa;
    int dem = 0;
    while (dem <= 3) {
        string user,pass;
        cout << "========= ĐĂNG NHẬP =========" << endl;
        cout << "Tài khoản : " << endl;
        cout << "Mật khẩu : " << endl;
        cout << "=============================" << endl;
        cout << "\x1b[3A"; //Di chuyển con trỏ lên 3 dòng
        cout << "\x1b[12C"; // Di chuyển con trỏ sang phải 12 ký tự
        getline(cin,user);
        cout << "\x1b[11C"; //Di chuyển con trỏ sang phải 11 ký tự
        getline(cin,pass);
        cout << "\x1b[1B"; //Di chuyển con trỏ xuống 1 dòng
        cout << "Vui lòng đợi...";
        usleep(1);
        eraseLines(1); //Xóa 1 dòng
        if (dem >= 3) {
            cout <<"Bạn đã nhập sai quá 3 lần !";
            return 0;
        }
        if (user == "admin" && pass == "admin") {
            cout << "Đăng nhập thành công !";
            usleep(1); //Chờ 1 giây
            break;
        } else {
            cout << "Bạn đã nhập sai, vui lòng nhập lại !";
            dem++;
            usleep(2); //Chờ 2 giây
            system("cls");
        }
    }
    //Chương trình chính
    Nhakhoa.loadData();
    return 0;
}
