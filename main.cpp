#include <bits/stdc++.h>
using namespace std;

class Date {
    int _year, _month, _day;
    static bool isLeap(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
    static int monthDays(int y, int m) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2) return isLeap(y) ? 29 : 28;
        return mdays[m];
    }
    static bool valid(int y, int m, int d) {
        if (y < 1900 || y > 2030) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > monthDays(y,m)) return false;
        return true;
    }
    // days since 1900-01-01
    static long long toOrdinal(int y, int m, int d) {
        long long days = 0;
        for (int yr = 1900; yr < y; ++yr) days += isLeap(yr) ? 366 : 365;
        for (int mo = 1; mo < m; ++mo) days += monthDays(y, mo);
        days += d - 1; // 1900-01-01 -> 0
        return days;
    }
    static void fromOrdinal(long long ord, int &y, int &m, int &d) {
        y = 1900;
        while (true) {
            int yearDays = isLeap(y) ? 366 : 365;
            if (ord >= yearDays) { ord -= yearDays; ++y; }
            else break;
        }
        m = 1;
        while (true) {
            int md = monthDays(y, m);
            if (ord >= md) { ord -= md; ++m; }
            else break;
        }
        d = (int)ord + 1;
    }
    static long long maxOrdinal() {
        return toOrdinal(2030, 12, 31);
    }


public:
    Date() : _year(1900), _month(1), _day(1) {}
    Date(int y, int m, int d) {
        if (valid(y,m,d)) { _year=y; _month=m; _day=d; }
        else { _year=1900; _month=1; _day=1; }
    }
    // pre-increment
    Date& operator++() {
        long long ord = toOrdinal(_year,_month,_day) + 1;
        if (ord > maxOrdinal()) ord = maxOrdinal();
        fromOrdinal(ord,_year,_month,_day);
        return *this;
    }
    // post-increment
    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }
    // pre-decrement
    Date& operator--() {
        long long ord = toOrdinal(_year,_month,_day) - 1;
        if (ord < 0) ord = 0;
        fromOrdinal(ord,_year,_month,_day);
        return *this;
    }
    // post-decrement
    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }
    Date operator+(int days) const {
        long long ord = toOrdinal(_year,_month,_day) + days;
        if (ord > maxOrdinal()) ord = maxOrdinal();
        if (ord < 0) ord = 0;
        int y,m,d; fromOrdinal(ord,y,m,d);
        return Date(y,m,d);
    }
    Date operator-(int days) const {
        long long ord = toOrdinal(_year,_month,_day) - days;
        if (ord > maxOrdinal()) ord = maxOrdinal();
        if (ord < 0) ord = 0;
        int y,m,d; fromOrdinal(ord,y,m,d);
        return Date(y,m,d);
    }
    long long operator-(const Date& other) const {
        long long a = toOrdinal(_year,_month,_day);
        long long b = toOrdinal(other._year, other._month, other._day);
        return llabs(a - b);
    }
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt._year << '-' << dt._month << '-' << dt._day;
        return os;
    }
    // optional out() for compatibility
    void out() const { cout << _year << '-' << _month << '-' << _day << '\n'; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int op; if(!(cin>>op)) return 0;
    int yy,mm,dd;
    if(op==1||op==0){
        Date d0; Date d1(2000,2,29); Date d2(1900,2,29);
        cout<<d0<<"\n"<<d1<<"\n"<<d2<<"\n";
    }
    if(op==2||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<"\n";
        for(int i=0;i<5;++i) cout<<d0++<<"\n";
        for(int i=0;i<5;++i) cout<<d0--<<"\n";
        for(int i=0;i<2;++i) cout<<--d0<<"\n";
        cout<<d0<<"\n";
    }
    if(op==3||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        cout<<d0+100<<"\n";
        cout<<d0-1000<<"\n";
    }
    if(op==4||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1)<<"\n";
    }
    if(op==5||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<d0-d1<<"\n";
    }
    return 0;
}
