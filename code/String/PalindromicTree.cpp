// 迴文樹的每個節點代表一個迴文串
// len[i] 表示第 i 個節點的長度
// fail[i] 表示第 i 個節點的失配指針
// fail[i] 是 i 的次長迴文後綴
// dep[i] 表示第 i 個節點有幾個迴文後綴
// nxt[i][c] 表示在節點 i 兩邊加上字元 c 得到的點
// nxt 邊構成了兩顆分別以 odd 和 even 為根的向下的樹
// len[odd] = -1, len[even] = 0
// fail 邊構成了一顆以 odd 為根的向上的樹
// fail[even] = odd
// 0 ~ node size 是一個好的 dp 順序
// walk 是構建迴文樹時 lst 經過的節點
struct PAM {
    vector<array<int, 26>> nxt;
    vector<int> fail, len, dep, walk;
    int odd, even, lst;
    string S;
    int newNode(int l) {
        fail.push_back(0);
        nxt.push_back({});
        len.push_back(l);
        dep.push_back(0);
        return fail.size() - 1;
    }
    PAM() : odd(newNode(-1)), even(newNode(0)) {
        lst = fail[even] = odd;
    } /* SPLIT-HASH */
    void reserve(int l) {
        fail.reserve(l + 2);
        len.reserve(l + 2);
        nxt.reserve(l + 2);
        dep.reserve(l + 2);
        walk.reserve(l);
    }
    void build(string_view s) {
        reserve(s.size());
        for (char c : s) {
            walk.push_back(add(c));
        }
    } /* SPLIT-HASH */
    int up(int p) {
        while (S.rbegin()[len[p] + 1] != S.back()) {
            p = fail[p];
        }
        return p;
    }
    int add(char c) {
        S += c;	
        lst = up(lst);
        c -= 'a';
        if (!nxt[lst][c]) {
            nxt[lst][c] = newNode(len[lst] + 2);
        }
        int p = nxt[lst][c];
        fail[p] = (lst == odd ? even : nxt[up(fail[lst])][c]);
        lst = p;
        dep[lst] = dep[fail[lst]] + 1;
        return lst;
    }
};
