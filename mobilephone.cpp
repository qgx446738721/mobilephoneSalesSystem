/*************************************************************************
    * File Name: mobilephone.cpp
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Created Time: 2013年09月08日 星期日 17时55分41秒
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool JudgeTimeWrong(int time)//判断时间是否合法
{
    int year, month, day;
    year = time / 10000;
    month = (time % 10000) /100;
    day = time % 100;
    if (year >= 1000 && year <= 3000 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
        return false;
    else
    {
        cout << "日期错误！" <<endl;
        return true;
    }
}

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
    mobilephone Change();//修改
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
    friend istream& operator>>(istream &,mobilephone &);//重载输入运算符
	friend ostream& operator<<(ostream &,mobilephone &);//重载输出运算符
};

class Profit//利润类
{
private:
    string name;
    double pro;//利润
public:
    Profit() {name = ""; pro = 0.0;}
    Profit(string str,double p)
	{
		name=str,p=pro;
	}
	void Outputs(int i)
	{
		cout << setiosflags(ios::left) << setw(10) << name << setw(10) << pro << setw(5) << i << endl;
		cout << resetiosflags(ios::left);
	}
	bool operator<(const Profit &v)const
	{
		return pro>v.pro;
	}
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
         << setw(4) << inTime/10000 << '-' << (inTime%10000)/100 << '-' << setw(4) <<inTime%100;
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
	do
	{
        cout << "请输入入库时间(例如：20130908)" << endl;
        cin >> inTime;
	} while (JudgeTimeWrong(inTime));
	cout << "请输入进价" << endl;
	cin >> inPrice;
	cout << "是否销售 0（否）/非零（是）" <<endl;
	cin >> sell;
	if (sell)
	{
		cout << "请输出销售价格" << endl;
		cin >> outPrice;
		cout << "请输销售时间" << endl;
        cin >> outTime;
	}
	return *this;
}

mobilephone mobilephone::Change()//修改
{
    string strTemp;
    int intTemp;
    double douTemp;
    cout << "请输入编号" << endl;
	cin >> id;
	cout << "请输入厂商,“...”代表跳过此项" << endl;
	cin>> strTemp;
	if (strTemp != "...")
        company = strTemp;
	cout << "请输入型号,“...”代表跳过此项" << endl;
	cin>> strTemp;
	if (strTemp != "...")
        model = strTemp;
    do
    {
        cout << "请输入入库时间(例如：20130908),“0”代表跳过此项" << endl;
        cin >> intTemp;
        if (intTemp != 0)
            inTime = intTemp;
        else
            break;
    } while(JudgeTimeWrong(inTime));
	cout << "请输入进价,“0”代表跳过此项" << endl;
	cin >> douTemp;
	if (douTemp != 0)
        inPrice = douTemp;
	cout << "是否销售 0（否）/非零（是）" <<endl;
	cin >> sell;
	if (sell)
	{
		cout << "请输出销售价格,“0”代表跳过此项" << endl;
		cin >> douTemp;
        if (douTemp != 0)
            outPrice = douTemp;
		cout << "请输销售时间(用空格分开),“0”代表跳过此项" << endl;
        cin >> intTemp;
        if (intTemp != 0)
            outTime = intTemp;
	}
	return *this;
}
istream& operator>>(istream &in,mobilephone &v)//重载输入运算符
{
	in >> v.id;
	in >> v.company;
	in >> v.model;
	in >> v.inTime;
	in >> v.inPrice;
	in >> v.outPrice;
	in >> v.outTime;
	in >> v.sell;
	return in;
}

ostream& operator <<(ostream &out,mobilephone &v)//重载输出运算符
{
	out << v.id << endl;
	out << v.company << endl;
	out << v.model << endl;
	out << v.inTime << endl;
	out << v.inPrice << endl;
	out << v.outPrice << endl;
	out << v.outTime << endl;
	out << v.sell << endl;
	return out;
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
	//phone &v=*p;
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

void FindMobilephone(string &c, string &m)//查询,手机厂商和型号
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
    c = com;
    m = mo;
}

bool ChangeMobilephoneMessage()//修改手机信息,修改成功返回true,失败返回false
{
    string c, m;
    FindMobilephone(c,m);
    string ID;
    cout << "输入手机的编号：";
    cin >> ID;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID && ite->getCompany() == c && ite->getModel() == m)
        {
            cout << "输入修改后的手机信息" << endl;
            ite->Change();
            return true;
        }
    }
    return false;
}

bool DeleteMobilephone()//删除手机,修改成功返回true,失败返回false
{
    string c ,m;
    FindMobilephone(c,m);
    string ID;
    cout << "输入手机的编号：";
    cin >> ID;
    bool del = false;
    vector<mobilephone>::iterator ite;
    for (ite = mobile.begin(); ite != mobile.end(); ite++)
    {
        if (ite->getId() == ID)
        {
            cout << "是否删除该手机?(y/n)";
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                mobile.erase(ite);//删除手机信息
                del = true;
                break;
            }
            else
            {
                cout << "取消操作！" << endl;
                return false;
            }
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
    string c,m;
    FindMobilephone(c,m);
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
               int time;
               do
               {
                   cout << "输入销售日期：";
                   cin >> time;
               } while (JudgeTimeWrong(time));
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
    string c,m;
    FindMobilephone(c,m);
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
    string c,m;
    FindMobilephone(c,m);
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
               cout << "输入修改后销售价格 “0代表跳过此项”:";
               double price;
               cin >> price;
               if (price != 0)
                    ite->setOutPrice(price);
                int time;
                do
                {
                   cout << "输入修改后销售日期“0代表跳过此项”:";
                   cin >> time;
                   if (time != 0)
                        ite->setOutTime(time);
                    else
                        break;
                } while (JudgeTimeWrong(ite->getOutTime()));
               return true;
            }
        }
    }
    return false;
}

void QueryMobilephone()//根据条件查询
{
    cout << endl;
    cout << "手机信息查询" << endl;
    cout<<"请选择数字标号"<<endl;
	cout<<"1)按价格"<<endl;
	cout<<"2)按型号"<<endl;
	cout<<"3)按厂商"<<endl;
	cout<<"4)按库存数量"<<endl;
    cout<<"5)显示所有手机记录"<< endl;
	cout<<"0)退出"<<endl;
    int chance;
    double lPrice, rPrice;//价格区间
    vector<mobilephone>::iterator ite;
    cin >> chance;
    switch(chance)
    {
    case 0:break;
    case 1:
        {
            /*按价格查询*/
            cout << "输入价格区间(以空格分割):" << endl;
            cin >> lPrice >> rPrice;
            cout << setiosflags(ios::left);
			cout << setw(20) << setfill(' ') << "编号" << setw(10) << "厂商"
                << setw(10) << "型号" << setw(10) << "进价"
                << setw(10) << "进货时间" << setw(10) << "出售价"
                << setw(10) << "出售时间" << endl;
			cout<<resetiosflags(ios::left);
			for(ite = mobile.begin(); ite != mobile.end(); ite++)
			{
				if (ite->getInPrice() >= lPrice && ite->getInPrice() < rPrice)
				{
					ite->Output();
				}
			}
            break;
        }
    case 2:
        {
            /*按型号查询*/
            cout << "输入手机型号：" << endl;
            string m;
            cin >> m;
            cout << setiosflags(ios::left);
			cout << setw(20) << setfill(' ') << "编号" << setw(10) << "厂商"
                << setw(10) << "型号" << setw(10) << "进价"
                << setw(10) << "进货时间" << setw(10) << "出售价"
                << setw(10) << "出售时间" << endl;
			cout<<resetiosflags(ios::left);
            for (ite = mobile.begin(); ite != mobile.end(); ite++)
            {
                if (ite->getModel() == m)
                {
                    ite->Output();
                }
            }
            break;
        }
    case 3:
        {
            /*按厂商查询*/
            cout << "输入手机厂商：" << endl;
            string m;
            cin >> m;
            cout << setiosflags(ios::left);
			cout << setw(20) << setfill(' ') << "编号" << setw(10) << "厂商"
                << setw(10) << "型号" << setw(10) << "进价"
                << setw(10) << "进货时间" << setw(10) << "出售价"
                << setw(10) << "出售时间" << endl;
			cout<<resetiosflags(ios::left);
            for (ite = mobile.begin(); ite != mobile.end(); ite++)
            {
                if (ite->getCompany() == m)
                {
                    ite->Output();
                }
            }
            break;
        }
    case 4:
        {
            /*按库存量查询*/
            cout << "输入库存量范围（空格分割）";
            int lNum, rNum;
            cin >> lNum >> rNum;
            /*统计库存量*/
            map<string,int>temp;
            vector<mobilephone>::iterator ite;
            for (ite = mobile.begin(); ite != mobile.end(); ite++)
            {
                temp[ite->getModel()]++;
            }
            /*在范围内查找*/
            cout<<setiosflags(ios::left);
            cout<<setw(10)<<"型号"<<setw(10)<<"库存量"<<endl;
            map<string,int>::iterator ite2;
            for (ite2 = temp.begin(); ite2 != temp.end(); ite2++)
            {
                if (ite2->second >= lNum && ite2->second <= rNum)
                {
                    cout << setw(10) << ite2->first << setw(10) << ite2->second << endl;
                }
            }
            cout<<resetiosflags(ios::left);
            break;
        }
    case 5:
        {
            vector<mobilephone>::iterator ite;
            cout << "所有手机信息显示" <<endl;
            cout << setiosflags(ios::left);
            cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(10)<<"进货时间"<<setw(10)<<"出售价"<<setw(10)<<"出售时间"<<endl;
            for (ite = mobile.begin(); ite != mobile.end(); ite++)
            {
                    ite->Output();
            }
            cout << endl;
            cout << resetiosflags(ios::left);
            break;
        }
    default:
        {
            QueryMobilephone();
            cin.clear();//清除输入流的错误状态
            cin.ignore();//读取输入流中下一个字符并丢弃之
            break;
        }
    }
}

void sellOutModeleProfit()//各类手机的销售利润统计
{
    map<string,double>temp;//model到profit的映射
    vector<mobilephone>::iterator ite;
    for (ite = sell.begin(); ite != sell.end(); ite++)
    {
        temp[ite->getModel()] += ite->getOutPrice() - ite->getInPrice();
    }
    map<string,double>::iterator ite2;
	vector<Profit>pro;//利润容器
    for (ite2 = temp.begin(); ite2 != temp.end(); ite2++)
    {
        pro.push_back(Profit(ite2->first,ite2->second));//将利润放入容器
    }
	sort(pro.begin(),pro.end());//排序
	int len=pro.size();
	cout << setiosflags(ios::left) << setw(10)<<"型号" << setw(10)<<"利润" << setw(5) << "排名" << endl;
	cout << resetiosflags(ios::left);
	for(int i = 0; i < len; i++)
	{
		pro[i].Outputs(i+1);
	}
}

void sellOutCompanyProfit()//各类产商的手机销售利润统计
{
    map<string,double>temp;//company到profit的映射
	vector<mobilephone>::iterator ite;
	for(ite = sell.begin(); ite != sell.end(); ite++)
	{
		temp[ite->getCompany()] += ite->getOutPrice() - ite->getInPrice();
	}
	map<string,double>::iterator ite2;
	vector<Profit>pro;
	for(ite2 = temp.begin(); ite2 != temp.end(); ite2++)
	{
		pro.push_back(Profit(ite2->first,ite2->second));//将利润放入容器
	}
	sort(pro.begin(),pro.end());//排序
	int len=pro.size();
	cout << setiosflags(ios::left) << setw(10) << "厂商" << setw(10) << "利润" << setw(5) << "排名" << endl;
	cout << resetiosflags(ios::left);
	for(int i = 0; i < len; i++)
	{
		pro[i].Outputs(i+1);
	}
}

void SalesStatistics()//销售信息统计
{
    cout << "请选择数字标号：" << endl;
    cout << " 1)某一时间段内某一型号的手机销售数量" << endl;
    cout << " 2)某一时间段内某一型号的手机利润" << endl;
    cout << " 3)某一时间段内的销售总利润" << endl;
    cout << " 4)各类手机的销售利润统计" << endl;
    cout << " 5)各类产商的手机销售利润统计" << endl;
    cout << " 6)手机在各个时间段的销售情况统计" << endl;
    cout << " 7)显示所有销售记录" << endl;
    cout << " 0)退出" << endl;
    int chance;
    int lTime, rTime;//时间段
    cin >> chance;
    switch(chance)
    {
    case 1:
        {
            /*某一时间段内某一型号的手机销售数量*/
            string company, model;//手机厂商和型号
            int num = 0;//销售数量
            cout << "输入时间段（空格分割）";
            cin >> lTime >> rTime;
            cout << "输入手机厂商，型号：";
            cin >> company >> model;
            vector<mobilephone>::iterator ite;
            for (ite = sell.begin(); ite != sell.end(); ite++)
            {
                if (ite->getCompany() == company && ite->getModel() == model
                        && ite->getOutTime() >= lTime && ite->getOutTime() <= rTime)
                    num++;
            }
            cout << "在" << lTime << "与" << rTime << "之间," << company << model << "销售量为" << num << endl;
            break;
        }
    case 2:
        {
            /*某一时间段内某一型号的手机利润*/
            string company, model;//手机厂商和型号
            double money = 0.0;//利润
            cout << "输入时间段（空格分割）";
            cin >> lTime >> rTime;
            cout << "输入手机厂商，型号：";
            cin >> company >> model;
            vector<mobilephone>::iterator ite;
            for (ite = sell.begin(); ite != sell.end(); ite++)
            {
                if (ite->getCompany() == company && ite->getModel() == model
                        && ite->getOutTime() >= lTime && ite->getOutTime() <= rTime)
                {
                    money += ite->getOutPrice() - ite->getInPrice();
                }
            }
            cout << "在" << lTime << "与" << rTime << "之间," << company << model << "利润为" << money << endl;

            break;
        }
    case 3:
        {
            /*某一时间段内的销售总利润*/
            double money = 0.0;//利润
            cout << "输入时间段（空格分割）";
            cin >> lTime >> rTime;
            vector<mobilephone>::iterator ite;
            for (ite = sell.begin(); ite != sell.end(); ite++)
            {
                if (ite->getOutTime() >= lTime && ite->getOutTime() <= rTime)
                {
                    money += ite->getOutPrice() - ite->getInPrice();
                }
            }
            cout << "在" << lTime << "与" << rTime << "之间," <<  "销售利润为" << money << endl;

            break;
        }
    case 4:
        {
            /*各类手机的销售利润统计*/
            sellOutModeleProfit();
            break;
        }
    case 5:
        {
            /*各类产商的手机销售利润统计*/
            sellOutCompanyProfit();
            break;
        }
    case 6:
        {
            /*手机在各个时间段的销售情况统计*/
            cout << "输入时间段（空格分割）";
            cin >> lTime >> rTime;
            map<string,int>temp;
            vector<mobilephone>::iterator ite;
            for (ite = sell.begin(); ite != sell.end(); ite++)
            {
                if (ite->getOutTime() >= lTime && ite->getOutTime() <= rTime)
                {
                    temp[ite->getModel()]++;
                }
            }
            cout << setiosflags(ios::left);
            cout << setw(10) << "类型" << setw(10) << "销售量" <<endl;
            map<string,int>::iterator ite2;
            for(ite2 = temp.begin(); ite2 != temp.end(); ite2++)
            {
                cout << setw(10) << ite2->first << setw(10) << ite2->second <<endl;
            }
            break;
        }
    case 7:
        {
            vector<mobilephone>::iterator ite;
            cout << setiosflags(ios::left) << setfill(' ');
            for (ite = sell.begin(); ite != sell.end(); ite++)
            {
                cout << setw(10) << ite->getId() << setw(10) << ite->getCompany() << setw(10) << ite->getModel()
                    << setw(10) << ite->getOutPrice()
                    << setw(4) << ite->getOutTime()/10000 << '-' << (ite->getOutTime()%10000)/100 << '-' << ite->getOutTime()%100 <<endl;
            }
            cout << resetiosflags(ios::left);
        }
    case 0:
        {
            /*退出*/
            break;
        }
    default:
        {
            cout << "选择错误！" << endl;
            cin.clear();//清除输入流的错误状态
            cin.ignore();//读取输入流中下一个字符并丢弃之
            SalesStatistics();
        }
    }
}

void ReadFile()//读取文件到内存中
{
	ifstream inFile;
	inFile.open("mobile.txt",ios::in);
	if (inFile.fail())
	{
		cout << "没有手机文件信息" << endl;
	}
	else
	{
		mobilephone temp;
		inFile >> temp;
		while (!inFile.eof())
		{
			mobile.push_back(temp);
			inFile >> temp;
		}
	}
	ifstream inFile2;
	inFile2.open("sell.txt",ios::in);
	if (inFile2.fail())
	{
		cout<<"没有销售文件信息"<<endl;
	}
    else
    {
        mobilephone temp;
        inFile2 >> temp;
        while (!inFile2.eof())
        {
            sell.push_back(temp);
            inFile2 >> temp;
        }
    }
}

void WriteFile()//写入内存中的数据到文件
{
    ofstream outFile;
	outFile.open("mobile.txt",ios::out);
	if (outFile.fail())
	{
		cout<<"文件读取失败，无法存入手机信息文件!"<<endl;
	}
	else
	{
		vector<mobilephone>::iterator ite;
		for(ite = mobile.begin(); ite != mobile.end(); ite++)
		{
			outFile << *ite;
		}
	}
	ofstream outFile2;
	outFile2.open("sell.txt",ios::out);
	if (outFile2.fail())
	{
		cout<<"文件读取失败，无法存入销售信息文件"<<endl;
	}
    else
    {
        vector<mobilephone>::iterator ite;
        for(ite = sell.begin(); ite != sell.end(); ite++)
        {
            outFile2 << *ite;
        }
    }
}

void menu()
{
    while(true)
    {
        cout << "|**********手机销售管理系统V1.0**********|" << endl;
        cout << "1> 添加手机信息" << endl;
        cout << "2> 修改手机信息" << endl;
        cout << "3> 删除手机信息" << endl;
        cout << "4> 添加销售列表" << endl;
        cout << "5> 修改销售列表" << endl;
        cout << "6> 删除销售列表" << endl;
        cout << "7> 手机信息查询" << endl;
        cout << "8> 销售信息统计" << endl;
        cout << "0> 退出系统" << endl;
        cout << "输入选择项的编号：";
        int chance;
        cin >> chance;
        switch(chance)
        {
        case 1:
            {
                AddMobilephone();
                break;
            }
        case 2:
            {
                ChangeMobilephoneMessage();
                break;
            }
        case 3:
            {
                DeleteMobilephone();
                break;
            }
        case 4:
            {
                AddSalesList();
                break;
            }
        case 5:
            {
                ChangeSalesList();
                break;
            }
        case 6:
            {
                DeleteSalesList();
                break;
            }
        case 7:
            {
                QueryMobilephone();
                break;
            }
        case 8:
            {
                SalesStatistics();
                break;
            }
        case 0:
            {
                WriteFile();
                exit(0);
            }
        default:
            {
                cout << "输入错误!" << endl;
                //清空缓存区
                //std::cin.clear();
                cin.clear();//清除输入流的错误状态
                cin.ignore();//读取输入流中下一个字符并丢弃之
                menu();
            }
        }
    }
}

int main()
{
    ReadFile();
    menu();
    //WriteFile();
    return 0;
}
