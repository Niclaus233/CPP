#include <iostream>
#include <string>

using namespace std;

class Sales_data
{
    friend istream& operator >> (istream& ,Sales_data&);//�����istreamΪʲô����һ��&����������������operator������&operator��ô��⣿����
    friend ostream& operator << (ostream& ,const Sales_data&);
    friend bool operator < (const Sales_data& , const Sales_data&);
    friend bool operator == (const Sales_data& lhs, const Sales_data& rhs);

public:
    Sales_data() = default;
    Sales_data(const string &book):bookNo(book){}
    Sales_data(istream &is){ is >> *this;} //�˾��*this��ô��⣿����//ò���ǿ������캯��

public:
    Sales_data& operator += (const Sales_data&);
    string isbn() const {return bookNo;}//����һ������Ա����

private:
    string bookNo;//�鼮���
    unsigned units_sold = 0;//������
    double sellingprice = 0.0;//ԭʼ�۸�
    double saleprice = 0.0;//ʵ�ۼ۸�
    double discount = 0.0;//�ۿ�
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
    return !(lhs == rhs);//����ԭ�е�== �����Լ��� ��= ����
}

Sales_data& Sales_data::operator += (const Sales_data& rhs)
{
    units_sold += rhs.units_sold;//�˴�Ϊʲô����ֱ�Ӳ�����Ա����������ʱ�ĳ�Ա����������������֪�����ù���ֵ�𣿣�
    saleprice = (rhs.saleprice * rhs.units_sold + saleprice * units_sold) / (rhs.units_sold + units_sold);
    if (sellingprice != 0)
    {
        discount = saleprice / sellingprice;
    }
    return *this;
}

Sales_data operator + (const Sales_data& lhs,const Sales_data& rhs)
{
    Sales_data ret(lhs);//��lhs��������ʱ����ret�У�����������
    ret += rhs;
    return ret ;
}

std::istream& operator >> (std::istream& in , Sales_data &s )
{
    in >> s.bookNo >> s.units_sold >> s.sellingprice >> s.saleprice;
    if (in && s.sellingprice != 0)
        s.discount = s.saleprice / s.sellingprice;
    else
        s = Sales_data();//�����������������������
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
    std::cout << "���������ۼ�¼��" <<std::endl;//Ϊʲô�˴�����std::�Ͳ���ʹ��cout�أ�build��ʱ��ͱ���ס������
    while (std::cin >> book )
    {
        std::cout << "ISBN���۳�������ԭʼ�۸�ʵ�ۼ۸��ۿ�Ϊ �� " << book <<std::endl;
    }

}
