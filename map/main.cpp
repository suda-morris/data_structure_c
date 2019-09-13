#include <iostream>

#include "chash.h"

using namespace std;

int main()
{
    cout << "CHash Test" << endl;
    struct hash_list *hlist = newHashList(3);
    const char *info[][10] = { { "tom", "tim", "mary", "kate", "henry", "jim",
            "henter", "jim", "jim", "tom"
        }, { "1234", "4444", "1004", "1234",
            "1334", "3234", "1134", "3234", "0000", "9999"
        }
    };
    for (int i = 0; i < 10; i++) {
        hlist->insert(hlist, info[0][i], info[1][i]);
    }
    hlist->print(hlist);
    cout << "查找kate: ";
    cout << hlist->search(hlist, "kate") << endl;
    cout << "删除kate后：" << endl;
    hlist->del(hlist, "kate");
    hlist->print(hlist);
    freeHashList(hlist);
    return 0;
}
