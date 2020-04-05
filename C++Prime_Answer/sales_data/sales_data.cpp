#include <iostream>
#include <string>

using namespace std;

class Sales_data
{
    friend istream& operator >> (istream& ,Sales_data&);//这里的istream为什么后有一个&，这个如果是作用在operator上面那&operator怎么理解？？？
    friend ostream& operator << (ostream& ,const Sales_data&);
    friend bool operator < (const Sales_data& , const Sales_data&);
    friend bool operator == (const Sales_data& lhs, const Sales_data& rhs);

public:
    Sales_data() = default;
    Sales_data(const string &book):bookNo(book){}
    Sales_data(istream &is){ is >> *this;} //此句的*this怎么理解？？？//貌似是拷贝构造函数

public:
    Sales_data& operator += (const Sales_data&);
    string isbn() const {return bookNo;}//定义一个常成员函数

private:
    string bookNo;//书籍编号
    unsigned units_sold = 0;//销售量
    double sellingprice = 0.0;//原始价格
    double saleprice = 0.0;//实售价格
    double discount = 0.0;//折扣
};

inline bool  compareIsbn(const Sales_data &lhs,const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

Sales_data operator + (const Sales_data& );

inline bool operator  == (const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.units_sold == rhs.units_sold &&
           lhs.sellingprice == rhs.sellingprice &&
           lhs.saleprice == rhs.saleprice &&
           lhs.isbn() == rhs.isbn();
}

inline bool operator != (const Sales_data& lhs , const Sales_data& rhs)
{
    return !(lhs == rhs);//基于原有的== 定义自己的 ！= 符号
}

Sales_data& Sales_data::operator += (const Sales_data& rhs)
{
    units_sold += rhs.units_sold;//此处为什么可以直接操作成员变量？？此时的成员变量不会是其他不知道的用过的值吗？？
    saleprice = (rhs.saleprice * rhs.units_sold + saleprice * units_sold) / (rhs.units_sold + units_sold);
    if (sellingprice != 0)
    {
        discount = saleprice / sellingprice;
    }
    return *this;
}

Sales_data operator + (const Sales_data& lhs,const Sales_data& rhs)
{
    Sales_data ret(lhs);//将lhs拷贝到临时变量ret中，有利于运算
    ret += rhs;
    return ret ;
}

std::istream& operator >> (std::istream& in , Sales_data &s )
{
    in >> s.bookNo >> s.units_sold >> s.sellingprice >> s.saleprice;
    if (in && s.sellingprice != 0)
        s.discount = s.saleprice / s.sellingprice;
    else
        s = Sales_data();//输入错误所以重置输入数据
    return in;
}

std::ostream& operator << (std::ostream &out , const Sales_data &s)
{
    out << s.isbn() << " " << s.units_sold << " " << s.sellingprice << " " << s.saleprice << " " << s.discount << endl;
    return out ;
}
int main()
{
    Sales_data book;
    std::cout << "请输入销售记录：" <<std::endl;//为什么此处不打std::就不能使用cout呢？build的时候就被卡住不动。
    while (std::cin >> book )
    {
        std::cout << "ISBN、售出本数、原始价格、实售价格、折扣为 ： " << book <<std::endl;
    }

}
