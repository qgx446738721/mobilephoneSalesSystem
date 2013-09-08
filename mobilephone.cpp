/*************************************************************************
    * File Name: mobilephone.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月08日 星期日 17时55分41秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class phone
{
protected:
    string company;//厂商
    string model;//型号
    double inPrice;//进价
public:
   void  setCompany(string c) { company = c; }
   void  setModel(string m) { model = m; }
   void  setInPrice(double in) {inPrice = in; }
   string getCompany() { return company; }
   string getModel() { return model; }
   double getInPrice() { return inPrice; }
};

class mobilephone : public phone
{
private:
    string id;//编号
    int inTime;//入库时间
    double outPrice;//出售价格
    int outTime;//出售时间
    bool sell;//是否出售，true为出售,false为未出售
public:
    mobilephone();
    void Output();//输出手机信息
    mobilephone Intput();//输入手机信息
    void setId(string i) {id = i; }
    void setInTime(int i) { inTime = i; }
    void setOutPrice(double o) { outPrice = o; }
    void setOutTime(int o) { outTime = o;}
    void setSell(bool s) { sell = s; }
    string getId() { return id; }
    int getInTime() { return inTime; }
    double getOutPrice() { return outPrice; }
    int getOutTime() { return outTime; }
    bool getSell() { return sell; }
};

mobilephone::mobilephone()//初始化手机
{
    company = model = id = "";
    inPrice = outPrice = 0.0;
    inTime = outTime = 0;
    sell = false;
}

void mobilephone::Output()//输出手机的编号，厂商，型号，进价，入库日期，出售价格，出售日期
{
	cout << setiosflags(ios::left) << setw(20) << setfill(' ') << id;
	cout << setw(10) << company
         << setw(10) << model
         << setw(10) << inPrice
         << setw(4) << inTime/10000 << '-' << (inTime%10000)/100 << '-' << inTime%100;
	if (sell)
	{
		cout << setw(10) << outPrice
             << setw(4) << outTime/10000 << '-' << (outTime%10000)/100 << '-' << outTime%100;
	}
	cout << endl;
	cout << resetiosflags(ios::left);
}

mobilephone mobilephone::Intput()//输入手机信息
{
    cout << "请输入编号" << endl;
	cin >> id;
	cout << "请输入厂商" << endl;
	cin>> company;
	cout << "请输入型号" << endl;
	cin >> model;
	cout << "请输入入库时间(用空格分开)" << endl;
    cin >> inTime;
	cout << "请输入进价" << endl;
	cin >> inPrice;
	cout << "是否销售 0（否）/非零（是）" <<endl;
	cin >> sell;
	if (sell)
	{
		cout << "请输出销售价格" << endl;
		cin >> outPrice;
		cout << "请输销售时间(用空格分开)" << endl;
        cin >> outTime;
	}
	return *this;
}

vector<mobilephone>mobile;//手机数组
vector<mobilephone>sell;//销售数组

void AddMobilephone()//添加手机信息
{
    mobilephone *p = new mobilephone();
    p -> Intput();
    vector<mobilephone>::iterator ite;
	for(ite=mobile.begin(); ite!=mobile.end(); ite++)
	{
		if (p->getId() == ite->getId()  && p->getCompany() == ite->getCompany() && p->getModel() == ite->getModel())//若存在此部手机
		{
			cout<<"手机信息存在，请检查输入"<<endl;
			return;
		}
	}
	phone &v=*p;
    p->setSell(false);
	mobile.push_back(*p);
}

void OutputCompanyAndModel(phone p)//通过厂商和型号进行查找手机
{
    vector<mobilephone>::iterator ite;
	cout<<setiosflags(ios::left);
	cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(10)<<"进货时间"<<setw(10)<<"出售价"<<setw(10)<<"出售时间"<<endl;
	cout<<resetiosflags(ios::left);
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
        if (p.getCompany() == ite->getCompany() && p.getModel() == ite->getModel())//查找到相匹配的手机
		{
			ite->Output();//将查找到的显示出来
		}
	}
}

void FindMobilephone()//查询,手机厂商和型号
{
    phone temp;
    string com, mo;
    cout << "输入手机厂商：";
    cin >> com;
    cout << "输入手机型号";
    cin >> mo;
    temp.setCompany(com);
    temp.setModel(mo);
    OutputCompanyAndModel(temp);//查找匹配厂商型号的手机
}

bool ChangeMobilephoneMessage()//修改手机信息,修改成功返回true,失败返回false
{
    FindMobilephone();
    string ID;
    cout << "输入手机的编号：";
    cin >> ID;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            cout << "输入修改后的手机信息" << endl;
            if (ite->getSell())//修改出售的手机
            {
                mobilephone *p=new mobilephone();
				p->Intput();
                p->setOutPrice(ite->getOutPrice());
                p->setOutTime(ite->getOutTime());
				*ite=*p;
				return true;
            }
            else
            {
                mobilephone *p=new mobilephone();
				p->Intput();
				*ite=*p;
				return true;
            }
        }
    }
    return false;
}

bool DeleteMobilephone()//删除手机,修改成功返回true,失败返回false
{
    FindMobilephone();
    string ID;
    cout << "输入手机的编号：";
    cin >> ID;
    bool del = false;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            mobile.erase(ite);//删除手机信息
            del = true;
            break;
        }
    }
    if (del == true)
    {
        cout << "删除成功！" << endl;
        return true;
    }
    else
    {
        cout << "删除失败，可能原因是没有该部手机！" << endl;
        return false;
    }
}

bool AddSalesList()//添加销售列表
{
    FindMobilephone();
    cout << "输入销售手机编号:";
    string ID;
    cin >> ID;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            cout << "确认销售编号为" << ite->getId() << "的" << ite->getCompany() << ite->getModel() << "手机?";
            cout << "(y/n)";
            char c;
            cin >> c;
            if (c == 'n' || c == 'N')
            {
                return true;
            }
            else if (c == 'y' || c == 'Y')
            {
               cout << "输入销售价格：";
               double price;
               cin >> price;
               ite->setOutPrice(price);
               cout << "输入销售日期：";
               int time;
               cin >> time;
               ite->setOutTime(time);
               ite->setSell(true);
               sell.push_back(*ite);
               return true;
            }
        }
    }
    return false;
}

bool DeleteSalesList()//删除销售列表,删除成功返回true
{
    FindMobilephone();
    cout << "输入销售手机编号:";
    string ID;
    cin >> ID;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            cout << "确认删除编号为" << ite->getId() << "的" << ite->getCompany() << ite->getModel() << "手机?";
            cout << "(y/n)";
            char c;
            cin >> c;
            if (c == 'n' || c == 'N')
            {
                return true;
            }
            else if (c == 'y' || c == 'Y')
            {
               sell.erase(ite);//删除记录
               return true;
            }
        }
    }
    return false;

}

bool ChangeSalesList()//修改销售列表
{
    FindMobilephone();
    cout << "输入销售手机编号:";
    string ID;
    cin >> ID;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            cout << "以下输入修改后的销售记录" << endl;
            if (ite->getSell())
            {
               mobilephone *p = new mobilephone();
               cout << "输入修改后销售价格：";
               double price;
               cin >> price;
               p->setOutPrice(price);
               cout << "输入修改后销售日期：";
               int time;
               cin >> time;
               p->setOutTime(time);
               p->setId(ite->getId());
               p->setCompany(ite->getCompany());
               p->setModel(ite->getModel());
               p->setInPrice(ite->getInPrice());
               p->setInTime(ite->getInTime());
               p->setSell(ite->getSell());
               *ite = *p;
               return true;
            }
        }
    }
    return false;

}

void QueryMobilephone()//根据条件查询
{
    cout<<"请选择数字标号"<<endl;
	cout<<"	1)按价格"<<endl;
	cout<<"	2)按型号"<<endl;
	cout<<"	3)按厂商"<<endl;
	cout<<"	4)按库存数量"<<endl;
	cout<<"	0)退出"<<endl;
    int chance;
    cin >> chance;
    switch(chance)
    {
    case 0:break;
    case 1:
        {
            /*按价格查询*/
            break;
        }
    case 2:
        {
            /*按型号查询*/
            break;
        }
    case 3:
        {
            /*按厂商查询*/
            break;
        }
    case 4:
        {
            /*按库存量查询*/
            break;
        }
    default:
        {
            QueryMobilephone();
            break;
        }
    }
}

void SalesStatistics()//销售信息统计
{

}

void ReadFile()//读取文件到内存中
{

}

void WriteFile()//写入内存中的数据到文件
{

}

int main()
{
    return 0;
}
