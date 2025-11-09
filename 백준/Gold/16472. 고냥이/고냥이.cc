#include <iostream>

using namespace std;

int main()
{
    int n;
    string s;
    cin>>n>>s;
    
    int len=s.length();
    
    int ans=1;
    
    int num[26]={0};
    num[s[0]-'a']++;
    int type=1;
    
    int a=0, b=0;
    while(b<len-1)
    {
        b++;
        if(++num[s[b]-'a']==1) type++;
        
        while(type>n && a<b)
        {
            if(--num[s[a++]-'a']==0) type--;
        }
        
        ans=max(ans, b-a+1);
    }
    
    cout<<ans;

    return 0;
}