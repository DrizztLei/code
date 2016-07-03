/*  朴素贝叶斯法 */

#include<iostream>
#include<string>
#include<fstream>
#include<istream>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<stdlib.h>

using namespace std;
class naiveBayes{
public: //载入数据并统计分量计数　　
    void loadData(){
        ifstream fin(dataFile.c_str());
        if(!fin){
            //cout<<"数据文件打开失败"<<endl;
            cout << "Error for file not found ." << endl;
            exit(1);
        }
        while(fin){
            string line;
            getline(fin,line);
            if(line.size()>1){
                stringstream sin(line);
                string s[2];
                int c;
                sin>>s[0]>>s[1]>>c;
                //cout<<s1<<" "<<s2<<" "<<c<<endl;
                dataSize++;
                if(ym.count(c)>0){
                    ym[c]++;
                }else{
                    ym[c]=1;
                }
                for(int i=0;i<2;i++){
                    if(feam.count(s[i])>0){
                        if(feam[s[i]].count(c)>0){
                            feam[s[i]][c]++;
                        }else{
                            feam[s[i]][c]=1;
                        }
                    }else{
                        map<int,int> mt;
                        mt[c]=1;
                        feam[s[i]]=mt;
                    }
                }
            }
        }
    }
//map模型
    void dispModel(){
        cout<<"训练数据总数"<<endl;
        cout<<dataSize<<endl;
        cout<<"分类统计计数"<<endl;
        for(map<int,int>::iterator mi=ym.begin();mi!=ym.end();mi++){
            cout<<mi->first<<" "<<mi->second<<endl;
        }
        cout<<"特征统计计数:"<<endl;
        for(map<string, map<int,int> >::iterator mi=feam.begin();mi!=feam.end();mi++){
            cout<<mi->first<<": ";
            for(map<int,int>::iterator ii=mi->second.begin();ii!=mi->second.end();ii++){
                cout<<"<"<<ii->first<<" "<<ii->second<<"> ";
            }
            cout<<endl;
        }
    }
//预测分类
    void predictive(){
        string x1,x2;
        cout<<"请输入测试数据（包括两维特征，第一维取值<1,2,3>；第二维取值<S,M,L>）"<<endl;
        string a1[]={"1","2","3"};
        string a2[]={"M","S","L"};
        set<string> a1set(a1,a1+3);
        set<string> a2set(a2,a2+3);
        while(cin>>x1>>x2){
            if(a1set.count(x1)>0&&a2set.count(x2)>0){
                double py1=(double(ym[-1])/dataSize)*(double(feam[x1][-1])/ym[-1])*(double(feam[x2][-1])/ym[-1]);
                double py2=(double(ym[1])/dataSize)*(double(feam[x1][1])/ym[1])*(double(feam[x2][1])/ym[1]);
                cout<<"y=-1的得分为"<<py1<<endl;
                cout<<"y=1的得分为"<<py2<<endl;
                cout<<"<"<<x1<<","<<x2<<">"<<"所属分类为:";
                if(py1>py2){
                    cout<<"-1";
                }else{
                    cout<<"1";
                }
                cout<<endl;
                cout<<endl;
                cout<<"继续测试(ctrl+Z结束)"<<endl;
            }else{
                cout<<"输入特征为：第一维取值<1,2,3>；第二维取值<S,M,L>，空格分隔。输入有误，请重新输入"<<endl;
            }
        }
    }

    naiveBayes(string df="data.txt"):dataFile(df),dataSize(0){

    }

private:
    string dataFile;
    int dataSize;
//分类->计数
    map<int,int> ym;
//分类->( 特征->计数 )
    map<string, map<int,int> >feam;
};

int main(){
    /*
      naiveBayes nb;
      nb.loadData();
      nb.dispModel();
      nb.predictive();
      system("pause");
    */
    float x = 2333333333333333;
    float y = 2222222222222222;
    //cout << - x *y*y*y*y*y*y*y << endl;
    float a = 1e-20;
    float b = 1e-20;
    for (int i = 0; i < 100; ++i)
    {
        a *= b;
    }
    return 0;
}
