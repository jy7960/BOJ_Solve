#include <stdio.h>
#include <string.h>

int char2code(char c){
    if (c == '_') return 0;
    if (c == '.') return 27;
    return c - 'a' + 1;
}

char code2char(int x){
    if (x == 0) return '_';
    if (x == 27) return '.';
    return 'a' + x - 1;
}

int main(){
    int k;
    char cmd[100];

    while(1){
        scanf("%d", &k);
        if(k == 0) break;

        scanf("%s", cmd);
        int n = strlen(cmd);

        int ciphercode[100], plaincode[100];
        char ans[100];

        for(int i = 0; i < n; i++)
            ciphercode[i] = char2code(cmd[i]);

        for(int i = 0; i < n; i++){
            int pos = (k * i) % n;
            plaincode[pos] = (ciphercode[i] + i) % 28;
        }

        for(int i = 0; i < n; i++)
            ans[i] = code2char(plaincode[i]);

        ans[n] = '\0';
        printf("%s\n", ans);
    }
}