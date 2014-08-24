/*
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

bool valid[21],used[21];
char s[101];
int L,best,ans[20],aux[20],cont;

void search(int pos){
    if(cont > best) return;

    if(pos == 0){
        if(s[0] == 'W' && !valid[1]) return;
        for(int i = 1,j = 0;i <= 20;++i)
            if(used[i]) aux[j++] = i;

        bool take = false;

        if(cont < best) take = true;
        else{
            for(int i = 0;i < cont;++i){
                if(ans[i] < aux[i]) break;
                if(aux[i] < ans[i]) take = true;
            }
        }

        if(take){
            best = cont;
            for(int i = 0;i < cont;++i) ans[i] = aux[i];
        }

        return;
    }

    bool done = false;

    if(s[pos] == 'L') done = true;
    else{
        if(pos < 20 && used[pos + 1]) done = true;

        for(int j = pos-1;j >= 0 && pos-j <= 20;--j)
            if(used[pos-j] && s[j] == 'L') done = true;
    }

    if(done) search(pos - 1);
    else{
        if(pos < 20 && valid[pos + 1]){
            used[pos + 1] = true;
            ++cont;

            search(pos - 1);

            used[pos + 1] = false;
            --cont;
        }

        for(int i = 1;i <= 20 && pos >= i;++i){
            if(!used[i] && valid[i] && s[pos-i] == 'L'){
                used[i] = true;
                ++cont;

                search(pos - 1);

                used[i] = false;
                --cont;
            }
        }
    }

}

int main(){
    int T;

    scanf("%d",&T);

    for(int tc = 1;tc <= T;++tc)
        {
        scanf("%s",s);
        L = strlen(s);

        memset(valid,true,sizeof(valid));

        for(int i = 0;i < L && i < 20;++i)
            if(s[i] == 'L')
                valid[i + 1] = false;

        for(int i = 0;i < L;++i)
            if(s[i] == 'L')
                for(int j = i-1;j >= 0 && i-j <= 20;--j)
                    if(s[j] == 'L') valid[i - j] = false;
          for(int i = 0;i < 21;++i) cout<<valid[i];

        memset(used,false,sizeof(used));
        cont = 0;

        if(s[0] == 'W' && valid[1]){
            used[1] = true;
            ++cont;
        }

        best = 21;
        search(L-1);

        printf("Case %d:",tc);

        if(best == 0) printf(" %d",L + 1);
        else if(best < 21)
            for(int i = 0;i < best;++i) printf(" %d",ans[i]);

        printf("\n");
    }

    return 0;
}
*/

/*
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
int main()
{
    bool brick[21];
    int answer[20],count;
    int times;
    char s[100];
    int L;
    scanf("%d",&times);
    for(int fuji = 1 ; fuji <= times;fuji ++)
    {
        count = 0;
        memset(brick,true,sizeof(brick));
        memset(answer,0,sizeof(answer));
        scanf("%s",&s);
        L = strlen(s);
        for(int i = 0 ;i < L && i <20;i++ )
       {
          if(s[i] == 'L')
            brick[i + 1] = false;      //set L's position = false
       }
        for(int i = 0 ;i < L;i++ )
       {
           if(s[i] == 'L')
           {
               for(int j = i-1;j >= 0 && i-j <=20; --j)    //set L to L = false
                 if(s[j] == 'L')    brick[i - j ] = false;
           }
       }
       if(s[1] == 'W')
         answer[count] = 1,count++;
       for(int i = 0; i< L; i++)
       {
           if(s[i]== 'W')         //back pointer
           {
               for(int j = i;j >=0; j--)
               {

               }
           }
       }

       for(int i = 1; i<= 20 ;i++)
       {
           if(brick[i] == true)
                    cout<< i <<" ";
       }
    }

    return 0;
}
*/
//======================================
/*
#include <algorithm>
//#include <iostream>
#include <cstdio>
#include <cstring>
#define FORI(i,s,n) for(int i = s; i < n; ++i)
int ans[21], cnt[128], L[128], ls, test[21];
bool must[21], valid[21];
char desc[128];
int count_in_sol, len, marked_wins, min_card, needed;
//using namespace std;
void put(int x, int dd, int n){
    test[n] = x;

    for(int i = 0; i < ls && L[i] + x < len; ++i){
        marked_wins += !cnt[x + L[i]];
        cnt[x + L[i]] += dd;
        marked_wins -= !cnt[x + L[i]];  //if used,mark_win++
    }
}
void bt(int n, int idx){
  //  cout<<"yo";
  //  cout<<"MK"<<marked_wins<<endl;
  // cout<<"n"<<n<<endl;
  //   FORI(i, 0, n) cout<<" "<<test[i];
  //   cout<<endl;
  //   FORI(i, 0, len) cout<<cnt[i];
  //   cout<<endl;

    if(marked_wins == needed && n < min_card){
     //       cout<<"ha";
        min_card = n;
        FORI(i, 0, n) ans[i] = test[i];
 //       FORI(i, 0, n) cout<<ans[i] ;

        return;
    }

 //   cout<<"yi";
 //   FORI(i, 0, min_card) printf(" %d", ans[i]);
 //   cout<<endl;
    if(count_in_sol >= min_card) return;
    FORI(i, idx, 21) if(valid[i]){
        put(i, 1, n);
          if(n< min_card)
        bt(n + 1, i + 1);
        put(i, -1, n);
    }
}

int main(void){
    int j, t; scanf("%d", &t);
    for(int cnum = 1; t--; ++cnum){
        desc[0] = 'L';
        ls = 0;
        min_card = 21;
        scanf("%s", desc+1);
        for(len = 0; desc[len]; ++len){        //keep reading string until null
            if(desc[len] == 'L') L[ls++] = len;  //if L[] means 'L' position (L[0] = 0),ls indicate how many'L'
            cnt[len] = 0;                  //set all cnt = 0
        }
        needed = len - ls;   //need = string length - how many L
        // Mark which numbers are valid
        memset(must,false,sizeof(must));
         FORI(i, 1, 21){
            valid[i] = i < len;      //valid[1~string length] = true
            for(j = 0; valid[i] && j < ls && L[j] + i < len; ++j)
                valid[i] &= desc[i + L[j]] == 'W';
           if(valid[i]) put(i, 1, 0);                  //  L  can't goto L
        }
    //    cout<< "cnt";
    //    FORI(i, 0, len) cout<<i<<cnt[i]<<endl;

         // Find which numbers must be in the set(only exist one time)
        FORI(i, 1, 21) if(valid[i]) for(j = 0; j < ls && L[j] + i < len; ++j)
            must[i] |= cnt[i + L[j]] == 1;//L[0] = 0
    //    FORI(i, 1, 21) cout<<"must"<<i<<" "<<must[i]<<endl;
        FORI(i, 0, len) cnt[i] = 0;
        count_in_sol = marked_wins = 0;

        // Insert numbers that must be in the set
        FORI(i, 1, 21) if(must[i]) put(i, 1, count_in_sol++), valid[i] = false;
   //     cout<<"sol"<<count_in_sol;
        // Backtrack to find the remaining ones
        bt(count_in_sol, 1);
        // Show answer
        printf("Case %d:", cnum);
        if(needed == 0) ans[0] = len, min_card = 1;  //if all L
        std::sort(ans, ans + min_card);
        FORI(i, 0, min_card) printf(" %d", ans[i]);
        puts("");
    }
    return 0;
}
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define FORI(i,s,n) for(int i = s; i < n; ++i)
using namespace std;
int ans[21], cnt[128], L[128], ls, test[21];
bool must[21], valid[21];
char desc[128];
int count_in_sol, len, marked_wins, min_card, needed;
void put(int x, int dd, int n){
    test[n] = x;

    for(int i = 0; i < ls && L[i] + x < len; ++i){
        marked_wins += !cnt[x + L[i]];
        cnt[x + L[i]] += dd;
        marked_wins -= !cnt[x + L[i]];  //if used,mark_win++
    }
}
void bt(int n, int idx){
   cout<<"n"<<n<<endl;
     FORI(i, 0, n) cout<<" "<<test[i];
     cout<<endl;
     FORI(i, 0, len) cout<<cnt[i];
     cout<<endl;

    if(marked_wins == needed && n < min_card){
            cout<<"ha";
        min_card = n;
        FORI(i, 0, n) ans[i] = test[i];

        return;
    }
 if(count_in_sol >= min_card) return;
    FORI(i, idx, 21) if(valid[i]){
        put(i, 1, n);
          if(n< min_card-1)
        bt(n + 1, i + 1);
        put(i, -1, n);
    }
}

int main(void){
    int j, t; scanf("%d", &t);
    for(int cnum = 1; t--; ++cnum){
        desc[0] = 'L';
        ls = 0;
        min_card = 21;
        scanf("%s", desc+1);
        for(len = 0; desc[len]; ++len){
            if(desc[len] == 'L') L[ls++] = len;
            cnt[len] = 0;
        }
        needed = len - ls;
        memset(must,false,sizeof(must));
         FORI(i, 1, 21){
            valid[i] = i < len;
            for(j = 0; valid[i] && j < ls && L[j] + i < len; ++j)
                valid[i] &= desc[i + L[j]] == 'W';
           if(valid[i]) put(i, 1, 0);
        }



        FORI(i, 1, 21) if(valid[i]) for(j = 0; j < ls && L[j] + i < len; ++j)
            must[i] |= cnt[i + L[j]] == 1;
        FORI(i, 0, len) cnt[i] = 0;
        count_in_sol = marked_wins = 0;

        FORI(i, 1, 21) if(must[i]) put(i, 1, count_in_sol++), valid[i] = false;
        bt(count_in_sol, 1);
        printf("Case %d:", cnum);
        if(needed == 0) ans[0] = len, min_card = 1;
        std::sort(ans, ans + min_card);
        FORI(i, 0, min_card) printf(" %d", ans[i]);
        puts("");
    }
    return 0;
}
