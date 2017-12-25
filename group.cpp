#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

static int n;
int connect[10];

void match(int x,vector<vector<int> >fm)
{
    if (x==n) return;
    int i,d(0),maxy,confx,secy,cxsy,max1,max2;
    for(i=0;i<n;++i)
        if(fm[x][i]>d)
        {
            maxy=i;
            d=fm[x][i];
        }
    if(connect[maxy]!=0)
    {
        confx=connect[maxy]-1;
        max1=0;
        max2=0;
        for(i=0;i<n;++i)
            if((connect[i]==0)&&(fm[confx][i]>max1))
            {
                max1=fm[confx][i];
                cxsy=i;
            }
        for(i=0;i<n;++i)
            if((connect[i]==0)&&(fm[x][i]>max1))
            {
                max2=fm[x][i];
                secy=i;
            }
        if(d+max1>=fm[confx][maxy]+max2)
        {
            connect[maxy]=x+1;
            connect[cxsy]=confx+1;
        }
        else connect[secy]=x+1;
    }
    else connect[maxy]=x+1;
    match(x+1,fm);
}

int main()
{
    int i,j,sat(0);
    fstream filein,fileout;
    filein.open("group.txt");
    fileout.open("answer.txt");
    filein>>n;
    vector<vector<int> >mf(n),fm(n);
    for(i=0;i<n;++i)
    {
        mf[i].resize(n);
        fm[i].resize(n);
    }
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            filein>>mf[i][j];
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        {
            filein>>fm[i][j];
            fm[i][j]+=mf[j][i];
        }
    /*for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        fileout<<fm[i][j]<<' ';
        fileout<<endl;
    }*/
    memset(connect,0,sizeof(connect));
    match(0,fm);
    for(i=0;i<n;++i)
    {
        fileout<<"female "<<i+1<<"->"<<"male "<<connect[i]<<endl;
        sat+=fm[connect[i]-1][i];
    }
    fileout<<sat<<endl;
    filein.close();
    fileout.close();
    for(i=0;i<n;++i)
    {
        vector<int>().swap(mf[i]);
        vector<int>().swap(fm[i]);
    }
    return 0;
}
