********************************************
*项目:手机销售管理系统
*组员：沈伟强 戚耿鑫 张蕾 刘金玲 卢文思
*完成时间：2013-9-12
*********************************************/
#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<map>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<fstream>
using namespace std;

//沈伟强
bool cmp(string a,string b)//判断a是不是b的前缀
{
	int len1=a.size(),len2=b.size();
	if (len1>len2)
	{
		return false;
	}
	for(int i=0;i<len1;i++)
	{
		if (a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
}

//沈伟强
int InputInt(int &v)//整数输入判断
{
	while (scanf("%d",&v)!=1)
	{
		cout<<"输入格式错误"<<endl;
		while (getchar()!='\n');
	}
	return v;
}

//沈伟强
double InputDouble(double &v)//双精度输入判断
{
	while (scanf("%lf",&v)!=1)
	{
		cout<<"输入格式错误"<<endl;
		while(getchar()!='\n');
	}
	return v;
}

//戚耿鑫
int InputTime(int &times)//输入时间判断输入正确性
{
	int tempYear,tempMonth,tempDay;
	cout<<"请输入年份"<<endl;
	while (scanf("%d",&tempYear)!=1||tempYear>=10000)
	{
		cout<<"输入格式错误"<<endl;
		while(getchar()!='\n');//清空缓存区
	}
	cout<<"请输入月份"<<endl;
	while (scanf("%d",&tempMonth)!=1||tempMonth>12)
	{
		cout<<"输入格式错误"<<endl;
		while(getchar()!='\n');//清空缓存区
	}
	cout<<"请输入日"<<endl;
	while (scanf("%d",&tempDay)!=1||tempDay>31)
	{
		cout<<"输入格式错误"<<endl;
		while(getchar()!='\n');//清空缓存区
	}
	if (tempYear||tempDay||tempMonth)
	{
		return times=tempYear*10000+tempMonth*100+tempDay;
	}
	else
	{
	    return times=0;
	}
}

//沈伟强
double InputPrice(double &pri)//输入价格判断正确性
{
	while (scanf("%lf",&pri)!=1)
	{
		cout<<"输入格式错误"<<endl;
		while (getchar()!='\n');
	}
	return pri;
}

//戚耿鑫
struct Father
{
	string company;//生产商
	string type;//型号
	double inPrice;//进价
	//---------------------------------------------//
	bool operator<(const Father &v)const
	{
		return type<v.type;
	}
	void Input()
	{
		cout<<"请输入厂商"<<endl;
		cin>>company;
		cout<<"请输入型号"<<endl;
		cin>>type;
	}
};

//戚耿鑫
struct phone:public Father
{
	//方法
	phone();//默认构造函数
	phone Input();//输入手机信息
	void Output();//输出产品信息
	//friend istream& operator>>(istream &,phone &);//重载输入运算符
	//friend ostream& operator<<(ostream &,phone &);//重载输出运算符
    friend istream & operator>>(istream &in,phone &v)
    {
        in>>v.id;
        in>>v.company;
        in>>v.type;
        in>>v.inTime;
        in>>v.inPrice;
        in>>v.outPrice;
        in>>v.outTime;
        in>>v.selt;
        return in;
    }
    friend ostream & operator <<(ostream &ou,phone &v)
    {
        ou<<v.id<<endl;
        ou<<v.company<<endl;
        ou<<v.type<<endl;
        ou<<v.inTime<<endl;
        ou<<v.inPrice<<endl;
        ou<<v.outPrice<<endl;
        ou<<v.outTime<<endl;
        ou<<v.selt<<endl;
        return ou;
    }
	bool operator<(const phone &v)const
	{
		return (outPrice-inPrice)>(v.outPrice-v.inPrice);
	}
	//------------------------------------------//
	//变量
	string id;//编号
	int inTime;//入库时间
	double outPrice;//出售价格
	int outTime;//出售时间
	bool selt;//是否销售
};

vector<phone>mobile;//手机数组
vector<phone>selt;//销售数组
map<Father,int>type;//手机库存

//戚耿鑫
phone::phone()//默认构造函数，初始化
{
	outTime=inTime=0;
	inPrice=outPrice=0.0;
	id=company=type="";
	selt=false;
}

//戚耿鑫
void phone::Output()//输出编号，厂商，型号，进价，进货时间，出售价，出售时间
{
	cout<<setiosflags(ios::left)<<setw(20)<<setfill(' ')<<id;
	cout<<setw(10)<<company<<setw(10)<<type<<setw(10)<<inPrice<<setw(4)<<inTime/10000<<'-'<<setw(2)<<(inTime%10000)/100<<'-'<<setw(4)<<inTime%100;
	if (selt)
	{
		cout<<setw(10)<<outPrice<<setw(4)<<outTime/10000<<'-'<<setw(2)<<(outTime%10000)/100<<'-'<<setw(4)<<outTime%100;
	}
	cout<<endl;
	cout<<resetiosflags(ios::left);
}

//戚耿鑫
phone phone::Input()
{
	string strTemp;
	double doubleTemp;
	int intTemp;
	cout<<"请输入编号,(输入...表示跳过该选项的输入)"<<endl;
	cin>>strTemp;
	if (strTemp!="..."||strTemp=="。。。")
	{
		id=strTemp;
	}
	cout<<"请输入厂商,(输入...表示跳过该选项的输入)"<<endl;
	cin>>strTemp;
	if (strTemp!="..."||strTemp=="。。。")
	{
		company=strTemp;
	}
	cout<<"请输入型号,(输入...表示跳过该选项的输入)"<<endl;
	cin>>strTemp;
	if (strTemp!="..."||strTemp=="。。。")
	{
		type=strTemp;
	}
	cout<<"请输入入库时间(用空格分开),(0 0 0表示跳过该选项并使用原先数据)"<<endl;
	InputTime(intTemp);
	if (intTemp)
	{
		inTime=intTemp;
	}
	cout<<"请输入进价,-1表示跳过"<<endl;
	InputPrice(doubleTemp);
	if (doubleTemp>=0.0)
	{
		inPrice=doubleTemp;
	}
	cout<<"是否销售 0（否）/非零（是）"<<endl;
	InputInt(intTemp);
	if (intTemp)
	{
		selt=intTemp;
		cout<<"请输出销售价格,-1跳过"<<endl;
		InputPrice(doubleTemp);
		if (doubleTemp>=0.0)
		{
			outPrice=doubleTemp;
		}
		cout<<"请输销售时间(用空格分开),(0 0 0表示跳过)"<<endl;
		InputTime(intTemp);
		if (intTemp)
		{
			outTime=intTemp;
		}
		//waikeung
        vector<phone>::iterator ite;
        for(ite=::selt.begin();ite!=::selt.end();ite++)
        {
            if (ite->id == id && ite->company == company)
            {
                *ite=*this;
                break;
            }
		}
	}
	return *this;
}

//沈伟强
struct Profit
{
	Profit()
	{
		name="";
		pro=0.0;
	}
	Profit(string str,double p)
	{
		name=str,pro=p;
	}
	void Outputs(int ranks)
	{
		cout<<setiosflags(ios::left)<<setw(10)<<name<<setw(10)<<pro<<setw(5)<<ranks<<endl;
		cout<<resetiosflags(ios::left);
	}
	bool operator<(const Profit &v)const
	{
		return pro>v.pro;
	}
	string name;//利润类型名
	double pro;//利润
};

//张蕾
void OutputsFactAndType(Father temp)//按型号和厂商查找
{
	vector<phone>::iterator ite;
	cout<<setiosflags(ios::left);
	cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(12)<<"进货时间"<<setw(10)<<"出售价"<<setw(12)<<"出售时间"<<endl;
	cout<<resetiosflags(ios::left);
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
		if ((cmp(temp.company,ite->company)||temp.company=="..."||temp.company=="。。。")&&(cmp(temp.type,ite->type)||temp.type=="..."||temp.company=="。。。"))
		{
			ite->Output();
		}
	}
}

//卢文思
bool AddPhone()//添加手机信息
{
	phone *p=new phone();
	p->Input();
	vector<phone>::iterator ite;
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
		if (p->id==ite->id&&p->company==ite->company&&p->type==ite->type)
		{
			cout<<"手机信息冲突，请检查输入"<<endl;
			return false;
		}
	}
	Father &v=*p;
	type[v]++;
	p->selt=false;
	mobile.push_back(*p);
	return true;
}

//卢文思
bool ChangePhoneMessage()//改变手机信息
{
	Father temp;
	temp.Input();
	OutputsFactAndType(temp);
	string ID;
	cout<<"请输入手机编号"<<endl;
	cin>>ID;
	vector<phone>::iterator ite;
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
		if (ite->id==ID && cmp(temp.company, ite->company))
		{
			cout<<"以下输入手机更新信息"<<endl;
			/*if (ite->selt)
			{
				phone *p=new phone();
				*p=*ite;
				p->Input();
				*ite=*p;
				return true;
			}*/
			ite->Input();
			return true;
		}
	}
	return false;
}

//卢文思
bool DeletePhone()//删除手机信息,删除失败返回false
{
	Father temp;
	temp.Input();
	OutputsFactAndType(temp);
	string ID;
	cout<<"请输入手机编号"<<endl;
	cin>>ID;
	bool flag=false;
	vector<phone>::iterator ite;
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
		if (ite->id==ID && cmp(temp.company, ite->company))
		{
			Father &v=*ite;
			if (type.find(v)==type.end())
			{
				cout<<"非法删除！"<<endl;
				break;
			}
			cout<<"你想要销售编号为："<<ID<<"的手机么（1(是)/2(否)）"<<endl;
			int c;
			InputInt(c);
			if (c==2)
			{
				return false;
			}
			flag=true;
			type[v]--;
			if (type[v]==0)
			{
				type.erase(type.find(v));
			}
			mobile.erase(ite);
			break;
		}
	}
	return flag;
}

//卢文思
bool AddLsit()//添加销售信息,无存货返回false
{
	Father temp;
	temp.Input();
	OutputsFactAndType(temp);
	cout<<"请输入销售手机编号"<<endl;
	string ID;
	cin>>ID;
	type[temp]--;
	if (type[temp]==0)
	{
		type.erase(type.find(temp));
	}
	vector<phone>::iterator ite;
	for(ite=mobile.begin();ite!=mobile.end();ite++)
	{
		if (ID==ite->id && cmp(temp.company, ite->company) && ite->selt == false)
		{
			cout<<"你想要销售编号为："<<ID<<"的手机么（1(是)/2(否)）"<<endl;
			int c;
			InputInt(c);
			if (c==2)
			{
				return true;
			}
			double price;
			cout<<"请输销售价格"<<endl;
			InputPrice(price);
			cout<<"请输销售时间"<<endl;
			InputTime(ite->outTime);
			ite->outPrice=price;
			ite->selt=true;
			selt.push_back(*ite);
			return true;
		}
	}
	return false;
};

//卢文思
bool DeleteList()//删除销售信息
{
	Father temp;
	temp.Input();
	OutputsFactAndType(temp);
	string ID;
	cout<<"请输入删除手机编号"<<endl;
	cin>>ID;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		if (ite->id==ID && cmp(temp.company, ite->company))
		{
			cout<<"你想要删除编号为："<<ID<<"的手机么（1(是)/2(否)）"<<endl;
			int c;
			InputInt(c);
			if (c==2)
			{
				return false;
			}
			temp=*ite;
			//selt.erase(ite);
			/*修改mobile中的数据*/
			//Begin
			vector<phone>::iterator ite2;
			for (ite2=mobile.begin();ite2!=mobile.end();ite2++)
			{
			    if (ite2->id == ite->id && ite2->company == ite->company && ite2->type == ite->type)
			    {
			        ite2->outPrice = 0.0;
			        ite2->outTime = 0;
			        ite2->selt = false;
			        selt.erase(ite);
			        break;
			    }
			}
			type[temp]++;
			//End
			return true;
		}
	}
	return false;
}

//沈伟强
int sellOutNum(int startTime,int endTime,string t)//在区间[startTime,endTime)，t类型的销售数
{
	int ans=0;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
        if(ite->type==t&& ite->outTime >=startTime && ite->outTime <= endTime)
            ans++;
	}
	return ans;
}

//沈伟强
double sellOutPro(int startTime,int endTime,string t)//在区间[startTime,endTime)，t厂商的利润
{
	double ans=0.0;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		if (ite->company==t)
		{
			ans+=ite->outPrice-ite->inPrice;
		}
	}
	return ans;
}

//沈伟强
double sellOutPro1(int startTime,int endTime,string t)////在区间[startTime,endTime)，t类型的利润
{
    double ans=0.0;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		if (ite->type==t&& ite->outTime >=startTime && ite->outTime <= endTime)
		{
			ans+=ite->outPrice-ite->inPrice;
		}
	}
	return ans;
}

//戚耿鑫
void sellOutFacNum(int start,int end)//某一段时间内，厂商的销售量
{
	map<string,int>temp;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		if (ite->outTime>=start&&ite->outTime<end)
		{
			temp[ite->company]++;
		}
	}
	cout<<setiosflags(ios::left);
	cout<<setw(10)<<"厂商"<<setw(10)<<"销售量"<<endl;
	map<string,int>::iterator ite2;
	for(ite2=temp.begin();ite2!=temp.end();ite2++)
	{
		cout<<setw(10)<<ite2->first<<setw(10)<<ite2->second<<endl;
	}
}

//戚耿鑫
void sellOutTypeNum(int start,int end)//某一段时间内的，型号销售信息
{
	map<string,int>temp;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		if (ite->outTime>=start&&ite->outTime<end)
		{
			temp[ite->type]++;
		}
	}
	cout<<setiosflags(ios::left);
	cout<<setw(10)<<"类型"<<setw(10)<<"销售量"<<endl;
	map<string,int>::iterator ite2;
	for(ite2=temp.begin();ite2!=temp.end();ite2++)
	{
		cout<<setw(10)<<ite2->first<<setw(10)<<ite2->second<<endl;
	}
}

//戚耿鑫
void sellOutFacProfit()//按厂商利润排名，从高到低
{
	map<string,double>temp;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		temp[ite->company]+=ite->outPrice-ite->inPrice;
	}
	map<string,double>::iterator ite2;
	vector<Profit>pro;
	for(ite2=temp.begin();ite2!=temp.end();ite2++)
	{
		pro.push_back(Profit(ite2->first,ite2->second));
	}
	sort(pro.begin(),pro.end());
	int len=pro.size();
	cout<<setiosflags(ios::left)<<setw(10)<<"厂商"<<setw(10)<<"利润"<<setw(5)<<"排名"<<endl;
	cout<<resetiosflags(ios::left);
	double avePro=0.0;
	for(int i=0;i<len;i++)
	{
		pro[i].Outputs(i+1);//输出名次
		avePro+=pro[i].pro;
	}
	cout<<"最大利润厂商为: "<<pro[0].name<<" 利润为："<<pro[0].pro<<endl;
	cout<<"最低利润厂商为："<<pro[len-1].name<<" 利润为: "<<pro[len-1].pro<<endl;
	cout<<"平均利润为："<<avePro/len<<endl;
}

//戚耿鑫
void sellOutTypeProfit()//按型号利润排名，从高到低
{
	map<string,double>temp;
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		temp[ite->type]+=ite->outPrice-ite->inPrice;
	}
	map<string,double>::iterator ite2;
	vector<Profit>pro;
	for(ite2=temp.begin();ite2!=temp.end();ite2++)
	{
		pro.push_back(Profit(ite2->first,ite2->second));
	}
	sort(pro.begin(),pro.end());
	int len=pro.size();
	cout<<setiosflags(ios::left)<<setw(10)<<"型号"<<setw(10)<<"利润"<<setw(5)<<"排名"<<endl;
	cout<<resetiosflags(ios::left);
	double avePro=0.0;
	for(int i=0;i<len;i++)
	{
		pro[i].Outputs(i+1);//输出名次
		avePro+=pro[i].pro;
	}
	cout<<"最大利润型号为: "<<pro[0].name<<" 利润为："<<pro[0].pro<<endl;
	cout<<"最低利润型号为："<<pro[len-1].name<<" 利润为: "<<pro[len-1].pro<<endl;
	cout<<"平均利润为："<<avePro/len<<endl;
}

//刘金玲
void QueryPhone()
{
	cout<<"请选择数字标号"<<endl;
	cout<<"	1,按价格"<<endl;
	cout<<"	2,按型号"<<endl;
	cout<<"	3,按厂商"<<endl;
	cout<<"	4,按库存数量"<<endl;
	cout<<"	其它，退出"<<endl;
	int chance,lNum,rNum;
	double lPrice,rPrice;
	string temp;
	vector<phone>::iterator ite;
	InputInt(chance);
	switch (chance)
	{
	case 1:
		{
			cout<<"请输入价格区间左端，区间左闭右开"<<endl;
			InputDouble(lPrice);
			cout<<"请输入价格区间右端，区间左闭右开"<<endl;
			InputDouble(rPrice);
			cout<<setiosflags(ios::left);
			cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(12)<<"进货时间"<<setw(10)<<"出售价"<<setw(12)<<"出售时间"<<endl;
			cout<<resetiosflags(ios::left);
			for(ite=mobile.begin();ite!=mobile.end();ite++)
			{
				if (ite->inPrice>=lPrice&&ite->inPrice<rPrice)
				{
					ite->Output();
				}
			}
			break;
		}
	case 2:
		{
			cout<<"请输入型号(...表示输出所有型号的手机)"<<endl;
			cin>>temp;
			cout<<setiosflags(ios::left);
			cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(12)<<"进货时间"<<setw(10)<<"出售价"<<setw(12)<<"出售时间"<<endl;
			cout<<resetiosflags(ios::left);
			for(ite=mobile.begin();ite!=mobile.end();ite++)
			{
				if (cmp(temp,ite->type)||temp=="..."||temp=="。。。")
				{
					ite->Output();
				}
			}
			break;
		}
	case 3:
		{
			cout<<"请输入厂商(...表示输出所有厂商的手机)"<<endl;
			cin>>temp;
			cout<<setiosflags(ios::left);
			cout<<setw(20)<<setfill(' ')<<"编号"<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(10)<<"进价"<<setw(12)<<"进货时间"<<setw(10)<<"出售价"<<setw(12)<<"出售时间"<<endl;
			cout<<resetiosflags(ios::left);
			for(ite=mobile.begin();ite!=mobile.end();ite++)
			{
				if (cmp(temp,ite->company)||temp=="..."||temp=="。。。")
				{
					ite->Output();
				}
			}
			break;
		}
	case 4:
		{
			cout<<"请输入库存数量左端,区间左闭右开"<<endl;
			InputInt(lNum);
			cout<<"请输入库存数量右端,区间左闭右开"<<endl;
			InputInt(rNum);
			cout<<setiosflags(ios::left);
			cout<<setfill(' ')<<setw(10)<<"厂商"<<setw(10)<<"型号"<<setw(11)<<"进价"<<setw(10)<<"库存"<<endl;
            map<Father,int>::iterator ite2;
			for(ite2=type.begin();ite2!=type.end();ite2++)
			{
				if (ite2->second>=lNum&&ite2->second<rNum)
				{
					cout<<setfill(' ')<<setw(10)<<ite2->first.company<<setw(10)<<ite2->first.type<<setw(10)<<ite2->first.inPrice<<setw(10)<<ite2->second<<endl;
				}
			}
			cout<<resetiosflags(ios::left);
			break;
		}
	default:
		break;
	}
}

//刘金玲
void QuerySelt()
{
	cout<<"请输入数字"<<endl;
	cout<<"	1,按厂商输出销售情况"<<endl;
	cout<<"	2,按类型输出销售新情况"<<endl;
	cout<<"====================================="<<endl;
	int chance;
	InputInt(chance);
	int s,e;
	cout<<"请输入开始时间,区间左闭右开"<<endl;
	InputTime(s);
	cout<<"请输入结束时间,区间左闭右开"<<endl;
	InputTime(e);
	if (chance==1)
	{
		sellOutFacNum(s,e);
	}
	else
	{
		sellOutTypeNum(s,e);
	}
}

//刘金玲
void QueryProfit()//询问利润
{
	cout<<"请输入数字"<<endl;
	cout<<"	1,按厂商输出利润排名情况"<<endl;
	cout<<"	2,按类型输出利润排名情况"<<endl;
	cout<<"====================================="<<endl;
	int chance;
	InputInt(chance);
	if (chance==1)
	{
		sellOutFacProfit();
	}
	else
	{
		sellOutTypeProfit();
	}
}

//张蕾
void ReadFile()
{
	ifstream inFile;
	inFile.open("mobile.txt",ios::in);
	if (inFile.fail())
	{
		cout<<"没有手机文件信息"<<endl;
	}
	else
	{
		phone temp;
		inFile>>temp;
		while (!inFile.eof())
		{
			mobile.push_back(temp);
			type[(Father &)temp]++;
			inFile>>temp;
		}
	}
	ifstream inFile2;
	inFile2.open("selt.txt",ios::in);
	if (inFile2.fail())
	{
		cout<<"没有销售文件信息"<<endl;
		return;
	}
	phone temp;
	inFile2>>temp;
	while (!inFile2.eof())
	{
		selt.push_back(temp);
		inFile2>>temp;
	}
}

//张蕾
void WriteFile()
{
	ofstream outFile;
	outFile.open("mobile.txt",ios::out);
	if (outFile.fail())
	{
		cout<<"文件读取失败，无法存入手机信息文件!"<<endl;
	}
	else
	{
		vector<phone>::iterator ite;
		for(ite=mobile.begin();ite!=mobile.end();ite++)
		{
			outFile<<*ite;
		}
	}
	ofstream outFile2;
	outFile2.open("selt.txt",ios::out);
	if (outFile2.fail())
	{
		cout<<"文件读取失败，无法存入销售信息文件"<<endl;
		return;
	}
	vector<phone>::iterator ite;
	for(ite=selt.begin();ite!=selt.end();ite++)
	{
		outFile2<<*ite;
	}
}

//张蕾
void LeftNum()
{
    vector<phone>::iterator ite;
    for (ite=mobile.begin();ite!=mobile.end();ite++)
    {
        if(ite->selt == false)
        {
            Father &v=*ite;
            type[v]++;
        }
    }
}

//张蕾
double AllProfit(int startTime, int endTime)
{
    double ans=0;
    vector<phone>::iterator ite;
    for(ite=selt.begin();ite!=selt.end();ite++)
    {
        if(ite->outTime >= startTime && ite->outTime <= endTime)
            ans+=ite->outPrice-ite->inPrice;
    }
    return ans;
}

//刘金玲
void SalesMenu()
{
    cout<<"销售情况统计，请选择数字："<<endl;
    cout<<" 1,某时间段某型号手机销售数量"<<endl;
    cout<<" 2,某时间段某型号手机销售利润"<<endl;
    cout<<" 3,某时间段销售总利润"<<endl;
    cout<<" 4,某时间段销售情况统计"<<endl;
    cout<<" 5,各类厂商，手机利润统计"<<endl;
    int s,e,chance;
    string temp;
    InputInt(chance);
    switch (chance)
    {
    case 1:
        {
            cout<<"请输入开始时间"<<endl;
            InputTime(s);
            cout<<"请输入结束时间"<<endl;
            InputTime(e);
            cout<<"请输入类型"<<endl;
            cin>>temp;
            int ans=sellOutNum(s,e,temp);
            if (!ans)
            {
                cout<<"无销售记录"<<endl;
                break;
            }
            cout<<(temp=="..."?"总共":temp)<<"手机的销售量为"<<ans<<endl;
            break;
        }
    case 2:
        {
            cout<<"请输入开始时间"<<endl;
            InputTime(s);
            cout<<"请输入结束时间"<<endl;
            InputTime(e);
            cout<<"请输入类型"<<endl;
            cin>>temp;
            cout<<(temp=="..."?"总共":temp)<<"手机的销售总利润为"<<sellOutPro1(s,e,temp)<<endl;
            break;
        }
    case 3:
        {
            cout<<"请输入开始时间"<<endl;
            InputTime(s);
            cout<<"请输入结束时间"<<endl;
            InputTime(e);
            cout<<"销售总利润为"<<AllProfit(s,e)<<endl;
            break;
        }
    case 4:
        {
            QuerySelt();
            break;
        }
    case 5:
        {
          	QueryProfit();
            break;
        }
    default:
        {

            return;
        }
    }
}

//刘金玲
void meun()
{
    ReadFile();
	LeftNum();
    cout<<"========Wellcom to Mobilephone Sales Management System==========="<<endl;
    while (true)
	{
		cout<<"1,添加手机信息"<<endl;
        cout<<"2,添加销售信息"<<endl;
        cout<<"3,删除信息"<<endl;
        cout<<"4,修改信息"<<endl;
        cout<<"5,手机信息查询"<<endl;
        cout<<"6,销售信息统计"<<endl;
        cout<<"0,退出系统"<<endl;
		cout<<"====================================="<<endl;
		int chance;
		InputInt(chance);
		switch(chance)
		{
        case 1:
            {
				AddPhone()?cout<<"手机信息添加成功":cout<<"手机信息添加失败";
				cout<<endl;
				break;
            }
        case 2:
            {
				if(!AddLsit())
				{
					cout<<"亲,没有您要找的手机哦,请查询后再来"<<endl;
				}
				else
				{
					cout<<"添加销售信息成功"<<endl;
				}
				break;
            }
        case 3:
            {
                cout<<"删除信息,请输入数字："<<endl;
                cout<<" 1,手机信息删除"<<endl;
                cout<<" 2,销售信息删除"<<endl;
                int i;
                InputInt(i);
                if (i==1)
                {
                    if(!DeletePhone())
                    {
                        cout<<"删除失败"<<endl;
                    }
                    else
                    {
                        cout<<"删除成功"<<endl;
                    }
                    break;
                }
                else if(i==2)
                {
                    DeleteList()?cout<<"删除销售信息成功":cout<<"删除销售信息失败";
                    cout<<endl;
                    break;
                }
            }
        case 4:
            {
				if(!ChangePhoneMessage())
				{
					cout<<"手机不存在"<<endl;
				}
				break;
            }
        case 5:
            {
				QueryPhone();
				break;
            }
        case 6:
            {
                SalesMenu();
                break;
            }
        case 0:
            {
                return;
            }
        default:
            {
                return;
            }
		}
	}
}


int main()
{
	meun();
	WriteFile();
	return 0;
}
